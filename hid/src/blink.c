#include "stdio.h"
#include "bsp/board.h"
#include "blink.h"

uint32_t start_ms_g = 0;
char led_state_g = 0;
uint32_t curr_blink_interval_g = blink.delay_unmounted;

void blink__update_task(void) {
    // Blink every interval ms
    if(board_millis() - start_ms_g < curr_blink_interval_g) {
        // Not enough time
        return;
    }
    start_ms_g += curr_blink_interval_g;

    board_led_write(led_state_g);
    led_state_g = !led_state_g;               // toggle
}
