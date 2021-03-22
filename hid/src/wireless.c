#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "nrf24l01.h"
#include "wireless.h"

static inline void cs_select(uint cs_pin) {
    asm volatile("nop \n nop \n nop"); // FIXME
    gpio_put(cs_pin, 0);
    asm volatile("nop \n nop \n nop"); // FIXME
}

static inline void cs_deselect(uint cs_pin) {
    asm volatile("nop \n nop \n nop"); // FIXME
    gpio_put(cs_pin, 1);
    asm volatile("nop \n nop \n nop"); // FIXME
}

static inline void config_register(uint8_t reg, uint8_t value) {
    cs_select(wireless.cs);
    uint8_t cmd = W_REGISTER | (REGISTER_MASK & reg);
    spi_write_blocking(spi0, &cmd, 1);
    spi_write_blocking(spi0, &value, 1);
    cs_deselect(wireless.cs);
}

static inline void transmit_sync(uint8_t *data_out, uint8_t len) {
    spi_write_blocking(spi0, data_out, len);
}

static inline void transfer_sync(uint8_t *data_out, uint8_t len) {
    spi_read_blocking(spi0, 0, data_out, len);
}

static inline void write_register(uint8_t reg, uint8_t *value, uint8_t len) {
    cs_select(wireless.cs);
    uint8_t cmd = W_REGISTER | (REGISTER_MASK & reg);
    spi_write_blocking(spi0, &cmd, 1);
    transmit_sync(value, len);
    cs_deselect(wireless.cs);
}

static inline void read_register(uint8_t reg, uint8_t *value, uint8_t len) {
    cs_select(wireless.cs);
    uint8_t cmd = R_REGISTER | (REGISTER_MASK & reg);
    spi_write_blocking(spi0, &cmd, 1);
    transfer_sync(value, len);
    cs_deselect(wireless.cs);
}

static inline void set_transmit_addr(uint8_t *addr) {
    write_register(RX_ADDR_P0, addr, ADDR_LEN);
    write_register(TX_ADDR, addr, ADDR_LEN);
}

static inline void set_receiving_addr(uint8_t *addr) {
    write_register(RX_ADDR_P1, addr, ADDR_LEN);
}

static inline uint8_t get_status(void) {
    uint8_t rv;
    read_register(STATUS, &rv, 1);
    return rv;
}

static inline char rx_fifo_empty(void) {
    uint8_t fifo_status;
    read_register(FIFO_STATUS, &fifo_status, 1);
    return (fifo_status & (1 << RX_EMPTY));
}

void wireless__init(void) {
    // Initialize SPI
    spi_init(spi0, wireless.spi_speed);
    
    gpio_set_function(wireless.miso, GPIO_FUNC_SPI);
    gpio_set_function(wireless.sck, GPIO_FUNC_SPI);
    gpio_set_function(wireless.mosi, GPIO_FUNC_SPI);

    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_init(wireless.cs);
    gpio_put(wireless.cs, 1);
    gpio_set_dir(wireless.cs, GPIO_OUT);
    
    // Configure NRF24L01
    config_register(RF_CH, wireless.channel);
    config_register(RX_PW_P0, wireless.payload);
    config_register(RX_PW_P1, wireless.payload);
    set_transmit_addr((uint8_t *) "radi1");
    set_receiving_addr((uint8_t *) "radio");
}

char wireless__data_ready(void) {
    uint8_t status = get_status();
    if(status & (1 << RX_DR)) {
        return 1;
    }
    return !rx_fifo_empty();
}

void wireless__get_data(uint8_t data[16]) {
    cs_select(wireless.cs);
    uint8_t cmd = R_RX_PAYLOAD;
    spi_write_blocking(spi0, &cmd, wireless.payload);
    transfer_sync(data, wireless.payload);
    cs_deselect(wireless.cs);
    config_register(STATUS, (1 << RX_DR));      // Reset status register
}
