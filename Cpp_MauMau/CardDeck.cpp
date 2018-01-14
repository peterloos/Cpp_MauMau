#include <time.h>
#include <iostream>
using namespace std;

#include "CardColor.h"
#include "CardPicture.h"
#include "Card.h"
#include "CardDeck.h"

// used for all players
CardDeck::CardDeck()
{
    m_top = 0;

    // initialize random number generator "by random"
    ::srand((unsigned int) time(NULL));
}

void CardDeck::Push(Card c)
{
    m_deck[m_top] = c;
    m_top++;
}

Card CardDeck::Pop()
{
    m_top--;
    return m_deck[m_top];
}

bool CardDeck::IsEmpty() const
{
    return m_top == 0;
}

int CardDeck::Size() const
{
    return m_top;
}

void CardDeck::SetRandomSeed()
{
    m_randomSeed = CardDeck::RandomSeed;
    ::srand(m_randomSeed);
}

void CardDeck::SetRandomSeed(int seed)
{
    m_randomSeed = seed;
    ::srand(m_randomSeed);
}

Card CardDeck::TopOfDeck()
{
    if (m_top == 0)
        throw "ERROR (PlaySeven): Should never be reached";

    int index = m_top - 1;
    return m_deck[index];
}

void CardDeck::Fill()
{
    // fill stack with all available cards
    Card c01(CardColor::Karo, CardPicture::Sieben);
    Card c02(CardColor::Karo, CardPicture::Acht);
    Card c03(CardColor::Karo, CardPicture::Neun);
    Card c04(CardColor::Karo, CardPicture::Zehn);
    Card c05(CardColor::Karo, CardPicture::Bube);
    Card c06(CardColor::Karo, CardPicture::Dame);
    Card c07(CardColor::Karo, CardPicture::König);
    Card c08(CardColor::Karo, CardPicture::As);

    Card c09(CardColor::Herz, CardPicture::Sieben);
    Card c10(CardColor::Herz, CardPicture::Acht);
    Card c11(CardColor::Herz, CardPicture::Neun);
    Card c12(CardColor::Herz, CardPicture::Zehn);
    Card c13(CardColor::Herz, CardPicture::Bube);
    Card c14(CardColor::Herz, CardPicture::Dame);
    Card c15(CardColor::Herz, CardPicture::König);
    Card c16(CardColor::Herz, CardPicture::As);

    Card c17(CardColor::Pik, CardPicture::Sieben);
    Card c18(CardColor::Pik, CardPicture::Acht);
    Card c19(CardColor::Pik, CardPicture::Neun);
    Card c20(CardColor::Pik, CardPicture::Zehn);
    Card c21(CardColor::Pik, CardPicture::Bube);
    Card c22(CardColor::Pik, CardPicture::Dame);
    Card c23(CardColor::Pik, CardPicture::König);
    Card c24(CardColor::Pik, CardPicture::As);

    Card c25(CardColor::Kreuz, CardPicture::Sieben);
    Card c26(CardColor::Kreuz, CardPicture::Acht);
    Card c27(CardColor::Kreuz, CardPicture::Neun);
    Card c28(CardColor::Kreuz, CardPicture::Zehn);
    Card c29(CardColor::Kreuz, CardPicture::Bube);
    Card c30(CardColor::Kreuz, CardPicture::Dame);
    Card c31(CardColor::Kreuz, CardPicture::König);
    Card c32(CardColor::Kreuz, CardPicture::As);

    Push(c01);
    Push(c02);
    Push(c03);
    Push(c04);
    Push(c05);
    Push(c06);
    Push(c07);
    Push(c08);
    Push(c09);
    Push(c10);
    Push(c11);
    Push(c12);
    Push(c13);
    Push(c14);
    Push(c15);
    Push(c16);
    Push(c17);
    Push(c18);
    Push(c19);
    Push(c20);
    Push(c21);
    Push(c22);
    Push(c23);
    Push(c24);
    Push(c25);
    Push(c26);
    Push(c27);
    Push(c28);
    Push(c29);
    Push(c30);
    Push(c31);
    Push(c32);
}

void CardDeck::Shuffle()
{
    // now mix stack per random
    int repetitionCount = 30;
    while (repetitionCount--)
    {
        int x1 = rand() % m_top;
        int x2 = rand() % m_top;

        Card temp = m_deck[x1];
        m_deck[x1] = m_deck[x2];
        m_deck[x2] = temp;
    }
}

void CardDeck::Clear()
{
    m_top = 0;
}

// output
ostream& operator<< (ostream& os, const CardDeck& deck)
{
    for (int i = 0; i < deck.m_top; i++)
        os << (i+1) << ": " << deck.m_deck[i] << endl;

    return os;
}
