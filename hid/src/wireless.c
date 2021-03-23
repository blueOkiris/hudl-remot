#include "pico/stdlib.h"
#include "hardware/uart.h"

#include "wireless.h"

void wireless__init(void) {
    gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);
    
    uart_init(uart0, CMD_MODE_BAUD);    // Set into command mode
    uart_puts(uart0, "AT+ROLE=0\r\n");  // Reprogram as slave
    uart_deinit(uart0);                 // Leave command mode
    
    uart_init(uart0, TXT_MODE_BAUD);    // Enter text mode
}

char wireless__ready(void) {
    return uart_is_readable(uart0);
}

uint8_t wireless__get_datum(void) {
    return uart_getc(uart0);
}
