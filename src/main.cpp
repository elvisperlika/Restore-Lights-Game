#include <Arduino.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

//Identificazione dello stato di gioco corrente
enum GameState {
  //Microcontroller (Il sistema stà inizializzando il gioco)
  MC,
  //Turno del giocatore
  PLAYER,
  //Il giocatore ha perso il gioco
  LOSE,
  //Il giocatore ha perso il gioco
  WIN_LEVEL};
GameState state = MC;

//Time constants
const unsigned long QUARTER_SECOND = 1000 / 4;
const unsigned long SIXTEENTH_SECOND = 1000 / 16;

//Variabili per il controllo dei led (OUTPUT)
int leds[N_LEDS] = {2, 3, 4, 5};
const int N_LEDS = sizeof(leds) / sizeof(leds[0]);

//Variabili per il controllo della difficoltà del livello (potenziometro)
const int POT_PIN = A0;

//Variabili per il controllo dei bottoni (INPUT)
int buttons[N_LEDS] = {6, 7, 8, 9};

//Vettore dei led accesi in ordine di accensione
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

//Livello corrente di gioco
int level = 1;

//Spegne un led random tra quelli accesi
static void switchOffRandomLed() {
    long rnd;

    do 
    {
        rnd = random(N_LEDS);
    } while (digitalRead(leds[rnd]) != HIGH);

    Serial.print("spengo la luce -> ");
    Serial.println(rnd);

    ledsToHigh[nLedsOn] = rnd;
    nLedsOn--;
    digitalWrite(leds[rnd], LOW);
}

void setup() {  
    //Imposta lo stato iniziale
    state = MC;

    //Inizializza i pin utilizzati
    for (int i = 0; i < N_LEDS; i++) {
        pinMode(leds[i], OUTPUT);
        pinMode(buttons[i], INPUT);
        digitalWrite(leds[i], HIGH);
    }
    
    //Inizializza la connessione seriale
    Serial.begin(9600);

    //Inizializza un seme per la generazione di numeri casuali
    randomSeed(analogRead(0));
}

void loop() {
    switch (state) {
        //Nella fase del main controller, verranno verranno spenti uno ad uno i led accesi in maniera casuale

        case MC:
            Serial.println("state: MC");
            delay(2000);
            Serial.println("Ho aspettato");
            Serial.print("nLightsOff: ");
            Serial.println(nLightsOff);
            
            if (nLightsOff == N_LEDS) {
                startTime = millis();
                Serial.print("start time 1: ");
                Serial.println(startTime);
                state = PLAYER;
            } else {
              switchOffRandomLed();
              nLightsOff++;
            }

            //Controllo del valore del potenziometro ed cambiamento della velocità in base all'impostazione selezionata
            int potValue = analogRead(POT_PIN);
            int dividedValue = map(potValue, 0, 1023, 0, 3);

            switch (dividedValue)
            {
                case 0:
                    level = 1;
                    break;
                case 1:
                    level = 2;
                    break;
                case 2:
                    level = 3;
                    break;
                case 3:
                    level = 4;
                    break;
                
                default:
                    level = 1;
                    break;
            }
            timeToPlay = initialTime * Math.Pow((1 - DECRESE_RATE), level);

            break;
        //Nella fase di Player, verrà rilevata la pressione dei pulsanti e gestita analogamente la logica di gioco
        case PLAYER:
            Serial.println("state: PLAYER");

            if (millis() - startTime >= timeToPlay ) {
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
      
            delay(QUARTER_SECOND);

            for (int i = 0; i < N_LEDS; i++) {
                digitalWrite(leds[i], HIGH);
            }

            delay(QUARTER_SECOND);

            for (int i = 0; i < N_LEDS; i++) {
                digitalWrite(leds[i], LOW);
            }

            break;
        case WIN_LEVEL:
            Serial.println("state: LEVEL PASSED");

            timeToPlay = initialTime * Math.Pow((1 - DECRESE_RATE), level++);

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
            break;
        default:
            Serial.println("state: DEFAULT");
            break;
    }
    
    /* utile per la lettura di input analogici */
    delay(2);
}