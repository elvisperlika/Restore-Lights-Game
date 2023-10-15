#include <Arduino.h>
#include "led_manager.h"

/// Array of green led's pins
const uint8_t greenLeds[] = {GREEN_LED1, GREEN_LED2, GREEN_LED3, GREEN_LED4};

/// Variables to manage ledFading
int fadeAmount = 5;
int currIntensity = 0;

/// @brief Getter of the total number of green leds
/// @return the number of green leds
uint8_t getGreenLeds() {
    return sizeof(greenLeds) / sizeof(greenLeds[0]);
}

/// @brief Getter of the total number of green leds turned on
/// @return the number of green leds turned on
uint8_t getGreenLedsOn() {
    uint8_t counter = 0;

    for (int i = 0; i < getGreenLeds(); i++)
    {
        if (digitalRead(greenLeds[i]) == HIGH) {
            counter++;
        }
    }

    return counter;
}

/// @brief Initialize green and red led's pins on OUTPUT
void ledsInit() {
    for (int i = 0; i < getGreenLeds(); i++)
    {
        pinMode(greenLeds[i], OUTPUT);
    }
    pinMode(RED_LED, OUTPUT);
    currIntensity = 0;
}

/// @brief Switch all the leds on or off
/// @param state: true to switch on, false to switch off
void switchGreenLeds(bool state) {
    for (int i = 0; i < getGreenLeds(); i++) {
        digitalWrite(greenLeds[i], state == true ? HIGH : LOW);
    }
}

/// @brief Switch on or off a single led
/// @param ledPin: pin of the led to switch on or off
/// @param state: true to switch on, false to switch off
void switchLed(uint8_t ledPin, bool state) {
    digitalWrite(ledPin, state == true ? HIGH : LOW);
}

/// @brief Switch a random led on or off depending on the parameter
/// @param state: if true, switch a random led on (that was off), if false switch a random led off (that was on)
void switchRandomLed(bool state) {

    if (state) {
        //No leds to switch on
        if (getGreenLedsOn() == getGreenLeds()){
            return;
        }

        //Set one random pin on LOW state
        uint8_t randomPin = random(getGreenLeds());
        while (digitalRead(randomPin) == LOW) {
            randomPin = random(getGreenLeds());
        }
        digitalWrite(randomPin, LOW);
    } else {
        //No leds to switch off
        if (getGreenLedsOn() == 0) {
            return;
        }

        //Set one random pin on HIGH state
        uint8_t randomPin = random(getGreenLeds());
        while (digitalRead(randomPin) == HIGH) {
            randomPin = random(getGreenLeds());
        }
        digitalWrite(randomPin, HIGH);
    }
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
