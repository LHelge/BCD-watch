#ifndef _STATE_MACHINE_HPP
#define _STATE_MACHINE_HPP

#include "State.hpp"
#include "Events.hpp"
#include "Task.hpp"
#include "Queue.hpp"

class StateMachine : public FreeRTOS::Task {
public:
    StateMachine(BCDWatch *watch, State *initialState);

    void Run() override;
    void Event(Events event);
private:
    void ChangeState(State *newState);
    FreeRTOS::Queue<Events> m_eventQueue;
    State *m_currentState;
    BCDWatch *m_watch;
};



#endif