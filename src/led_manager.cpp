#include <Arduino.h>
#include "led_manager.h"

/// Array of green led's pins
const uint8_t greenLeds[] = {GREEN_LED1, GREEN_LED2, GREEN_LED3, GREEN_LED4};

/// Variables to manage ledFading
int fadeAmount = 5;
int currIntensity = 0;

/// @brief Getter of the total number of green leds
/// @return the number of green leds
int getGreenLedsNumber() {
    return sizeof(greenLeds) / sizeof(greenLeds[0]);
}

/// @brief Initialize green and red led's pins on OUTPUT
void ledsInit() {
    for (int i = 0; i < getGreenLedsNumber(); i++)
    {
        pinMode(greenLeds[i], OUTPUT);
    }
    pinMode(RED_LED, OUTPUT);
    currIntensity = 0;
}

/// @brief Switch all the leds on or off
/// @param state: true to switch on, false to switch off
void switchGreenLeds(bool state) {
    for (int i = 0; i < getGreenLedsNumber(); i++) {
        digitalWrite(greenLeds[i], state == true ? HIGH : LOW);
    }
}

/// @brief Switch on or off a single led
/// @param ledPin: pin of the led to switch on or off
/// @param state: true to switch on, false to switch off
void switchLed(uint8_t ledPin, bool state) {
    digitalWrite(ledPin, state == true ? HIGH : LOW);
}

/// @brief If the fading is activated the led will fade in and out else the led will be switched off
/// @param ledPin pin of the led to switch on or off
void ledFading(uint8_t ledPin) {
    analogWrite(ledPin, currIntensity);
    currIntensity += fadeAmount;

    if (currIntensity <= 0 || currIntensity >= 255) {
        fadeAmount = -fadeAmount;
    }
}
