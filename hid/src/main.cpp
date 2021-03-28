#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pico/stdlib.h>
#include <bsp/board.h>
#include <ButtonIds.hpp>
#include <Wireless.hpp>
#include <Hid.hpp>

using namespace hudlremot;

void testBluetooth() {
    // Remove when using usb
    stdio_init_all();
    
    const Hc05 bluetooth(false);
    uint8_t inputData[7];
    while(1) {
        if(bluetooth.canRead()) {
            bluetooth.getData(inputData, 7);
            
            // Parity
            while(inputData[0] != '\n' || inputData[6] != '\n') {
                if(bluetooth.canRead()) {
                    for(int i = 0; i < 6; i++) {
                        inputData[i] = inputData[i + 1];
                    }
                    bluetooth.getData(inputData + 6, 1);    // Shift until okay
                }
            }
            
            printf(
                "Received: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\r\n",
                inputData[0],
                
                inputData[1],
                (static_cast<uint16_t>(inputData[2]) << 8)
                    + static_cast<uint16_t>(inputData[3]),
                (static_cast<uint16_t>(inputData[4]) << 8)
                    + static_cast<uint16_t>(inputData[5]),
                
                inputData[6]
            );
        }
    }
}

void interpretBluetooth() {
    const Hc05 bluetooth(false);
    UsbHid usb;
    
    uint8_t inputData[7];
    bool hasReleased = true;
    while(1) {
        usb.update();
        if(bluetooth.canRead()) {
            bluetooth.getData(inputData, 7);
            
            // Parity
            while(inputData[0] != '\n' || inputData[6] != '\n') {
                usb.update();
                if(bluetooth.canRead()) {
                    for(int i = 0; i < 6; i++) {
                        inputData[i] = inputData[i + 1];
                    }
                    bluetooth.getData(inputData + 6, 1);    // Shift until okay
                }
            }
            
            // Handle buttons
            switch(static_cast<ControllerButton>(inputData[1])) {
                case ControllerButton::MouseLeft:
                    usb.clickMouse(true);
                    break;
                case ControllerButton::MouseRight:
                    usb.clickMouse(false);
                    break;
                case ControllerButton::None:
                    usb.releaseKey();
                    hasReleased = true;
                    break;
                case ControllerButton::Rewind:
                    if(hasReleased) {
                        usb.releaseKey();
                        usb.pressKey(HID_KEY_ARROW_LEFT);
                        hasReleased = false;
                    }
                    break;
                case ControllerButton::FastForward:
                    if(hasReleased) {
                        usb.releaseKey();
                        usb.pressKey(HID_KEY_ARROW_RIGHT);
                        hasReleased = false;
                    }
                    break;
                case ControllerButton::SlowRewind:
                    if(hasReleased) {
                        usb.releaseKey();
                        usb.pressKey(HID_KEY_ARROW_UP);
                        hasReleased = false;
                    }
                    break;
                case ControllerButton::SlowForward:
                    if(hasReleased) {
                        usb.releaseKey();
                        usb.pressKey(HID_KEY_ARROW_DOWN);
                        hasReleased = false;
                    }
                    break;
                case ControllerButton::Previous:
                    if(hasReleased) {
                        usb.pressKey(HID_KEY_ARROW_LEFT);
                        usb.update();
                        usb.releaseKey();
                        usb.update();
                        hasReleased = false;
                    }
                    break;
                case ControllerButton::Next:
                    if(hasReleased) {
                        usb.pressKey(HID_KEY_ARROW_RIGHT);
                        usb.update();
                        usb.releaseKey();
                        usb.update();
                        hasReleased = false;
                    }
                    break;
                case ControllerButton::Play:
                    if(hasReleased) {
                        usb.pressKey(HID_KEY_SPACE);
                        usb.update();
                        usb.releaseKey();
                        usb.update();
                        hasReleased = false;
                    }
                    break;
            }
            
            // Handle stick positions
            uint16_t stickX =
                (static_cast<uint16_t>(inputData[2]) << 8)
                + static_cast<uint16_t>(inputData[3]);
            uint16_t stickY =
                (static_cast<uint16_t>(inputData[4]) << 8)
                + static_cast<uint16_t>(inputData[5]);
            int16_t moveX = (static_cast<int16_t>(stickX) - 435)/  100;
            int16_t moveY = (static_cast<int16_t>(stickY) - 435) / 100;
            usb.moveMouse(-moveX, -moveY);
        }
    }
}


int main() {
    //testBluetooth();
    interpretBluetooth();
    
    return 0;
}
