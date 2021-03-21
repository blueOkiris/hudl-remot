cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(hid)

pico_sdk_init()

add_executable(
    hid
    src/main.c src/blink.c src/usb_descriptors.c src/hid.c
)
include_directories(
    include
)
target_link_libraries(hid pico_stdlib tinyusb_device tinyusb_board)

pico_add_extra_outputs(hid)
