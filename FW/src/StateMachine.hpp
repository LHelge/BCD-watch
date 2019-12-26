#ifndef _STATE_MACHINE_HPP
#define _STATE_MACHINE_HPP

#include "State.hpp"
#include "Events.hpp"

#define EVENT_QUEUE_LENGTH (64)

class StateMachine {
public:
    StateMachine(BCDWatch *watch);

    void Event(Events event);
    void HandleNextEvent();
    void ChangeState(State *newState);
private:
    class EventQueue {
    public:
        EventQueue();
        void Enqueue(Events event);
        bool Dequeue(Events &event);
    private:
        Events m_queue[EVENT_QUEUE_LENGTH];
        Events *m_head;
        Events *m_tail;
    };

    EventQueue m_eventQueue;
    State *m_currentState;
    BCDWatch *m_watch;
};



#endif