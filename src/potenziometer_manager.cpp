#include <Arduino.h>
#include "potenziometer_manager.h"

/// Define potentiometer pin
static const uint8_t POTENTIOMETER_PIN = A0;

uint8_t getDifficulty() {
    int potValue = analogRead(POTENTIOMETER_PIN);
    return map(potValue, 0, 1023, 0, 3);
}

void potentiometerInit() {
    pinMode(POTENTIOMETER_PIN, INPUT);
}