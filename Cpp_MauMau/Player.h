class Player
{
private:
    CardSet    m_hand;       // player's hand of cards (usually 5)
    CardDeck*  m_playing;    // deck to play (Kartenstapel zum Ablegen)
    CardDeck*  m_drawing;    // deck to draw (Kartenstapel zum Ziehen)
    char*      m_name;       // players name
    bool       m_isPlaying;  // false, after getting rid of all cards

public:
    // c'tor / d'tor
    Player();
    ~Player();

    // properties
    void SetPlayingDeck(CardDeck* playing);
    void SetDrawingDeck(CardDeck* drawing);
    int GetNumberCards();
    void IsPlaying(bool isPlaying);
    bool IsPlaying();

    // methods
    CardColor ChooseAColor();
    void DrawCards(int number);
    bool CounterSeven(int numCardsToDraw);
    bool PlayCard(CardColor requestedColor, CardPicture requestedPicture);
    bool PlayCard(CardColor requestedColor);
    void PlayArbitraryCard();
    void ReleaseAllCards();

    // private helper methods
    void SetName(const char* name);
    void GetName(char name[], int len);
    Card DrawCard();
    bool HasSeven();
    void PlaySeven();
    void PrintMauMauIf();

    // output
    friend ostream& operator<< (ostream&, const Player&);
};
