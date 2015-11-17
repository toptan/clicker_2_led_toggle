# STM32F4XX Buttons and Leds demo

This is a small university project of mine, which should show the process of developing for STM32F4XX chips under Linux and OS X.
There are four sub directories, each having the code that does the very same thing. First button toggles second LED and vice versa.

* hal subdirectory contains example with plain make files and uses STM HAL library
* raw subdirectory contains example with plain make files and does not use STM HAL library
* cmake-hal subdirectory contains example with CMake and uses STM HAL library
* cmake-raw subdirectory contains example with CMake and does not use STM HAL library

## Requirements ##
- arm-none-eabi gcc toolchain. On Fedora package is **arm-none-eabi-gcc-cs**, on Ubuntu package is **gcc-arm-none-eabi**
- CMake minimum version 2.8.11
- mikroe-uhb from [https://github.com/thotypous/mikroe-uhb](https://github.com/thotypous/mikroe-uhb)
- OpenOCD - optional

## Makefile examples build instructions
Simply go to one of the project directories and execute make

## CMake examples build instructions
1. Create build dir outside the source tree and enter it.
2. Execute `cmake -DCMAKE_TOOLCHAIN_FILE=<path-to-arm-toolchain.cmake> <path-to-project-sources>`
3. Execute `make`

The toolchain file is located in subdirectory cmake and is named arm-toolchain.cmake

## Flasing image to the device
1. Connect device via USB
2. Execute `mikroe-uhb image.hex`
3. Reset or cycle power on the clicker 2 device

## Running OpenOCD
To run OpenOCD for clicker 2 device execute:

`openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/share/openocd/scripts/target/stm32f4x.cfg`

_On OS X paths to openocd configuration files may differ depending on the way how OpenOCD is installed._

The code is tested with Mikroelektronika Clicker 2 for STM32 board http://www.mikroe.com/stm32/clicker-2/

