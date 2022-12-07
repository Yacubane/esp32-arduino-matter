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

## Installing on PlatformIO
1. Use espressif32 platform at version 5.2.0
2. Turn on C++17 support for, by setting `build_unflags=-std=gnu++11` and `build_flags=-std=gnu++17`.
3. Add this library: `lib_deps=https://github.com/jakubdybczak/esp32-arduino-matter.git`
4. Choose larger partition scheme, for example `board_build.partitions=min_spiffs.csv`
5. Run example sketch

## Example usage
Please look at [examples](https://github.com/jakubdybczak/esp32-arduino-matter/tree/master/examples).

## Limitations
* Library only works on base ESP32 (with experimental support for ESP32-S3, ESP32-C3).
* There is no possibility to change vendor/product ID as this value is pre-compiled.
* There is no known possibility to change setup PIN.
* This library comes with precompiled NimBLE, because default Bluedroid shipped with arduino-esp32 takes too much RAM memory.
* Matter Controllers such as Apple Home, Google Home, Smarthings and other might not have full support of all device types.

## Versions
This project is currently build based on these projects:

| Project       | Tag/Commit Hash |
| ------------- | ------------- |
| [Espressif's esp-idf](https://github.com/espressif/esp-idf) | 4.4.2</br>Arduino IDE ESP32 board @ 2.0.5</br>PlatformIO espressif platform @ 5.2.0 |
| [Espressif's SDK for Matter](https://github.com/espressif/esp-matter) | a0f13786  |
| [Matter](https://github.com/project-chip/connectedhomeip) | 7c2353bb |

## Enabling C++17 on Arduino IDE
1. Find `platform.txt` for ESP32 board. Location of this file is platform depended.

    MacOS: `~/Library/Arduino15/packages/esp32/hardware/esp32/2.0.5/platform.txt`

    Windows: `C:\Users\<USER>\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.5\platform.txt`

2. Inside `platform.txt` find `ESP32 Support Start` section and it's `compiler.cpp.flags.esp32` key. Change `-std=gnu++11` to ` -std=gnu++17`.

3. Restart Arduino IDE.

## Building custom version of this library
Please look [here](https://github.com/jakubdybczak/esp32-arduino-matter-builder).

## Future and possibilities
* Creating more user-friendly wrapper API.