#include "stdio.h"
#include "tusb.h"
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

// Device callbacks
// Invoked when device is mounted
void tud_mount_cb(void) {
    curr_blink_interval_g = blink.delay_mounted;
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
    curr_blink_interval_g = blink.delay_unmounted;
}

/*
 * Invoked when usb bus is suspended
 * remote_wakeup_en : if host allow us  to perform remote wakeup
 * Within 7ms, device must draw an average of current less than 2.5 mA from bus
 */
void tud_suspend_cb(bool remote_wakeup_en) {
    (void) remote_wakeup_en;
    curr_blink_interval_g = blink.delay_suspended;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void) {
    curr_blink_interval_g = blink.delay_mounted;
}
