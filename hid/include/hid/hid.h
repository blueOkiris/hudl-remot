/*
 * This file contains the code for how the actual hid will interact with things
 * Mainly, it contains the task() function
 */

#ifndef _HID_H_
#define _HID_H_

void hid__init(void);
void hid__update(void);
void hid__move_mouse(int delta_x, int delta_y);
void hid__mouse_click(char left_btn);
void hid__press_key(unsigned char key);
void hid__release_key(void);
char hid__is_key_pressed(unsigned char key);

static const struct {
    int poll_interval_ms;
    
    void (*init)(void);
    void (*update)(void);
    void (*move_mouse)(int, int);
    void (*mouse_click)(char left_btn);
    void (*press_key)(unsigned char);
    void (*release_key)(void);
    char (*is_key_pressed)(unsigned char);
} hid = {
    10,
    hid__init,
    hid__update,
    hid__move_mouse,
    hid__mouse_click,
    hid__press_key,
    hid__is_key_pressed
};

#endif
