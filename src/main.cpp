#include <Arduino.h>
#include "game_system.h"
#include "led_menager.h"
#include "sleep_mode_utility.h"

GameState gameState = SETUP;

unsigned long sleepModeStartTime = millis();
/**
 * Player have 10s to start the game or the system go in deep sleep mode.
*/
unsigned long sleepModeTime = 10000;

void setup() {
    led_init_output();
    Serial.begin(9600);
}

void loop() {
    switch (gameState)
    {
    case SETUP:
        Serial.println("Press the Button 0 to start the game");
        switchGreenLeds(false);
        ledFading(RED_LED, true);
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

void sleepModeTimer(unsigned long time) {
    if (millis() - sleepModeStartTime >= time) {
        Serial.println("Deep sleep mode");
        sleepNow();
    }
}
