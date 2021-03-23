#include <stdio.h>
#include "pico/stdlib.h"
//#include "bsp/board.h"
//#include "bsp/board.h"
//#include "tusb.h"

#include "wireless.h"
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
    
    while(1) {
        //tud_task();             // Device task for usb
        //blink.update_task();    // Show device state
        //hid.update();           // Go through update process
        
        while(wireless.ready()) {
            printf("%c", wireless.get_datum());
        }
    }
    
    return 0;
}