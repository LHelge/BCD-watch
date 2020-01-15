#include "StateMachine.hpp"


StateMachine::StateMachine(BCDWatch *watch) {
    this->m_watch = watch;
}


void StateMachine::Event(Events event) {
    this->m_eventQueue.Enqueue(event);
}


void StateMachine::HandleNextEvent() {
    Events event;
    State *nextState;

    // Ugly hack while trying out FreeRTOS always tick current state
    nextState = this->m_currentState->Tick(this->m_watch);
    if(nextState != m_currentState) {
        ChangeState(nextState);
        return;
    }

    if(this->m_eventQueue.Dequeue(event)) {
        switch (event) {
            case Events::ButtonPress:     nextState = this->m_currentState->ButtonPress(this->m_watch); break;
            case Events::ButtonLongPress: nextState = this->m_currentState->ButtonLongPress(this->m_watch); break;
            case Events::ButtonHold:      nextState = this->m_currentState->ButtonHold(this->m_watch); break;
            default:                      nextState = this->m_currentState; break; // Not necessary
        }
        this->ChangeState(nextState);
    }
}


void StateMachine::ChangeState(State *newState) {
    if(this->m_currentState != newState && newState != nullptr) {
        if(this->m_currentState != nullptr)  {
            this->m_currentState->DeInit(this->m_watch);
        }
        this->m_currentState = newState;
        this->m_currentState->Init(this->m_watch);
    }
}


StateMachine::EventQueue::EventQueue() {
    this->m_head = this->m_queue;
    this->m_tail = this->m_queue;
}

void StateMachine::EventQueue::Enqueue(Events event) {
    *this->m_head++ = event;

    if(this->m_head >= &this->m_queue[EVENT_QUEUE_LENGTH]) {
        // Wrap
        this->m_head = this->m_queue;
    }
}

bool StateMachine::EventQueue::Dequeue(Events &event) {
    if(this->m_head == this->m_tail) {
        return false;
    }

    event = *this->m_tail++;

    if(this->m_tail >= &this->m_queue[EVENT_QUEUE_LENGTH]) {
        this->m_tail = this->m_queue;
    }

    return true;
}