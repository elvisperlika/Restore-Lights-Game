#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "sleep_mode_utility.h"

void sleepNow() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    attachInterrupt(digitalPinToInterrupt(BUTTON1), wakeUpNow, RISING);
    attachInterrupt(digitalPinToInterrupt(BUTTON2), wakeUpNow, RISING);
    attachInterrupt(digitalPinToInterrupt(BUTTON3), wakeUpNow, RISING);
    attachInterrupt(digitalPinToInterrupt(BUTTON4), wakeUpNow, RISING);
    sleep_mode();
    sleep_disable();
    
    detachInterrupt(BUTTON1);
    detachInterrupt(BUTTON2);
    detachInterrupt(BUTTON3);
    detachInterrupt(BUTTON4);
}

void wakeUpNow(){
    Serial.println("pressed");
};
