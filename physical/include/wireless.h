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

void wireless__init(char *slave_addr);
void wireless__put_data(char *str);

static const struct {
    void (*init)(char *);
    void (*put_data)(char *);
} wireless = {
    wireless__init,
    wireless__put_data
};

#endif
