#include "stddef.h"
#include "stdio.h"
#include "tusb.h"
#include "bsp/board.h"
#include "usb_descriptors.h"

#include "hid.h"

static uint32_t start_ms_g = 0;
static char has_key_g = 0, toggle_g = 0;

void hid__update(void) {
    // Not enough time
    if(board_millis() - start_ms_g < hid.poll_interval_ms) {
        return;
    }
    start_ms_g += hid.poll_interval_ms;

    // Remote wakeup
    if (tud_suspended()) {
        /*
         * Wake up host if we are in suspend mode
         * and REMOTE_WAKEUP feature is enabled by host
         */
        tud_remote_wakeup();
    }

    // Mouse control
    if(tud_hid_ready()) {
        if(hid.delta_x != 0 || hid.delta_y != 0) {
            tud_hid_mouse_report(
                REPORT_ID_MOUSE, 0x00, 
                hid.delta_x, hid.delta_y,
                0, 0
            );
            hid.delta_x = hid.delta_y = 0;

            // delay a bit before attempt to send keyboard report
            board_delay(10);
        }
    }

    // Keyboard control
    if (tud_hid_ready()) {
        if(hid.key != 0 && (toggle_g = !toggle_g)) {
            uint8_t keycode[6] = { 0 };
            keycode[0] = hid.key;

            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            
            has_key_g = 1;
            hid.key = 0;
        } else {
            // send empty key report if previously has key pressed
            if(has_key_g) {
                tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
            }
            has_key_g = 0;
        }
    }
}