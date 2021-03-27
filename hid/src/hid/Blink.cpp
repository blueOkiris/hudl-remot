#include <stdio.h>
#include <tusb.h>
#include <bsp/board.h>
#include <Blink.hpp>

using namespace hudlremot;

BlinkerDelay Blinker::currBlinkInterval = BlinkerDelay::Unmounted;

void Blinker::updateTask(void) {
    // Blink every interval ms
    if(board_millis() - _startMs < static_cast<uint32_t>(currBlinkInterval)) {
        // Not enough time
        return;
    }
    _startMs += static_cast<uint32_t>(currBlinkInterval);

    board_led_write(_ledState);
    _ledState = !_ledState;                 // toggle
}

// Device callbacks
// Invoked when device is mounted
void tud_mount_cb(void) {
    Blinker::currBlinkInterval = BlinkerDelay::Mounted;
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
    Blinker::currBlinkInterval = BlinkerDelay::Mounted;
}

/*
 * Invoked when usb bus is suspended
 * remote_wakeup_en : if host allow us  to perform remote wakeup
 * Within 7ms, device must draw an average of current less than 2.5 mA from bus
 */
void tud_suspend_cb(bool remote_wakeup_en) {
    (void) remote_wakeup_en;
    Blinker::currBlinkInterval = BlinkerDelay::Suspended;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void) {
    Blinker::currBlinkInterval = BlinkerDelay::Mounted;
}
