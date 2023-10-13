#include <Arduino.h>
#include "game_system.h"
#include "led_manager.h"

/// Array of each decrease rate for each difficulty.
const float DECREASE_RATES[] = {0.05, 0.07, 0.09, 0.11};

//Euler's constant
const float e = 2.7182818284;

/// Initial leds turning off time in milliseconds
const unsigned int INITIAL_T2 = 3000;

/// Initial time Player have to finish the level on easiest difficulty in milliseconds
const unsigned int INITIAL_T3 = 10000;

// Variables value related to the current session
int currentT2;
int currentT3;
int currentLevel;
int currentDifficulty;

/// @brief Apply a formula that follow an'exponential decrese of the time
/// @param initialValue: starting value 
/// @param decreaseRatio: the greater, the fastest the number goes down 
/// @param level: starting from 0, more level means less time, less level more time
/// @return
float ApplyDecreasingFormula(float initialValue, float decreaseRatio, int level) {
  return initialValue * pow(e, -decreaseRatio * level);
}

/// @brief Calculate the value of T2 of the given level.
/// @param level: current level.
/// @param difficulty: current difficulty.
/// @return the new T2.
float CalculateT2(int level, int difficulty) {
  return ApplyDecreasingFormula(INITIAL_T2, DECREASE_RATES[difficulty], level);
}

/// @brief Calculate the value of T3 of the given level.
/// @param level: current level.
/// @param difficulty: current difficulty.
/// @return the new T3.
float CalculateT3(int level, int difficulty) {
  return ApplyDecreasingFormula(INITIAL_T3, DECREASE_RATES[difficulty], level);
}

/// @brief Initialize the game variables
/// @param difficulty: current game difficulty.
void gameInit(int difficulty) {
  currentLevel = 0;
  currentDifficulty = difficulty;
  currentT2 = CalculateT2(currentLevel, difficulty);
  currentT3 = CalculateT3(currentLevel, difficulty);
}

/// @brief Execute the game over steps
/// @param points: number of levels that the player passed
void gameOver(int points){
    Serial.println(points);
    int startingTime = millis();
    //arduino led fade from light on to light off over 10 sec
    analogWrite(RED_LED, 255);
    for (; millis() - startingTime < 10000;) {
        analogWrite(RED_LED, map(millis() - startingTime, 0, 10000, 255, 0));
    }
    analogWrite(RED_LED, 0);
}