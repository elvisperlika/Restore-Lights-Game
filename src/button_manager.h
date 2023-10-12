#ifndef __BUTTON_MANAGER_H__
#define __BUTTON_MANAGER_H__
#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 10
#define BUTTON4 11

/**
 * Initialize buttons as input.
*/
void button_init_input();

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

/**
 * Deactivate buttons interrupt util to game.
*/
void deactivateButtonsGameInterrupt();

int inLevelScoreGetter();

#endif
