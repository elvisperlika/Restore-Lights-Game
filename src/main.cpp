#include <Arduino.h>
#include "game_system.h"
#include "led_menager.h"
#include "sleep_mode_utility.h"
#include "button_manager.h"
#include "game_over.h"

#define TEN_SECONDS 10000
#define THREE_SECONDS 3000
GameState gameState = SETUP;

/**
 * Set the game state to GAMEOVER.
 * @param s is not used, it's only to respect the function's signature.
*/
void setGameOver(boolean s);

/**
 * This timer launch method after a certain time.
 * @param limitTime is the time after which the function is launched
 * @param startTime is the time when the timer start
 * @param function function to launch
 * @param s is the function's parameter 
*/
void basicTimer(unsigned long limitTime, unsigned long startTime, void (*function)(boolean), boolean s);

/**
 * Print a string one time if the field 'printed' is false.
 * If you wont to print the string again, you have to set the field 'printed' to false.
 * @param s string to print
*/
void printStringOneTime(String s);

/**
 * This function is a trampoline to the sleepNow() function.
 * @param s is not used, it's only to respect the function's signature.
*/
static void sleepNowTrampoline(boolean s);

static boolean printed = false;

unsigned long sleepModeStartTime;
unsigned long switchGreenLedsStartTime;
unsigned long gameOverStartTime;

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

void gameOver(boolean s) {
    gameState = GAMEOVER;
}

void loop() {
    switch (gameState)
    {
    case SETUP:
        printStringOneTime("Welcome to the Restore the Light Game. Press Key B1 to Start");
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
        gameOver(points);
        gameState = SETUP;
        break;
    default:
        break;
    }
}

void basicTimer(unsigned long limitTime, unsigned long startTime, void (*function)(boolean), boolean s) {
    if (millis() - startTime >= limitTime) {
        function(s);
        startTime = millis();
    }
}

void printStringOneTime(String s) {
    if (!printed) {
        Serial.println(s);
        printed = true;
    }
}

static void sleepNowTrampoline(boolean s) {
    Serial.println("Sleep mode actived");
    switchGreenLeds(false);
    switchLed(RED_LED, false);
    sleepNow();
}

void setGameOver(boolean s) {
    gameState = GAMEOVER;
}
