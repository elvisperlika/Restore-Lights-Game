#ifndef __SLEEP_MODE_UTILITY_H__
#define __SLEEP_MODE_UTILITY_H__

/// @brief Activate deep sleep mode and set the interrupt to wake up the system for each button
void sleepNow();

/// @brief Empty function for wake up interrupt
void wakeUpNow();

#endif
