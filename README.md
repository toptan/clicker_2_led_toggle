# STM32F4XX Buttons and Leds demo

This is a small university project of mine, which should show the process of developing for STM32F4XX chips under Linux and OS X.
There are four sub directories, each having the code that does the very same thing. First button toggles second LED and vice versa.

 * hal subdirectory contains example with plain make files and uses STM HAL library
 * raw subdirectory contains example with plain make files and does not use STM HAL library
 * cmake-hal subdirectory contains example with CMake and uses STM HAL library
 * cmake-raw subdirectory contains example with CMake and does not use STM HAL library

OpenOCD start command:
openocd -f /opt/local/share/openocd/scripts/interface/stlink-v2.cfg -f /opt/local/share/openocd/scripts/target/stm32f4x.cfg

The code is tested with Mikroelektronika Clicker 2 for STM32 board http://www.mikroe.com/stm32/clicker-2/


