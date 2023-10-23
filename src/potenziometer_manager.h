#ifndef __POTENTIOMETER_MANAGER_H__
#define __POTENTIOMETER_MANAGER_H__

/// @brief Get the selected difficulty by reading the value from the potentiometer.
/// @return the selected difficulty.
uint8_t getDifficulty();

/// @brief Initialize potentiometer's pin.
void potentiometerInit();

#endif