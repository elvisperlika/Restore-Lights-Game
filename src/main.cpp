#include <Arduino.h>
#include "main.h"
#include "game_engine.h"
#include "time_utility.h"


/// Define the current state of the game
GameState gameState = SETUP;

/// Variables managing timers for events
unsigned long sleepModeStartTime;
unsigned long switchOnGreenLedsStartTime;
unsigned long switchOffGreenLedStartTime;
unsigned long gameOverStartTime;

/// Player have 10s to start the game or the system go in deep sleep mode
const unsigned long sleepModeTime = 10000;

/// Variable used on not blocking delays
unsigned long prevTime = 0;

/// State of the MC phase, true if still have to light up some leds, false otherwise
bool ledsTurningOn = true;

void setup() {
    boardInit();
    Serial.begin(9600);
}

void loop() {
    switch (gameState)
    {
    case SETUP:
        gameSetup();
        gameState = INITIALIZATION;
        break;
    case INITIALIZATION:
        basicTimer(sleepModeTime, &sleepModeStartTime, sleepMode);
        if (checkStartGame()) {
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

        // Check if the MC phase is finished
        if (checkPatternCreated()) {
            //Initialize the PLAYER state
            activateGameControls();
            T3_StartTime = millis();
            //Change to PLAYER state            
            gameState = PLAYER;
        }

        break;
    case PLAYER:
        /* here check if the player pressed wrong button */
        /* here check if the player win the game */
        /* this is one of the last function to launch in this state */
        basicTimer(T3_TIME, &T3_StartTime, setGameOver);
        /* this is the last function to launch in this state */
        gameState = checkGameStatus();
        
        break;
    case NEWLEVEL:
        levelPassed();
        gameState = LEDS_ON;
        break;
    case GAMESCORE:
        showGameScore();
        gameState = GAMEOVER;
        break;
    case GAMEOVER:
        // !! Aggiungi il map al red led fade down 10s
        basicTimer(ResetGame_TIME, &ResetGame_StartTime, resetGame());
        showGameOverAllert();
        break;
    default:
        break;
    }
}

/// @brief Set the game state to GAMEOVER (used with an iterrupt).
void setGameOver() {
    deactivateButtonsGameInterrupt();
    gameState = GAMEOVER;
}