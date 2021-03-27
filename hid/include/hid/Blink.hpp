/*
 * This file contains code for updating a blink on the hid device
 * If the device is unmounted, it blinks quickly
 * If the device is mounted, it blinks slowly
 * If the device is suspended, it blinks REALLY slowly
 */

#pragma once

namespace hudlremot {
    enum class BlinkerDelay {
        Unmounted = 250,
        Mounted = 1000,
        Suspended = 2500
    };
    
    class Blinker {
        private:
            uint32_t _startMs;
            bool _ledState;
            
        public:
            /*
             * This must be public static b/c tud_... functions need access
             * This is nonnegotiable. Those functions can't be under this class
             * And they must exist
             */
            static BlinkerDelay currBlinkInterval;
            
            void updateTask();
    };
}
