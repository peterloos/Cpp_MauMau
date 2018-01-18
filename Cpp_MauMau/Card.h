class Card
{
private:
    CardColor    m_color;
    CardPicture  m_picture;

public:
    static const char* CardColorDisplay[];
    static const char* CardPictureDisplay[];

public:
    // c'tors
    Card();
    Card(CardColor, CardPicture);

    // getter
    CardColor GetColor() { return m_color; }
    CardPicture GetPicture() { return m_picture; }
    const char* GetColorAsString() { return CardColorDisplay[(int) m_color]; }
    const char*  GetPictureAsString() { return CardPictureDisplay[(int) m_picture]; }

    // operators
    friend bool operator== (const Card&, const Card&);
    friend bool operator!= (const Card&, const Card&);
    friend ostream& operator<< (ostream&, const Card&);
};
