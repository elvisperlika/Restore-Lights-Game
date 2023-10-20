#ifndef __BUTTON_MANAGER_H__
#define __BUTTON_MANAGER_H__

#include "Arduino.h"

#define BUTTON1 7
#define BUTTON2 8
#define BUTTON3 9
#define BUTTON4 10

extern const uint8_t buttons[];

/// @brief Initialize buttons as input.
void buttonsInit();

/// @brief Get the number of buttons.
/// @return the number of buttons.
int getButtonsNumber();

/// @brief Attach a buttonPressed function as interrupt to each button.
void activateButtonsGameInterrupt();

/// @brief Detach interrupts from each button.
void deactivateButtonsGameInterrupt();

/// @brief Check if has been pressed the correct button.
/// @param buttonIndex index of the button to check.
void buttonPressed(uint8_t buttonIndex);

/// @brief Check if the interrupt is probably due to a bouncing problem.
/// @param btnId Index of the button to check the bouncing on.
/// @return true if there are no bouncing problem, false if is probably bouncing.
bool checkBouncing(uint8_t buttonIndex);

/// @brief Get the last pressed button.
/// @return the index of the last pressed button.
int8_t getLastButtonPressedIndex();

/// @brief Activate deep sleep mode and set the interrupt to wake up the system for each button.
void sleepNow();

/// @brief Empty function to wake up from interrupt.
void wakeUpNow();

#endif
