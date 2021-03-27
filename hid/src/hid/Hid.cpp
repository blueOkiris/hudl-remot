#include <stddef.h>
#include <stdio.h>
#include <tusb.h>
#include <bsp/board.h>
#include <usb_descriptors.h>

#include <Blink.hpp>
#include <Hid.hpp>

using namespace hudlremot;

UsbHid::UsbHid() :
        _pollIntervalMs(10), _led(),
        _startMs(0),
        _hasKey(false), _toggle(false), _release(false),
        _deltaX(0), _deltaY(0), _key(0), _mouseBtn(0) {
    board_init();
    tusb_init();
}

void UsbHid::releaseKey() {
    _release = true;
}

void UsbHid::pressKey(const uint8_t key) {
    _key = key;
    _release = false;               // force release
}

bool UsbHid::isKeyPressed(const uint8_t key) {
    return (_key == key) && !_release;
}

void UsbHid::moveMouse(const int deltaX, const int deltaY) {
    _deltaX = deltaX;
    _deltaY = deltaY;
}

void UsbHid::clickMouse(const bool isLeftBtn) {
    _mouseBtn = isLeftBtn ? MOUSE_BUTTON_LEFT : MOUSE_BUTTON_RIGHT;
}

void UsbHid::update() {
    // HID library stuff
    tud_task();                     // Device task for usb
    _led.updateTask();              // Show device state
    
    // Not enough time
    if(board_millis() - _startMs < _pollIntervalMs) {
        return;
    }
    _startMs += _pollIntervalMs;

    // Remote wakeup
    if(tud_suspended()) {
        /*
         * Wake up host if we are in suspend mode
         * and REMOTE_WAKEUP feature is enabled by host
         */
        tud_remote_wakeup();
    }

    // Mouse control
    if(tud_hid_ready()) {
        if(_deltaX != 0 || _deltaY != 0 || _mouseBtn != 0) {
            tud_hid_mouse_report(
                REPORT_ID_MOUSE, _mouseBtn, _deltaX, _deltaY, 0, 0
            );
            _deltaX = _deltaY = 0;
            _mouseBtn = 0;

            // delay a bit before attempt to send keyboard report
            board_delay(10);
        }
    }

    // Keyboard control
    if (tud_hid_ready()) {
        if(_key != 0 && (_toggle = !_toggle) && !_hasKey) {
            uint8_t keycode[6] = { 0 };
            keycode[0] = _key;

            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            
            _hasKey = true;
            _key = 0;
        } else if(_release) {
            // send empty key report if previously has key pressed
            if(_hasKey) {
                tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
            }
            _hasKey = 0;
        }
    }
}