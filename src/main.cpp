#include <Arduino.h>
#include "game_system.h"
#include "led_menager.h"
#include "sleep_mode_utility.h"

#define TEN_SECONDS 10000
GameState gameState = SETUP;

/**
 * Check if the time is expired.
*/
boolean sleepModeTimer(unsigned long time);

/**
 * Print a string one time.
*/
void printStringOneTime(String s);

unsigned long sleepModeStartTime = millis();
/**
 * Player have 10s to start the game or the system go in deep sleep mode.
*/
unsigned long sleepModeTime = TEN_SECONDS;

void setup() {
    led_init_output();
    Serial.begin(9600);
}

void loop() {
    switch (gameState)
    {
    case SETUP:
        printStringOneTime("Welcome to the Restore the Light Game. Press Key B1 to Start");
        switchGreenLeds(false);
        ledFading(RED_LED, true);
        if (sleepModeTimer(sleepModeTime)) {
            sleepNow();
        }
        break;
    case MC:
        break;
    case PLAYER:
        break;
    case NEWLEVEL:
        break;
    case GAMEOVER:
        break;
    default:
        break;
    }
    delay(1000);
}

boolean sleepModeTimer(unsigned long time) {
    if (millis() - sleepModeStartTime >= time) {
        Serial.println("Deep sleep mode");
        return true;
    }
    return false;
}

void printStringOneTime(String s) {
    static boolean printed = false;
    if (!printed) {
        Serial.println(s);
        printed = true;
    }
}