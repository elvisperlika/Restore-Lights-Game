#include "led_menager.h"

/**
 * Activate deep sleep mode and set the interrupt 
 * to wake up the system for each button.
*/
void sleepNow();

/**
 * Wake up from deep sleep mode.
*/
static void wakeUpNow();