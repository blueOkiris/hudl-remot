/*
 * This file contains the code for how the actual hid will interact with things
 * Mainly, it contains the task() function
 */

#ifndef _HID_H_
#define _HID_H_

void hid__task(void);

static struct {
    void (*task)(void);
} hid = {
    hid__task
};

#endif
