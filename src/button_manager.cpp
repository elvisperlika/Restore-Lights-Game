#include <Arduino.h>
#include "button_manager.h"

const int buttons[] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};
/** 
 * Button pressed index.
*/
int bp;
int inLevelScore = 0;
boolean gameOverFlag = false;

int getButtonsNumber() {
    return sizeof(buttons) / sizeof(buttons[0]);
}

void activateButtonsGameInterrupt() {
    bp = -1;
    attachInterrupt(buttons[0], buttonPressed1, HIGH);
    attachInterrupt(buttons[1], buttonPressed2, HIGH);
    attachInterrupt(buttons[2], buttonPressed3, HIGH);
    attachInterrupt(buttons[3], buttonPressed4, HIGH);
}

void buttonPressed1() {
    buttonPressed(BUTTON1);
}

void buttonPressed2() {
    buttonPressed(BUTTON2);
}

void buttonPressed3() {
    buttonPressed(BUTTON3);
}

void buttonPressed4() {
    buttonPressed(BUTTON4);
}

void buttonPressed(int buttonPin) {
    bp++;
    if (buttonPin == buttons[bp]) {
        inLevelScore++;
    } else if (buttonPin != buttons[bp]) {
        gameOverFlag = true;
    }
}
