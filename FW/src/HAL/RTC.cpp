#include "RTC.hpp"
#include "stm32l0xx_ll_rcc.h"
#include "stm32l0xx_ll_rtc.h"

namespace RealTimeClock {

    void RealTimeClock::Init(const uint8_t asynchPrescaler, const uint8_t synchPrescaler) {
        LL_RCC_EnableRTC();
        
        this->EnableInit();
        LL_RTC_SetHourFormat(RTC, LL_RTC_HOURFORMAT_24HOUR);
        LL_RTC_SetAsynchPrescaler(RTC, asynchPrescaler);
        LL_RTC_SetSynchPrescaler(RTC, synchPrescaler);
        this->DisableInit();
    }

    void RealTimeClock::GetTime(Time &time) {
        time.H = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetHour(RTC));
        time.M = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetMinute(RTC));
        time.S = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetSecond(RTC));
    }


    void RealTimeClock::SetTime(const Time &time) {
        this->EnableInit();
        LL_RTC_TIME_Config(RTC, LL_RTC_TIME_FORMAT_AM_OR_24, 
            __LL_RTC_CONVERT_BIN2BCD(time.H),
            __LL_RTC_CONVERT_BIN2BCD(time.M),
            __LL_RTC_CONVERT_BIN2BCD(time.S));
        this->DisableInit();

        LL_RTC_BAK_SetRegister(RTC, LL_RTC_BKP_DR0, RTC_IS_SET_BACKUP_FLAG);
    }

    void RealTimeClock::GetDate(Date &date) {
        date.Y = 19;
        date.M = 12;
        date.D = 24;
    }

    void RealTimeClock::SetDate(const Date &date) {
        // Todo
    }


    bool RealTimeClock::IsSet() {
        uint32_t flag = LL_RTC_BAK_GetRegister(RTC, LL_RTC_BKP_DR0);
        return flag == RTC_IS_SET_BACKUP_FLAG;
    }


    void RealTimeClock::EnableInit() {
        LL_RTC_DisableWriteProtection(RTC);
        LL_RTC_EnableInitMode(RTC);
        while(LL_RTC_IsActiveFlag_INIT(RTC) == false) {}
    }


    void RealTimeClock::DisableInit() {
        LL_RTC_DisableInitMode(RTC);
        LL_RTC_EnableWriteProtection(RTC);
    }
}