cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(hid)

pico_sdk_init()

add_executable(
    hid
    src/main.c src/wireless.c # src/blink.c src/hid.c
#    src/usb_descriptors.c src/report.c
)
#include_directories(include)

target_link_libraries(
    hid pico_stdlib hardware_spi #tinyusb_device tinyusb_board 
)

pico_enable_stdio_usb(hid 1)
pico_enable_stdio_uart(hid 1)

pico_add_extra_outputs(hid)
