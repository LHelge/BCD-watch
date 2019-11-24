#include "rtc.hpp"
#include "string.h"

namespace RealTimeClock
{
    Clock::Clock() {
        memset(&this->m_handle, 0, sizeof(RTC_InitTypeDef));

        // __HAL_RCC_RTC_ENABLE();

        // this->m_handle.Instance = RTC;
        // this->m_handle.Init.HourFormat = RTC_HOURFORMAT_24;
        // this->m_handle.Init.AsynchPrediv = 127;
        // this->m_handle.Init.SynchPrediv = 255;
        // this->m_handle.Init.OutPut = RTC_OUTPUT_DISABLE;
        // this->m_handle.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
        // this->m_handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
        // this->m_handle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
        // if (HAL_RTC_Init(&this->m_handle) != HAL_OK)
        // {
        //     // TODO: assert
        // }

        this->Update();
    }

    void Clock::Update() {
        // TODO: update time/date from RTC HW

        this->m_time.H = 12;
        this->m_time.M = 13;
        this->m_time.S = 14;

        this->m_date.Y = 19;
        this->m_date.M = 11;
        this->m_date.D = 25;
    }

    void Clock::Tick() {
        if(++this->m_ticks >= 1000) {
            this->m_ticks = 0;
            this->m_time.S++;
        }

        if(this->m_time.S >= 60) {
            this->m_time.S = 0;
            this->m_time.M++;
        }

        if(this->m_time.M >= 60) {
            this->m_time.M = 0;
            this->m_time.H++;
        }

        if(this->m_time.H >= 24) {
            // Let HW RTC handle calendar.
            this->Update();
        }
    }

    void Clock::SetTime(const Time& time) {
        this->m_time.H = time.H;
        this->m_time.M = time.M;
        this->m_time.S = time.S;

    }

    void Clock::GetTime(Time& time) const {
        time.H = this->m_time.H;
        time.M = this->m_time.M;
        time.S = this->m_time.S;
    }


    void Clock::SetDate(const Date& date) {
        this->m_date.Y = date.Y;
        this->m_date.M = date.M;
        this->m_date.D = date.D;

    }

    void Clock::GetDate(Date& date) const {
        date.Y = this->m_date.Y;
        date.M = this->m_date.M;
        date.D = this->m_date.D;
    }


} // namespace RTC
