#include <Arduino.h>
#include "potenziometer_manager.h"

/// Define potentiometer pin
const uint8_t POTENTIOMETER_PIN = A0;

/// T1 is the time after which the green led switch on
unsigned long T1 = 3000;

/// @brief Get the selected difficulty by reading the value from the potentiometer
/// @return the selected difficulty
uint8_t getDifficulty() {
    int potValue = analogRead(POTENTIOMETER_PIN);
    return map(potValue, 0, 1023, 1, 3);
}

/// @brief Initialize potentiometer's pin
void potentiometerInit() {
    pinMode(POTENTIOMETER_PIN, INPUT);
}