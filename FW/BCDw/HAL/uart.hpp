#ifndef _UART_H
#define _UART_H

#include "gpio.hpp"
#include "stm32l0xx_hal.h"

namespace UART {

    enum Number {
        UART1
    };

    class SerialPort {
    public: 
        SerialPort(const Number number, const uint32_t baudrate, GPIO::Alternate *txPin, GPIO::Alternate *rxPin);

        void Write(const char *s);
    private:
        UART_HandleTypeDef m_handle;
        GPIO::Alternate *m_txPin;
        GPIO::Alternate *m_rxPin;

    };

}

#endif