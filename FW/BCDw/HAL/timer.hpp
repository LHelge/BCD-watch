#ifndef _TIMER_HPP
#define _TIMER_HPP

#include "stdint.h"
#include "stdbool.h"
#include "stm32l0xx_hal.h"
#include "gpio.hpp"


namespace Timer
{
    enum Number { TIMER2, TIMER21 };
    enum Channel : uint32_t {
        CHANNEL_1 = TIM_CHANNEL_1,
        CHANNEL_2 = TIM_CHANNEL_2,
        CHANNEL_3 = TIM_CHANNEL_3,
        CHANNEL_4 = TIM_CHANNEL_4,
        //CHANNEL_ALL = TIM_CHANNEL_ALL,
    };

    class BaseTimer {
    public:
        BaseTimer(const Number number, const uint32_t prescaler);
    protected:
        TIM_HandleTypeDef m_handle;

        friend class PWM;
    };


    class PWM {
    public:
        PWM(BaseTimer *timer, const Channel channel, GPIO::Alternate *pin);

        void SetDutyCycle(const uint16_t dutycycle);
    private:
        BaseTimer *m_timer;
        Channel m_channel;
        GPIO::Pin *m_pin;
    };
} // namespace Timer


#endif