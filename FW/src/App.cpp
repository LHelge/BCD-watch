#include "App.hpp"
#include "System.hpp"
#include "BCDWatch.hpp"
#include "StateMachine.hpp"
#include "DisplayTime.hpp"


static BCDWatch Watch;
static StateMachine StateMachine(&Watch);

void App::Run() {

#if DEBUG == 1
    System::System::Initialize(true);
    Watch.Init(true);
#else
    System::System::Initialize();
    Watch.Init();
#endif


    Watch.Brightness = 128;

    // Starting state
    StateMachine.ChangeState(&States::DisplayTime::Instance);

    while(1) {
        StateMachine.HandleNextEvent();
    }
}

void App::Tick() {
    Events event;

    // Check button events
    event = Watch.Button.Tick();
    if(event) {
        StateMachine.Event(event);
    }

    // Check Accelerometer events
    event = Watch.Accelerometer.Tick();
    if(event) {
        StateMachine.Event(event);
    }

    StateMachine.Event(Events::Tick);
}