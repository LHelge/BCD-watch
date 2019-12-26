#include "DisplayTime.hpp"
#include "Standby.hpp"
#include "SetTime.hpp"

#define STATE_TIMEOUT_MILLISECONDS  (15000)
#define FADE_MILLISECONDS (512)

namespace States {

    DisplayTime DisplayTime::Instance;

    void DisplayTime::Init(BCDWatch *watch) {
        State::Init(watch);

        watch->Rtc.GetTime(this->m_time);

        watch->Display.Dim(Display::Column::ALL, 0);
        watch->Display.Set(this->m_time);
    }

    State* DisplayTime::Tick(BCDWatch *watch) {
        State::Tick(watch);

        // Set correct time
        if(this->m_stateTime % 1000 == 0) {
            this->m_time.TickS();
            watch->Display.Set(this->m_time);
        }

        // Set correct dimming level
        uint8_t dutycycle;
        if(this->m_stateTime < FADE_MILLISECONDS) {
            dutycycle = (uint8_t)((this->m_stateTime * watch->Brightness / FADE_MILLISECONDS) & 0xFF);
        }
        else if(STATE_TIMEOUT_MILLISECONDS - this->m_stateTime < FADE_MILLISECONDS) {
            dutycycle = (uint8_t)(((STATE_TIMEOUT_MILLISECONDS - this->m_stateTime) * watch->Brightness / FADE_MILLISECONDS) & 0xFF);
        }
        else {
            dutycycle = 0xFF;
        }
        watch->Display.Dim(Display::Column::ALL, dutycycle);

        // Goto next state
        if(this->m_stateTime >= STATE_TIMEOUT_MILLISECONDS) {
            return &Standby::Instance;
        }

        // Stay in this state
        return this;
    }

    State* DisplayTime::ButtonPress(BCDWatch *watch) {
        // Reset state time counter to where fade in is done.
        this->m_stateTime = FADE_MILLISECONDS;
        return this;
    }

    State* DisplayTime::ButtonLongPress(BCDWatch *watch) {
        // GOTO set time state
        return &SetTime::Instance;
    }

}