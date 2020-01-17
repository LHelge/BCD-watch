#ifndef _FREERTOS_TIMER_HPP
#define _FREERTOS_TIMER_HPP

#include "FreeRTOS.h"
#include "timers.h"

namespace FreeRTOS
{
    class Ticker;

    class Timer {
    public:
        Timer(uint32_t period, Ticker *ticker);
        ~Timer();
        void Start();
        void Start(uint32_t repeats);
        void Stop();
    private:
        static void TimerFunction(TimerHandle_t handle);
        TimerHandle_t m_handle;
        StaticTimer_t m_buffer;
        uint32_t m_counter;
        Ticker *m_ticker;
        bool m_active;
    };
    

    class Ticker {
    public:
        virtual void Tick(Timer *timer) = 0;
    };
} // namespace FreeRTOS



#endif