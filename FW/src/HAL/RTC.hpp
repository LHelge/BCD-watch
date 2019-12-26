#ifndef _RTC_HPP
#define _RTC_HPP


#include "stdint.h"


namespace RealTimeClock {
    struct Time
    {
        Time() : H(0), M(0), S(0) {}
        Time(const uint8_t h, const uint8_t m, const uint8_t s) : H(h), M(m), S(s) {}

        uint8_t H;
        uint8_t M;
        uint8_t S;

        void TickS() {
            if(++S >= 60) {
                S = 0;
                TickM();
            }
        }

        void TickM() {
            if(++M >= 60) {
                M = 0;
                TickH();
            }
        }

        void TickH() {
            if(++H >= 24) {
                H = 0;
            }
        }
    };

    struct Date
    {
        Date() : Y(0), M(0), D(0) {}
        Date(const uint8_t y, const uint8_t m, const uint8_t d) : Y(y), M(m), D(d) {}

        uint8_t Y;
        uint8_t M;
        uint8_t D;
    };

    class RealTimeClock {
    public:
        void Init(const uint8_t asynchPrescaler, const uint8_t synchPrescaler);
        void GetTime(Time &time);
        void SetTime(const Time &time);
        void GetDate(Date &date);
        void SetDate(const Date &date);
        bool IsSet();
    private:
        void EnableInit();
        void DisableInit();

        static const uint32_t RTC_IS_SET_BACKUP_FLAG = 0xdeadbeef;
    };
}

#endif