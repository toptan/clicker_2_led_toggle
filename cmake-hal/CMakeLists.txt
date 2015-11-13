cmake_minimum_required(VERSION 2.8.11)
project(led-toggle C)

# Enabling assembler
enable_language(ASM)

# Definitions
add_definitions(-DSTM32F407xx)

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles")

# Assembler flags
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -Wall")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -Os")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -nostartfiles")

# Linker flags
set(LINKER_FLAGS "${CMAKE_C_FLAGS}")
set(LINKER_FLAGS "${LINKER_FLAGS} -T${CMAKE_SOURCE_DIR}/link/STM32F407VG_FLASH.ld")
set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,--gc-sections")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/driver/cmsis/include)
include_directories(${CMAKE_SOURCE_DIR}/driver/hal/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

# System source files
set(SYSTEM_FILES ${CMAKE_SOURCE_DIR}/driver/cmsis/src/system_stm32f4xx.c)

# Startup assembler files
set(ASM_FILES ${CMAKE_SOURCE_DIR}/driver/cmsis/src/startup_stm32f407xx.s)

# HAL source files
file(GLOB HAL_FILES ${CMAKE_SOURCE_DIR}/driver/hal/src/*.c)

# Project source files
file(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.c)

# Our target image
add_executable(image.elf ${SOURCE_FILES} ${SYSTEM_FILES} ${ASM_FILES} ${HAL_FILES})
set_target_properties(image.elf PROPERTIES LINKER_LANGUAGE C CXX ASM)
set_target_properties(image.elf PROPERTIES LINK_FLAGS "${LINKER_FLAGS}")
add_custom_command(TARGET image.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY} -Oihex image.elf image.hex)

# Extra files for clean target
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES image.hex)