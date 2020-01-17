#ifndef _BUTTON_HPP
#define _BUTTON_HPP

#include "GPIO.hpp"
#include "stdint.h"
#include "stdbool.h"
#include "Events.hpp"
#include "Task.hpp"
#include "Queue.hpp"

namespace Button {

    class PushButton : public FreeRTOS::Task<256> {
    public:
        PushButton(GPIO::Pin *pin, FreeRTOS::Queue<Events, EventQueueLength> *eventQueue);

        void Run() override;
    private:
        GPIO::Pin *m_pin;
        FreeRTOS::Queue<Events, EventQueueLength> *m_eventQueue;
        static constexpr uint32_t ButtonPeriodMilliseconds = 100;
    };
}

#endif
