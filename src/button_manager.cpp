#include "Arduino.h"
#include "button_manager.h"
#include <avr/sleep.h>

#include <EnableInterrupt.h>

#define DEBOUNCE_DELAY 100 // in ms

/// Array of millisecs to keep track of the last interrupt call on each button
unsigned long* lastInterruptTime;

/// Array to map button's index to button's pin
const uint8_t buttons[] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};

/// Array of the buttons pressed pins to keep track of the pressed order
uint8_t* pressedButtons;

// Index of the next button to press
uint8_t buttonPressedIndex;

/// Number of button pressed
uint8_t buttonPressedCounter = 0;

void buttonPressed1() {
    buttonPressed(1);
}

void buttonPressed2() {
    buttonPressed(2);
}

void buttonPressed3() {
    buttonPressed(3);
}

void buttonPressed4() {
    buttonPressed(4);
}

void buttonsInit() {
    for (int i = 0; i < getButtonsNumber(); i++) {
        pinMode(buttons[i], INPUT);
    }

    lastInterruptTime = (unsigned long*)malloc(getButtonsNumber() * sizeof(unsigned long));
    pressedButtons = (uint8_t*)malloc(getButtonsNumber() * sizeof(uint8_t));
}

int getButtonsNumber() {
    return sizeof(buttons) / sizeof(buttons[0]);
}

void activateButtonsGameInterrupt() {
    buttonPressedIndex = -1;
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
        pressedButtons[buttonPressedCounter] = buttonIndex;
        buttonPressedCounter++;
    }
}

uint8_t* getPressedButton() {
    return pressedButtons;
}

bool checkBouncing(uint8_t buttonIndex) {
    unsigned long interruptTime = millis();
    if (interruptTime - lastInterruptTime[buttonIndex] > DEBOUNCE_DELAY) {
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
    }
}

void wakeUpNow(){};
