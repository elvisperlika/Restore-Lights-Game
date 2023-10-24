#ifndef __GAME_ENGINE_H_
#define __GAME_ENGINE_H_

#include <stdint.h>

#define INITIAL_T1 1500UL
#define INITIAL_T2 1000UL
#define INITIAL_T3 10000UL

#define RESET_GAME_TIME 10000UL
#define SLEEP_MODE_TIME 10000UL

/// Defining time vaiables:
/// Time passed after pressing B1 and before turning all green leds on.
extern const unsigned long T1_TIME;
extern unsigned long T1_StartTime; 

/// Initial leds turning off time and the session related variable.
extern unsigned long T2_TIME;
extern unsigned long T2_StartTime;

/// Initial time Player have to finish the level on easiest difficulty, and the serrion related variable.
extern unsigned long T3_TIME;
extern unsigned long T3_StartTime;

/// Time passed between the end of the game and the start of a new one.
extern unsigned long ResetGame_TIME;
extern unsigned long ResetGame_StartTime;

/// Time passed before entering in Sleep Mode.
extern unsigned long SleepMode_TIME;
extern unsigned long SleepMode_StartTime;

/**
 * All possible game states.
 * SETUP: executed only one time at the beginning of every new game to reset variables
 * INITIALIZATION: waiting phase: 10s -> sleep mode or interrupt -> start game.
 * LEDS_ON: turning on of all leds and waiting T1 time.
 * LEDS_OFF: randomly switch off a led every T2 time.
 * PLAYER: Player have to switch on leds in T3 time in the opposite order of swithcing off.
 * NEW_LEVEL: Player win the level and start a new one with less time to play.
 * GAMESCORE: Show the final score of the current game.
 * GAMEOVER: Player wait to restart the game.
*/
enum GameState {
    SETUP,
    INITIALIZATION,
    LEDS_ON,
    LEDS_OFF,
    PLAYER,
    NEW_LEVEL,
    GAMESCORE,
    GAMEOVER
};

/// @brief Initialize board components.
void boardInit();

/// @brief Initialize the game (game one time events).
void gameSetup();

/// @brief Show Initialization Game allert.
void initializationAllert();

/// @brief Check if the game have to start (player pushed the B1 button).
bool checkStartGame();

/// @brief Initialize level variables (called every level change).
void levelInit();

/// @brief Switch the green leds on.
/// @param s true if switching the leds on, false if switching off.
void ledsOn(bool s);

/// @brief Check if all green leds are turned on.
/// @return true if all leds are on, false otherwise.
bool checkLightsOn();

/// @brief Turn off a random led.
void disableRandomLed();

/// @brief Check if the pattern was created.
/// @return true if all leds are switched off.
bool checkPatternCreated();

/// @brief Enable game's controls.
void activateGameControls();

/// @brief Check if the player lost the game.
/// @return NEW_LEVEL if the player pressed all buttons in the correct order; 
///         GAMESCORE if the player pushed a wrong button;
///         PLAYER otherwise. 
GameState checkGameStatus();

/// @brief Initialize a new level.
void levelPassed();

/// @brief Show in Serial the player's score.
void showGameScore();

/// @brief Show Game Over led allert.
void showGameOverAllert();

/// @brief Disable game's controls.
void deactivateGameControls();

/// @brief Set Arduino in Deep Sleep Mode.
void sleepMode();

#endif
