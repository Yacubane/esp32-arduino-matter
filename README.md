# ESP32 Arduino Matter
This projects aims at possibility to easily launch Matter internet-of-things protocol on ESP32 with Arduino. Repository contains precompiled and ready to use components from two projects: [Espressif's SDK for Matter](https://github.com/espressif/esp-matter) and [Matter](https://github.com/project-chip/connectedhomeip).

## Installing on Arduino IDE
1. Make sure that ESP32 board version is **2.0.8**. **This is crucial**, because this library contains pre-compiled files.
2. [Turn on C++17 support for Arduino](#enabling-c17-on-arduino-ide).
3. [Download](https://github.com/Yacubane/esp32-arduino-matter/releases) and [import library into Arduino IDE](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries).
4. Choose larger partition scheme, for example `Minimal SPIFFS`.
5. To prevent some issues related to old data, enable `Erase Flash Before Sketch Upload` option.
6. Run example sketch.

## Installing on PlatformIO
1. Use espressif32 platform at version **6.1.0**, by setting `platform = espressif32@6.1.0` in `platformio.ini`. **This is crucial**, because this library contains pre-compiled files.
2. Turn on C++17 support, by setting `build_unflags=-std=gnu++11` and `build_flags=-std=gnu++17` in `platformio.ini`.
3. [Download](https://github.com/Yacubane/esp32-arduino-matter/releases) and put library into `lib` folder of project (:warning: you cannot use `lib_deps` in `platformio.ini`, because this repository does not contain binaries due to too big size). The desired structure is as follows:
```
|--platformio-project
|  |--lib
|  |  |--esp32-arduino-matter
|  |  |  |--examples
|  |  |  |--src
|  |  |  |--...
```
4. Choose larger partition scheme, for example `board_build.partitions=min_spiffs.csv` in `platformio.ini`. `min_spiffs.csv` is one of build-in partition schemas and does need to be created.
5. Copy and run example sketch.

## Example usage
In `examples` folder there are some sketches that demonstrates usage of Matter. `Light` example is tested every release. Example sketches are in [release](https://github.com/Yacubane/esp32-arduino-matter/releases) created from [esp32-arduino-matter-builder repository](https://github.com/Yacubane/esp32-arduino-matter-builder/tree/master/lib_files/examples).

## Compatibility
This project contains precompiled libraries based on specific version of ESP32 SDK and this library does not guarantee support for other versions. Current build is based on `esp-idf` at version v4.4.4 and will work with:
* Arduino IDE with [ESP32 board](https://github.com/espressif/arduino-esp32) at version 2.0.8
* PlatformIO with [PlatformIO espressif32 platform](https://github.com/platformio/platform-espressif32) at version v6.1.0

## Limitations
* Library only works on ESP32 (ESP32-C3 and ESP32-S3 might work as well, but aren't tested).
* There is no possibility to change vendor/product ID as this value is pre-compiled.
* There is no known possibility to change setup PIN.
* This library comes with precompiled NimBLE, because default Bluedroid shipped with arduino-esp32 takes too much RAM memory.
* Matter Controllers such as Apple Home, Google Home, SmartThings and others might not have full support of all device types.
* This repository does not contain source code of this library, because binaries were too big and exceeded Github limits. Please look at Github [releases](https://github.com/Yacubane/esp32-arduino-matter/releases) to download whole package. All library files without binaries are stored [here](https://github.com/Yacubane/esp32-arduino-matter-builder).

## Versions
This project is currently build based on these projects:

| Project       | Tag / Commit hash |
| ------------- | ------------- |
| [esp32-arduino-matter-builder](https://github.com/Yacubane/esp32-arduino-matter-builder) | v1.0.0-beta.4 |
| [Matter](https://github.com/project-chip/connectedhomeip) | bd17b9f52f |
| [esp-matter](https://github.com/espressif/esp-matter) | 0b1762e |
| [esp-idf](https://github.com/espressif/esp-idf) | v4.4.4 |
| [arduino-esp32](https://github.com/espressif/arduino-esp32) | 2.0.8 |

## Enabling C++17 on Arduino IDE
1. Find `platform.txt` for ESP32 board. Location of this file is platform depended.

    MacOS: `~/Library/Arduino15/packages/esp32/hardware/esp32/2.0.8/platform.txt`

    Windows: `C:\Users\<USER>\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.8\platform.txt`

2. Inside `platform.txt` find `ESP32 Support Start` section and it's `compiler.cpp.flags.esp32` key. Change `-std=gnu++11` to `-std=gnu++17`. Do the same thing for `ESP32S3` and `ESP32C3` `Support Start` section if you are using ESP32-S3/ESP32-C3.

3. Restart Arduino IDE.

## Rest of files and process of building custom version of this library
Please look [here](https://github.com/Yacubane/esp32-arduino-matter-builder).
