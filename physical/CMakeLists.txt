cmake_minimum_required(VERSION 3.12)
get_filename_component(PARENT_DIR ../ ABSOLUTE)
include(pico_sdk_import.cmake)
project(physical)

pico_sdk_init()

add_executable(
    physical src/main.cpp src/Controller.cpp
    ${PARENT_DIR}/common/src/Wireless.cpp
)
include_directories(
    include
    ${PARENT_DIR}/common/include
)

target_link_libraries(physical pico_stdlib hardware_adc)

pico_enable_stdio_usb(physical 1)
pico_enable_stdio_uart(physical 0)

pico_add_extra_outputs(physical)
