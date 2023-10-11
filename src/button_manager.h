#ifndef __BUTTON_MANAGER_H__
#define __BUTTON_MANAGER_H__
#define BUTTON1 7
#define BUTTON2 8
#define BUTTON3 9
#define BUTTON4 10

/**
 * Buttons number getter.
*/
int getButtonsNumber();

/**
 * Activate buttons interrupt util to game.
 * Set the variable 'bp' to -1.
*/
void activateButtonsGameInterrupt();

/**
 * Check if is the correct button to press.
 * @param buttonPin button pin to check.
*/
void buttonPressed(int buttonPin);


#endif
