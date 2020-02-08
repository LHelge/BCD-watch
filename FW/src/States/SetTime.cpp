#include "SetTime.hpp"
#include "DisplayTime.hpp"

#define DUTYCYCLE_MAX (0xff)
#define DUTYCYCLE_MIN (0x1f)

#define IDLE_TIME_LIMIT (30000)  // Milliseconds


namespace States {
    
    SetTime SetTime::Instance;

    void SetTime::Init(BCDWatch *watch) {
        m_dutycycle = DUTYCYCLE_MAX;
        m_dutycycleSign = -1;
        m_idleTimer = 0;
        watch->Rtc.GetTime(m_time);
        m_time.S = 0;

        watch->Display.Set(m_time);

        m_mode = MODE_M;
    }


    void SetTime::DeInit(BCDWatch *watch) {
        watch->Rtc.SetTime(m_time);
    }


    State* SetTime::Tick(BCDWatch *watch) {
        m_dutycycle += m_dutycycleSign;
        if(m_dutycycle <= DUTYCYCLE_MIN) {
            m_dutycycleSign = 1;
        }
        else if( m_dutycycle >= DUTYCYCLE_MAX) {
            m_dutycycleSign  =-1;
        }
        if (m_mode == MODE_M) {
            watch->Display.Dim(Display::Column::S0, 25);
            watch->Display.Dim(Display::Column::S1, 25);
            watch->Display.Dim(Display::Column::M0, m_dutycycle);
            watch->Display.Dim(Display::Column::M1, m_dutycycle);
            watch->Display.Dim(Display::Column::H0, 25);
            watch->Display.Dim(Display::Column::H1, 25);
        } else if (m_mode == MODE_H) {
            watch->Display.Dim(Display::Column::S0, 25);
            watch->Display.Dim(Display::Column::S1, 25);
            watch->Display.Dim(Display::Column::M0, 25);
            watch->Display.Dim(Display::Column::M1, 25);
            watch->Display.Dim(Display::Column::H0, m_dutycycle);
            watch->Display.Dim(Display::Column::H1, m_dutycycle);
        }

        if(m_idleTimer++ >= IDLE_TIME_LIMIT) {
            return &DisplayTime::Instance;
        }

        return this;
    }

    State* SetTime::ButtonPress(BCDWatch *watch) {
        switch (m_mode) {
        case MODE_M:
            // Don't increase the hours if the minutes wrap from 59 to 0.
            m_time.TickM(RealTimeClock::Time::TICK_ISOLATED);
            break;
        case MODE_H:
            m_time.TickH();
            break;
        default:
            watch->Debug.Write("Unknown SetTime::Mode: ");
            watch->Debug.Write(static_cast<uint8_t>(m_mode));
            watch->Debug.Write("\r\n");
            break;
        }
        watch->Display.Set(m_time);

        m_idleTimer = 0;

        return this;
    }

    State* SetTime::ButtonLongPress(BCDWatch *watch) {
        if (m_mode == MODE_M) {
            m_mode = MODE_H;
            return this;
        }
        m_mode = MODE_M;
        m_time.S = 0;
        return &DisplayTime::Instance;
    }

    State* SetTime::ButtonHold(BCDWatch *watch) {

        switch (m_mode) {
        case MODE_M:
            m_time.TickM();
            break;
        case MODE_H:
            m_time.TickH();
            break;
        default:
            watch->Debug.Write("Unknown SetTime::Mode: ");
            watch->Debug.Write(static_cast<uint8_t>(m_mode));
            watch->Debug.Write("\r\n");
            break;
        }

        watch->Display.Set(m_time);

        m_idleTimer = 0;

        return this;
    }

}
