#include <Arduino.h>
#include "game_engine.h"
#include "time_utility.h"

GameState gameState = SETUP;

void setup() {
    boardInit();
    Serial.begin(9600);
}

void resetGame() {
    gameState = SETUP;
}

void setGameOver() {
    deactivateGameControls();
    gameState = GAMESCORE;
}

void loop() {
    switch (gameState)
    {
    case SETUP:
        Serial.println("Game setup");
        gameSetup();
        gameState = INITIALIZATION;
        break;
    case INITIALIZATION:
        basicTimer(SleepMode_TIME, &SleepMode_StartTime, sleepMode);
        initializationAllert();
        if (checkStartGame()) {
            Serial.println("Game started");
            gameInit();
            T1_StartTime = millis();
            gameState = LEDS_ON;
        }

        break;
    case LEDS_ON:
        basicTimer(T1_TIME, &T1_StartTime, ledsOn, true);
        if (checkLedsOn()) {
            T2_StartTime = millis();
            gameState = LEDS_OFF;
        }

        break;
    case LEDS_OFF:
        basicTimer(T2_TIME, &T2_StartTime, disableRandomLed);
        if (checkPatternCreated()) {
            Serial.println("Pattern created");
            activateGameControls();
            T3_StartTime = millis();
            gameState = PLAYER;
        }

        break;
    case PLAYER:
        basicTimer(T3_TIME, &T3_StartTime, setGameOver);
        gameState = checkGameStatus();
        break;
    case NEW_LEVEL:
        levelPassed();
        gameState = LEDS_ON;
        break;
    case GAMESCORE:
        showGameScore();
        gameState = GAMEOVER;
        break;
    case GAMEOVER:
        basicTimer(ResetGame_TIME, &ResetGame_StartTime, resetGame);
        showGameOverAllert();
        break;
    default:
        break;
    }
}
