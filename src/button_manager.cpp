#include "Arduino.h"
#include "button_manager.h"
#include "led_manager.h"
#include <avr/sleep.h>

#include <EnableInterrupt.h>

#define DEBOUNCE_DELAY 100 // in ms

/// Array of millisecs to keep track of the last interrupt call on each btn
unsigned long* lastInterruptTime;

/// Array to map btn's index to btn's pin
const uint8_t btns[] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};

/// Array of the btns pressed pins to keep track of the pressed order
uint8_t* pressedBtns;

// Index of the next btn to press
uint8_t btnPressedIndex;
uint8_t led_status = 0;
/// Number of btn pressed
uint8_t btnPressedCounter = 0;

void btnPressed1() {
    btnPressed(0);
}

void btnPressed2() {
    btnPressed(1);
}

void btnPressed3() {
    btnPressed(2);
}

void btnPressed4() {
    btnPressed(3);
}

void btnsInit() {
    for (int i = 0; i < getBtnsNumber(); i++) {
        pinMode(btns[i], INPUT);
    }

    lastInterruptTime = (unsigned long*)malloc(getBtnsNumber() * sizeof(unsigned long));
    pressedBtns = (uint8_t*)malloc(getBtnsNumber() * sizeof(uint8_t));
}

int getBtnsNumber() {
    return sizeof(btns) / sizeof(btns[0]);
}

void activateBtnsGameInterrupt() {
    pressedBtn = -1;
    btnPressedIndex = -1;
    enableInterrupt(BUTTON1, btnPressed1, RISING);
    enableInterrupt(BUTTON2, btnPressed2, RISING);
    enableInterrupt(BUTTON3, btnPressed3, RISING);
    enableInterrupt(BUTTON4, btnPressed4, RISING);
}

void deactivateBtnsGameInterrupt() {
    for (int i = 0; i < getBtnsNumber(); i++) {
        disableInterrupt(btns[i]);
    }
}

void btnPressed(int8_t btnIndex) {    
    if (checkBouncing()) {
        pressedBtn[btnPressedCounter] = btnIndex;
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
    
    for (int i = 0; i < getBtnsNumber(); i++) {
        enableInterrupt(btns[i], wakeUpNow, RISING);
    }    
    
    sleep_mode();
    sleep_disable();    

    for (int i = 0; i < getBtnsNumber(); i++) {
        disableInterrupt(btns[i]);
    }
}

void wakeUpNow(){};

int8_t getPressedBtn() {
    return pressedBtn;
}
