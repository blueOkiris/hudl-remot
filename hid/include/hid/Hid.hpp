/*
 * This file contains the code for how the actual hid will interact with things
 * Mainly, it contains the task() function
 */

#pragma once

#include <Blink.hpp>

namespace hudlremot {
    class UsbHid {
        private:
            const int _pollIntervalMs;
            Blinker _led;
            
            uint32_t _startMs;
            bool _hasKey, _toggle, _release;
            int _deltaX, _deltaY;
            uint8_t _key, _mouseBtn;
        
        public:
            UsbHid();
            
            void update();
            void moveMouse(const int deltaX, const int deltaY);
            void clickMouse(const bool isLeftBtn);
            void pressKey(const uint8_t key);
            void releaseKey();
            bool isKeyPressed(const uint8_t key);
    };
}
