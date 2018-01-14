class CardSet
{
private:
    Card m_set[32];
    int m_top;

public:
    // c'tor
    CardSet();

    // public interface - properties
    int Size() const;

    // public interface - methods
    void Add(Card c);
    void Remove(int num);
    void Clear();

    // operators
    Card operator[](int) const;

    // output
    friend ostream& operator<< (ostream&, const CardSet&);
};
