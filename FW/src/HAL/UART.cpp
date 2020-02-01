#include "UART.hpp"
#include "System.hpp"

namespace UART {

    SerialPort::SerialPort(const Number number) {
        switch (number)
        {
        case UART1:
            System::System::EnableClock(System::ClockHW::Usart1);
            this->m_uart = USART1;
            this->m_irqn = USART1_IRQn;
            break;
        default:
            break;
        }

        this->m_initialized = false;
    }

    void SerialPort::Init(const uint32_t baudrate) {
        LL_USART_Disable(this->m_uart);
        LL_USART_SetTransferDirection(this->m_uart, LL_USART_DIRECTION_TX_RX);
        LL_USART_ConfigCharacter(this->m_uart, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);
        LL_USART_SetHWFlowCtrl(this->m_uart, LL_USART_HWCONTROL_NONE);
        LL_USART_SetOverSampling(this->m_uart, LL_USART_OVERSAMPLING_16);
        LL_USART_SetBaudRate(this->m_uart, System::System::GetCoreClock(), LL_USART_OVERSAMPLING_16, baudrate); 
        SET_BIT(this->m_uart->CR3, USART_CR3_OVRDIS);

        NVIC_SetPriority(this->m_irqn, configLIBRARY_LOWEST_INTERRUPT_PRIORITY);
        NVIC_EnableIRQ(this->m_irqn);

        LL_USART_Enable(this->m_uart);

        while((!(LL_USART_IsActiveFlag_TEACK(this->m_uart))) || (!(LL_USART_IsActiveFlag_REACK(this->m_uart)))) {}

        LL_USART_EnableIT_RXNE(this->m_uart);

        this->m_initialized = true;
    }

    void SerialPort::Write(const char *s) {
        if(this->m_initialized) {
            uint16_t len = 0;

            while(s[len]) len++;

            this->Write((uint8_t *)s, len);
        }
    }

    void SerialPort::Write(uint8_t *data, uint16_t len) {
        if(this->m_initialized) {
            for(uint16_t i = 0; i < len; i++) {
                // Wait until ready
                while (!LL_USART_IsActiveFlag_TXE(this->m_uart)) {}

                if(i == len-1) {
                    LL_USART_ClearFlag_TC(this->m_uart); 
                }
                LL_USART_TransmitData8(this->m_uart, data[i]);
            }

            while (!LL_USART_IsActiveFlag_TC(this->m_uart)) {}
        }
    }

    void SerialPort::UART1Interrupt() {
        if(LL_USART_IsActiveFlag_RXNE(USART1) && LL_USART_IsEnabledIT_RXNE(USART1)) {
            uint8_t c = LL_USART_ReceiveData8(USART1);
            LL_USART_TransmitData8(USART1, c);
        }
    }
}