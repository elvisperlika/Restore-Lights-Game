#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/// Adjust dimensions as needed
LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD() {
    lcd.init();
    lcd.backlight();
}

void changeCursorLCD(uint8_t row, uint8_t column) {
    lcd.setCursor(row, column);
}

void printLCD(int num) {
    lcd.print(num);
}

void printLCD(const char* text) {
  lcd.print(text);
}

void clearLCD() {
    lcd.clear();
}