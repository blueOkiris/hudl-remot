#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/uart.h>
#include <Wireless.hpp>

using namespace hudlremot;

Hc05::Hc05(const bool isUart0) : _isUart0(isUart0) {
    gpio_set_function(_isUart0 ? UART0_TX_PIN : UART1_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(_isUart0 ? UART0_RX_PIN : UART1_RX_PIN, GPIO_FUNC_UART);
    
    uart_init(_isUart0 ? uart0 : uart1, BAUD);     // Set into command mode
}

bool Hc05::canRead() const {
    return uart_is_readable(_isUart0 ? uart0 : uart1);
}

uint8_t Hc05::getDatum() const {
    return uart_getc(_isUart0 ? uart0 : uart1);
}

// Only used for debug
void Hc05::putData(const char *str) const {
    uart_puts(_isUart0 ? uart0 : uart1, str);
}
