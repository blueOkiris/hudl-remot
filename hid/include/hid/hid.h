/*
 * This file contains the code for how the actual hid will interact with things
 * Mainly, it contains the task() function
 */

#ifndef _HID_H_
#define _HID_H_

void hid__update(void);
void hid__move_mouse(int delta_x, int delta_y);
void hid__press_key(unsigned char key);

static const struct {
    int poll_interval_ms;
    
    void (*update)(void);
    void (*move_mouse)(int, int);
    void (*press_key)(unsigned char);
} hid = {
    10,
    hid__update,
    hid__move_mouse,
    hid__press_key
};

#endif