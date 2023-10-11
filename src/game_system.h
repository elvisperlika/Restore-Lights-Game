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

// Initial leds turning off time
#define INITIAL_T2 3000;

// Initial time Player have to finish the level on easiest difficulty
#define INITIAL_T3 10000;

// F factors for each difficulty
extern const double DECRESE_RATES[];

// Current Player level
extern int currentLevel;

// Current game difficulty
extern int currentDifficulty;

/**
 * Calculate the value of T2 of the given level.
 * @param level: current level.
 * @param difficulty: current difficulty.
*/
int CalculateT2(int level, int difficulty);

/**
 * Calculate the value of T3 of the given level.
 * @param level: current level.
 * @param difficulty: current difficulty.
*/
int CalculateT3(int level, int difficulty);