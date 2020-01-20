#include "TMR.hpp"
#include "System.hpp"
#include "stm32l0xx_ll_bus.h"

namespace Timer {

    Timer::Timer(const TimerHW timer, const uint32_t prescaler) : 
        m_tim(nullptr),
        PWMChannel1(this, Channel::Channel1),
        PWMChannel2(this, Channel::Channel2),
        PWMChannel3(this, Channel::Channel3),
        PWMChannel4(this, Channel::Channel4) {

        switch (timer)
        {
        case TimerHW::Tim2:
            System::System::EnableClock(System::ClockHW::Tim2);
            this->m_tim = TIM2;
            break;
        case TimerHW::Tim21:
            System::System::EnableClock(System::ClockHW::Tim21);
            this->m_tim = TIM21;
            break;
        }

        LL_TIM_SetCounterMode(this->m_tim, LL_TIM_COUNTERMODE_UP);
        LL_TIM_SetPrescaler(this->m_tim, prescaler);
        LL_TIM_EnableARRPreload(this->m_tim);
        LL_TIM_SetAutoReload(this->m_tim, 0xFFFF);
        LL_TIM_EnableCounter(this->m_tim);
    }

    PWMChannel::PWMChannel(Timer *timer, const Channel channel) {
        this->m_timer = timer;
        this->m_channel = channel;
    }

    void PWMChannel::Init(const Polarity polarity) {
        LL_TIM_OC_SetMode(this->m_timer->m_tim, this->m_channel, LL_TIM_OCMODE_PWM1);
        LL_TIM_OC_SetPolarity(this->m_timer->m_tim, this->m_channel, polarity);
    }

    void PWMChannel::SetDutyCycle(const uint16_t dutycycle) {
        if(this->m_timer->m_tim == nullptr) {
            // TODO: Assert
            return;
        }
        

        switch(this->m_channel) {
            case Channel::Channel1: LL_TIM_OC_SetCompareCH1(this->m_timer->m_tim, dutycycle); break;
            case Channel::Channel2: LL_TIM_OC_SetCompareCH2(this->m_timer->m_tim, dutycycle); break;
            case Channel::Channel3: LL_TIM_OC_SetCompareCH3(this->m_timer->m_tim, dutycycle); break;
            case Channel::Channel4: LL_TIM_OC_SetCompareCH4(this->m_timer->m_tim, dutycycle); break;
        }

        LL_TIM_OC_EnablePreload(this->m_timer->m_tim, this->m_channel);
        LL_TIM_CC_EnableChannel(this->m_timer->m_tim, this->m_channel);

    }

}
