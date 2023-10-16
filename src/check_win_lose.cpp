#include <Arduino.h>
#include "check_win_lose.h"
#include "button_manager.h"

//I take the level score variable from button_manager.cpp
int flag = inScoreLevelGetter();
//I checl if the player won or not
int checkWinLose(flag) {
    if(flag == 4) {
        return 0; //The player won
    }
    else {
        return 1; //The player lost
    }
}
//I print the correct message in the two case
void printMessage() {
    if(checkWinLose(flag) == 0) {//If the player won...
        Serial.println("You WIN");
    }
    else {
        Serial.println("You LOSE");
    }
}
