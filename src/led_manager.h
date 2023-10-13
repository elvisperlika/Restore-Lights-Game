#include "Arduino.h"

#ifndef __LED_BOARD__
#define __LED_BOARD__

#define GREEN_LED1 4
#define GREEN_LED2 5
#define GREEN_LED3 6
#define GREEN_LED4 7
/**
 * Red led pin must be a PWM pin.
*/
#define RED_LED 9

/**
 * Set the leds pin as output.
*/
void led_init_output();

/**
 * Switch all the leds on or off.
 * @param state: true to switch on, false to switch off.
*/
void switchGreenLeds(boolean state);

/**
 * Switch on or off a single led.
 * @param ledPin: pin of the led to switch on or off.
 * @param state: true to switch on, false to switch off.
*/
void switchLed(uint8_t ledPin, boolean state);

/**
 * If the fading is activated the led will fade in and out
 * else the led will be switch off.
 * @param ledPin: pin of the led to switch on or off.
* @param state: true to switch on, false to switch off.
*/
void ledFading(uint8_t ledPin, boolean state);

/**
 * Leds number getter.
*/
int getGreenLedsNumber();

#endif
