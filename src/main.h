#include <Arduino.h>

#define TEN_SECONDS 10000
#define THREE_SECONDS 3000

/// @brief Set the game state to GAMEOVER.
/// @param s 
void setGameOver(bool s);

/// @brief Call a function if enough time passed
/// @param limitTime is the time after which the function is launched
/// @param startTime is a pointer to a variable representing the start time
/// @param function function to launch
/// @param s is the function's parameter
void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)(bool), bool s);

/// @brief Call a function if enough time passed
/// @param limitTime is the time after which the function is launched
/// @param startTime is a pointer to a variable representing the start time
/// @param function function to launch
void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)());


/// @brief This function is a trampoline to the sleepNow() function.
/// @param s is not used, it's only to respect the function's signature.
static void sleepNowTrampoline(bool s);