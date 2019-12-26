#include "I2C.hpp"
#include "System.hpp"
#include "stm32l0xx_ll_i2c.h"

namespace I2C {

    I2C::I2C(const Number number) {
        switch (number)
        {
        case I2C_1:
            System::System::EnableClock(System::ClockHW::I2c1);
            this->m_i2c = I2C1;
            break;
        default:
            break;
        }
    }

    void I2C::Init() {
        LL_I2C_Disable(this->m_i2c);
        LL_I2C_SetTiming(this->m_i2c, 0x00300F38); // From CubeMX
        LL_I2C_EnableClockStretching(this->m_i2c);
        LL_I2C_EnableAnalogFilter(this->m_i2c);
        LL_I2C_SetDigitalFilter(this->m_i2c, 0x00);
        LL_I2C_DisableOwnAddress1(this->m_i2c);
        LL_I2C_DisableOwnAddress2(this->m_i2c);
        LL_I2C_SetMasterAddressingMode(this->m_i2c, LL_I2C_ADDRESSING_MODE_7BIT);
        LL_I2C_SetMode(this->m_i2c, LL_I2C_MODE_I2C);
        LL_I2C_Enable(this->m_i2c);
    }

    void I2C::Transmit(const uint8_t address, const uint8_t *data, const uint8_t length) {
        LL_I2C_HandleTransfer(this->m_i2c, address, LL_I2C_ADDRSLAVE_7BIT, length, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
        
        while(!LL_I2C_IsActiveFlag_STOP(this->m_i2c)) {

            if(LL_I2C_IsActiveFlag_TXIS(this->m_i2c)) {
                LL_I2C_TransmitData8(this->m_i2c, (*data++));
            }
        }
        LL_I2C_ClearFlag_STOP(this->m_i2c);
    }


    void I2C::Receive(const uint8_t address, uint8_t *data, const uint8_t length) {
        LL_I2C_HandleTransfer(this->m_i2c, address, LL_I2C_ADDRSLAVE_7BIT, length, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);

        while(!LL_I2C_IsActiveFlag_STOP(this->m_i2c)) {

            if(LL_I2C_IsActiveFlag_RXNE(this->m_i2c)) {
                *data++ = LL_I2C_ReceiveData8(this->m_i2c);
            }
        }
        LL_I2C_ClearFlag_STOP(this->m_i2c);
    }

    I2CDevice::I2CDevice(I2C *i2c, const uint8_t address) {
        this->m_i2c = i2c;
        this->m_txAddr = (address << 1) & 0b11111110;
        this->m_rxAddr = (address << 1) | 0b00000001;
    }


    void I2CDevice::WriteReg(uint8_t reg, uint8_t value) {
        uint8_t data[2];
        data[0] = reg;
        data[1] = value;

        this->m_i2c->Transmit(this->m_txAddr, data, 2);
    }

    void I2CDevice::ReadReg(const uint8_t reg, uint8_t *data, const uint8_t length) {
        data[0] = reg;

        this->m_i2c->Transmit(this->m_txAddr, data);
        this->m_i2c->Receive(this->m_rxAddr, data, length);
    }
}