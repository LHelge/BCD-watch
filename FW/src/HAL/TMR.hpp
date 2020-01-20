#ifndef _TMR_HPP
#define _TMR_HPP

#include "stm32l0xx_ll_tim.h"

namespace Timer {

    class Timer;

    enum TimerHW {
        Tim2,
        Tim21
    };

    enum Channel{
        Channel1 = LL_TIM_CHANNEL_CH1,
        Channel2 = LL_TIM_CHANNEL_CH2,
        Channel3 = LL_TIM_CHANNEL_CH3,
        Channel4 = LL_TIM_CHANNEL_CH4
    };

    enum Polarity {
        High = LL_TIM_OCPOLARITY_HIGH,
        Low = LL_TIM_OCPOLARITY_LOW
    };

    class PWMChannel {
    public:
        PWMChannel(Timer *timer, const Channel channel);

        void Init(const Polarity polarity);
        void SetDutyCycle(const uint16_t dutycycle);
    private:
        Timer *m_timer;
        Channel m_channel;    
    };

    class Timer {
        friend class PWMChannel;
    public:
        Timer(const TimerHW tim, const uint32_t prescaler);

    private:
        TIM_TypeDef *m_tim;
    public:
        PWMChannel PWMChannel1;
        PWMChannel PWMChannel2;
        PWMChannel PWMChannel3;
        PWMChannel PWMChannel4;
    };
}



#endif