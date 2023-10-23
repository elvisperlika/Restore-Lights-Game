#ifndef __LED_BOARD__
#define __LED_BOARD__

/// Define green leds pins
#define GREEN_LED1 2
#define GREEN_LED2 3
#define GREEN_LED3 4
#define GREEN_LED4 5

/// Define red led pin (must be a PWM pin).
#define RED_LED 6

/// Millisecs of delay every fade's function call must have.
#define FADE_DELAY 20

/// @brief Getter of the total number of green leds.
/// @return the number of green leds.
uint8_t getGreenLedsNumber();

/// @brief Initialize green and red led's pins on OUTPUT.
void ledsInit();

/// @brief Switch all the leds on or off.
/// @param state: true to switch leds on, false to switch leds off.
void switchGreenLeds(bool state);

/// @brief Switch on or off a single led.
/// @param ledPin: pin of the led to switch on or off.
/// @param state: true to switch on, false to switch off.
void switchLed(uint8_t ledPin, bool state);

/// @brief Switch on or off a single led.
/// @param ledIndex Index of the led to switch.
/// @param state true to switch on, false to switch off.
void switchLedByIndex(uint8_t ledIndex, bool state);

/// @brief Check if all the leds are switched on.
/// @return true if all the leds are switched on, false otherwise.
bool checkLedsOn();

/// @brief If the fading is activated the led will fade in and out else the led will be switched off.
/// @param ledPin pin of the led to switch on or off.
void ledFading(uint8_t ledPin);

/// @brief Switch a random led off.
/// @return the index of the switched led.
uint8_t switchRandomLedOff();

#endif
