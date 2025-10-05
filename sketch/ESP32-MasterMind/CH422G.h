/*
 * CH422G I2C I/O Expander Control
 * Note: The original file had a comment about changing gnu++11 to gnu++17.
 * This is generally handled by the Arduino Core for ESP32 and shouldn't need manual changes.
 */
 #pragma once

#include <esp_io_expander.hpp>
#include <Arduino.h>

#define SD_MOSI 11  // SD card master output slave input pin
#define SD_CLK 12   // SD card clock pin
#define SD_MISO 13  // SD card master input slave output pin
#define SD_SS -1    // SD card select pin (not used)

// Pins used to connect to CAN bus transceiver:
#define CAN_RX 19
#define CAN_TX 20





//turn on off backlight
extern esp_expander::CH422G *expander;

void backlight_on();
void backlight_off();

void expanderInit();
