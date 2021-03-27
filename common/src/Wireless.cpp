#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/uart.h>
#include <Wireless.hpp>

using namespace hudlremot;

Hc05::Hc05() {
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    uart_init(UART, BAUD);              // Set into command mode
    
}

bool Hc05::canRead() const {
    return uart_is_readable(UART);
}

uint8_t Hc05::getDatum() const {
    return uart_getc(UART);
}

// Only used for debug
void Hc05::putData(const char *str) const {
    uart_puts(UART, str);
}
