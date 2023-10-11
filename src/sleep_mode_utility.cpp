#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "sleep_mode_utility.h"

const int buttons[] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};

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

void wakeUpNow(){};
