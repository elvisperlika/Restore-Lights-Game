#include <Arduino.h>
#include "potenziometer_manager.h"

const uint8_t POTENTIOMETER_PIN = A0;

int getDifficulty() {
    int potValue = analogRead(POTENTIOMETER_PIN);
    return map(potValue, 0, 1023, 1, 3);
}

void potentiometerInit() {
    pinMode(POTENTIOMETER_PIN, INPUT);
}
