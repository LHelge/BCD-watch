#ifndef _STATE_DISPLAY_TIME_HPP
#define _STATE_DISPLAY_TIME_HPP

#include "State.hpp"

namespace States {

    class DisplayTime : public State {    
    public:
        void Init(BCDWatch *watch) override;
        State* Tick(BCDWatch *watch) override;
        State* ButtonPress(BCDWatch *watch) override;
        State* ButtonLongPress(BCDWatch *watch) override;

        static DisplayTime Instance;
    private:
        RealTimeClock::Time m_time;
    };

}

#endif
