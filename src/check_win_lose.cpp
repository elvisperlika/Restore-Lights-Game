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
    if(checkWinLose(inLevelScoreGetter()) == 0) {//If the player won...
        Serial.println("You WIN");
    }
    else {
        Serial.println("You LOSE");
    }
}
//I reduce the time of T2 and T3 by a factor F defined by the potentiometer
void reduceT2T3(unsigned long time2, unsigned long time3) {
    unsigned long F = analogRead(potentiometerPin) / 1023.0;
    time2 = time2 * F;
    time3 = time3 * F;
}