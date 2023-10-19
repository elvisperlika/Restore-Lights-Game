#ifndef __GAME_ENGINE_H_
#define __GAME_ENGINE_H_

#include <stdint.h>
#define INITIAL_T2 3000UL
#define INITIAL_T3 10000UL

extern unsigned long T1_TIME;
extern unsigned long T1_StartTime; 

extern unsigned long T2_TIME;
extern unsigned long T2_StartTime;

extern unsigned long T3_TIME;
extern unsigned long T3_StartTime;

extern unsigned long ResetGame_TIME = 10000;
extern unsigned long ResetGame_StartTime;

extern unsigned long SleepMode_TIME = 10000;
extern unsigned long SleepMode_StartTime;

enum GameState {
    SETUP,
    INITIALIZATION,
    LEDS_ON,
    LEDS_OFF,
    PLAYER,
    NEWLEVEL,
    GAMESCORE,
    GAMEOVER
};

/**
 * Show the Welcome message.
*/
void gameSetup();

/**
 * Initialize all pins connected.
*/
void boardInit();

/**
 * Initialize the game stats.
*/
void gameInit();

/**
 * 
*/
void levelInit(uint8_t difficulty);

/**
 * Set Arduino in Deep Sleep Mode.
*/
void sleepMode();

/**
 * Check if the player pushed the B1 button.
*/
bool checkStartGame();

/**
 * Switch the green leds on.
*/
void ledsOn(bool s);

/**
 * Check if all green leds are turned on.
*/
bool checkLedsOn();

/**
 * Turn off a random led.
*/
void disableRandomLed();

/**
 * Check if the player lose the game.
 * @return NEWLEVEL if the player pressed the button
 *      in the correct order or GAMESCORE if the player push the wrong button. 
*/
GameState checkGameStatus();

/**
 * Check if the pattern was created.
 * @return true if all leds are switched off. 
*/
bool checkPatternCreated();

/**
 * Enable game's controls.
*/
void activateGameControls();

/**
 * Disable game's controls.
*/
void deactivateGameControls();

/**
 * Set new level stats.
*/
void levelPassed();

/**
 * Show in Serial the new score and the bast score.
*/
void showGameScore();

/**
 * Show Game Over led allert.
*/
void showGameOverAllert();

/**
 * Show Initialization Game led allert. 
*/
void initializationAllert();

#endif
