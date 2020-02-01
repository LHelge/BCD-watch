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
    virtual State* TiltRight(BCDWatch *watch);
    virtual State* TiltLeft(BCDWatch *watch);
    virtual State* TiltUp(BCDWatch *watch);
    virtual State* TiltDown(BCDWatch *watch);
protected:
    uint32_t m_stateTime;
};

#endif