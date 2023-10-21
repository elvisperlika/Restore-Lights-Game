#include <Arduino.h>
#include "game_engine.h"
#include "time_utility.h"

GameState gameState = SETUP;

void setup() {
    boardInit();
    Serial.begin(9600);
}

/// @brief Restart from SETUP state.
void resetGame() {
    gameState = SETUP;
}

/// @brief Deactivate game controls, then enter GAMESCORE state.
void setGameOver() {
    deactivateGameControls();
    gameState = GAMESCORE;
}

void loop() {
    switch (gameState)
    {
        case SETUP:
            gameSetup();
            SleepMode_StartTime = millis();
            gameState = INITIALIZATION;
            break;
        case INITIALIZATION:
            basicTimer(SleepMode_TIME, &SleepMode_StartTime, sleepMode);
            initializationAllert();
            if (checkStartGame()) {
                gameInit();
                Serial.println("GO!");
                T1_StartTime = millis();
                gameState = LEDS_ON;
            }

            break;
        case LEDS_ON:
            Serial.println("asdf");
            basicTimer(T1_TIME, &T1_StartTime, ledsOn, true);
            if (checkLedsOn()) {
                T2_StartTime = millis();
                gameState = LEDS_OFF;
            }

            break;
        case LEDS_OFF:
            Serial.println("asdfpt2");
            basicTimer(T2_TIME, &T2_StartTime, disableRandomLed);
            if (checkPatternCreated()) {
                activateGameControls();
                T3_StartTime = millis();
                gameState = PLAYER;
            }

            break;
        case PLAYER:
            gameState = checkGameStatus();
            basicTimer(T3_TIME, &T3_StartTime, setGameOver);
            break;
        case NEW_LEVEL:
            levelPassed();
            T1_StartTime = millis();
            gameState = LEDS_ON;
            break;
        case GAMESCORE:
            showGameScore();
            ResetGame_StartTime = millis();
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
