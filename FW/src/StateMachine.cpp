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
                case Events::TiltRight:         nextState = m_currentState->TiltRight(m_watch);         break;
                case Events::TiltLeft:          nextState = m_currentState->TiltLeft(m_watch);          break;
                case Events::TiltUp:            nextState = m_currentState->TiltUp(m_watch);            break;
                case Events::TiltDown:          nextState = m_currentState->TiltDown(m_watch);          break;
                default:                        nextState = m_currentState; break; // Not necessary
            }
            ChangeState(nextState);

            if(event != Events::Tick) {
                m_watch->Debug.Write("Event: ");
                m_watch->Debug.Write(static_cast<uint8_t>(event));
                m_watch->Debug.NewLine();
            }
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

