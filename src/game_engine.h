#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

enum GameState {
    SETUP,
    INITIALIZATION,
    LEDS_ON,
    LEDS_OFF,
    PLAYER,
    NEWLEVEL,
    GAMEOVER
};

void gameSetup();

void boardInit();

void gameInit();

void levelInit();

void sleepMode();

bool checkStartGame();

void ledsOn();

bool checkLedsOn();

void disableRandomLed();

#endif
