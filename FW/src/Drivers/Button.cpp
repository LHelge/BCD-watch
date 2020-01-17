#include "Button.hpp"

#define BUTTONPRESS_LIMIT_LOW     (2)
#define BUTTONPRESS_LIMIT_SHORT  (15)
#define BUTTONPRESS_LIMIT_LONG   (25)
#define BUTTONPRESS_LIMIT_HOLD   (50)


namespace Button {
    PushButton::PushButton(GPIO::Pin *pin, FreeRTOS::Queue<Events, EventQueueLength> *eventQueue) : 
        Task("Btn", Task::LowPriority) 
    {
        m_pin = pin;
        m_eventQueue = eventQueue;
    }


    void PushButton::Run() {
        InitPeriod(ButtonPeriodMilliseconds);

        uint32_t downCounter = 0;
        Events event = Events::None;
        while(1) {
            event = Events::None;
            
            if(m_pin->Get()) {
                downCounter++;

                if(downCounter > BUTTONPRESS_LIMIT_HOLD) {
                    event = Events::ButtonHold;
                    m_eventQueue->Enqueue(&event, 0);
                }
            }
            else {
                if(downCounter > BUTTONPRESS_LIMIT_LOW && downCounter < BUTTONPRESS_LIMIT_SHORT) {
                    event = Events::ButtonPress;
                    m_eventQueue->Enqueue(&event, ButtonPeriodMilliseconds / 2);
                }
                else if(downCounter > BUTTONPRESS_LIMIT_LONG && downCounter < BUTTONPRESS_LIMIT_HOLD) {
                    event = Events::ButtonLongPress;
                    m_eventQueue->Enqueue(&event, ButtonPeriodMilliseconds / 2);
                }

                if(downCounter > 0)
                    downCounter = 0;
            }

            EndPeriod();
        }
    }


}
