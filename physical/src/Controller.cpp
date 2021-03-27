#include <pico/stdlib.h>
#include <hardware/adc.h>
#include <Controller.hpp>

using namespace hudlremot;
Controller::Controller() {
    // Initialize buttons (skip 0 and 1 as those are fo uart)
    for(int i = 0; i < 9; i++) {
        gpio_init(i + 2);
        gpio_set_dir(i + 2, GPIO_IN);
        gpio_pull_up(i + 2);
    }
    
    // Initialize thumbstick
    adc_init();
    adc_gpio_init(CONT_ADC_X);
    adc_gpio_init(CONT_ADC_Y);
}

uint8_t Controller::buttonState() const {
    for(int i = 0; i < 9; i++) {        // Go through all the buttons in order
        if(!gpio_get(i + 2)) {
            return i;                   // Return the first one pressed
        }
    }
    return 0;                           // Otherwise return no btns pressed
}

void Controller::readThumbstick(uint16_t &x, uint16_t &y) const {
    adc_select_input(CONT_ADC_X_NUM);
    x = adc_read();
    adc_select_input(CONT_ADC_Y_NUM);
    y = adc_read();
}
