#ifndef _I2C_HPP
#define _I2C_HPP


#include "gpio.hpp"
#include "stm32l0xx_hal.h"

namespace I2C {

    enum Number {
        I2C_1
    };

    class I2CDevice {
    public:
        I2CDevice(const Number number, const uint8_t m_address, GPIO::Alternate *sclPin, GPIO::Alternate *sdaPin);

        void WriteReg(uint8_t reg, uint8_t value);
        void ReadReg(uint8_t reg, uint8_t *data, uint16_t length = 1);
    private:
        I2C_HandleTypeDef m_handle;
        GPIO::Alternate *m_sclPin;
        GPIO::Alternate *m_sdaPin;
        uint8_t m_txAddr;
        uint8_t m_rxAddr;
    };
}

#endif