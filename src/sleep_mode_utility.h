#ifndef __SLEEP_MODE_UTILITY_H__
#define __SLEEP_MODE_UTILITY_H__
#include "led_manager.h"
#include "button_manager.h"

/**
 * Activate deep sleep mode and set the interrupt 
 * to wake up the system for each button.
*/
void sleepNow();

/**
 * Empty function for wake up interrupt.
*/
void wakeUpNow();

#endif
