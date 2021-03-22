#include "stdio.h"
#include "pico/stdlib.h"
#include "wireless.h"

int main() {
    stdio_init_all();
    sleep_ms(1000);
    printf("Hello, world!\n");
    
    wireless.init();
    
    while(1) {
        wireless.put_data("Hello, world!\n");
        sleep_ms(1000);
    }
}