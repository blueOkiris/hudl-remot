#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pico/stdlib.h>
#include <wireless.h>
#include <btn_ids.h>
//#include "hid.h"

int main() {
    // Remove when using hid
    stdio_init_all();
    sleep_ms(1000);
    printf("Hello, world!\n");
    
    wireless.init();
    //hid.init();
    
    // Debug print:
    wireless.print_addr();
    
    char cmd, btn_id, curr;
    int i;
    char stick_val[5];
    uint16_t stick_x, stick_y;
    while(1) {
        //hid.update();                         // Go through update process
        
        while(wireless.ready()) {
            printf("%c", wireless.get_datum());
            
            // Get the command character
            /*cmd = wireless.get_datum();
            switch(cmd) {
                case 'b':                       // Button data
                    while(!wireless.ready());   // Wait for next character
                    btn_id = wireless.get_datum();
                    
                    switch(btn_id) {
                        case CONT_BTN_PLAY:
                            hid.press_key(HID_KEY_SPACE);
                            hid.release_key();
                            break;
                            
                        case CONT_BTN_MOUSE_LEFT:
                            hid.mouse_click(1);
                            break;
                            
                        case CONT_BTN_MOUSE_RIGHT:
                            hid.mouse_click(0);
                            break;
                            
                        case CONT_BTN_REWIND:
                            hid.press_key(HID_KEY_ARROW_LEFT);
                            break;
                            
                        case CONT_BTN_FAST_FORWARD:
                            hid.press_key(HID_KEY_ARROW_RIGHT);
                            break;
                            
                        case CONT_BTN_SLOW_REWIND:
                            hid.press_key(HID_KEY_ARROW_UP);
                            break;
                            
                        case CONT_BTN_SLOW_FORWARD:
                            hid.press_key(HID_KEY_ARROW_DOWN);
                            break;
                            
                        case CONT_BTN_PREV:
                            hid.press_key(HID_KEY_ARROW_LEFT);
                            hid.release_key();
                            break;
                            
                        case CONT_BTN_NEXT:
                            hid.press_key(HID_KEY_ARROW_RIGHT);
                            hid.release_key();
                            break;
                        
                        case '0':
                            hid.release_key();
                            break;
                    }
                    
                    // Wait for '\n' '\0'
                    while(!wireless.ready());
                    wireless.get_datum();
                    while(!wireless.ready());
                    wireless.get_datum();
                    break;
                
                case 'x':                       // Stick x position
                    // Get the number from the formatted string: x %u \n \0
                    i = 0;
                    while(!wireless.ready());
                    curr = wireless.get_datum();
                    while(curr != '\n') {       // Get (up to) 4 chars of num
                        stick_val[i++] = curr;
                        
                        while(!wireless.ready());
                        curr = wireless.get_datum();
                    }
                    
                    // Wait for '\0'
                    while(!wireless.ready());
                    wireless.get_datum();
                    
                    stick_x = atoi((char *) stick_val);
                    break;
                
                case 'y':                       // Stick y position
                    // Get the number from the formatted string: x %u \n \0
                    i = 0;
                    while(!wireless.ready());
                    curr = wireless.get_datum();
                    while(curr != '\n') {       // Get (up to) 4 chars of num
                        stick_val[i++] = curr;
                        
                        while(!wireless.ready());
                        curr = wireless.get_datum();
                    }
                    
                    // Wait for '\0'
                    while(!wireless.ready());
                    wireless.get_datum();
                    
                    stick_y = atoi((char *) stick_val);
                    break;
            }*/
        }
        
        // Do something like hid.move_mouse(stick_x, stick_y)
    }
    
    return 0;
}
