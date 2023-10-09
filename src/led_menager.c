#include <Arduino.h>
#include "led_menager.h"

const int greenLeds[] = {GREEN_LED1, GREEN_LED2, GREEN_LED3, GREEN_LED4};

int getGreenLedsNumber() {
    int size = sizeof(greenLeds) / sizeof(greenLeds[0]);
}

void led_init_output() {
    int leds[] = {GREEN_LED1, GREEN_LED2, GREEN_LED3, GREEN_LED4, RED_LED};
    int size = sizeof(leds) / sizeof(leds[0]);
    for (int i = 0; i < size; i++)
    {
        pinMode(leds[i], OUTPUT);
    }
}

void switchGreenLeds(boolean state) {
    int value = (state == true) ? HIGH : LOW;
    for (int i = 0; i < getGreenLedsNumber(); i++) {
        digitalWrite(greenLeds[i], value);
    }
}

void switchLed(uint8_t ledPin, boolean state) {
    digitalWrite(ledPin, (state == true) ? HIGH : LOW);
}

void ledFading(uint8_t ledPin, boolean state) {
    if (state == true) {
        static int currIntensity = 0;
        static fadeAmount = 5;
        analogWrite(ledPin, currIntensity);   
        currIntensity = currIntensity + fadeAmount;
        if (currIntensity == 0 || currIntensity == 255) {
            fadeAmount = -fadeAmount; 
        }     
        delay(15);
    } else {
        digitalWrite(ledPin, LOW);
    }
}
