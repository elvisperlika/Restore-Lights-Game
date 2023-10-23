#include "time_utility.h"

//Euler's constant
static const float E = 2.7182818284;

void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)()) {
    if (millis() - *startTime >= limitTime) {
        function();
        *startTime = millis();
    }
}

void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)(bool), bool s) {
    if (millis() - *startTime >= limitTime) {
        function(s);
        *startTime = millis();
    }
}

float CalculateNewT(unsigned long initialT, float decreaseRatio, uint8_t level) {
     return initialT * pow(E, -decreaseRatio * level);
}