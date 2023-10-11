#include <Arduino.h>
#include "game_system.h"

const double DECRESE_RATES[] = {0.05, 0.1, 0.15, 0.2};

int CalculateT2(int level, int difficulty) {
  return INITIAL_T2 * pow(1 - DECRESE_RATES[difficulty], level);
}

int CalculateT3(int level, int difficulty) {
  return INITIAL_T3 * pow(1 - DECRESE_RATES[difficulty], (double)level);
}