# Hudl Remot

## Description

The software repo for a cheap alternative to the Hudl remote devices

Unfortunately, the pico uses the Cmake build system which is an utter piece of garbage, so you'll have to deal with that to build the project. Sorry. Nothing I can do.

The project is separated into two parts:
 * The HID device which acts as a mouse and keyboard on the computer to control Hudl
 * The Physical device which takes button and PSP thumbstick inputs and sends them to the HID device

Now, the Pico is overkill for this project. However, at $4, it's not unreasonable to use them, so why the heck not?
