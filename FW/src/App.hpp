#ifndef _APP_HPP
#define _APP_HPP

#include "Task.hpp"
#include "Queue.hpp"
#include "Events.hpp"
#include "StateMachine.hpp"
#include "Timer.hpp"

class App : public FreeRTOS::Task<2048>, public FreeRTOS::Ticker {
public:
    App();
    void Run() override;
    void Tick(FreeRTOS::Timer *timer) override;
private :
    FreeRTOS::Queue<Events, EventQueueLength> m_eventQueue;
    StateMachine m_stateMachine;
    BCDWatch m_watch;
    FreeRTOS::Timer m_tickTimer;
};

#endif