#include <Arduino.h>
#include "game_system.h"

/// Array of each decrease rate for each difficulty.
const float DECREASE_RATES[] = {0.05, 0.07, 0.09, 0.11};

const float e = 2.7182818284;

/// @brief Apply a formula that follow an'exponential decrese of the time
/// @param initialValue 
/// @param decreaseRatio 
/// @param level 
/// @return 
double ApplyDecreasingFormula(float initialValue, float decreaseRatio, int level) {
  return initialValue * pow(e, -decreaseRatio * level);
}

/// @brief Calculate the value of T2 of the given level.
/// @param level: current level.
/// @param difficulty: current difficulty.
/// @return the new T2.
double CalculateT2(int level, int difficulty) {
  return ApplyDecreasingFormula(INITIAL_T2, DECREASE_RATES[difficulty], level);
}

/// @brief Calculate the value of T3 of the given level.
/// @param level: current level.
/// @param difficulty: current difficulty.
/// @return the new T3.
double CalculateT3(int level, int difficulty) {
  return ApplyDecreasingFormula(INITIAL_T3, DECREASE_RATES[difficulty], level);
}