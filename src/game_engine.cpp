#include "game_engine.h"

#include <Arduino.h>
#include "button_manager.h"
#include "led_manager.h"
#include "potenziometer_manager.h"
#include "time_utility.h"

/// Array of each decrease rate for each difficulty.
const float DECREASE_RATES[] = {0.05, 0.07, 0.09, 0.11};

/// Current Player level (score) and best player's score
static int currentLevel;
static int bestScore;

/// TO DOCUMENT (flags 🤢)
bool ledsOnFlag = false;
int i = 0;

/// Led's id turning off order ~~~~~~
uint8_t ledsOff[] = {0, 0, 0, 0};

void boardInit() {
    ledsInit();
    buttonsInit();
    potentiometerInit();
}

void gameSetup() {
    Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
    SleepMode_StartTime = millis();
}

void initializationAllert() {
    ledFading(RED_LED);
}

bool checkStartGame() {
    return digitalRead(BUTTON1) == HIGH ? true : false;
}

static void levelInit(uint8_t difficulty) {
    T2_TIME = CalculateNewT(INITIAL_T2, DECREASE_RATES[difficulty], currentLevel);
    T3_TIME = CalculateNewT(INITIAL_T3, DECREASE_RATES[difficulty], currentLevel);
    i = getButtonsNumber() - 1;
}

void gameInit() {
    switchLed(RED_LED, false);
    currentLevel = 0;
    bestScore = 0;
    levelInit(getDifficulty());
}

void ledsOn(bool s) {
    switchGreenLeds(s);
    ledsOnFlag = true;
}

bool checkLedsOn() {
    bool tmp = ledsOnFlag;
    ledsOnFlag = false;
    return tmp;
}

void disableRandomLed() {
    ledsOff[i] = switchRandomLedOff();
    i--;
}

bool checkPatternCreated() {
    // TO DO
}

void activateGameControls() {
    activateButtonsGameInterrupt();
}

GameState checkGameStatus() {
    for (int j = 0; j < btnPressedCounter; j++) {
        if (getPressedBtn()[j] != ledsOff[j]) {
            return GAMEOVER;
        }    
    }
    return PLAYER;
}

void levelPassed() {
    currentLevel++;
    //note: is possible to change game difficulty runtime
    levelInit(getDifficulty());
}

void showGameScore() {
    Serial.print("Game Over. Final Score: ");
    Serial.println(currentLevel);

    if (currentLevel > bestScore) {
        bestScore = currentLevel;
        Serial.println("NEW BEST SCORE!");
    }
}

void showGameOverAllert() {
    ledFading(RED_LED);
}

void deactivateGameControls() {
    deactivateButtonsGameInterrupt();
}

void sleepMode() {
    Serial.println("Sleep mode actived");
    delay(100);
    switchLed(RED_LED, false);
    sleepNow();
}




