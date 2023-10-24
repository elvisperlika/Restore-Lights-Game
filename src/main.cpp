#include <Arduino.h>
#include "game_engine.h"
#include "time_utility.h"

static GameState gameState = SETUP;

/// @brief Restart from SETUP state (called by a timer function).
void resetGame();

/// @brief Deactivate game controls, then enter GAMESCORE state (called by a timer function).
void setGameOver();

/// @brief Enter deep sleep mode, and then return to SETUP state, needed to 
//reactivate button interrupts (called by a timer function).
void setSleepMode();

void setup() {
    Serial.begin(9600);
    boardInit();
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
                levelInit();
                T1_StartTime = millis();
                gameState = LEDS_ON;
            }
            break;
        case LEDS_ON:
            basicTimer(T1_TIME, &T1_StartTime, ledsOn, true);
            if (checkLightsOn()) {
                T2_StartTime = millis();
                gameState = LEDS_OFF;
            }
            break;
        case LEDS_OFF:
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
            //note: here the red light should light up just for one second,
            //but since there would be 10sec of nothing we decided to keep the light on.
            showGameOverAllert();
            gameState = GAMEOVER;
            break;
        case GAMEOVER:
            basicTimer(ResetGame_TIME, &ResetGame_StartTime, resetGame);            
            break;
        default:
            break;
    }
}


void resetGame() {
    gameState = SETUP;
}

void setGameOver() {
    deactivateGameControls();
    gameState = GAMESCORE;
}

void setSleepMode() {
    sleepMode();
    gameState = SETUP;
}
