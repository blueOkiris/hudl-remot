# Hudl Remot

## Description

The software repo for a cheap alternative to the Hudl remote devices

Because the Pico is designed to be used with Circuit Python, I don't like the C Make build system, and performance is not a large concern, I will be programming this in Python for ease of use.

The project is separated into two parts:
 * The HID device which acts as a mouse and keyboard on the computer to control Hudl
 * The Physical device which takes button and PSP thumbstick inputs and sends them to the HID device

Now, the Pico is overkill for this project. However, at $4, it's not unreasonable to use them, so why the heck not?

## Programming

To program either of the devices:
 * Plug in the pico while holding the bootselect button
 * Copy the python.uf2 file to the device which will cause it to reboot and remount as a CIRCUITPY drive
 * Then copy the corresponding program to the drive and you're done!
