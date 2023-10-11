
/**
 * MC: Microcontroller (Il sistema stà inizializzando il gioco)
 * PLAYER: Turno del giocatore
 * LOSE: Il giocatore ha perso il gioco
 * WINLEVEL: Il giocatore ha perso il gioco
 */
enum GameState { MC, PLAYER, LOSE, WINLEVEL};
GameState state = MC;


/**
 * Switch off a random led and
 * save his pin number in the ledsToHigh array
 * begining from the end position.
*/
void switchOffRandomLed();

/**
 * Timer 'not blocking' function only usable from MC.
*/
int mcTimer(unsigned long time);

/**
 * Timer 'not blocking' function only usable from PLAYER.
*/
int playerTimer(unsigned long time);

/**
 * Initialize the game.
*/
void game_init();