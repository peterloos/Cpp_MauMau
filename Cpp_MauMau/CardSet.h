class CardSet
{
private:
    Card m_set[32];
    int m_top;

public:
    // c'tor
    CardSet();

    // properties
    int Size() const;

    // methods
    void Add(Card c);
    void Remove(int index);
    void Clear();

    // operators
    Card operator[](int index) const;

    // output
    friend ostream& operator<< (ostream&, const CardSet&);
};
