#include "game_engine.h"

#include <Arduino.h>
#include <button_manager.h>
#include <led_manager.h>
#include <potenziometer_manager.h>

void boardInit() {
    ledsInit();
    buttonsInit();
    potentiometerInit();
}

void gameSetup() {
    Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
    ledFading(RED_LED);
    sleepModeStartTime = millis();
}

void gameInit() {
    currentLevel = 0;
    bestScore = 0;
    currentDifficulty = getDifficulty();
    levelInit(currentDifficulty);
}

void createPattern() {
    switchGreenLeds(true);

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

void ledsOn() {
    switchGreenLeds(true);
    ledsOnFlag = true;
}

bool checkLedsOn() {
    return ledsOnFlag;
}

void disableRandomLed() {
    ledButtonMap[i]->led = switchRandomLedOff();
    i++;
}