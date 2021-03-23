/*
 * This file contains information for wireless communication
 * over HC-05 bluetooth, specifically receiving
 */

#ifndef _WIRELESS_H_
#define _WIRELESS_H_

#define CMD_MODE_BAUD   38400
#define TXT_MODE_BAUD   9600
#define UART0_TX_PIN    0
#define UART0_RX_PIN    1

void wireless__init(void);
char wireless__ready(void);
uint8_t wireless__get_datum(void);
void wireless__print_addr(void);

static const struct {
    void (*init)(void);
    char (*ready)(void);
    uint8_t (*get_datum)(void);
    void (*print_addr)(void);
} wireless = {
    wireless__init,
    wireless__ready,
    wireless__get_datum,
    wireless__print_addr
};

#endif
