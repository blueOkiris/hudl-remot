#include <pico/stdlib.h>
#include <hardware/uart.h>
#include <wireless.h>

void wireless__init(void) {
    gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);
    
    uart_init(uart0, CMD_MODE_BAUD);    // Set into command mode
    uart_puts(uart0, "AT+ROLE=1\r\n");  // Reprogram as master
    uart_deinit(uart0);                 // Leave command mode
    
    uart_init(uart0, TXT_MODE_BAUD);    // Enter text mode
}

void wireless__put_data(char *str) {
    uart_puts(uart0, str);
}
