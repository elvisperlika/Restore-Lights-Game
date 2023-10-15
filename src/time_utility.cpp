#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "time_utility.h"
#include "button_manager.h"
#include "led_manager.h"

/// @brief Setup the environement for the deep sleep, then enter deep sleep
void prepareSleep() {
    Serial.println("Sleep mode actived");
    switchGreenLeds(false);
    switchLed(RED_LED, false);
    sleepNow();
}

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

/// @brief Call a function if enough time passed
/// @param limitTime is the time after which the function is launched
/// @param startTime is a pointer to a variable representing the start time
/// @param function function to launch
void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)()) {
    if (millis() - *startTime >= limitTime) {
        function();
        *startTime = millis();
    }
}

/// @brief Call a function if enough time passed
/// @param limitTime is the time after which the function is launched
/// @param startTime is a pointer to a variable representing the start time
/// @param function function to launch
/// @param s is the function's parameter
void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)(bool), bool s) {
    if (millis() - *startTime >= limitTime) {
        function(s);
        *startTime = millis();
    }
}