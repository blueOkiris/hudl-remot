/*
 * This file contains information for wireless communication
 * over HC-05 bluetooth, specifically receiving
 */

#pragma once

#define BAUD            38400
#define UART0_TX_PIN    0
#define UART0_RX_PIN    1
#define UART1_TX_PIN    4
#define UART1_RX_PIN    5

namespace hudlremot {
    class Hc05 {
        private:
            const bool _isUart0;
            
        public:
            Hc05(const bool isUart0);
            
            bool canRead() const;
            void getData(uint8_t *data, const size_t len) const;
            void putData(const uint8_t *data, const size_t len) const;
    };
}
