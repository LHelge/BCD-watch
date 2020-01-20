#ifndef _DEBUG_HPP
#define _DEBUG_HPP

#include "UART.hpp"
#include "RTC.hpp"
#include "LIS3DH.hpp"


namespace Debug
{
    enum Mode {
        NormalMode = 0,
        DebugMode
    };

#ifdef DEBUG
    static const Mode MODE = DebugMode;
#else  // DEBUG
    static const Mode MODE = NormalMode;
#endif  // DEBUG

    class Debug  {
    public:
        Debug(UART::SerialPort *port);

        void Write(const char *s);
        void Write(uint8_t i);
        void Write(uint16_t i);
        void Write(uint32_t i);
        void Write(int8_t i);
        void Write(int16_t i);
        void Write(int32_t i);
        void Write(RealTimeClock::Time time);
        void Write(RealTimeClock::Date date);
        void Write(Accelerometer::AccelerationVector &vec);
        void WriteLine(const char *line);
        void NewLine();
    private:
        void Write2Digit(uint8_t i, uint8_t *buf);
        UART::SerialPort *m_port;
    };
} // namespace Debug



#endif
