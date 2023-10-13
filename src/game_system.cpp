#include <Arduino.h>
#include "game_system.h"

/// Array of each decrease rate for each difficulty.
const float DECREASE_RATES[] = {0.05, 0.07, 0.09, 0.11};

//Euler's constant
const float e = 2.7182818284;

/// Initial leds turning off time in milliseconds
const unsigned int INITIAL_T2 = 3000;

/// Initial time Player have to finish the level on easiest difficulty in milliseconds
const unsigned int INITIAL_T3 = 10000;

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