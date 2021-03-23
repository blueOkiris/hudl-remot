#include "pico/stdlib.h"
#include "controller.h"

void controller__init(void) {
    // Initialize buttons
    for(int i = 0; i < 9; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
    }
}

char controller__button_pressed(void) {
    for(int i = 0; i < 9; i++) {        // Go through all the buttons in order
        char btn_state = gpio_get(i);
        if(btn_state) {
            return i;                   // Return the first one pressed
        }
    }
    return 0;                           // Otherwise return no btns pressed
}
