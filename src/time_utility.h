#ifndef __SLEEP_MODE_UTILITY_H__
#define __SLEEP_MODE_UTILITY_H__

#include "Arduino.h" 

/**
 * @brief Call a function if enough time passed
 * @param limitTime is the time after which the function is launched
 * @param startTime is a pointer to a variable representing the start time
 * @param function function to launch
*/
void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)());

#endif
