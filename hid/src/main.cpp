#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pico/stdlib.h>
#include <bsp/board.h>
#include <ButtonIds.hpp>
#include <Wireless.hpp>
#include <Hid.hpp>

using namespace hudlremot;

void testReceiveBluetooth();
void testStickXBluetoothParse();

int main() {
    // Remove when using usb
    stdio_init_all();
    
    //testReceiveBluetooth();
    //testStickXBluetoothParse();
    
    const Hc05 bluetooth(false);
    UsbHid usb;
    
    while(1) {
        if(bluetooth.canRead()) {
            // Get the command character
            auto curr = bluetooth.getDatum();
            if(curr == 'x') {
                usb.moveMouse(-4, 0);
            }
        }
        usb.update();
    }
    
    return 0;
}

void testReceiveBluetooth() {
    const Hc05 bluetooth(false);
    
    while(1) {
        while(bluetooth.canRead()) {
            printf("%c", bluetooth.getDatum());
        }
    }
}

void testStickXBluetoothParse() {
    const Hc05 bluetooth(false);
    
    char stickVal[5];
    while(1) {
        if(bluetooth.canRead()) {
            auto curr = bluetooth.getDatum();
            if(curr == 'x') {
                int i = 0;
                
                while(!bluetooth.canRead());
                curr = bluetooth.getDatum();
                
                while(curr != '\r') {
                    stickVal[i++] = curr;
                    
                    while(!bluetooth.canRead());
                    curr = bluetooth.getDatum();
                }
                
                stickVal[4] = '\0';
                uint16_t stickX = atoi((char *) stickVal);
                int16_t moveX = (static_cast<int16_t>(stickX) - 435) / 50;
                
                printf(
                    "Received: \"%s\", Parsed: %u, Move: %d\r\n",
                    stickVal, stickX, moveX
                );
                
                for(int j = 0; j < 5; j++) {
                    stickVal[i] = '\0';
                }
            }
        }
    }
}
