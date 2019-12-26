#include "App.hpp"
#include "System.hpp"
#include "BCDWatch.hpp"
#include "StateMachine.hpp"
#include "DisplayTime.hpp"


static BCDWatch Watch;
static StateMachine StateMachine(&Watch);

void App::Run() {
    System::System::Initialize();

    Watch.Init();
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