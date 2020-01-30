#include "Timer.hpp" // TODO: Solve name conflict with HAL/Timer.hpp


namespace FreeRTOS
{
    Timer::Timer(uint32_t period, Ticker * ticker) {
        m_handle = xTimerCreateStatic("", pdMS_TO_TICKS(period), pdFALSE, this, TimerFunction, &m_buffer);
        m_ticker = ticker;
    }
    

    Timer::~Timer() {
        xTimerDelete(m_handle,0);
    }



    void Timer::Start() {
        if(m_active) {
            return;
        }

        vTimerSetReloadMode(m_handle, pdTRUE);
        xTimerStart(m_handle, 0);
        m_active = true;
    }
    
    
    void Timer::Start(uint32_t repeats) {
        if(m_active || repeats == 0) {
            return;
        }

        vTimerSetReloadMode(m_handle, repeats > 1);
        xTimerStart(m_handle, 0);
        m_active = true;
        m_counter = repeats;
    }
    

    void Timer::Stop() {
        xTimerStop(m_handle, 0);
    }


    void Timer::TimerFunction(TimerHandle_t handle) {
        Timer *timer = (Timer*)pvTimerGetTimerID(handle);

        timer->m_ticker->Tick(timer);

        if(timer->m_counter > 0) {
            timer->m_counter--;

            if(timer->m_counter == 0) {
                timer->Stop();
            }
        }
    }

} // namespace FreeRTOS
