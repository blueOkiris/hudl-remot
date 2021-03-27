/*
 * This file contains information for wireless communication
 * over HC-05 bluetooth, specifically receiving
 */

#pragma once

#define BAUD            38400
#define UART            uart0
#define UART_TX_PIN     0
#define UART_RX_PIN     1

namespace hudlremot {
    class Hc05 {
        public:
            Hc05();
            
            bool canRead() const;
            uint8_t getDatum() const;
            void putData(const char *str) const;
    };
}
