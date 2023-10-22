#include "Arduino.h"
#include "button_manager.h"
#include "led_manager.h"
#include <avr/sleep.h>

#include <EnableInterrupt.h>

#define BUTTON_DELAY 1000 // in ms

/// Array of millisecs to keep track of the last interrupt call on each button
unsigned long* lastInterruptTime;

/// Array to map button's index to button's pin
const uint8_t buttons[] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};

/// Index of the next button to press
uint8_t buttonPressedIndex;
uint8_t led_status = 0;

/// Number of button pressed
int8_t lastButtonPressedIndex;

void buttonPressed1() {
    buttonPressed(0);
}

void buttonPressed2() {
    buttonPressed(1);
}

void buttonPressed3() {
    buttonPressed(2);
}

void buttonPressed4() {
    buttonPressed(3);
}

void buttonsInit() {
    for (int i = 0; i < getButtonsNumber(); i++) {
        pinMode(buttons[i], INPUT);
    }

    lastButtonPressedIndex = -1;
    lastInterruptTime = (unsigned long*)calloc(getButtonsNumber(), sizeof(unsigned long));
}

int getButtonsNumber() {
    return sizeof(buttons) / sizeof(buttons[0]);
}

void activateButtonsGameInterrupt() {
    lastButtonPressedIndex = -1;
    enableInterrupt(BUTTON1, buttonPressed1, RISING);
    enableInterrupt(BUTTON2, buttonPressed2, RISING);
    enableInterrupt(BUTTON3, buttonPressed3, RISING);
    enableInterrupt(BUTTON4, buttonPressed4, RISING);
}

void deactivateButtonsGameInterrupt() {
    for (int i = 0; i < getButtonsNumber(); i++) {
        disableInterrupt(buttons[i]);
    }
}

void buttonPressed(uint8_t buttonIndex) {
    if (checkBouncing(buttonIndex)) {
        lastButtonPressedIndex = buttonIndex;
    }
}

int8_t getLastButtonPressedIndex() {
    int8_t lastButtonPressedIndexCopy = lastButtonPressedIndex;
    lastButtonPressedIndex = -1;
    return lastButtonPressedIndexCopy;
}

bool checkBouncing(uint8_t buttonIndex) {
    unsigned long interruptTime = millis();

    if (interruptTime - lastInterruptTime[buttonIndex] < BUTTON_DELAY) {
        return false;
    }

    lastInterruptTime[buttonIndex] = interruptTime;

    return true;
}

void sleepNow() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    
    for (int i = 0; i < getButtonsNumber(); i++) {
        enableInterrupt(buttons[i], wakeUpNow, RISING);
    }
    
    sleep_mode();
    sleep_disable();    

    for (int i = 0; i < getButtonsNumber(); i++) {
        disableInterrupt(buttons[i]);
        lastInterruptTime[i] = millis();
    }
    activateButtonsGameInterrupt();
}

void wakeUpNow(){};