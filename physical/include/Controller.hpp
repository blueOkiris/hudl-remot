/*
 * This file contains an interface for getting info from
 * the buttons through the gpio system
 */

#pragma once

#define CONT_ADC_X              26
#define CONT_ADC_X_NUM          0
#define CONT_ADC_Y              27
#define CONT_ADC_Y_NUM          1

#define X_MAX                   3200
#define X_MIN                   800
#define Y_MAX                   3500
#define Y_MIN                   885

namespace hudlremot {
    class Controller {
        public:
            Controller();
            
            uint8_t buttonState() const;
            void readThumbstick(uint16_t &x, uint16_t &y) const;
    };
}
