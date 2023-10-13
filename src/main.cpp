#include <Arduino.h>
#include "main.h"
#include "game_system.h"
#include "led_manager.h"
#include "sleep_mode_utility.h"
#include "button_manager.h"

bool printSetupMessage = true;

/// Define the current state of the game
GameState gameState = SETUP;

/// Variables managing timers for events
unsigned long sleepModeStartTime;
unsigned long switchGreenLedsStartTime;
unsigned long gameOverStartTime;

/**
 * T1 is the time after which the green led switch on.
*/
unsigned long T1 = THREE_SECONDS;

/**
 * Player have 10s to start the game or the system go in deep sleep mode.
*/
unsigned long sleepModeTime = TEN_SECONDS;

/// Variable used on not blocking delays
int prevTime = 0;

/// State of the MC phase, true if still have to light up some leds, false otherwise
bool ledsTurningOn = true;

void setup() {
    led_init_output();
    button_init_input();
    sleepModeStartTime = millis();
    Serial.begin(9600);
}

void loop() {
    switch (gameState)
    {
    case SETUP:
        if (printSetupMessage) {
            Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
            printSetupMessage = false;
        }
        switchGreenLeds(false);
        ledFading(RED_LED, true);
        basicTimer(TEN_SECONDS, &sleepModeStartTime, sleepNowTrampoline);
        /* this initialization must bo done before changing state in MC */
        switchGreenLedsStartTime = millis();
        
        if (digitalRead(BUTTON1) == HIGH) {
            gameState = MC;
            Serial.println("GO!");
        }
        break;
    case MC:
        // Two separate phases, when leds are turing on, and when are turning off one by one
        if (ledsTurningOn) {
            basicTimer(T1, &switchGreenLedsStartTime, switchGreenLeds, true);
            ledsTurningOn = false;
            prevTime = millis();
        } else {
            if (millis() - prevTime >= currentT2) {                
                
                // Check if the MC phase is finished
                if (getGreenLedsNumber() == 0) {
                    gameState = PLAYER;
                    break;
                }
                
                //Set one random pin on LOW state
                uint8_t randomPin = random(getGreenLedsNumber());
                while (digitalRead(randomPin) == LOW) {
                    randomPin = random(getGreenLedsNumber());
                }
                digitalWrite(randomPin, LOW);
            }
            
            /* this is one of the last function to launch in this state */
            activateButtonsGameInterrupt();
        /* this initialization must bo done before changing state in PLAYER */
        gameOverStartTime = millis();
        }
        // prevTime reset for the next cycle
        prevTime = millis();    

        break;
    case PLAYER:
        /* here check if the player pressed wrong button */
        /* here check if the player win the game */
        /* this is one of the last function to launch in this state */
        basicTimer(currentT3, &gameOverStartTime, setGameOver);
        /* this is the last function to launch in this state */
        deactivateButtonsGameInterrupt();
        break;
    case NEWLEVEL:
        break;
    case GAMEOVER:
        gameOver(currentLevel);
        gameState = SETUP;
        printSetupMessage = true;
        break;
    default:
        break;
    }
}
/// @brief Call a function if enough time passed
/// @param limitTime is the time after which the function is launched
/// @param startTime is a pointer to a variable representing the start time
/// @param function function to launch
void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)()) {
    if (millis() - *startTime >= limitTime) {
        function();
        *startTime = millis();
    }
}

/// @brief Call a function if enough time passed
/// @param limitTime is the time after which the function is launched
/// @param startTime is a pointer to a variable representing the start time
/// @param function function to launch
/// @param s is the function's parameter
void basicTimer(unsigned long limitTime, unsigned long *startTime, void (*function)(bool), bool s) {
    if (millis() - *startTime >= limitTime) {
        function(s);
        *startTime = millis();
    }
}

void sleepNowTrampoline() {
    Serial.println("Sleep mode actived");
    switchGreenLeds(false);
    switchLed(RED_LED, false);
    sleepNow();
}

void setGameOver() {
    gameState = GAMEOVER;
}