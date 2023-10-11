#include <Arduino.h>
#include <avr/sleep.h>
#include "sleep_mode_utility.h"

void sleepNow() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    attachInterrupt(BUTTON1, wakeUpNow, LOW);
    attachInterrupt(BUTTON2, wakeUpNow, LOW);
    attachInterrupt(BUTTON3, wakeUpNow, LOW);
    attachInterrupt(BUTTON4, wakeUpNow, LOW);
    sleep_mode();
    sleep_disable();
    detachInterrupt(BUTTON1);
    detachInterrupt(BUTTON2);
    detachInterrupt(BUTTON3);
    detachInterrupt(BUTTON4);
}

void wakeUpNow(){};
