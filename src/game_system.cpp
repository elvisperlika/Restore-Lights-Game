#include <Arduino.h>
#include "game_system.h"
#include "led_manager.h"

/// Array of each decrease rate for each difficulty.
const float DECREASE_RATES[] = {0.05, 0.07, 0.09, 0.11};

//Euler's constant
const float e = 2.7182818284;

/// Initial leds turning off time in milliseconds
const unsigned long INITIAL_T2 = 3000UL;

/// Initial time Player have to finish the level on easiest difficulty in milliseconds
const unsigned long INITIAL_T3 = 10000UL;

// Variables value related to the current session
unsigned long currentT2;
unsigned long currentT3;
uint8_t currentLevel;
uint8_t currentDifficulty;
uint8_t ledsToSwitchOffLeft;

// variable to keep track of the best score
uint8_t bestScore = 0;

// vector of order of the switched pins
uint8_t* pinsOrder;

float ApplyDecreasingFormula(float initialValue, float decreaseRatio, uint8_t level) {
     return initialValue * pow(e, -decreaseRatio * level);
}

float CalculateT2(uint8_t level, uint8_t difficulty) {
     return ApplyDecreasingFormula(INITIAL_T2, DECREASE_RATES[difficulty], level);
}

float CalculateT3(uint8_t level, uint8_t difficulty) {
     return ApplyDecreasingFormula(INITIAL_T3, DECREASE_RATES[difficulty], level);
}

void gameInit(uint8_t difficulty) {
      currentLevel = 0;
      bestScore = 0;
      currentDifficulty = difficulty;
      currentT2 = CalculateT2(currentLevel, difficulty);
      currentT3 = CalculateT3(currentLevel, difficulty);
      ledsToSwitchOffLeft = 0;
      pinsOrder = (uint8_t*)malloc(getGreenLedsNumber() * sizeof(uint8_t));
}

void switchRandomLedOff () {
      uint8_t randomPin = random(getGreenLedsNumber());
      while (digitalRead(greenLeds[randomPin]) == LOW) {
        randomPin = random(getGreenLedsNumber());
      }
      digitalWrite(greenLeds[randomPin], LOW);
      pinsOrder[ledsToSwitchOffLeft++] = greenLeds[randomPin];
}

void levelPassed() {
    currentLevel++;
    currentT2 = CalculateT2(currentLevel, currentDifficulty);
    currentT3 = CalculateT3(currentLevel, currentDifficulty);
}

void printFinalScore() {
    Serial.print("Game Over. Final Score: ");
    Serial.println(currentLevel);

    if (currentLevel > bestScore) {
        bestScore = currentLevel;
        Serial.println("NEW BEST SCORE!");
    }
}

void changeState(GameState &gameState, GameState newState) {
    gameState = newState;
}
