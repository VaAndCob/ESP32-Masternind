# ESP32-S3 Mastermind Game
![front](/waveshare7_3D/front.png
)

This repository contains the source code for a classic Mastermind board game, implemented on the WaveShare 7-inch Touch LCD for the ESP32-S3. The project includes the game logic, user interface created with SquareLine Studio, and drivers for the specific hardware.

A custom 3D-printable case was also designed for this project to provide a clean and integrated final product.

## Features

*   **Classic Mastermind Gameplay**: Try to guess the secret 4-peg color code in 12 attempts or less.
*   **Timed Mode**: A 60-second countdown timer for each guess adds a layer of challenge.
*   **Touch Interface**: A fully touch-based UI for selecting colors and checking your guess.
*   **Engaging UI**: A retro-themed interface designed with SquareLine Studio and powered by the LVGL graphics library.
*   **Hardware-Specific Drivers**: Includes configurations for the LovyanGFX graphics driver and the CH422G I/O expander used on the WaveShare board.
*   **Custom 3D-Printed Case**: STL files for a custom-designed case are available to house the electronics.

## Hardware

This project is specifically designed for the following hardware:

*   **Main Board**: [WaveShare ESP32-S3 7-inch Capacitive Touch LCD (800x480)](https://www.waveshare.com/7inch-capacitive-touch-lcd-f.htm)
*   **3D-Printed Case**: The STL files for the case can be found in the `/3d-print` directory of this repository.

## Software & Dependencies

The project is built using the Arduino IDE with the ESP32 board package.

### Libraries

You will need to install the following libraries through the Arduino Library Manager:

*   **LovyanGFX** by lovyan03
*   **LVGL** by LVGL Kft. (v8.4.0 is used in this project)
*   **esp_io_expander** by Espressif

### Build Environment

*   **Arduino IDE**: Version 2.x recommended.
*   **ESP32 Board Package**: Version 2.0.17 or newer.
*   **C++ Standard**: This project requires C++17. You must modify the ESP32 platform configuration to enable it.

## Setup and Installation
*   Please read the README.md file in "sketch" folder

## How to Play

1.  When the device powers on, it will display a "Restart" button. Press it to begin a new game.
2.  A secret code of 4 colored pegs is generated.
3.  Tap the pegs in the current row to cycle through the available colors.
4.  Once you have set your 4-peg guess, press the checkmark button on the right to submit your guess.
5.  Feedback pegs will appear:
    *   **White Peg**: Correct color in the correct position.
    *   **Black Peg**: Correct color but in the wrong position.
6.  You have 12 attempts to guess the code.
7.  A 60-second timer will count down for each guess. If you don't submit your guess in time, you lose the game.
8.  If you guess the code, you win! If you run out of attempts, you lose. The secret code will be revealed at the end of the game.

## License

This project is open-source. Please feel free to use, modify, and distribute the code. If you create something cool, I'd love to hear about it!
