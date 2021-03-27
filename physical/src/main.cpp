#include <stdio.h>
#include <pico/stdlib.h>
#include <Wireless.hpp>
#include <Controller.hpp>

using namespace hudlremot;

void testBluetooth();

int main() {
    stdio_init_all();
    printf("Hudl remote physical device\n");
    
    //testBluetooth();
    
    const Hc05 bluetooth;
    const Controller controller;
    
    char btnState;
    uint16_t stickX, stickY;
    char btnMsg[5] = { 'b', 0, '\r', '\n', '\0' };
    char stickMsg[16];
    while(1) {
        // Send "b <button pin> \n"
        btnState = controller.buttonState();
        btnMsg[1] = btnState + '0';
        bluetooth.putData((char *) btnMsg);
        
        // Always send the current stick input as "x <x val> \n y <y val> \n"
        controller.readThumbstick(stickX, stickY);
        sprintf(stickMsg, "x%u\r\ny%u\r\n", stickX, stickY);
        bluetooth.putData((char *) stickMsg);
        
        // Add a tad of delay
        sleep_ms(10);
    }
}

void testBluetooth() {
    const Hc05 bluetooth;
    
    while(1) {
        bluetooth.putData("Hello, world!\r\n");
        sleep_ms(1000);
    }
}
