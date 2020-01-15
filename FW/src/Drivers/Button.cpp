#include "Button.hpp"

#define BUTTONPRESS_LIMIT_LOW     (100)
#define BUTTONPRESS_LIMIT_SHORT  (2000)
#define BUTTONPRESS_LIMIT_LONG   (4000)
#define BUTTONPRESS_LIMIT_HOLD   (5000)
#define BUTTONHOLD_FREQUENCY      (100)  // Bad name, not frequency, timestep?

namespace Button {
    PushButton::PushButton(GPIO::Pin *pin) {
        this->m_pin = pin;
        this->m_timer = 0;
    }

    Events PushButton::Tick() {
        if(this->m_pressed) {
            this->m_timer++;

            if(this->m_pin->Get()) {
                // Button kept down
                if( this->m_timer > BUTTONPRESS_LIMIT_HOLD &&
                    this->m_timer % BUTTONHOLD_FREQUENCY == 0) {
                    return Events::ButtonHold;
                }
            }
            else {
                this->m_pressed = false;
                // Button relesed
                if(this->m_timer > BUTTONPRESS_LIMIT_LOW &&
                   this->m_timer < BUTTONPRESS_LIMIT_SHORT) {
                    return Events::ButtonPress;
                }
                else if(this->m_timer > BUTTONPRESS_LIMIT_SHORT && 
                        this->m_timer < BUTTONPRESS_LIMIT_LONG) {
                    return Events::ButtonLongPress;
                }
            }
        }
        else {
            if(this->m_pin->Get()) {
                // Button down
                this->m_pressed = true;
                this->m_timer = 0;
            }
        }

        return Events::None;
    }

}
