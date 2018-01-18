#define VERBOSE
// #define SINGLE_STEP

class MauMaster
{
private:
    static const char* Version;
    static const int MaxCardsAtBegin;

    CardDeck m_playing;     // deck to play (Kartenstapel zum Ablegen - offen)
    CardDeck m_drawing;     // deck to draw (Kartenstapel zum Ziehen - verdeckt)
    Player*  m_players;     // array of players
    int      m_numPlayers;  // number of players
    int      m_rounds;      // counting rounds of a game

public:
    // c'tor
    MauMaster(const char* names[], int len);
    ~MauMaster();

    // properties
    int GetRounds();

    // public interface
    void Init(int randomSeed);
    void Play();

private:
    // private helper methods
    int NextPlayer(int currentPlayer);
    int IncrementNumberOfCardsToDraw(int numberOfCardsToDraw);
    void LogGameStatusDebug(Card topMostCard, int currentPlayer);
    void LogFinalGameStatus(char* name);

public:
    // general purpose helpers
    static void PrintVersion();

    // logging methods
    static void Log(char const* message);
    static void Log(char const* message, char const* string);
    static void Log(char const* message, char const* string, CardColor col);
    static void Log(char const* message, char const* string, int n);
    static void Log(char const* message, char const* string1, char const* string2, char const* string3);
};
