# sdlxl: the Atari 800XL and 130XE with SDL 3.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/sdlxl --help
#
# The Atari itself is esp32xl's (../esp32xl/components/atari_xl, platform
# independent), the runtime sdlemu's (../sdlemu), the 6502 esp32emu's
# (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(sdlxl C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32XL_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32xl" CACHE PATH "esp32xl checkout: the Atari XL")
if(NOT EXISTS "${ESP32XL_DIR}/components/atari_xl/include/xl.h")
    message(FATAL_ERROR "No esp32xl at ${ESP32XL_DIR}: clone github.com/rlucencic/esp32xl beside sdlxl")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../sdlemu" sdlemu)

file(GLOB XL_SOURCES "${ESP32XL_DIR}/components/atari_xl/*.c")
add_executable(sdlxl
    src/main.c
    src/settings.c
    src/rom_store.c
    ${XL_SOURCES})
target_include_directories(sdlxl PRIVATE
    src
    "${ESP32XL_DIR}/components/atari_xl/include"
    "${ESP32XL_DIR}/components/atari_xl")
sdlemu_add_cores(sdlxl m6502 diskspace)
target_link_libraries(sdlxl PRIVATE sdlemu)
target_compile_options(sdlxl PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-unused-result)

install(TARGETS sdlxl)
