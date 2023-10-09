/**
 * Game states.
 * SETUP: initialize the game, set the difficulty with potentiometer.
 * MC: Microcontroller swith off the leds in T2 time after waiting T1 time.
 * PLAYER: Player have to switch on leds in T3 time in the opposite order of swithcing off.
 * NEWLEVEL: Player win the level and start a new one whit less time to play.
 * GAMEOVER: Player lose the game and the system show the score.
*/
enum GameState {
    SETUP,
    MC,
    PLAYER,
    NEWLEVEL,
    GAMEOVER
};
