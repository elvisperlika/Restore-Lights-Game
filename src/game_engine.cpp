#include "game_engine.h"

#include <Arduino.h>
#include "button_manager.h"
#include "led_manager.h"
#include "potenziometer_manager.h"
#include "time_utility.h"

/// Array of each decrease rate for each difficulty.
const float DECREASE_RATES[] = {0.05, 0.07, 0.09, 0.11};

/// Current Player level (score) and best player's score
static int currentLevel;
static int bestScore;

/// TO DOCUMENT (flags 🤢)
bool ledsOnFlag = false;
int currentLedId = 0;

/// Led's id turning off order ~~~~~~
uint8_t ledsOffOrdered[] = {0, 0, 0, 0};

/// Defining time vaiables
/// Time passed after pressing B1 and before turning all green leds on
unsigned long T1_TIME;
unsigned long T1_StartTime; 

/// Initial leds turning off time and the session related variable
unsigned long T2_TIME;
unsigned long T2_StartTime;

/// Initial time Player have to finish the level on easiest difficulty, and the serrion related variable
unsigned long T3_TIME;
unsigned long T3_StartTime;

unsigned long ResetGame_TIME = RESET_GAME_TIME;
unsigned long ResetGame_StartTime;

unsigned long SleepMode_TIME = SLEEP_MODE_TIME;
unsigned long SleepMode_StartTime;

void boardInit() {
    ledsInit();
    buttonsInit();
    potentiometerInit();
}

void gameSetup() {
    Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
    SleepMode_StartTime = millis();
}

void initializationAllert() {
    ledFading(RED_LED);
}

bool checkStartGame() {
    return digitalRead(BUTTON1) == HIGH ? true : false;
}

void levelInit(uint8_t difficulty) {
    T1_TIME = INITIAL_T1;
    T2_TIME = CalculateNewT(INITIAL_T2, DECREASE_RATES[difficulty], currentLevel);
    T3_TIME = CalculateNewT(INITIAL_T3, DECREASE_RATES[difficulty], currentLevel);
    currentLedId = getButtonsNumber() - 1;
}

void gameInit() {
    switchLed(RED_LED, false);
    currentLevel = 0;
    bestScore = 0;
    levelInit(getDifficulty());
}

void ledsOn(bool s) {
    switchGreenLeds(s);
    ledsOnFlag = true;
}

bool checkLedsOn() {
    bool tmp = ledsOnFlag;
    ledsOnFlag = false;
    return tmp;
}

void disableRandomLed() {
    ledsOffOrdered[currentLedId] = switchRandomLedOff();
    currentLedId--;
}

bool checkPatternCreated() {
    // TO DO
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
    Serial.print("PressedButton: ");
    Serial.println(getPressedButton());
    digitalWrite(getButtonsNumber(), HIGH);
    return PLAYER;
}

void levelPassed() {
    currentLevel++;
    //note: is possible to change game difficulty runtime
    levelInit(getDifficulty());
}

void showGameScore() {
    Serial.print("Game Over. Final Score: ");
    Serial.println(currentLevel);

    if (currentLevel > bestScore) {
        bestScore = currentLevel;
        Serial.println("NEW BEST SCORE!");
    }
}

void showGameOverAllert() {
    ledFading(RED_LED);
}

void deactivateGameControls() {
    deactivateButtonsGameInterrupt();
}

void sleepMode() {
    Serial.println("Sleep mode actived");
    delay(100);
    switchLed(RED_LED, false);
    sleepNow();
}




