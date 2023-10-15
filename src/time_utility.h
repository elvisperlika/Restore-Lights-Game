#ifndef __SLEEP_MODE_UTILITY_H__
#define __SLEEP_MODE_UTILITY_H__

/// @brief Activate deep sleep mode and set the interrupt to wake up the system for each button
void sleepNow();

/// @brief Empty function for wake up interrupt
void wakeUpNow();

/// @brief Call a function if enough time passed
/// @param limitTime is the time after which the function is launched
/// @param startTime is a pointer to a variable representing the start time
/// @param function function to launch
void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)());

/// @brief Call a function if enough time passed
/// @param limitTime is the time after which the function is launched
/// @param startTime is a pointer to a variable representing the start time
/// @param function function to launch
/// @param s is the function's parameter
void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)(bool), bool s);

#endif
