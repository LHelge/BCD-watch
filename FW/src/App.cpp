#include "App.hpp"
#include "System.hpp"
#include "BCDWatch.hpp"
#include "StateMachine.hpp"
#include "DisplayTime.hpp"


static BCDWatch Watch;
static StateMachine AppStateMachine(&Watch, &States::DisplayTime::Instance);

void App::Run() {

#if DEBUG == 1
    System::System::Initialize(true);
    Watch.Init(true);
#else
    System::System::Initialize();
    Watch.Init();
#endif

    AppStateMachine.Start();

    Watch.Brightness = 128;

    InitPeriod(1);

    #if DEBUG == 1
    uint32_t counter = 0;
    #endif

    while(1) {
        Events event;

        // Check button events
        event = Watch.Button.Tick();
        if(event) {
            AppStateMachine.Event(event);
        }

        // Check Accelerometer events
        event = Watch.Accelerometer.Tick();
        if(event) {
            AppStateMachine.Event(event);
        }

        AppStateMachine.Event(Events::Tick);

        #if DEBUG == 1
        if(counter++ > 1000) {
            Accelerometer::AccelerationVector vec;

            Watch.Accelerometer.getAcceleration(vec);
            Watch.Debug.Write(vec);
            Watch.Debug.NewLine();

            counter = 0;
        }
        #endif

        EndPeriod();
    }
}