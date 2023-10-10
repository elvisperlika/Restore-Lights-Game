#include "button_manager.h"

const int buttons[] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};


int getButtonsNumber() {
    return sizeof(buttons) / sizeof(buttons[0]);
}
