#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

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

void gameSetup();

void boardInit();

void gameInit();

void levelInit();

void sleepMode();

bool checkStartGame();

void ledsOn(bool s);

bool checkLedsOn();

void disableRandomLed();

GameState checkGameStatus();

bool checkPatternCreated();

void activateGameControls();

void levelPassed();

void showGameScore();

void showGameOverAllert();

void deactivateButtonsGameInterrupt();

void resetGame();

void setGameOver();

#endif
