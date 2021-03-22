#ifndef _WIRELESS_H_
#define _WIRELESS_H_

void wireless__init(void);
char wireless__data_ready(void);
void wireless__get_data(uint8_t data[16]);

static const struct {
    unsigned int miso, cs, sck, mosi, ce;
    unsigned int spi_speed;
    uint8_t channel, payload;
    void (*init)(void);
    char (*data_ready)(void);
    void (*get_data)(uint8_t data[16]);
} wireless = {
    4, 5, 6, 7, 8,
    10000000,
    1, 16,
    wireless__init,
    wireless__data_ready,
    wireless__get_data
};

#endif
