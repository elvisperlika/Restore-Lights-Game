#include "game_engine.h"

#include <Arduino.h>
#include "button_manager.h"
#include "led_manager.h"
#include "potenziometer_manager.h"
#include "time_utility.h"

/// Array of each decrease rate for each difficulty.
const float DECREASE_RATES[] = {0.05, 0.07, 0.09, 0.11};
static int currentLevel;
static int bestScore; 

bool ledsOnFlag = false;
int i = 0;

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

void gameInit() {
    switchLed(RED_LED, false);
    currentLevel = 0;
    bestScore = 0;
    levelInit(getDifficulty());
}

void initializationAllert() {
    ledFading(RED_LED);
}

void showGameOverAllert() {
    ledFading(RED_LED);
}

void sleepMode() {
    Serial.println("Sleep mode actived");
    delay(100);
    switchLed(RED_LED, false);
    sleepNow();
}

bool checkStartGame() {
    return digitalRead(BUTTON1) == HIGH ? true : false;
}

void levelInit(uint8_t difficulty) {
    T2_TIME = CalculateNewT(INITIAL_T2, DECREASE_RATES[difficulty], currentLevel);
    T3_TIME = CalculateNewT(INITIAL_T3, DECREASE_RATES[difficulty], currentLevel);
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
    i++;
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
    /* TODO */
}

void showGameScore() {
    /* TODO */
}

void deactivateGameControls() {
    deactivateButtonsGameInterrupt();
}

void activateGameControls() {
    activateButtonsGameInterrupt();
}
