#include <iostream>
using namespace std;

#include "CardColor.h"
#include "CardPicture.h"
#include "Card.h"

// note: list of strings must match enumeration type CardColor !
const char* Card::CardColorDisplay[] =
{
    "Empty", "Karo", "Herz", "Pik", "Kreuz"
};

// note: list of strings must match enumeration type CardPicture !
const char* Card::CardPictureDisplay[] = 
{ 
    "Empty", "Sieben", "Acht", "Neun", "Zehn", "Bube", "Dame", "Koenig", "Ass"
};

// c'tors
Card::Card()
{
    m_color = CardColor::Empty;
    m_picture = CardPicture::Empty;
    m_empty = true;
}

Card::Card(const Card& card)
{
    m_color = card.m_color;
    m_picture = card.m_picture;
    m_empty = card.m_empty;
}

Card::Card(CardColor color, CardPicture picture)
{
    m_color = color;
    m_picture = picture;
    m_empty = false;
}

// operators
bool operator== (const Card& c1, const Card& c2)
{
    return c1.m_color == c2.m_color && c1.m_picture == c2.m_picture;
}

bool operator!= (const Card& c1, const Card& c2)
{
    return !(c1 == c2);
}

// output
ostream& operator<< (ostream& os, const Card& card)
{
    const char* colorDisplay = Card::CardColorDisplay[(int) card.m_color];
    const char* pictureDisplay = Card::CardPictureDisplay[(int) card.m_picture];
    os << colorDisplay << ' ' << pictureDisplay;
    return os;
}
