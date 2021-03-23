/*
 * This file contains an interface for getting info from
 * the buttons through the gpio system
 */
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

void controller__init(void);

static const struct {
    void (*init)(void);
} controller = {
    controller__init
};

#endif
