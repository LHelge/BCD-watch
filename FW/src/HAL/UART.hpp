#ifndef _UART_H
#define _UART_H

#include "GPIO.hpp"
#include "stm32l0xx_ll_usart.h"

namespace UART {

    enum Number {
        UART1
    };

    class SerialPort {
    public: 
        SerialPort(const Number number);

        void Init(const uint32_t baudrate);

        void Write(const char *s);
        void Write(uint8_t *data, uint16_t len);

        static void UART1Interrupt();
    private:
        USART_TypeDef *m_uart;
        IRQn_Type m_irqn;
        bool m_initialized;
    };

}

#endif
