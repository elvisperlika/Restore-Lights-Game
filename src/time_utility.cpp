#include "time_utility.h"



void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)()) {
    if (millis() - *startTime >= limitTime) {
        function();
        *startTime = millis();
    }
}
