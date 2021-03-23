cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(physical)

pico_sdk_init()

add_executable(physical src/main.c src/wireless.c src/controller.c)
include_directories(include)

target_link_libraries(physical pico_stdlib)

pico_enable_stdio_usb(physical 1)
pico_enable_stdio_uart(physical 1)

pico_add_extra_outputs(physical)
