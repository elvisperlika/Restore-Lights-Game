#ifndef __SLEEP_MODE_UTILITY_H__
#define __SLEEP_MODE_UTILITY_H__

#include "Arduino.h" 

/// @brief Call a function if enough time passed.
/// @param limitTime is the time after which the function is launched.
/// @param startTime is a pointer to a variable representing the start time.
/// @param function function to launch.
void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)());

/// @brief Call a function if enough time passed.
/// @param limitTime is the time after which the function is launched.
/// @param startTime is a pointer to a variable representing the start time.
/// @param function function to launch.
/// @param s is the function's parameter.
void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)(bool), bool s);

/// @brief Apply a formula that follow an'exponential decrese to calculate new level's time.
/// @param initialT: starting T value .
/// @param decreaseRatio: the greater it is, the fastest the number goes down .
/// @param level: starting from 0, more level means less time, less level more time.
/// @return the new time.
float CalculateNewT(unsigned long initialT, float decreaseRatio, uint8_t level);
#endif
