cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(hid)

pico_sdk_init()

add_executable(hid src/main.c)
include_directories(include)
target_link_libraries(hid pico_stdlib hardware_i2c pico_multicore)

pico_enable_stdio_usb(hid 1)
pico_enable_stdio_uart(hid 0)

pico_add_extra_outputs(hid)
