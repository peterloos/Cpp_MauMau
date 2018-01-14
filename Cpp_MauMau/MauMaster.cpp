#include <string>
#include <conio.h>
#include <time.h>
#include <iostream>
using namespace std;

#include "CardColor.h"
#include "CardPicture.h"
#include "Card.h"
#include "CardSet.h"
#include "CardDeck.h"
#include "Player.h"
#include "MauMaster.h"

// initialization of static class members
const char* MauMaster::Version = "    Simple Mau-Mau Cards Game (Version 1.00)";
const int MauMaster::MaxCardsAtBegin = 5;  // used for testing - should be 5 regularly

// c'tor
MauMaster::MauMaster(const char* names[], int len)
{
    // create array of players
    m_numPlayers = len;
    m_players = new Player[m_numPlayers];
    for (int i = 0; i < m_numPlayers; i++)
    {
        m_players[i].SetName(names[i]);
        m_players[i].SetPlayingDeck(&m_playing);
        m_players[i].SetDrawingDeck(&m_drawing);
        m_players[i].IsPlaying(true);
    }
}

MauMaster::~MauMaster()
{
    delete[] m_players;
}

// properties
int MauMaster::GetRounds()
{
    return m_rounds;
}

// public interface
void MauMaster::Init(int randomSeed)
{
    // create new random generator (prefer unique results to make testing more easier)
    m_playing.SetRandomSeed(randomSeed);
    m_drawing.SetRandomSeed(randomSeed);

    // intialize card decks
    m_playing.Clear();
    m_drawing.Clear();
    m_drawing.Fill();       // fill deck with all available cards ...
    m_drawing.Shuffle();    // ... and mix them ...

    for (int i = 0; i < m_numPlayers; i++)
    {
        m_players[i].IsPlaying(true);
        m_players[i].ReleaseAllCards();
        m_players[i].DrawCards(MaxCardsAtBegin);  // draw initial amount of cards
    }

    m_rounds = 0;

    // print summary of players at begin of game
#if defined (VERBOSE)
    cout << "------------------------------------------------------------------" << endl;
    for (int i = 0; i < m_numPlayers; i++)
    {
        cout << "Player " << (i + 1) << ": " << m_players[i] << endl;
    }
#endif
}

void MauMaster::Play()
{
    // controlling game variables
    int numberOfCardsToDraw = 2;
    int activePlayers = m_numPlayers;
    int currentPlayer = 0;
    CardColor requestedCardColor = CardColor::Empty;

    // controlling special games state 'Bube'
    bool bubeIsActive = false;

    // controlling special games states '8'
    bool eightIsActive = false;
    bool skipNextPlayer = false;

    // uncover first card
    Card firstCard = m_drawing.Pop();
    m_playing.Push(firstCard);

    // and now lets play an aweful game
    while (activePlayers > 1)
    {
        Card topMostCard = m_playing.TopOfDeck();
        LogGameStatusDebug(topMostCard, currentPlayer); 

        m_rounds ++;  // count rounds of this game

        // handle special cards
        if (topMostCard.GetPicture() == CardPicture::Sieben)
        {
            // '7' is on top of card deck
            MauMaster::Log(">   '7' is on top of deck");    
            if (m_players[currentPlayer].CounterSeven(numberOfCardsToDraw))
            {
                numberOfCardsToDraw = IncrementNumberOfCardsToDraw(numberOfCardsToDraw);
            }
            else
            {
                numberOfCardsToDraw = 2;  // no more '7' on top of card deck

                // player may now draw a card, if he can
                m_players[currentPlayer].PlayArbitraryCard();

                Card peek = m_playing.TopOfDeck();

                if (peek.GetPicture() == CardPicture::Bube)
                {
                    requestedCardColor = m_players[currentPlayer].ChooseAColor();

                    bubeIsActive = true; 

                    char name[32];
                    m_players[currentPlayer].GetName(name, 32);
                    MauMaster::Log(">   %s has choosen color %s", name, requestedCardColor);
                }
                else if (peek.GetPicture() == CardPicture::Acht)
                {
                    MauMaster::Log(">   '8' is on top of deck - skip next player");  

                    eightIsActive = true;
                    skipNextPlayer = true;
                }
            }
        }
        else if (topMostCard.GetPicture() == CardPicture::Acht && !eightIsActive)
        {
            MauMaster::Log(">   '8' is on top of deck - skip next player");

            eightIsActive = true;
            skipNextPlayer = false;
        }
        else if (topMostCard.GetPicture() == CardPicture::Bube && !bubeIsActive)
        {
            requestedCardColor = m_players[currentPlayer].ChooseAColor();

            bubeIsActive = true;   

            char name[32];
            m_players[currentPlayer].GetName(name, 32);
            MauMaster::Log(">   %s has choosen color %s", name, requestedCardColor);
        }
        else
        {
            // regular mode -- no special cards --
            // current player plays according to "standard" rules
            bool success;
            if (!bubeIsActive)
            {
                // picture or color can be played
                success =
                    m_players[currentPlayer].PlayCard(topMostCard.GetColor(), topMostCard.GetPicture());
            }
            else
            {
                // a color has been choosen right before, only color must match
                success =
                    m_players[currentPlayer].PlayCard(requestedCardColor);
            }

            if (success)
            {
                // reset special state(s), if any 
                eightIsActive = false;
                bubeIsActive = false;

                Card peek = m_playing.TopOfDeck();
                if (peek.GetPicture() == CardPicture::Bube)
                {
                    requestedCardColor = m_players[currentPlayer].ChooseAColor();

                    bubeIsActive = true;

                    char name[32];
                    m_players[currentPlayer].GetName(name, 32);
                    MauMaster::Log(">   %s has choosen color %s", name, requestedCardColor);
                }
                else if (peek.GetPicture() == CardPicture::Acht)
                {
                    MauMaster::Log(">   '8' is on top of deck - skip next player");   

                    eightIsActive = true;
                    skipNextPlayer = true;
                }
            }
            else
            {
                char name[32];
                m_players[currentPlayer].GetName(name, 32);
                MauMaster::Log(">   %s cannot serve, draws %d card(s)", name, 1);

                m_players[currentPlayer].DrawCards(1);
            }
        }

        // test, if current player quits
        if (m_players[currentPlayer].GetNumberCards() == 0)
        {
            char name[32];
            m_players[currentPlayer].GetName(name, 32);
            MauMaster::Log(">   %s quits game !", name);

            m_players[currentPlayer].IsPlaying(false);
            activePlayers--;
        }

        // switch to next player
        currentPlayer = NextPlayer(currentPlayer);

        // '8' has just been played, next player pauses
        if (skipNextPlayer == true)
        {
            // skip next player
            currentPlayer = NextPlayer(currentPlayer);

            skipNextPlayer = false;
        }
    }

    // last player loses the game
    char name[32];
    m_players[currentPlayer].GetName(name, 32);
    LogFinalGameStatus(name);
}

// private helper methods
int MauMaster::NextPlayer(int currentPlayer)
{
    // move to next player
    currentPlayer++;
    if (currentPlayer == m_numPlayers)
        currentPlayer = 0;

    // search next array slot with still active player
    while (!m_players[currentPlayer].IsPlaying())
    {
        currentPlayer++;
        if (currentPlayer == m_numPlayers)
            currentPlayer = 0;
    }

    return currentPlayer;
}

int MauMaster::IncrementNumberOfCardsToDraw(int numberOfCardsToDraw)
{
    numberOfCardsToDraw += 2;
    return numberOfCardsToDraw;
}

void MauMaster::LogFinalGameStatus(char* name)
{
#if defined (VERBOSE)
    cout << name << " has lost --- Game over [" << m_rounds << " rounds]" << endl;
#endif
}

void MauMaster::LogGameStatusDebug(Card topMostCard, int currentPlayer)
{
#if defined (VERBOSE)
    cout << "------------------------------------------------------------------" << endl;
    cout << "Topmost card: " << topMostCard << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int i = 0; i < m_numPlayers; i++)
    {
        const char* prefix = (i == currentPlayer) ? "-->" : "   ";
        cout << prefix << " " << m_players[i] << endl;
    }

    cout << "------------------------------------------------------------------" << endl;
#endif

#if defined (SINGLE_STEP)  
    _getch();   // just for testing
#endif
}

void MauMaster::PrintVersion()
{
    cout << "------------------------------------------------------------------" << endl;
    cout << MauMaster::Version << endl;
    cout << "------------------------------------------------------------------" << endl;
}

// logging methods
void MauMaster::Log(char const* message)
{
#if defined (VERBOSE)
    cout << message << endl;
#endif
}

void MauMaster::Log(char const* message, char const* string)
{
#if defined (VERBOSE)
    char buf[128];
    snprintf(buf, sizeof(buf), message, string);
    cout << buf << endl;
#endif
}

void MauMaster::Log(char const* message, char const* string, int n)
{
#if defined (VERBOSE)
    char buf[128];
    snprintf(buf, sizeof(buf), message, string, n);
    cout << buf << endl;
#endif
}

void MauMaster::Log(char const* message, char const* string, CardColor col)
{
#if defined (VERBOSE)
    const char* colorDisplay[] =
    {
        "Empty", "Karo", "Herz", "Pik", "Kreuz"
    };

    char buf[128];
    snprintf(buf, sizeof(buf), message, string, colorDisplay[(int)col]);
    cout << buf << endl;
#endif
}

void MauMaster::Log(char const* message, char const* string1, char const* string2, char const* string3)
{
#if defined (VERBOSE)
    char buf[128];
    snprintf(buf, sizeof(buf), message, string1, string2, string3);
    cout << buf << endl;
#endif
}