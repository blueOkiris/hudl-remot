/*
 * This file contains the code for how the actual hid will interact with things
 * Mainly, it contains the task() function
 */

#ifndef _HID_H_
#define _HID_H_

void hid__update(void);

static struct {
    const int poll_interval_ms;
    int delta_x, delta_y;
    unsigned char key;
    
    void (*update)(void);
} hid = {
    10,
    0, 0,
    0,
    hid__update
};

#endif
