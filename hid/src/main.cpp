#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pico/stdlib.h>
//#include <bsp/board.h>
#include <ButtonIds.hpp>
#include <Wireless.hpp>
//#include <Hid.hpp>

using namespace hudlremot;

void testReceiveBluetooth();

int main() {
    // Remove when using usb
    stdio_init_all();
    sleep_ms(1000);
    printf("Hudl remote v2.0 HID side\r\n");
    
    testReceiveBluetooth();
    
    /*const Hc05 bluetooth;
    UsbHid usb;
    
    char cmd, btnId, curr;
    int i;
    char stickVal[5];
    uint16_t stickX, stickY;
    while(1) {
        usb.update();                               // Go through update process
        
        while(bluetooth.canRead()) {
            // Get the command character
            cmd = bluetooth.getDatum();
            switch(cmd) {
                case 'b':                           // Button data
                    while(!bluetooth.canRead());    // Wait for next character
                    btnId = bluetooth.getDatum() - '0';
                    
                    switch(static_cast<ControllerButton>(btnId)) {
                        case ControllerButton::Play:
                            usb.pressKey(HID_KEY_SPACE);
                            usb.releaseKey();
                            break;
                            
                        case ControllerButton::MouseLeft:
                            usb.clickMouse(1);
                            break;
                            
                        case ControllerButton::MouseRight:
                            usb.clickMouse(0);
                            break;
                            
                        case ControllerButton::Rewind:
                            usb.pressKey(HID_KEY_ARROW_LEFT);
                            break;
                            
                        case ControllerButton::FastForward:
                            usb.pressKey(HID_KEY_ARROW_RIGHT);
                            break;
                            
                        case ControllerButton::SlowRewind:
                            usb.pressKey(HID_KEY_ARROW_UP);
                            break;
                            
                        case ControllerButton::SlowForward:
                            usb.pressKey(HID_KEY_ARROW_DOWN);
                            break;
                            
                        case ControllerButton::Previous:
                            usb.pressKey(HID_KEY_ARROW_LEFT);
                            usb.releaseKey();
                            break;
                            
                        case ControllerButton::Next:
                            usb.pressKey(HID_KEY_ARROW_RIGHT);
                            usb.releaseKey();
                            break;
                        
                        case ControllerButton::None:
                            usb.releaseKey();
                            break;
                    }
                    
                    // Wait for '\n' '\0'
                    while(!bluetooth.canRead());
                    bluetooth.getDatum();
                    while(!bluetooth.canRead());
                    bluetooth.getDatum();
                    break;
                
                case 'x':                           // Stick x position
                    // Get the number from the formatted string: x %u \n \0
                    i = 0;
                    while(!bluetooth.canRead());
                    curr = bluetooth.getDatum();
                    while(curr != '\n') {           // Get (up to) 4 chars of num
                        stickVal[i++] = curr;
                        
                        while(!bluetooth.canRead());
                        curr = bluetooth.getDatum();
                    }
                    
                    // Wait for '\0'
                    while(!bluetooth.canRead());
                    bluetooth.getDatum();
                    
                    stickX = atoi((char *) stickVal);
                    break;
                
                case 'y':                           // Stick y position
                    // Get the number from the formatted string: x %u \n \0
                    i = 0;
                    while(!bluetooth.canRead());
                    curr = bluetooth.getDatum();
                    while(curr != '\n') {           // Get (up to) 4 chars of num
                        stickVal[i++] = curr;
                        
                        while(!bluetooth.canRead());
                        curr = bluetooth.getDatum();
                    }
                    
                    // Wait for '\0'
                    while(!bluetooth.canRead());
                    bluetooth.getDatum();
                    
                    stickY = atoi((char *) stickVal);
                    break;
            }
        }
        
        // Do something like usb.mouseMove(stickX, stickY)
    }*/
    
    return 0;
}

void testReceiveBluetooth() {
    const Hc05 bluetooth;
    
    while(1) {
        while(bluetooth.canRead()) {
            printf("%c", bluetooth.getDatum());
        }
    }
}
