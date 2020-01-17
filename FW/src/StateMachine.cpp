#include "StateMachine.hpp"


/**
 * @brief Construct a new State Machine object
 * 
 * @param watch Pointer to watch object, used by internal states
 * @param initialState Starting state for state machine
 */
StateMachine::StateMachine(BCDWatch *watch, State *initialState) : Task("SM", Task::MediumPriority)
{
    m_currentState = initialState;
    m_watch = watch;
}


void StateMachine::Event(Events event) {
    m_eventQueue.Enqueue(&event);
}

/**
 * @brief Run state machine task.
 * 
 */
void StateMachine::Run() {
    Events event;
    State *nextState;

    while (1)
    {   
        if(m_eventQueue.Dequeue(&event)) {
            switch (event) {
                case Events::Tick:              nextState = m_currentState->Tick(m_watch);              break;
                case Events::ButtonPress:       nextState = m_currentState->ButtonPress(m_watch);       break;
                case Events::ButtonLongPress:   nextState = m_currentState->ButtonLongPress(m_watch);   break;
                case Events::ButtonHold:        nextState = m_currentState->ButtonHold(m_watch);        break;
                default:                        nextState = m_currentState; break; // Not necessary
            }
            ChangeState(nextState);
        }
    }
    
}


/**
 * @brief Change to a new state (or remain if current state is passed)
 * 
 * @param newState The state to change to
 */
void StateMachine::ChangeState(State *newState) {
    if(m_currentState != newState && newState != nullptr) {
        if(m_currentState != nullptr)  {
            m_currentState->DeInit(m_watch);
        }
        m_currentState = newState;
        m_currentState->Init(m_watch);
    }
}

