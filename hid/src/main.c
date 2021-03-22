#include "pico/stdlib.h"
#include "bsp/board.h"
#include "bsp/board.h"
#include "tusb.h"

#include "wireless.h"
#include "blink.h"
#include "hid.h"

int main() {
    // Initialize the HID libraries (from pico-sdk)
    board_init();
    tusb_init();
    
    wireless.init();
    char rf_buffer[16];
    
    while(1) {
        tud_task();             // Device task for usb
        blink.update_task();    // Show device state
        hid.update();           // Go through update process
        
        if(wireless.data_ready()) {
            wireless.get_data(rf_buffer);
        }
    }
    
    return 0;
}