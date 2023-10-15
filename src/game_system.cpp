#include <Arduino.h>
#include "game_system.h"
#include "led_manager.h"
#include "button_manager.h"

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

/// @brief Apply a formula that follow an'exponential decrese of the time
/// @param initialValue: starting value 
/// @param decreaseRatio: the greater, the fastest the number goes down 
/// @param level: starting from 0, more level means less time, less level more time
/// @return
float ApplyDecreasingFormula(float initialValue, float decreaseRatio, uint8_t level) {
     return initialValue * pow(e, -decreaseRatio * level);
}

/// @brief Calculate the value of T2 of the given level.
/// @param level: current level.
/// @param difficulty: current difficulty.
/// @return the new T2.
float CalculateT2(uint8_t level, uint8_t difficulty) {
     return ApplyDecreasingFormula(INITIAL_T2, DECREASE_RATES[difficulty], level);
}

/// @brief Calculate the value of T3 of the given level.
/// @param level: current level.
/// @param difficulty: current difficulty.
/// @return the new T3.
float CalculateT3(uint8_t level, uint8_t difficulty) {
     return ApplyDecreasingFormula(INITIAL_T3, DECREASE_RATES[difficulty], level);
}

/// @brief Initialize the game variables
/// @param difficulty: current game difficulty.
void gameInit(uint8_t difficulty) {
      currentLevel = 0;
      bestScore = 0;
      currentDifficulty = difficulty;
      currentT2 = CalculateT2(currentLevel, difficulty);
      currentT3 = CalculateT3(currentLevel, difficulty);
      ledsToSwitchOffLeft = 0;
}

/// @brief switch a random led off (saving the order), do nothing if all leds are off
void switchRandomLedOff () {
      //No leds to switch off
      if (getGreenLedsOn() == 0) {
          return;
      }

      //Set one random pin on LOW state
      uint8_t randomPin = random(getGreenLeds());
      while (digitalRead(randomPin) == LOW) {
        randomPin = random(getGreenLeds());
      }
      digitalWrite(randomPin, LOW);
}

/// @brief Called when current level is passed
void levelPassed() {
    currentLevel++;
    currentT2 = CalculateT2(currentLevel, currentDifficulty);
    currentT3 = CalculateT3(currentLevel, currentDifficulty);
}

/// @brief Print the final score
void printFinalScore() {
    Serial.print("Game Over. Final Score: ");
    Serial.println(currentLevel);

    if (currentLevel > bestScore) {
        bestScore = currentLevel;
        Serial.println("NEW BEST SCORE!");
    }
}