#include <stdio.h>
#include "pico/stdlib.h"
//#include "bsp/board.h"
//#include "bsp/board.h"
//#include "tusb.h"

#include "../include/wireless.h"
//#include "blink.h"
//#include "hid.h"

int main() {
    // Remove when using hid
    stdio_init_all();
    sleep_ms(1000);
    printf("Hello, world!\n");
    
    // Initialize the HID libraries (from pico-sdk)
    //board_init();
    //tusb_init();
    
    wireless.init();
    char rf_buffer[16];
    
    while(1) {
        //tud_task();             // Device task for usb
        //blink.update_task();    // Show device state
        //hid.update();           // Go through update process
        
        if(wireless.data_ready()) {
            wireless.get_data(rf_buffer);
            printf("Data: ");
            for(int i = 0; i < wireless.payload; i++) {
                printf("%x ", rf_buffer[i]);
            }
            printf("\n");
        } else {
            printf("No data available.\n");
        }
    }
    
    return 0;
}