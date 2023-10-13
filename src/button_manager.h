#ifndef __BUTTON_MANAGER_H__
#define __BUTTON_MANAGER_H__
#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 10
#define BUTTON4 11

/// @brief Initialize buttons as input.
void buttonsInit();

/// @brief Buttons number getter.
/// @return the number of buttons.
int getButtonsNumber();

/// @brief Attach interrupts to each button.
void activateButtonsGameInterrupt();

/// @brief Detach interrupts from each button.
void deactivateButtonsGameInterrupt();

/// @brief Check if has been pressed the correct button.
/// @param buttonPin button pin to check.
/// @return true if the button was correct, false if it was wrong.
bool buttonPressed(int buttonPin);

#endif
