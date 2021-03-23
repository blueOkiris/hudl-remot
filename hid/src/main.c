#include <stdio.h>
#include "pico/stdlib.h"
#include "wireless.h"
//#include "hid.h"

int main() {
    // Remove when using hid
    stdio_init_all();
    sleep_ms(1000);
    printf("Hello, world!\n");
    
    wireless.init();
    //hid.init();
    
    char cmd;
    while(1) {
        //hid.update();                 // Go through update process
        
        while(wireless.ready()) {
            printf("%c", wireless.get_datum());
            
            // Get the command character
            cmd = wireless.get_datum();
            while(!wireless.ready());   // Wait for next character
            switch(cmd) {
                case 'b':               // Button data
                    break;
                
                case 'x':               // Stick x position
                    break;
                
                case 'y':               // Stick y position
                    break;
            }
        }
    }
    
    return 0;
}
