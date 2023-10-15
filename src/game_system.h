/**
 * Game states.
 * SETUP: executed only one time at the beginning of every new game to reset variables
 * INITIALIZATION: waiting phase: 10s -> sleep mode or/and interrupt -> start game
 * LEDS_ON: turning on of all leds and waiting 
 * LEDS_OFF: randomly switch off of every led
 * PLAYER: Player have to switch on leds in T3 time in the opposite order of swithcing off.
 * NEWLEVEL: Player win the level and start a new one whit less time to play.
 * GAMEOVER: Player lose the game and the system show the score.
*/
enum GameState {
    SETUP,
    INITIALIZATION,
    LEDS_ON,
    LEDS_OFF,
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
extern uint8_t currentLevel;

/// Current game difficulty
extern uint8_t currentDifficulty;

/// @brief Calculate the value of T2 of the given level.
/// @param level: current level.
/// @param difficulty: current difficulty.
/// @return the new T2.
float CalculateT2(uint8_t level, uint8_t difficulty);

/// @brief Calculate the value of T3 of the given level.
/// @param level: current level.
/// @param difficulty: current difficulty.
/// @return the new T3.
float CalculateT3(uint8_t level, uint8_t difficulty);

/// @brief Initialize the game variables
/// @param difficulty: current game difficulty.
void gameInit(uint8_t difficulty);

/// @brief switch a random led off (saving the order), do nothing if all leds are off
void switchRandomLedOff();

/// @brief Called when current level is passed
void levelPassed();

/// @brief Print the final score
void printFinalScore();

/// @brief Execute the game over steps
void gameOver();