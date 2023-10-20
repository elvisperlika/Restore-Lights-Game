#include "Arduino.h"
#include "button_manager.h"
#include "led_manager.h"
#include <avr/sleep.h>

#include <EnableInterrupt.h>

#define DEBOUNCE_DELAY 100 // in ms
const int8_t buttons[] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};
uint32_t lastInterruptTime = 0;
uint8_t led_status = 0;
// vector of order of the switched pins
int8_t pressedBtn[4]; // !! rendilo dinamico con la malloc
int8_t pressedButton;
int8_t btnPressedCounter = 0;

int8_t buttonPressedIndex;

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
}

int getButtonsNumber() {
    return sizeof(buttons) / sizeof(buttons[0]);
}

void activateButtonsGameInterrupt() {
    pressedButton = -1;
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

void buttonPressed(int8_t btnIndex) {    
    if (checkBouncing()) {
        pressedButton = btnIndex;
        btnPressedCounter++;
    }
}

bool checkBouncing() {
    unsigned long interruptTime = millis();
    if (millis() - lastInterruptTime > DEBOUNCE_DELAY) {
        return true;
    }
    lastInterruptTime = interruptTime;
    return false;
}

int8_t* getPressedBtn() {
    return pressedBtn;
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

int8_t getPressedButton() {
    return pressedButton;
}
