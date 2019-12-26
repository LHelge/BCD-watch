#ifndef _CLOCK_HPP
#define _CLOCK_HPP

#include <stdint.h>
#include "stm32l0xx_ll_pwr.h"

namespace System {


    enum ClockHW {
        GpioA = 0,
        GpioB,
        GpioC,
        GpioD,
        GpioE,
        GpioH,
        Tim2,
        Tim21,
        I2c1,
        Usart1
    };

    enum Wakeup : uint32_t {
        Pin1 = LL_PWR_WAKEUP_PIN1,
        Pin2 = LL_PWR_WAKEUP_PIN2,
        Pin3 = LL_PWR_WAKEUP_PIN3
    };


    
    

    class System {
    public:
        static void Initialize();
        static void EnableClock(const ClockHW clock);
        static void Delay(const uint32_t milliseconds);
        static void Reset();
        static void Standby(const Wakeup wakeup);
        static uint32_t GetCoreClock();

        // Interrupts
        static void SysTickInterrupt();
    private:
        static volatile uint32_t m_delayCounter;
    };

}

#endif