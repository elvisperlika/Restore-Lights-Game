#include <Arduino.h>

/// @brief This function is a trampoline to the sleepNow() function.
void sleepNowTrampoline();

/// @brief Set the game state to GAMEOVER (used with an iterrupt).
void setGameOver();