#include "stddef.h"
#include "stdio.h"
#include "tusb.h"
#include "bsp/board.h"
#include "usb_descriptors.h"

#include "hid.h"

void hid__task(void) {
    // Poll every 10ms
    const uint32_t interval_ms = 10;
    static uint32_t start_ms = 0;

    if (board_millis() - start_ms < interval_ms) return; // not enough time
    start_ms += interval_ms;

    uint32_t const btn = 1;

    // Remote wakeup
    if (tud_suspended() && btn) {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    }

    /*------------- Mouse -------------*/
    if (tud_hid_ready()) {
        if (btn) {
            int8_t const delta = 5;

            // no button, right + down, no scroll pan
            tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, delta, delta, 0, 0);

            // delay a bit before attempt to send keyboard report
            board_delay(10);
        }
    }

    /*------------- Keyboard -------------*/
    if (tud_hid_ready()) {
        // use to avoid send multiple consecutive zero report for keyboard
        static bool has_key = false;

        static bool toggle = false;
        if (toggle = !toggle) {
            uint8_t keycode[6] = {0};
            keycode[0] = HID_KEY_A;

            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);

            has_key = true;
        } else {
            // send empty key report if previously has key pressed
            if (has_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
            has_key = false;
        }
    }
}