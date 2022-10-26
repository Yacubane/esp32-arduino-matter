> :warning: This library is currently meant to be used only for research purposes. Please read limitations section before using it.

# ESP32 Arduino Matter
This projects aims at possibility to easily launch Matter internet-of-things protocol on ESP32 with Arduino. Project contains precompiled and ready to use components from two projects: [Espressif's SDK for Matter](https://github.com/espressif/esp-matter) and [Matter](https://github.com/project-chip/connectedhomeip).

## Installing on Arduino IDE
1. Make sure that ESP32 board version is 2.0.5
2. [Turn on C++17 support for Arduino](#enabling-c17-on-arduino-ide)
3. Download this repository and [import library into Arduino IDE](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)
4. Choose larger partition scheme, for example `Minimal SPIFFS`
5. To prevent some issues related to old data, enable `Erase Flash Before Sketch Upload` option
6. Run example sketch

## Example usage
Please look at [examples](https://github.com/jakubdybczak/esp32-arduino-matter/tree/master/examples). You can test integration with Android and Matter controller by downloading compiled [CHIPTool](https://drive.google.com/file/d/14tjTz52_rd6S-O1drdVseWj6jXSrGoRx/view?usp=sharing) for Android.

## Limitations
* Library only works on base ESP32 (no support for ESP32-S2 and other variants).
* There is no possibility to change vendor/product ID as this value is pre-compiled.
* There is no known possibility to change setup PIN.
* This library comes with precompiled NimBLE, because default Bluedroid shipped with arduino-esp32 takes too much RAM memory.
* As of 26 Oct 2022, this library does not work with Google Home as this app is compatible with older version of Matter. You can test this library with CHIPTool.

## Versions
This project is currently build based on these projects:

| Project       | Tag/Commit Hash |
| ------------- | ------------- |
| [Espressif's esp-idf](https://github.com/espressif/esp-idf) | 4.4.2 (Arduino ESP32 board 2.0.5) |
| [Espressif's SDK for Matter](https://github.com/espressif/esp-matter) | 6fb13868  |
| [Matter](https://github.com/project-chip/connectedhomeip) | 4f7669b0 |

## Enabling C++17 on Arduino IDE
1. Find `platform.txt` for ESP32 board. Location of this file is platform depended.

    MacOS: `~/Library/Arduino15/packages/esp32/hardware/esp32/2.0.5/platform.txt`

    Windows: `C:\Users\<USER>\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.5\platform.txt`

2. Inside `platform.txt` find `ESP32 Support Start` section and it's `compiler.cpp.flags.esp32` key. Change `-std=gnu++11` to ` -std=gnu++17`.

3. Restart Arduino IDE.

## Future and possibilities
* Building packages for other variants of ESP32
* Providing scripts for buliding ESP32 Arduino Matter for specified Matter / esp-matter / ESP-IDF branches
* Creating more user-friendly access to Matter clusters