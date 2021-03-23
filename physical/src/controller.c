#include <pico/stdlib.h>
#include <hardware/adc.h>
#include <controller.h>

void controller__init(void) {
    // Initialize buttons
    for(int i = 0; i < 9; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
    }
    
    // Initialize thumbstick
    adc_init();
    adc_gpio_init(CONT_ADC_X);
    adc_gpio_init(CONT_ADC_Y);
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

void controller__read_thumbstick(uint16_t *ref_x, uint16_t *ref_y) {
    adc_select_input(CONT_ADC_X_NUM);
    *ref_x = adc_read();
    adc_select_input(CONT_ADC_Y_NUM);
    *ref_y = adc_read();
}
