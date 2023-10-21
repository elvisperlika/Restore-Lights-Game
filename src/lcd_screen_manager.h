#ifndef __LCD_SCREEN_MANAGER__
#define __LCD_SCREEN_MANAGER__

/// @brief Initialize the LCD.
void initLCD();

/// @brief Set the cursor on the lcd screen.
/// @param row the row on the LCD screen.
/// @param column the column of the row on the LCD screen.
void changeCursorLCD(uint8_t row, uint8_t column);

/// @brief Print a number on the LCD.
/// @param num number to print.
void printLCD(int num);

/// @brief Print a string on the LCD.
/// @param text the text to write.
void printLCD(const char* text);

/// @brief Clear the display.
void clearLCD();

#endif
