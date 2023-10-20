# assignment_1
## Setup
1. Install PlatformIO IDE in VSCode
2. Connect the arduino
3. Upload and have fun!
## Digital Arduino 
-- insert images here --

## TO DO LIST
Gieck
- gestione di T2 e T3
- suddivisone del codice 
- start al premeere di B1
- messaggio di "GO!" nel Seriale
- spegnimento dei led (uno alla volta) randomicamente con un distacco di tempo T2

Elvis
- il sistema si riattiva al premere di un qualsiasi pulsante -> dallo stato di SETUP (funzionante)
- timer 10 secondi -> deep sleeping (funzioanante)
- accensione di tutti i led dopo un certo tempo T1 (funzionante)
- {il giocatore ha T3 tempo per completare il pattern dello spegnimento delle luci in ordine inverso} (da testare)

Moro
- check del end-game (WIN or LOSE)
WIN:
- aumenta lo score
- stampa  il messaggio
- rideuce T2 e T3 di un fattore F (definito dal potenziometro)

Ene
LOSE:
- si accende il led rosso per 1 secondo oppure va in fade out in tempo 10s
- stampa il risultato dello score raggiunto per 10 secondi
- reset totale del gioco 

PRE-GAME:
- settare il fattoriale F con il potenziometro (da eseguirsi nello stato di SETUP)
- vettore di Decrease-Rate di 4 elemeni, viene estratto un elemento in base al livellod el potenziometro mappato 0-3
    -> testare se va mappato in 0-3 o 1-4

TO-DO List pt2
- Race condion
- Check docs
- Fixare il gameplay -> controllo push pulsante corretto
- Stampa la score