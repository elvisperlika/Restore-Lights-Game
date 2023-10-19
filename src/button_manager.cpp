#include "Arduino.h"
#include "button_manager.h"
#include <avr/sleep.h>

#include <EnableInterrupt.h>

#define DEBOUNCE_DELAY 100 // in ms
const int8_t buttons[] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};
uint32_t last_interrupt_time = 0;
uint8_t led_status = 0;
int8_t pressedBtn[4] = {0, 0, 0, 0};
int8_t btnPressedCounter = 0;

int8_t buttonPressedIndex;

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

void buttonPressed(int8_t btnIndex) {    
    if (checkBouncing()) {
        pressedBtn[btnPressedCounter] = btnIndex;
        btnPressedCounter++;
    }
}


int8_t* getPressedBtn() {
    return pressedBtn;
}

bool checkBouncing() {
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE_DELAY) {
        return false;
    }
    last_interrupt_time = interrupt_time;
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
