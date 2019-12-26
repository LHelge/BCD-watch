#ifndef _STATE_HPP
#define _STATE_HPP

#include "BCDWatch.hpp"



class State {
public:
    virtual void Init(BCDWatch *watch);
    virtual void DeInit(BCDWatch *watch);

    // Events
    virtual State* Tick(BCDWatch *watch);
    virtual State* ButtonPress(BCDWatch *watch);
    virtual State* ButtonLongPress(BCDWatch *watch);
    virtual State* ButtonHold(BCDWatch *watch);
protected:
    uint32_t m_stateTime;
};

#endif