#include <Arduino.h>
#include "button_manager.h"
#include "game_system.h"

const int buttons[] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};

/// Button pressed index, used to know how many button still need to press, to finish the game 
int buttonPressedIndex;

/// @brief Function to attach to button 1
void buttonPressed1() {
    buttonPressed(BUTTON1);
}

/// @brief Function to attach to button 2
void buttonPressed2() {
    buttonPressed(BUTTON2);
}

/// @brief Function to attach to button 3
void buttonPressed3() {
    buttonPressed(BUTTON3);
}

/// @brief Function to attach to button 4
void buttonPressed4() {
    buttonPressed(BUTTON4);
}

/// @brief Initialize buttons as input.
void buttonsInit() {
    for (int i = 0; i < getButtonsNumber(); i++) {
        pinMode(buttons[i], INPUT);
    }
}

/// @brief Buttons number getter.
/// @return the number of buttons.
int getButtonsNumber() {
    return sizeof(buttons) / sizeof(buttons[0]);
}

/// @brief Attach interrupts to each button.
void activateButtonsGameInterrupt() {
    buttonPressedIndex = -1;
    attachInterrupt(digitalPinToInterrupt(BUTTON1), buttonPressed1, HIGH);
    attachInterrupt(digitalPinToInterrupt(BUTTON2), buttonPressed2, HIGH);
    attachInterrupt(digitalPinToInterrupt(BUTTON3), buttonPressed3, HIGH);
    attachInterrupt(digitalPinToInterrupt(BUTTON4), buttonPressed4, HIGH);
}

/// @brief Detach interrupts from each button.
void deactivateButtonsGameInterrupt() {
    for (int i = 0; i < getButtonsNumber(); i++) {
        detachInterrupt(buttons[i]);
    }
}

/// @brief Check if has been pressed the correct button.
/// @param buttonPin button pin to check.
/// @return true if the button was correct, false if it was wrong.
bool buttonPressed(int buttonPin) {    
    if (buttonPin != buttons[buttonPressedIndex]) {
        return false;
    }
    
    buttonPressedIndex++;
    return true;
}