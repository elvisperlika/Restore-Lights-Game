#include "game_engine.h"

#include <Arduino.h>
#include "button_manager.h"
#include "led_manager.h"
#include "potenziometer_manager.h"
#include "time_utility.h"

/// Array of each decrease rate for each difficulty.
static const float DECREASE_RATES[] = {0.05, 0.07, 0.09, 0.11};

/// Current Player level (score) and best player's score
static int currentLevel;
static int bestScore;

/// Array containing the order of the leds switched off
static uint8_t* ledsOffOrdered;
static int currentLedId;

const unsigned long T1_TIME = INITIAL_T1;
unsigned long T1_StartTime; 

unsigned long T2_TIME;
unsigned long T2_StartTime;

unsigned long T3_TIME;
unsigned long T3_StartTime;

unsigned long ResetGame_TIME;
unsigned long ResetGame_StartTime;

unsigned long SleepMode_TIME;
unsigned long SleepMode_StartTime;

void boardInit() {
    ledsInit();
    buttonsInit();
    potentiometerInit();
    ResetGame_TIME = RESET_GAME_TIME;
    SleepMode_TIME = SLEEP_MODE_TIME;
    ledsOffOrdered = (uint8_t*)calloc(getGreenLedsNumber(), sizeof(uint8_t));
}

void gameSetup() {
    Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
    SleepMode_StartTime = millis();
    activateButtonsGameInterrupt();
}

void initializationAllert() {
    ledFading(RED_LED);
}

bool checkStartGame() {
    int8_t var = getLastButtonPressedIndex();
    return var == 0 ? true : false;
}

void levelInit(uint8_t difficulty) {
    T2_TIME = CalculateNewT(INITIAL_T2, DECREASE_RATES[difficulty], currentLevel);
    T3_TIME = CalculateNewT(INITIAL_T3, DECREASE_RATES[difficulty], currentLevel);
    currentLedId = getGreenLedsNumber() - 1;
    srand(millis());
}

void gameInit() {
    ResetGame_TIME = RESET_GAME_TIME;
    SleepMode_TIME = SLEEP_MODE_TIME;    
    currentLevel = 0;
    bestScore = 0;
    switchLed(RED_LED, false);
    levelInit(getDifficulty());
    
    Serial.println("GO!"); 
}

void ledsOn(bool s) {
    switchGreenLeds(s);
    ledsOnFlag = true;
}

bool checkLightsOn() {
    return checkLedsOn();
}

void disableRandomLed() {

    ledsOffOrdered[currentLedId] = switchRandomLedOff();
    currentLedId--;
}

bool checkPatternCreated() {
    // note: the counter starts from getGreenLedsNumber and goes -1 for each led switched off
    if (currentLedId == -1)
    {
        return true;
    }
    return false;    
}

void activateGameControls() {
    activateButtonsGameInterrupt();
}

GameState checkGameStatus() {
    int8_t lastButtonPressedIndex = getLastButtonPressedIndex();
    if (lastButtonPressedIndex != -1) {
        currentLedId++;
        if (ledsOffOrdered[currentLedId] == lastButtonPressedIndex) {
            switchLedByIndex(ledsOffOrdered[currentLedId], true);
            if (currentLedId == getGreenLedsNumber() - 1) {
                return NEW_LEVEL;
            }
        } else {
            return GAMESCORE;
        }
    }
    return PLAYER;
}

void levelPassed() {
    currentLevel++;
    Serial.println("Newpoint!");
    Serial.print("Score: ");
    Serial.println(currentLevel);
    //note: is possible to change game difficulty runtime by potentiometer
    levelInit(getDifficulty());
}

void showGameScore() {
    switchGreenLeds(false);

    Serial.println("Game Over.");
    Serial.print("Final Score: ");
    Serial.println(currentLevel);

    if (currentLevel > bestScore) {
        bestScore = currentLevel;
        Serial.println("NEW BEST SCORE!");
    }
}

void showGameOverAllert() {
    switchGreenLeds(false);
    switchLed(RED_LED, true);
}

void deactivateGameControls() {
    deactivateButtonsGameInterrupt();
}

void sleepMode() {
    switchLed(RED_LED, false);
    deactivateButtonsGameInterrupt();
    sleepNow();
}