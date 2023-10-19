#include "game_engine.h"

#include <Arduino.h>
#include <button_manager.h>
#include <led_manager.h>
#include <potenziometer_manager.h>

bool ledsOnFlag = false;
int i = 0;

uint8_t ledsOff[4] = {0, 0, 0, 0};

void boardInit() {
    ledsInit();
    buttonsInit();
    potentiometerInit();
}

void gameSetup() {
    Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
    ledFading(RED_LED);
    SleepMode_StartTime = millis();
}

void gameInit() {
    currentLevel = 0;
    bestScore = 0;
    currentDifficulty = getDifficulty();
    levelInit(currentDifficulty);
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

void boardInit() {
    ledsInit();
    buttonsInit();
    potentiometerInit();
}

bool checkStartGame() {
    return digitalRead(BUTTON1) == HIGH ? true : false;
}

void levelInit(uint8_t difficulty) {
    T2_TIME = CalculateT2(currentLevel, difficulty);
    T3_TIME = CalculateT3(currentLevel, difficulty);
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
    for (int j = 0; j < 4; j++) {
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

void showGameOverAllert() {
    /* TODO */
}

void deactivateButtonsGameInterrupt() {
    /* TODO */
}

void resetGame() {
    /* TODO */
}

void setGameOver() {
    deactivateButtonsGameInterrupt();
    gameState = GAMEOVER;
}