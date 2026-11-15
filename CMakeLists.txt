# rpi5xl: the Atari 800XL and 130XE on the Raspberry Pi 5.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/rpi5xl --help
#
# The Atari itself is esp32xl's (../esp32xl/components/atari_xl, platform
# independent), the runtime rpi5emu's (../rpi5emu), the 6502 esp32emu's
# (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(rpi5xl C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32XL_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32xl" CACHE PATH "esp32xl checkout: the Atari XL")
if(NOT EXISTS "${ESP32XL_DIR}/components/atari_xl/include/xl.h")
    message(FATAL_ERROR "No esp32xl at ${ESP32XL_DIR}: clone github.com/rlucencic/esp32xl beside rpi5xl")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../rpi5emu" rpi5emu)

file(GLOB XL_SOURCES "${ESP32XL_DIR}/components/atari_xl/*.c")
add_executable(rpi5xl
    src/main.c
    src/settings.c
    src/rom_store.c
    ${XL_SOURCES})
target_include_directories(rpi5xl PRIVATE
    src
    "${ESP32XL_DIR}/components/atari_xl/include"
    "${ESP32XL_DIR}/components/atari_xl")
rpi5emu_add_cores(rpi5xl m6502 diskspace)
target_link_libraries(rpi5xl PRIVATE rpi5emu)
target_compile_options(rpi5xl PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-unused-result)

install(TARGETS rpi5xl)
