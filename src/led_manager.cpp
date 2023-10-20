#include <Arduino.h>
#include "led_manager.h"

/// Array of green led's pins
const uint8_t greenLeds[] = {GREEN_LED1, GREEN_LED2, GREEN_LED3, GREEN_LED4};

/// Variables to manage ledFading
int fadeAmount = 5;
int currIntensity = 0;

uint8_t getGreenLedsNumber() {
    return sizeof(greenLeds) / sizeof(greenLeds[0]);
}

uint8_t getGreenLedsOnNumber() {
    uint8_t counter = 0;

    for (int i = 0; i < getGreenLedsNumber(); i++)
    {
        if (digitalRead(greenLeds[i]) == HIGH) {
            counter++;
        }
    }

    return counter;
}

void ledsInit() {
    for (int i = 0; i < getGreenLedsNumber(); i++)
    {
        pinMode(greenLeds[i], OUTPUT);
    }
    pinMode(RED_LED, OUTPUT);
    currIntensity = 0;
}

void switchGreenLeds(bool state) {
    for (int i = 0; i < getGreenLedsNumber(); i++) {
        digitalWrite(greenLeds[i], state == true ? HIGH : LOW);
    }
}

void switchLed(uint8_t ledPin, bool state) {
    digitalWrite(ledPin, state == true ? HIGH : LOW);
}

void ledFading(uint8_t ledPin) {
    analogWrite(ledPin, currIntensity);
    currIntensity += fadeAmount;

    if (currIntensity <= 0 || currIntensity >= 255) {
        fadeAmount = -fadeAmount;
    }
}

uint8_t switchRandomLedOff() {
    uint8_t rand = random(getGreenLedsNumber());
    while (digitalRead(greenLeds[rand]) == LOW) {
    rand = random(getGreenLedsNumber());
    }
    digitalWrite(greenLeds[rand], LOW);
    return greenLeds[rand];
}
