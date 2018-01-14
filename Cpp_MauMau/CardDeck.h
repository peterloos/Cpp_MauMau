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

    // public interface - properties
    void SetRandomSeed();
    void SetRandomSeed(int seed);
    bool IsEmpty() const;
    int Size() const;

    // public interface - methods
    void Fill();
    void Clear();
    void Shuffle();

    void Push(Card);
    Card Pop();
    Card TopOfDeck();

    // output
    friend ostream& operator<< (ostream&, const CardDeck&);
};