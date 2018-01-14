#include <iostream>
using namespace std;

#include "CardColor.h"
#include "CardPicture.h"
#include "Card.h"
#include "CardSet.h"

CardSet::CardSet()
{
    m_top = 0;
}

int CardSet::Size() const
{
    return m_top;
}

void CardSet::Add(Card c)
{
    m_set[m_top] = c;
    m_top++;
}

void CardSet::Remove(int index)
{
    if (index < 0 || index >= m_top)
    {
        throw "Wrong Index";
    }

    m_set[index] = m_set[m_top - 1];
    m_top--;
}

void CardSet::Clear()
{
    m_top = 0;
}

Card CardSet::operator[] (int index) const
{
    return m_set[index];
}

// output
ostream& operator<< (ostream& os, const CardSet& set)
{
    for (int i = 0; i < set.Size(); i++)
    {
        os << set[i];
        if (i < set.Size() - 1)
            os << ", ";
    }

    return os;
}
