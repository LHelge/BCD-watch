#ifndef _BUTTON_HPP
#define _BUTTON_HPP

#include "gpio.hpp"
#include "stdint.h"
#include "stdbool.h"
#include "Events.hpp"

namespace Button {

    class PushButton {
    public:
        PushButton(GPIO::Pin *pin);
        Events Tick();

    private:
        GPIO::Pin *m_pin;
        uint32_t m_timer;
        bool m_pressed;
    };
}

#endif