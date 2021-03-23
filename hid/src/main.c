#include <stdio.h>
#include "pico/stdlib.h"
#include "wireless.h"
#include "btn_ids.h"
//#include "hid.h"

int main() {
    // Remove when using hid
    stdio_init_all();
    sleep_ms(1000);
    printf("Hello, world!\n");
    
    wireless.init();
    //hid.init();
    
    char cmd, btn_id;
    while(1) {
        //hid.update();                         // Go through update process
        
        while(wireless.ready()) {
            printf("%c", wireless.get_datum());
            
            // Get the command character
            cmd = wireless.get_datum();
            switch(cmd) {
                case 'b':                       // Button data
                    while(!wireless.ready());   // Wait for next character
                    btn_id = wireless.get_datum();
                    
                    switch(btn_id) {
                        case CONT_BTN_PLAY:
                            break;
                        case CONT_BTN_MOUSE_LEFT:
                            break;
                        case CONT_BTN_MOUSE_RIGHT:
                            break;
                        case CONT_BTN_REWIND:
                            break;
                        case CONT_BTN_FAST_FORWARD:
                            break;
                        case CONT_BTN_SLOW_REWIND:
                            break;
                        case CONT_BTN_SLOW_FORWARD:
                            break;
                        case CONT_BTN_PREV:
                            break;
                        case CONT_BTN_NEXT:
                            break;
                    }
                    
                    // Wait for '\n' '\0'
                    while(!wireless.ready());
                    wireless.get_datum();
                    while(!wireless.ready());
                    wireless.get_datum();
                    break;
                
                case 'x':                       // Stick x position
                    break;
                
                case 'y':                       // Stick y position
                    break;
            }
        }
    }
    
    return 0;
}
