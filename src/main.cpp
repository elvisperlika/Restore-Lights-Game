#include <Arduino.h>
#include "main.h"
#include "game_system.h"
#include "led_manager.h"
#include "sleep_mode_utility.h"
#include "button_manager.h"

/// 
unsigned long sleepModeStartTime;
unsigned long switchGreenLedsStartTime;
unsigned long gameOverStartTime;

//Current session variables
int currentDifficulty = 0;
int currentLevel = 0;

int currentT2 = INITIAL_T2;
int currentT3 = INITIAL_T3;

bool printSetupMessage = true;

// Define the current state of the game
GameState gameState = SETUP;

/**
 * T1 is the time after which the green led switch on.
*/
unsigned long T1 = THREE_SECONDS;
/**
 * T2 is the interval time between the led's switching off.
*/
unsigned long T2;
/**
 * T3 is the time that the player have to complete the pattern.
*/
unsigned long T3;
unsigned long points;
/**
 * Player have 10s to start the game or the system go in deep sleep mode.
*/
unsigned long sleepModeTime = TEN_SECONDS;

// Variable used on not blocking delays
int prevTime = 0;

// State of the MC phase, true if still have to light up some leds, false otherwise
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
        basicTimer(TEN_SECONDS, sleepModeStartTime, sleepNowTrampoline, true);
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
            basicTimer(T1, switchGreenLedsStartTime, switchGreenLeds, true);
            ledsTurningOn = false;
            prevTime = millis();
        } else {
            // !! Invece che una call alla funzione dovrebbe esserci una var currentT2
            if (millis() - prevTime >= CalculateT2(currentLevel, currentDifficulty)) {                
                
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
        basicTimer(T3, gameOverStartTime, setGameOver, true);
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

void basicTimer(unsigned long limitTime, unsigned long startTime, void (*function)(bool), bool s) {
    if (millis() - startTime >= limitTime) {
        function(s);
        startTime = millis();
    }
}

static void sleepNowTrampoline(bool s) {
    Serial.println("Sleep mode actived");
    switchGreenLeds(false);
    switchLed(RED_LED, false);
    sleepNow();
}

void setGameOver(bool s) {
    gameState = GAMEOVER;
}