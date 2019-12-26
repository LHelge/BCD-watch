#ifndef _STATE_STANDBY_HPP
#define _STATE_STANDBY_HPP

#include "StateMachine.hpp"


namespace States {

    class Standby : public State {
    public:
        void Init(BCDWatch *watch) override;

        static Standby Instance;
    };
}


#endif