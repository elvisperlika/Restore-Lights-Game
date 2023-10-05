#include <Arduino.h>
#include <time.h>
#include <stdlib.h>

const unsigned long ONE_SEC = 1000;
const int N_LEDS = 4;
enum GameState {MC, PLAYER, LOSE, WIN_LEVEL};
GameState state = MC;
int leds[N_LEDS] = {2, 3, 4, 5};
int buttons[N_LEDS] = {6, 7, 8, 9};
int ledsToHigh[N_LEDS];
long r;
int n = 0;
int j = N_LEDS - 1;
int l = 0;
unsigned long startTime;
unsigned long timeToPlay = 10000; /* tempo a disposizione del giocatore */
unsigned long deltaTime = 1000; /* tempo da rimuovere ad ogni nuovo livello */
int level = 1; /* livello del gioco */

static void wait(unsigned long time) {
    int beginTime = millis();
    while (millis() - beginTime <= time);
}

static void switchOffAnRandomLed() {

    do 
    {
        r = random(N_LEDS);
    } while (digitalRead(leds[r]) != HIGH);
    Serial.print("spengo la luce -> ");
    Serial.println(r);
    ledsToHigh[j] = r;
    j--;
    digitalWrite(leds[r], LOW);

}

void setup() {  
    state = MC;
    for (int i = 0; i < N_LEDS; i++) {
        pinMode(leds[i], OUTPUT);
        pinMode(buttons[i], INPUT);
        digitalWrite(leds[i], HIGH);
    }
    
    Serial.begin(9600);
    randomSeed(analogRead(0));
}

void loop() {
    switch (state) {
    case MC:
        Serial.println("state: MC");
        wait(2000);
        Serial.println("Ho aspettato");
        Serial.print("n: ");
        Serial.println(n);
        
        if (n == N_LEDS) {
            startTime = millis();
            Serial.print("start time 1: ");
            Serial.println(startTime);
            state = PLAYER;
        } else {
          switchOffAnRandomLed();
          n++;
        }
        break;
    case PLAYER:
        Serial.println("state: PLAYER");
        if (millis() - startTime >= timeToPlay ) {
            l = 0;
            state = LOSE;
        }
        for (int i = 0; i < N_LEDS; i++) {
            if (digitalRead(buttons[i]) == HIGH) {
                if (i == ledsToHigh[l]) {
                    l++;
                    Serial.print("l: ");
                    Serial.println(l);
                    digitalWrite(leds[i], HIGH);
                    if (l == N_LEDS) {
                        state = WIN_LEVEL;
                    }
                } else {
                    state = LOSE;
                }
                delay(500);
            }
        }

        break;
    case LOSE:
        Serial.println("state: LOSE");
        wait(ONE_SEC / 4);
        for (int i = 0; i < N_LEDS; i++) {
            digitalWrite(leds[i], HIGH);
        }
        wait(ONE_SEC / 4);
        for (int i = 0; i < N_LEDS; i++) {
            digitalWrite(leds[i], LOW);
        }
        break;
    case WIN_LEVEL:
        Serial.println("state: LEVEL PASSED");
        timeToPlay -= deltaTime;
        level++;
        for (int i = 0; i < N_LEDS; i++)
        {
            wait(ONE_SEC / 16);
            for (int i = 0; i < N_LEDS; i++) {
                digitalWrite(leds[i], HIGH);
            }
            wait(ONE_SEC / 16);
            for (int i = 0; i < N_LEDS; i++) {
                digitalWrite(leds[i], LOW);
            }
        }
        
        for (int i = 0; i < N_LEDS; i++) {
            digitalWrite(leds[i], HIGH);
        }
        n = 0;
        state = MC;
        break;
    default:
        Serial.println("state: DEFAULT");
        break;
    }
    
    /* utile per la lettura di input analogici */
    delay(2);
}