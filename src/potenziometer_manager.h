#ifndef __POTENTIOMETER_MANAGER_H__
#define __POTENTIOMETER_MANAGER_H__

/// Define potentiometer pin
extern const uint8_t POTENTIOMETER_PIN;

/// T1 is the time after which the green led switch on
extern unsigned long T1;

/// @brief Get the selected difficulty by reading the value from the potentiometer
/// @return the selected difficulty
uint8_t getDifficulty();

/// @brief Initialize potentiometer's pin
void potentiometerInit();

#endif