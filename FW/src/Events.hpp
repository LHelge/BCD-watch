#ifndef _EVENTS_HPP
#define _EVENTS_HPP

#include "stddef.h"

enum Events : uint8_t {
    None = 0,
    Tick,
    ButtonPress,
    ButtonLongPress,
    ButtonHold,
    TiltLeft,
    TiltRight,
    TiltUp,
    TiltDown
};


static constexpr size_t EventQueueLength = 64;

#endif
