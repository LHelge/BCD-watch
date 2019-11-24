#ifndef _DEBUG_HPP
#define _DEBUG_HPP

#include "uart.hpp"
#include "rtc.hpp"

// Comment this line out if not building for debug
#define DEBUG

namespace Debug
{
    class Debug {
    public:
        virtual void Write(const char *s);
        virtual void Write(uint8_t i);
        virtual void Write(uint16_t i);
        virtual void Write(uint32_t i);
        virtual void Write(int8_t i);
        virtual void Write(int16_t i);
        virtual void Write(int32_t i);
        virtual void Write(RealTimeClock::Time time);
        virtual void Write(RealTimeClock::Date date);
        virtual void WriteLine(const char *line);
        virtual void NewLine();
    };

    class SerialDebug : public Debug {
    public:
        SerialDebug(UART::SerialPort *port);

        void Write(const char *s) override;
        void Write(uint8_t i) override;
        void Write(uint16_t i) override;
        void Write(uint32_t i) override;
        void Write(int8_t i) override;
        void Write(int16_t i) override;
        void Write(int32_t i) override;
        void Write(RealTimeClock::Time time) override;
        void Write(RealTimeClock::Date date) override;
        void WriteLine(const char *line) override;
        void NewLine() override;
    private:
        void Write2Digit(uint8_t i, uint8_t *buf);
        UART::SerialPort *m_port;
    };
} // namespace Debug



#endif