#include "uart.hpp"

namespace UART {

    SerialPort::SerialPort(const Number number, const uint32_t baudrate, GPIO::Alternate *txPin, GPIO::Alternate *rxPin) {

        switch (number)
        {
        case UART1:
            __HAL_RCC_USART1_CLK_ENABLE();
            this->m_handle.Instance = USART1;
            break;
        
        default:
            break;
        }

        // Not really needed, but good check that it's configured
        this->m_txPin = txPin;
        this->m_rxPin = rxPin;

        this->m_handle.gState = HAL_UART_STATE_RESET;
        this->m_handle.Init.BaudRate = baudrate;
        this->m_handle.Init.WordLength = UART_WORDLENGTH_8B;
        this->m_handle.Init.StopBits = UART_STOPBITS_1;
        this->m_handle.Init.Parity = UART_PARITY_NONE;
        this->m_handle.Init.Mode = UART_MODE_TX_RX;
        this->m_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        this->m_handle.Init.OverSampling = UART_OVERSAMPLING_16;
        this->m_handle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
        this->m_handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
        if (HAL_UART_Init(&this->m_handle) != HAL_OK)
        {
            // TODO: Assert
        }
    }

    void SerialPort::Write(const char *s) {
        uint16_t len = 0;
        while(*s++) len++;

        HAL_UART_Transmit(&this->m_handle, (uint8_t *)s, len, 100);
    }


}