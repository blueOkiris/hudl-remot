#include <stdio.h>
#include <pico/stdlib.h>
#include <Wireless.hpp>
#include <Controller.hpp>

using namespace hudlremot;

int main() {
    stdio_init_all();
    printf("Hudl remote physical device\n");
    
    //testBluetooth();
    
    const Hc05 bluetooth(true);
    const Controller controller;
    
    uint16_t stickX, stickY;
    uint8_t inputData[7];
    while(1) {
        inputData[0] = '\n';
        inputData[1] = controller.buttonState();
        controller.readThumbstick(stickX, stickY);
        inputData[2] = static_cast<uint8_t>(stickX >> 8);
        inputData[3] = static_cast<uint8_t>(stickX & 0x00FF);
        inputData[4] = static_cast<uint8_t>(stickY >> 8);
        inputData[5] = static_cast<uint8_t>(stickY & 0x00FF);
        inputData[6] = '\n';
        bluetooth.putData(inputData, 7);
    }
}
