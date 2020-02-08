#include "Button.hpp"

// Limits for regular press, long press and button hold, measured in
// deciseconds(??).
#define BUTTONPRESS_LIMIT_LOW     (0)
#define BUTTONPRESS_LIMIT_SHORT  (10)
//#define BUTTONPRESS_LIMIT_LONG   (25)
//#define BUTTONPRESS_LIMIT_HOLD   (50)


namespace Button {
    PushButton::PushButton(GPIO::Pin *pin, FreeRTOS::Queue<Events, EventQueueLength> *eventQueue)
        : Task("Btn", Task::LowPriority), m_pin(pin), m_eventQueue(eventQueue)
    { }


    void PushButton::Run() {
        InitPeriod(ButtonPeriodMilliseconds);

        uint32_t downCounter = 0;
        uint32_t upCounter = 0;
        Events event = Events::None;
        while (true) {
            
            if (m_pin->Get()) {
                // Button is pressed down.
                downCounter++;

                if (downCounter > BUTTONPRESS_LIMIT_SHORT) {
                    if (event == Events::None) {
                        // There's no previously recorded button event, or it
                        // happened too far back. Send a long press.
                        event = Events::ButtonLongPress;
                        m_eventQueue->Enqueue(&event, ButtonPeriodMilliseconds / 2);
                    } else if (event == Events::ButtonPress || event == Events::ButtonHold) {
                        // The previous event was a button press or we're still
                        // holding down. Send a button hold event.
                        event = Events::ButtonHold;
                        m_eventQueue->Enqueue(&event, 0);
                    }
                }

                upCounter = 0;
            } else {
                // Button is up.
                upCounter++;

                if (downCounter > 0 && downCounter < BUTTONPRESS_LIMIT_SHORT) {
                    event = Events::ButtonPress;
                    m_eventQueue->Enqueue(&event, ButtonPeriodMilliseconds / 2);
                } else if (event == Events::ButtonLongPress || event == Events::ButtonHold) {
                    // The button was released and the previously sent event
                    // was wither long press or hold, clear the saved event, so
                    // we don't go back into hold again until we do another
                    // click-hold.
                    event = Events::None;
                }

                downCounter = 0;
            }

            if (upCounter > BUTTONPRESS_LIMIT_SHORT) {
                // If the last button press ended more than the button press
                // limit time back, clear the press event that would trigger a
                // button hold on long press.
                event = Events::None;
            }

            EndPeriod();
        }
    }


}
