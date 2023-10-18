#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// !! CHECK DISPLAY SIZE
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adjust dimensions as needed

/// @brief Initialize the LCD
void lcdInit() {
    lcd.init();
    lcd.backlight();  
}

/// @brief Print a number on the LCD
/// @param num number to print
void print(int num) {
    lcd.setCursor(0, 0);
    lcd.print(num);
}

/// @brief Clear the display
void clear() {
    lcd.clear();
}