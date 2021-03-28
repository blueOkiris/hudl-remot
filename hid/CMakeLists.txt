cmake_minimum_required(VERSION 3.12)
get_filename_component(PARENT_DIR ../ ABSOLUTE)
include(pico_sdk_import.cmake)
project(hid)

pico_sdk_init()

add_executable(
    hid
    src/main.cpp
    src/hid/Blink.cpp src/hid/Hid.cpp
    src/hid/usb_descriptors.c src/hid/report.c
    ${PARENT_DIR}/common/src/Wireless.cpp
)
include_directories(
    include
    include/hid
    ${PARENT_DIR}/common/include
)

target_link_libraries(
    hid pico_stdlib hardware_spi tinyusb_device tinyusb_board 
)

#pico_enable_stdio_usb(hid 1)
#pico_enable_stdio_uart(hid 0)

pico_add_extra_outputs(hid)
