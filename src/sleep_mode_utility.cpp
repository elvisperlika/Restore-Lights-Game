#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "sleep_mode_utility.h"
#include "button_manager.h"

/// @brief Activate deep sleep mode and set the interrupt to wake up the system for each button
void sleepNow() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    
    for (int i = 0; i < getButtonsNumber(); i++) {
        attachInterrupt(digitalPinToInterrupt(buttons[i]), wakeUpNow, RISING);
    }    
    
    sleep_mode();

    sleep_disable();    
    for (int i = 0; i < getButtonsNumber(); i++) {
        detachInterrupt(digitalPinToInterrupt(buttons[i]));
    }
}

/// @brief Empty function for wake up interrupt
void wakeUpNow(){};
