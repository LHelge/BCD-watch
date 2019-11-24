#ifndef _RTC_HPP
#define _RTC_HPP

#include "stdint.h"
#include "stm32l0xx_hal.h"

namespace RealTimeClock
{
    struct Time {
        uint8_t H;
        uint8_t M;
        uint8_t S;
    };

    struct Date {
        uint8_t Y; // Only two digits needed
        uint8_t M;
        uint8_t D;
    };

    class Clock {
    public:
        Clock();

        /**
         * @brief Update time from HW RTC
         * 
         */
        void Update();


        /**
         * @brief Advance time beween fetches from the hardware RTC
         *        Should be called from SysTick interrupt every millisecond
         * 
         */
        void Tick();


        /**
         * @brief Set the hardware RTC time
         * 
         * @param time Time to set the hardware RTC to.
         */
        void SetTime(const Time& time);


        /**
         * @brief Get current time
         * 
         * @param time Current time
         */
        void GetTime(Time& time) const;


        /**
         * @brief Set the hardware RTC date
         * 
         * @param date 
         */
        void SetDate(const Date& date);


        /**
         * @brief Get current date
         * 
         * @param date 
         */
        void GetDate(Date& date) const;



    private:
        Time m_time;
        Date m_date;
        uint16_t m_ticks;
        RTC_HandleTypeDef m_handle;
    };

} // namespace RTC



#endif