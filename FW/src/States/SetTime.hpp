#ifndef _STATE_SET_TIME_HPP
#define _STATE_SET_TIME_HPP

#include "State.hpp"

namespace States {

    class SetTime : public State {    
    public:
        void Init(BCDWatch *watch) override;
        void DeInit(BCDWatch *watch) override;
        State* Tick(BCDWatch *watch) override;
        State* ButtonPress(BCDWatch *watch) override;
        State* ButtonLongPress(BCDWatch *watch) override;
        State* ButtonHold(BCDWatch *watch) override;

        static SetTime Instance;
    private:
        RealTimeClock::Time m_time;
        uint8_t m_dutycycle;
        int8_t m_dutycycleSign;
        uint32_t m_idleTimer;
    };

}

#endif
