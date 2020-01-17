#include "App.hpp"
#include "System.hpp"
#include "BCDWatch.hpp"
#include "StateMachine.hpp"
#include "DisplayTime.hpp"

/**
 * @brief Construct a new App object
 * 
 */
App::App() : 
    Task("App", Task::MediumPriority),
    m_stateMachine(&m_watch, &States::DisplayTime::Instance),
    m_watch(&m_eventQueue),
    m_tickTimer(1, this) {}


/**
 * @brief Run application task
 * 
 */
void App::Run() {

#if DEBUG == 1
    System::System::Initialize(true);
    m_watch.Init(true);
#else
    System::System::Initialize();
    Watch.Init();
#endif

    m_stateMachine.Start();
    m_tickTimer.Start();
    m_watch.Button.Start();

    // TODO: put Accelerometer in a task as well

    m_watch.Brightness = 128;

    while(1) {
        Events event;

        if(m_eventQueue.Dequeue(&event)) {
            m_stateMachine.Event(event);
        }
    }
}


void App::Tick(FreeRTOS::Timer *timer) {
    Events tick = Events::Tick;
    m_eventQueue.Enqueue(&tick);
}