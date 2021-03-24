#include <stddef.h>
#include <stdio.h>
#include <tusb.h>
#include <bsp/board.h>
#include <usb_descriptors.h>

#include <blink.h>
#include <hid.h>

static uint32_t start_ms_g = 0;
static char has_key_g = 0, toggle_g = 0, release_g = 0;
static int delta_x_g = 0, delta_y_g = 0;
static unsigned char key_g = 0, mouse_btn = 0;

void hid__init(void) {
    board_init();
    tusb_init();
}

void hid__release_key(void) {
    release_g = 1;
}

void hid__press_key(unsigned char key) {
    key_g = key;
    release_g = 0;                  // force release
}

void hid__move_mouse(int delta_x, int delta_y) {
    delta_x_g = delta_x;
    delta_y_g = delta_y;
}

void hid__mouse_click(char left_btn) {
    if(left_btn) {
        mouse_btn = MOUSE_BUTTON_LEFT;
    } else {
        mouse_btn = MOUSE_BUTTON_RIGHT;
    }
}

void hid__update(void) {
    // HID library stuff
    tud_task();                     // Device task for usb
    blink.update_task();            // Show device state
    
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
        if(delta_x_g != 0 || delta_y_g != 0 || mouse_btn != 0) {
            tud_hid_mouse_report(
                REPORT_ID_MOUSE, mouse_btn, 
                delta_x_g, delta_y_g,
                0, 0
            );
            delta_x_g = delta_y_g = 0;
            mouse_btn = 0;

            // delay a bit before attempt to send keyboard report
            board_delay(10);
        }
    }

    // Keyboard control
    if (tud_hid_ready()) {
        if(key_g != 0 && (toggle_g = !toggle_g) && !has_key_g) {
            uint8_t keycode[6] = { 0 };
            keycode[0] = key_g;

            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            
            has_key_g = 1;
            key_g = 0;
        } else if(release_g) {
            // send empty key report if previously has key pressed
            if(has_key_g) {
                tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
            }
            has_key_g = 0;
        }
    }
}