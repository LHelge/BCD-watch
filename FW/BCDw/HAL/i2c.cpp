#include "i2c.hpp"
#include "string.h"

namespace I2C {

    I2CDevice::I2CDevice(const Number number, const uint8_t address, GPIO::Alternate *sclPin, GPIO::Alternate *sdaPin) {
        memset(&this->m_handle, 0, sizeof(I2C_HandleTypeDef));

        switch (number)
        {
        case I2C_1:
            __HAL_RCC_I2C1_CLK_ENABLE();
            this->m_handle.Instance = I2C1;
            break;
        
        default:
            break;
        }

        // Not needed, but good check that pins are initialized
        this->m_sclPin = sclPin;
        this->m_sdaPin = sdaPin;

        this->m_txAddr = (address << 1) & 0b11111110;
        this->m_rxAddr = (address << 1) | 0b00000001;

        this->m_handle.Init.Timing = 0x00303D5B;
        this->m_handle.Init.OwnAddress1 = 0;
        this->m_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
        this->m_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
        this->m_handle.Init.OwnAddress2 = 0;
        this->m_handle.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
        this->m_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
        this->m_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
        if (HAL_I2C_Init(&this->m_handle) != HAL_OK)
        {
            //TODO: Assert
        }
        /** Configure Analogue filter 
         */
        if (HAL_I2CEx_ConfigAnalogFilter(&this->m_handle, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
        {
            //TODO: Assert
        }
        /** Configure Digital filter 
         */
        if (HAL_I2CEx_ConfigDigitalFilter(&this->m_handle, 0) != HAL_OK)
        {
            //TODO: Assert
        }
    }


    void I2CDevice::WriteReg(uint8_t reg, uint8_t value) {
        uint8_t data[2];
        data[0] = reg;
        data[1] = value;

        HAL_I2C_Master_Transmit(&this->m_handle, this->m_txAddr, data, 2, 100);

    }

    // void I2CDevice::ReadReg(uint8_t reg, uint8_t *data) {
        
    // }

    void I2CDevice::ReadReg(uint8_t reg, uint8_t *data, uint16_t length) {
        data[0] = reg;

        HAL_I2C_Master_Transmit(&this->m_handle, this->m_txAddr, data, 1, 100);
        HAL_I2C_Master_Receive(&this->m_handle, this->m_rxAddr, data, length, 100);
    }
}