#ifndef _I2C_HPP
#define _I2C_HPP

#include "stm32l0xx_ll_i2c.h"

namespace I2C {

    enum Number {
        I2C_1
    };

    class I2C {
    public:
        I2C(const Number number);

        void Init();

        void Transmit(const uint8_t address, const uint8_t *data, const uint8_t length = 1);
        void Receive(const uint8_t address, uint8_t *data, const uint8_t length = 1);

    private:
        I2C_TypeDef *m_i2c;
    };

    class I2CDevice {
    public:
        I2CDevice(I2C *i2c, const uint8_t m_address);

        void WriteReg(const uint8_t reg, const uint8_t value);
        void ReadReg(const uint8_t reg, uint8_t *data, const uint8_t length = 1);
    private:
        I2C *m_i2c;
        uint8_t m_txAddr;
        uint8_t m_rxAddr;
    };
}

#endif