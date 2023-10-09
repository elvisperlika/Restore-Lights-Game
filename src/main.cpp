#include <Arduino.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"

GameState state;

const unsigned long QUARTER_SECOND = 1000 / 4;
const unsigned long SIXTEENTH_SECOND = 1000 / 16;

/** 
 * Leds pin number (OUTPUT)
*/
int leds[] = {2, 3, 4, 5};
const int N_LEDS = sizeof(leds) / sizeof(leds[0]);

/** 
 * Variabili per il controllo della difficoltà del livello (potenziometro)
*/
const int POT_PIN = A0;

/**
 * Buttons pin numbers (INPUT)
*/
int buttons[N_LEDS] = {6, 7, 8, 9};

/**
 * Leds to switch on.
*/
int ledsToHigh[N_LEDS];
int nLedsOn = N_LEDS - 1;

int nLightsOff = 0;

int currentCorrectLeds = 0;

//Variabili per il controllo del tempo di gioco
unsigned long startTime;
//Tempo di gioco del primo livello
unsigned long initialTime = 10000;
//Tempo di gioco del livello corrente
unsigned long timeToPlay = 10000;
//Tasso di decadimento del tempo del livello
const double DECRESE_RATE = 0.05;

unsigned long mcDiffTime = 0;

//Livello corrente di gioco
int level = 1;

void setup() {  
    state = MC;

    for (int i = 0; i < N_LEDS; i++) {
        pinMode(leds[i], OUTPUT);
        pinMode(buttons[i], INPUT);
        digitalWrite(leds[i], HIGH);
    }
    
    Serial.begin(9600);

    //Initialize random seed
    randomSeed(analogRead(0));

    mcDiffTime = millis();
}

void loop() {
    switch (state) {
        case MC: 
        {
            if (mcTimer(2000))
            {
                if (nLightsOff == N_LEDS) {
                    startTime = millis();
                    state = PLAYER;
                } else {
                    switchOffRandomLed();
                    nLightsOff++;
                }

                //Controllo del valore del potenziometro ed cambiamento della
                //velocità in base all'impostazione selezionata
                int potValue = analogRead(POT_PIN);
                int dividedValue = map(potValue, 0, 1023, 1, 3);
                level = dividedValue;
                timeToPlay = initialTime * pow((1 - DECRESE_RATE), level);
            }
        }
        break;
        //Nella fase di Player, verrà rilevata la pressione dei pulsanti e gestita analogamente la logica di gioco
        case PLAYER:
        {
            Serial.println("state: PLAYER");
            if (playerTimer(timeToPlay)) {
                currentCorrectLeds = 0;
                state = LOSE;
            }

            for (int i = 0; i < N_LEDS; i++) {
                if (digitalRead(buttons[i]) == HIGH) {
                    if (i == ledsToHigh[currentCorrectLeds]) {
                        currentCorrectLeds++;

                        Serial.print("currentCorrectLeds: ");
                        Serial.println(currentCorrectLeds);

                        digitalWrite(leds[i], HIGH);

                        if (currentCorrectLeds == N_LEDS) {
                            state = WINLEVEL;
                        }
                    } else {
                        state = LOSE;
                    }
                    /**
                     * ????
                    */
                    delay(500);
                }
            }
        }
        break;
        case LOSE:
        {
            Serial.println("state: LOSE");
      
            delay(QUARTER_SECOND);

            for (int i = 0; i < N_LEDS; i++) {
                digitalWrite(leds[i], HIGH);
            }

            delay(QUARTER_SECOND);

            for (int i = 0; i < N_LEDS; i++) {
                digitalWrite(leds[i], LOW);
            }
        }
        break;
        case WINLEVEL:
        {
            Serial.println("state: LEVEL PASSED");

            timeToPlay = initialTime * pow((1 - DECRESE_RATE), level++);

            for (int i = 0; i < N_LEDS; i++)
            {
                delay(SIXTEENTH_SECOND);

                for (int i = 0; i < N_LEDS; i++) {
                    digitalWrite(leds[i], HIGH);
                }

                delay(SIXTEENTH_SECOND);

                for (int i = 0; i < N_LEDS; i++) {
                    digitalWrite(leds[i], LOW);
                }
            }
            
            for (int i = 0; i < N_LEDS; i++) {
                digitalWrite(leds[i], HIGH);
            }

            //Reset delle impostazioni in preparazione al riavvio del livello
            nLightsOff = 0;
            state = MC;
        }
        break;
        default:
        {
            Serial.println("state: DEFAULT");
        }
        break;
    }
    
    /* utile per la lettura di input analogici */
    delay(2);
}

void switchOffRandomLed() {
    long rnd;

    do 
    {
        rnd = random(N_LEDS);
    } while (digitalRead(leds[rnd]) != HIGH);

    ledsToHigh[nLedsOn] = leds[rnd];
    nLedsOn--;
    digitalWrite(leds[rnd], LOW);
}

int mcTimer(unsigned long time) {
    mcDiffTime = millis() - time;
    if (mcDiffTime >= time) {
        time = millis();
        return 1;
    } else {
        return 0;
    }
}

int playerTimer(unsigned long time) {
    startTime = millis() - time;
    if (mcDiffTime >= time) {
        time = millis();
        return 1;
    } else {
        return 0;
    }
}
