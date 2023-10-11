#include <Arduino.h>
#include "button_manager.h"

const int buttons[] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};
/** 
 * Button pressed index.
*/
int bp;
int inLevelScore = 0;
boolean gameOverFlag = false;

void button_init_input() {
    for (int i = 0; i < getButtonsNumber(); i++) {
        pinMode(buttons[i], INPUT);
    }
}

int getButtonsNumber() {
    return sizeof(buttons) / sizeof(buttons[0]);
}

static void buttonPressed1() {
    buttonPressed(BUTTON1);
}

static void buttonPressed2() {
    buttonPressed(BUTTON2);
}

static void buttonPressed3() {
    buttonPressed(BUTTON3);
}

static void buttonPressed4() {
    buttonPressed(BUTTON4);
}

void activateButtonsGameInterrupt() {
    bp = -1;
    attachInterrupt(digitalPinToInterrupt(BUTTON1), buttonPressed1, HIGH);
    attachInterrupt(digitalPinToInterrupt(BUTTON2), buttonPressed2, HIGH);
    attachInterrupt(digitalPinToInterrupt(BUTTON3), buttonPressed3, HIGH);
    attachInterrupt(digitalPinToInterrupt(BUTTON4), buttonPressed4, HIGH);
}

void deactivateButtonsGameInterrupt() {
    for (int i = 0; i < getButtonsNumber(); i++) {
        detachInterrupt(buttons[i]);
    }
}

void buttonPressed(int buttonPin) {
    bp++;
    if (buttonPin == buttons[bp]) {
        inLevelScore++;
    } else if (buttonPin != buttons[bp]) {
        gameOverFlag = true;
    }
}
