#include "State.hpp"

void State::Init(BCDWatch *watch) {
    this->m_stateTime = 0;
}

void State::DeInit(BCDWatch *watch) {
    // Nothing to do right now
}


State* State::Tick(BCDWatch *watch) {
    this->m_stateTime++;

    return this;
}


State* State::ButtonPress(BCDWatch *watch) {
    // Nothing to do right now

    return this;
}


State* State::ButtonLongPress(BCDWatch *watch) {
    // Nothing to do right now

    return this;
}


State* State::ButtonHold(BCDWatch *watch) {
    // Nothing to do right now

    return this;
}