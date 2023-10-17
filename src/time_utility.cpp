#include "time_utility.h"

#include <avr/sleep.h>
#include <EnableInterrupt.h>

/// @brief Activate deep sleep mode and set the interrupt to wake up the system for each button
void sleepNow() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    
    for (int i = 0; i < 5; i++) {
        //enableInterrupt(buttons[i], wakeUpNow, HIGH);
    }    
    
    sleep_mode();
    sleep_disable();    

    for (int i = 0; i < 5; i++) {
        //disableInterrupt(buttons[i]);
    }
}

/// @brief Empty function for wake up interrupt
void wakeUpNow(){
    Serial.println("Wake up");
};

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