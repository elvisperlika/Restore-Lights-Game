/**
 * Game states.
 * SETUP: initialize the game, set the difficulty with potentiometer.
 * MC: Microcontroller swith off the leds in T2 time after waiting T1 time.
 * PLAYER: Player have to switch on leds in T3 time in the opposite order of swithcing off.
 * NEWLEVEL: Player win the level and start a new one whit less time to play.
 * GAMEOVER: Player lose the game and the system show the score.
*/
enum GameState {
    SETUP,
    MC,
    PLAYER,
    NEWLEVEL,
    GAMEOVER
};

/// Initial leds turning off time and the session related variable
extern const unsigned long INITIAL_T2;
extern unsigned long currentT2;

/// Initial time Player have to finish the level on easiest difficulty, and the serrion related variable
extern const unsigned long INITIAL_T3;
extern unsigned long currentT3;

/// Current Player level
extern int currentLevel;

/// Current game difficulty
extern uint8_t currentDifficulty;

/// @brief Calculate the value of T2 of the given level.
/// @param level: current level.
/// @param difficulty: current difficulty.
/// @return the new T2.
float CalculateT2(int level, uint8_t difficulty);

/// @brief Calculate the value of T3 of the given level.
/// @param level: current level.
/// @param difficulty: current difficulty.
/// @return the new T3.
float CalculateT3(int level, uint8_t difficulty);

/// @brief Initialize the game variables
/// @param difficulty: current game difficulty.
void gameInit(uint8_t difficulty);

/// @brief Called when current level is passed
void levelPassed();

/// @brief Execute the game over steps
/// @param points: number of levels that the player passed
void gameOver(int points);