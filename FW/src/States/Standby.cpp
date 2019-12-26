#include "Standby.hpp"
#include "System.hpp"

namespace States {

    Standby Standby::Instance;

    void Standby::Init(BCDWatch *watch) {
        System::System::Standby(System::Wakeup::Pin2);
    }
}