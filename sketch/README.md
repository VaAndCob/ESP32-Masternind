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

1.  **Install Arduino IDE and ESP32 Core**:
    *   Download and install the Arduino IDE.
    *   Install the ESP32 board package. You can follow the instructions here.

2.  **Install Required Libraries**:
    *   Open the Arduino IDE.
    *   Go to `Sketch` -> `Include Library` -> `Manage Libraries...`.
    *   Search for and install `LovyanGFX`, `lvgl`, and `esp_io_expander`.

3.  **Configure C++17 Standard**:
    *   This is a critical step. The `esp_io_expander` library requires C++17.
    *   Locate the `platform.txt` file for your ESP32 board package. The path is typically:
        *   **macOS**: `~/Library/Arduino15/packages/esp32/hardware/esp32/<version>/platform.txt`
        *   **Windows**: `C:\Users\<YourUser>\AppData\Local\Arduino15\packages\esp32\hardware\esp32\<version>\platform.txt`
        *   **Linux**: `~/.arduino15/packages/esp32/hardware/esp32/<version>/platform.txt`
    *   Open `platform.txt` in a text editor.
    *   Find the line that starts with `compiler.cpp.flags=`.
    *   Change `-std=gnu++11` to `-std=gnu++17`.
    *   Save the file and **restart the Arduino IDE**.

4.  **Configure LVGL**:
    *   The LVGL library requires a configuration file. This project already includes a pre-configured `lv_conf.h`.
    *   Copy the `lv_conf.h` file from this repository's `sketch/ESP32-MasterMind/` directory into your Arduino libraries folder, inside the LVGL library directory (e.g., `~/Documents/Arduino/libraries/lvgl/`).
    *   Alternatively, you can place `lv_conf.h` in the same directory as your main `.ino` sketch file and add `#define LV_CONF_INCLUDE_SIMPLE` at the top of your sketch.

5.  **Clone the Repository**:
    ```bash
    git clone https://github.com/vaandcob/ESP32-MasterMind.git
    ```

6.  **Open and Upload**:
    *   Open the `ESP32-MasterMind.ino` file located in `sketch/ESP32-MasterMind/`.
    *   In the Arduino IDE, select "ESP32S3 Dev Module" as your board.
    *   Select the correct COM port.
    *   Click "Upload" to flash the firmware to your board.


This project is open-source. Please feel free to use, modify, and distribute the code. If you create something cool, I'd love to hear about it!
