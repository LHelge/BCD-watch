#include "SetTime.hpp"
#include "DisplayTime.hpp"

#define DUTYCYCLE_MAX (0xff)
#define DUTYCYCLE_MIN (0x1f)

#define IDLE_TIME_LIMIT (30000)  // Milliseconds


namespace States {
    
    SetTime SetTime::Instance;

    void SetTime::Init(BCDWatch *watch) {
        this->m_dutycycle = DUTYCYCLE_MAX;
        this->m_dutycycleSign = -1;
        this->m_idleTimer = 0;
        watch->Rtc.GetTime(this->m_time);
        this->m_time.S = 0;

        watch->Display.Set(this->m_time);
    }


    void SetTime::DeInit(BCDWatch *watch) {
        watch->Rtc.SetTime(this->m_time);
    }


    State* SetTime::Tick(BCDWatch *watch) {
        this->m_dutycycle += this->m_dutycycleSign;
        if(this->m_dutycycle <= DUTYCYCLE_MIN) {
            this->m_dutycycleSign = 1;
        }
        else if( this->m_dutycycle >= DUTYCYCLE_MAX) {
            this->m_dutycycleSign  =-1;
        }
        watch->Display.Dim(Display::Column::ALL, this->m_dutycycle);

        if(this->m_idleTimer++ >= IDLE_TIME_LIMIT) {
            return &DisplayTime::Instance;
        }

        return this;
    }

    State* SetTime::ButtonPress(BCDWatch *watch) {
        this->m_time.TickM();
        watch->Display.Set(this->m_time);

        this->m_idleTimer = 0;

        return this;
    }

    State* SetTime::ButtonLongPress(BCDWatch *watch) {
        return &DisplayTime::Instance;
    }

    State* SetTime::ButtonHold(BCDWatch *watch) {
        this->m_time.TickM();
        watch->Display.Set(this->m_time);

        this->m_idleTimer = 0;

        return this;
    }

}