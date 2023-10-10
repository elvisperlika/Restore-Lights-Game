#include <Arduino.h>
#include "game_system.h"
#include "led_menager.h"
#include "sleep_mode_utility.h"

#define TEN_SECONDS 10000
#define THREE_SECONDS 3000
GameState gameState = SETUP;

/**
 * This timer launch method after a certain time.
 * @param time time in milliseconds
 * @param function function to launch
*/
void basicTimer(unsigned long time, void (*function)(boolean), boolean s);

/**
 * Print a string one time.
 * @param s string to print
*/
void printStringOneTime(String s);

unsigned long sleepModeStartTime = millis();
unsigned long T1 = millis();
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
        basicTimer(TEN_SECONDS, sleepNowTrampoline, true);
        break;
    case MC:
        basicTimer(THREE_SECONDS, switchGreenLeds, true);
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

void basicTimer(unsigned long time, void (*function)(boolean), boolean s) {
    if (millis() - sleepModeStartTime >= time) {
        Serial.println("Switch on green leds");
        function(s);
    }
}

static void sleepNowTrampoline(boolean s) {
    sleepNow();
}

void printStringOneTime(String s) {
    static boolean printed = false;
    if (!printed) {
        Serial.println(s);
        printed = true;
    }
}
