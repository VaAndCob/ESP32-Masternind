/*
 * CH422G I2C I/O Expander Control
 * Edit file /Users/{user_name}/Library/Arduino15/packages/esp32/hardware/esp32/2.0.17/platform.txt
 * Replace "gnu++11" with "gnu++17"
 */

#include "CH422G.h"

// I2C Pin definitions for the expander
#define I2C_SDA 8
#define I2C_SCL 9
#define CH422G_I2C_ADDR 0x27

// Expander Pin definitions using the library's bitmasks
#define EXPANDER_TP_RST  0 // Touch Reset
#define EXPANDER_LCD_BL  1 // LCD Backlight control
#define EXPANDER_LCD_RST 2 // LCD Reset
#define EXPANDER_SD_CS   3 // SD Card Chip Select
#define EXPANDER_USB_SEL 4 // USB or CAN selection

//turn on off backlight
esp_expander::CH422G *expander;

void backlight_on() {
    if (expander) expander->digitalWrite(EXPANDER_LCD_BL, HIGH);
}

void backlight_off() {
    if (expander) expander->digitalWrite(EXPANDER_LCD_BL, LOW);
}

void expanderInit() {
  Serial.println("Init CH422G");
  if (!expander) {
      // Explicitly use I2C port 1 to match the touch controller configuration
      expander = new esp_expander::CH422G(I2C_SCL, I2C_SDA, CH422G_I2C_ADDR, 1);
      expander->init();
      expander->begin();
      expander->enableAllIO_Output(); //Set the IO0-7 pin to output mode.
      expander->multiDigitalWrite(EXPANDER_TP_RST | EXPANDER_LCD_BL | EXPANDER_LCD_RST, HIGH);
  }
}
