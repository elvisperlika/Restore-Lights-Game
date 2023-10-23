#include <Arduino.h>
#include "led_manager.h"

/// Array of green led's pins
static const uint8_t greenLeds[] = {GREEN_LED1, GREEN_LED2, GREEN_LED3, GREEN_LED4};

/// Variables needed to manage ledFading.
static int fadeAmount = 5;
static int currIntensity = 0;
static unsigned long lastFadeCallTime;

uint8_t getGreenLedsNumber() {
    return sizeof(greenLeds) / sizeof(greenLeds[0]);
}

void ledsInit() {
    for (int i = 0; i < getGreenLedsNumber(); i++)
    {
        pinMode(greenLeds[i], OUTPUT);
    }

    currIntensity = 0;
    lastFadeCallTime = millis();
}

void switchGreenLeds(bool state) {
    for (int i = 0; i < getGreenLedsNumber(); i++) {
        digitalWrite(greenLeds[i], state == true ? HIGH : LOW);
    }
}

void switchLed(uint8_t ledPin, bool state) {
    digitalWrite(ledPin, state == true ? HIGH : LOW);
}

void switchLedByIndex(uint8_t ledIndex, bool state) {
    switchLed(greenLeds[ledIndex], state);
}

bool checkLedsOn() {
    for (int i = 0; i < getGreenLedsNumber(); i++) {
        if (digitalRead(greenLeds[i]) == LOW) {
            return false;
        }
    }
    return true;
}

void ledFading(uint8_t ledPin) {
    if (millis() - lastFadeCallTime >= FADE_DELAY) {
        analogWrite(ledPin, currIntensity);
        currIntensity += fadeAmount;

        if (currIntensity <= 0 || currIntensity >= 255) {
            fadeAmount = -fadeAmount;
        }
        
        lastFadeCallTime = millis();
    }    
}

uint8_t switchRandomLedOff() {
    uint8_t random = rand() % getGreenLedsNumber();
    while (digitalRead(greenLeds[random]) == LOW) {
        random = rand() % getGreenLedsNumber();
    }
    digitalWrite(greenLeds[random], LOW);
    return random;
}
