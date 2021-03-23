#include "stdio.h"
#include "pico/stdlib.h"
#include "wireless.h"
#include "controller.h"

int main() {
    stdio_init_all();
    sleep_ms(1000);
    printf("Hudl remote physical device\n");
    
    wireless.init();
    controller.init();
    
    char button_state;
    uint16_t stick_x, stick_y;
    char btn_msg[4] = { 'b', 0, '\n', '\0' };
    char stick_msg[16];
    while(1) {
        // If any buttons are pressed, send "b <button pin> \n"
        button_state = controller.button_pressed();
        if(button_state) {
            btn_msg[1] = button_state + '0';
            wireless.put_data((char *) btn_msg);
        }
        
        // Always send the current stick input as "x <x val> \n y <y val> \n"
        controller.read_thumbstick(&stick_x, &stick_y);
        sprintf(stick_msg, "x%u\ny%u\n", stick_x, stick_y);
        wireless.put_data((char *) stick_msg);
        
        // Add a tad of delay
        sleep_ms(50);
    }
}
