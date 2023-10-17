#include "Arduino.h"
#include "button_manager.h"

#include <EnableInterrupt.h>

#define DEBOUNCE_DELAY 100 // in ms
const int8_t buttons[] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};
uint32_t last_interrupt_time = 0;
uint8_t led_status = 0;

/// Button pressed index, used to know how many button still need to press, to finish the game 
int8_t buttonPressedIndex;

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
    enableInterrupt(BUTTON1, isr_handler, RISING);
}

/// @brief Detach interrupts from each button.
void deactivateButtonsGameInterrupt() {
    for (int i = 0; i < getButtonsNumber(); i++) {
        disableInterrupt(buttons[i]);
    }
}

/// @brief Check if has been pressed the correct button.
/// @param buttonPin button pin to check.
/// @return true if the button was correct, false if it was wrong.
bool buttonPressed(int8_t buttonPin) {    
    if (buttonPin != buttons[buttonPressedIndex]) {
        return false;
    }
    
    buttonPressedIndex++;
    return true;
}

void isr_handler() {
  uint32_t interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > DEBOUNCE_DELAY) {
    led_status = !led_status;
  }

  last_interrupt_time = interrupt_time;
}
