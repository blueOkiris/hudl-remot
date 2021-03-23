/*
 * This file contains code for updating a blink on the hid device
 * If the device is unmounted, it blinks quickly
 * If the device is mounted, it blinks slowly
 * If the device is suspended, it blinks REALLY slowly
 */

#ifndef _BLINK_H_
#define _BLINK_H_

// Methods
void blink__update_task(void);

// Use this struct like a C++ object
static const struct {
    int delay_unmounted, delay_mounted, delay_suspended;
    void (*update_task)(void);
} blink = {
    250, 1000, 2500,
    blink__update_task
};

#endif
