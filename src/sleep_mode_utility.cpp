#include <Arduino.h>
#include <avr/sleep.h>
#include "sleep_mode_utility.h"

void sleepNow() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    // al posto del 4 ci va un metodo che ritorna il numero di pulsanti
    for (int i = 0; i < 4; i++) {
        // al posto di 0 si deve scorrere il vettore di pulsanti
        attachInterrupt(0, wakeUpNow, LOW);
    }
    sleep_mode();
    sleep_disable();
}

static void wakeUpNow() {
    /* TODO */
}