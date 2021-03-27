/*
 * This maps all the button characters
 * to a def
 */

#pragma once

namespace hudlremot {
    enum class ControllerButton {
        None = 0,
        Play = 9,
        MouseLeft = 7,
        MouseRight = 8,
        Rewind = 4,
        FastForward = 1,
        SlowRewind = 5,
        SlowForward = 2,
        Previous = 6,
        Next = 3
    };
}
