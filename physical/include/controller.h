/*
 * This file contains an interface for getting info from
 * the buttons through the gpio system
 */
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#define CONT_BTN_NONE           0
#define CONT_BTN_PLAY           1
#define CONT_BTN_MOUSE_LEFT     2
#define CONT_BTN_MOUSE_RIGHT    3
#define CONT_BTN_REWIND         4
#define CONT_BTN_FAST_FORWARD   5
#define CONT_BTN_SLOW_REWIND    6
#define CONT_BTN_SLOW_FORWARD   7
#define CONT_BTN_PREV           8
#define CONT_BTN_NEXT           9

#define CONT_ADC_X              26
#define CONT_ADC_X_NUM          0
#define CONT_ADC_Y              27
#define CONT_ADC_Y_NUM          1

void controller__init(void);
char controller__button_pressed(void);
void controller__read_thumbstick(uint16_t *ref_x, uint16_t *ref_y);

static const struct {
    void (*init)(void);
    char (*button_pressed)(void);
    void (*read_thumbstick)(uint16_t *ref_x, uint16_t *ref_y);
} controller = {
    controller__init,
    controller__button_pressed,
    controller__read_thumbstick
};

#endif
