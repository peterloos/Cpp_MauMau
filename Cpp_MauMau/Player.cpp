#include <iostream>
using namespace std;

#include "CardColor.h"
#include "CardPicture.h"
#include "Card.h"
#include "CardSet.h"
#include "CardDeck.h"
#include "Player.h"
#include "MauMaster.h"

Player::Player()
{
    m_name = (char*) 0;
    m_isPlaying = true;
    m_playing = (CardDeck*) 0; 
    m_drawing = (CardDeck*) 0; 
}

Player::~Player()
{
    delete m_name;
}

// properties
void Player::SetPlayingDeck(CardDeck* playing)
{
    m_playing = playing;
}

void Player::SetDrawingDeck(CardDeck* drawing)
{
    m_drawing = drawing;
}

int Player::GetNumberCards()
{
    return m_hand.Size();
}

void Player::IsPlaying(bool isPlaying)
{
    m_isPlaying = isPlaying;
}

bool Player::IsPlaying()
{
    return m_isPlaying;
}

void Player::GetName(char name[], int len)
{
    strcpy_s(name, len, m_name);
}

void Player::SetName(const char* name)
{
    int len = 0;
    while (name[len] != '\0')
        len++;

    m_name = new char[len + 1];
    strcpy_s(m_name, len + 1, name);
}

// public interface
CardColor Player::ChooseAColor()
{
    if (m_hand.Size() > 0)
    {
        // players has (still) some cards in his hand
        return m_hand[0].GetColor();
    }
    else
    {
        // players has no more cards, chooses arbitrary card color
        return CardColor::Herz;
    }
}

void Player::DrawCards(int number)
{
    for (int i = 0; i < number; i++)
    {
        Card card = DrawCard();
        m_hand.Add(card);

        MauMaster::Log(">   %s draws %s %s from drawing deck!", 
            m_name, card.GetColorAsString(), card.GetPictureAsString());
    }
}

bool Player::CounterSeven(int numCardsToDraw)
{
    if (HasSeven())
    {
        // players holds '7' in his hand
        MauMaster::Log(">   %s counters '7' with another '7' !", m_name);
        PlaySeven();
        return true;
    }
    else
    {
        MauMaster::Log(">   %s cannot respond to '7', draws %d card(s)!", 
            m_name, numCardsToDraw);
        DrawCards(numCardsToDraw);
        return false;
    }
}

bool Player::PlayCard(CardColor requestedColor, CardPicture requestedPicture)
{
    for (int i = 0; i < m_hand.Size(); i++)
    {
        Card card = m_hand[i];
        if (card.GetColor() == requestedColor || card.GetPicture() == requestedPicture)
        {
            m_hand.Remove(i);
            m_playing->Push(card);
            MauMaster::Log(">   %s plays %s %s", 
                m_name, card.GetColorAsString(), card.GetPictureAsString());
            PrintMauMauIf();
            return true;
        }
    }

    // 'Bube' maybe played upon every card!
    for (int i = 0; i < m_hand.Size(); i++)
    {
        Card card = m_hand[i];
        if (card.GetPicture() == CardPicture::Bube)
        {
            m_hand.Remove(i);
            m_playing->Push(card);
            MauMaster::Log(">   %s plays %s %s", 
                m_name, card.GetColorAsString(), card.GetPictureAsString());
            PrintMauMauIf();
            return true;
        }
    }

    return false;
}

bool Player::PlayCard(CardColor requestedColor)
{
    for (int i = 0; i < m_hand.Size(); i++)
    {
        Card card = m_hand[i];

        // 'Bube' upon 'Bube' not allowed ("Bube auf Bube" stinkt)
        if (card.GetPicture() == CardPicture::Bube)
            continue;

        if (card.GetColor() == requestedColor)
        {
            m_hand.Remove(i);
            m_playing->Push(card);
            MauMaster::Log(">   %s plays %s %s", 
                m_name, card.GetColorAsString(), card.GetPictureAsString());
            PrintMauMauIf();
            return true;
        }
    }

    return false;
}

void Player::PlayArbitraryCard()
{
    int lastIndex = m_hand.Size() - 1;
    Card card = m_hand[lastIndex];
    m_hand.Remove(lastIndex);
    m_playing->Push(card);
    MauMaster::Log(">   %s plays %s %s", 
        m_name, card.GetColorAsString(), card.GetPictureAsString());
    PrintMauMauIf();
}

void Player::ReleaseAllCards()
{
    m_hand.Clear();
}

// private helper methods
Card Player::DrawCard()
{
    // turn over playing deck to serve as new drawing deck
    if (m_drawing->Size() == 0)
    {
        MauMaster::Log (">   turn over playing deck to serve as new drawing deck");

        // save topmost card of playing stack
        Card topmostPlayingCard = m_playing->Pop();

        // copy rest of playing deck to drawing deck
        while (!m_playing->IsEmpty())
        {
            Card tmp = m_playing->Pop();
            m_drawing->Push(tmp);
        }

        // shuffle drawing stack
        m_drawing->Shuffle();

        // restore topmost card of playing stack
        m_playing->Push(topmostPlayingCard);
    }

    return m_drawing->Pop();
}

bool Player::HasSeven()
{
    for (int i = 0; i < m_hand.Size(); i++)
    {
        Card c = m_hand[i];
        if (c.GetPicture() == CardPicture::Sieben)
            return true;
    }

    return false;
}

void Player::PlaySeven()
{
    for (int i = 0; i < m_hand.Size(); i++)
    {
        Card card = m_hand[i];
        if (card.GetPicture() == CardPicture::Sieben)
        {
            m_hand.Remove(i);
            m_playing->Push(card);

            MauMaster::Log(">   %s drops %s %s onto deck!", 
                m_name, card.GetColorAsString(), card.GetPictureAsString());

            PrintMauMauIf();
            return;
        }
    }

    throw "ERROR (PlaySeven): Should never be reached";
}

void Player::PrintMauMauIf()
{
    if (m_hand.Size() == 1)
    {
        MauMaster::Log("==> %s says 'Mau'", m_name);
    }
    else if (m_hand.Size() == 0)
    {
        MauMaster::Log("##> %s says 'MAU MAU !!!'", m_name);
    }
}

// output
ostream& operator<< (ostream& os, const Player& player)
{
    os << player.m_name << "[" << (player.m_isPlaying ? "X" : "-") << "]";
    if (player.m_hand.Size() > 0)
    {
        os << ": ";
        os << player.m_hand;
    }

    return os;
}
