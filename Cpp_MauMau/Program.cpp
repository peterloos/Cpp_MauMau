#include <limits>
#include <iostream>
using namespace std;

#include "CardColor.h"
#include "CardPicture.h"
#include "Card.h"
#include "CardDeck.h"
#include "CardSet.h"
#include "Player.h"
#include "MauMaster.h"

void TestUnit_01_Cards()
{
    Card c1(CardColor::Kreuz, CardPicture::Neun);
    Card c2(CardColor::Pik, CardPicture::König);

    cout << c1 << endl;
    cout << c2 << endl;

    cout << "Farbe: " << c1.GetColorAsString() << endl;
    cout << "Bild: " << c1.GetPictureAsString() << endl;

    if (c1 == c2)
        cout << "Die Karten sind gleich" << endl;
    else
        cout << "Die Karten sind verschieden" << endl;
}

void TestUnit_02_CardDeck()
{
    Card c1(CardColor::Kreuz, CardPicture::Neun);
    Card c2(CardColor::Pik, CardPicture::König);
    Card c3(CardColor::Herz, CardPicture::Sieben);

    CardDeck deck;
    deck.Push(c1);
    deck.Push(c2);
    deck.Push(c3);

    cout << deck << endl;
}

void TestUnit_03_CardDeck()
{
    // test frame for CardDeck objects
    CardDeck deck;
    deck.SetRandomSeed(1);
    deck.Fill();
    cout << deck << endl;
    deck.Shuffle();
    cout << deck << endl;
}

void TestUnit_04_CardSet()
{
    // test frame for a single CardSet object
    Card card1 (CardColor::Kreuz, CardPicture::Neun);
    Card card2 (CardColor::Pik, CardPicture::König);
    Card card3 (CardColor::Herz, CardPicture::Sieben);

    CardSet set;
    set.Add(card1);
    set.Add(card2);
    set.Add(card3);

    for (int i = 0; i < set.Size(); i++)
    {
        cout << "Karte " << i << ": " << set[i] << endl;
    }

    cout << "Karten auf der Hand:" << endl << set << endl;
    set.Remove(1);
    cout << "Karten auf der Hand:" << endl << set << endl;
}

void TestUnit_10_PlayTheGame()
{
    MauMaster::PrintVersion();
    const char* names[] = { "Hans", "Sepp", "Ulli" };
    MauMaster mm (names, 3);
    mm.Init(111);
    mm.Play();
}

void TestUnit_11_SingleTestMauMaster()
{
    MauMaster::PrintVersion();
    const char* names[] = { "Hans", "Sepp", "Ulli" };
    MauMaster mm(names, 3);
    int randomSeed = 71;
    mm.Init(randomSeed);
    mm.Play();
}

void TestUnit_12_StressTestMauMaster()
{
    MauMaster::PrintVersion();
    const char* names[] = { "Hans", "Sepp", "Ulli" };
    MauMaster mm(names, 3);

    int minRounds = numeric_limits<int>::max();
    int minRoundsIndex = -1;
    int maxRounds = -1;
    int maxRoundsIndex = -1;

    for (int i = 1; i < 1000; i++)
    {
        mm.Init(i);
        mm.Play();

        if (mm.GetRounds() < minRounds)
        {
            minRounds = mm.GetRounds();
            minRoundsIndex = i;
        }

        if (mm.GetRounds() > maxRounds)
        {
            maxRounds = mm.GetRounds();
            maxRoundsIndex = i;
        }

        cout << "Game at " << i << ": " << mm.GetRounds() << endl;
    }

    cout << "Minumum number of rounds: " << minRounds << " [Index " << minRoundsIndex << "]" << endl;
    cout << "Maximum number of rounds: " << maxRounds << " [Index " << maxRoundsIndex << "]" << endl;
}

int main()
{
    TestUnit_01_Cards();
    TestUnit_02_CardDeck();
    TestUnit_03_CardDeck();
    TestUnit_04_CardSet();
    TestUnit_10_PlayTheGame();
    TestUnit_11_SingleTestMauMaster();
    // TestUnit_12_StressTestMauMaster();

    return 0;
}

