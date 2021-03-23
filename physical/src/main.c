#include "stdio.h"
#include "pico/stdlib.h"
#include "wireless.h"
#include "controller.h"

int main() {
    stdio_init_all();
    sleep_ms(1000);
    printf("Hello, world!\n");
    
    wireless.init();
    controller.init();
    
    while(1) {
        char button_state = controller.button_pressed();
        if(button_state) {
            char msg[2] = { button_state + '0', '\0' };
            wireless.put_data((char *) msg);
        }
    }
}
