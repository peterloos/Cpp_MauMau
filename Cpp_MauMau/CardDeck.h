class CardDeck
{
private:
    Card m_deck[32];
    int m_top;
    int m_randomSeed;

private:
    static const int RandomSeed = 1;

public:
    // c'tor
    CardDeck();

    // properties
    void SetRandomSeed();
    void SetRandomSeed(int seed);
    bool IsEmpty() const;
    int Size() const;

    // methods
    void Push(Card);
    Card Pop();
    Card TopOfDeck();
    void Fill();
    void Clear();
    void Shuffle();

    // output
    friend ostream& operator<< (ostream&, const CardDeck&);
};