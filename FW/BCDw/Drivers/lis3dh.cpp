#include "lis3dh.hpp"

namespace Accelerometer
{
    // Memory registers of the accelerometer
    static const uint8_t STATUS_REG_AUX = 0x07;
    static const uint8_t OUT_ADC1_L = 0x08;
    static const uint8_t OUT_ADC1_H = 0x09;
    static const uint8_t OUT_ADC2_L = 0x0A;
    static const uint8_t OUT_ADC2_H = 0x0B;
    static const uint8_t OUT_ADC3_L = 0x0C;
    static const uint8_t OUT_ADC3_H = 0x0D;
    static const uint8_t WHO_AM_I = 0x0F;
    static const uint8_t CTRL_REG0 = 0x1E;
    static const uint8_t TEMP_CFG_REG = 0x1F;
    static const uint8_t CTRL_REG1 = 0x20;
    static const uint8_t CTRL_REG2 = 0x21;
    static const uint8_t CTRL_REG3 = 0x22;
    static const uint8_t CTRL_REG4 = 0x23;
    static const uint8_t CTRL_REG5 = 0x24;
    static const uint8_t CTRL_REG6 = 0x25;
    static const uint8_t REFERENCE = 0x26;
    static const uint8_t STATUS_REG = 0x26;
    static const uint8_t OUT_X_L = 0x28;
    static const uint8_t OUT_X_H = 0x29;
    static const uint8_t OUT_Y_L = 0x2A;
    static const uint8_t OUT_Y_H = 0x2B;
    static const uint8_t OUT_Z_L = 0x2C;
    static const uint8_t OUT_Z_H = 0x2D;
    static const uint8_t FIFO_CTRL_REG = 0x2E;
    static const uint8_t FIFO_SRC_REG = 0x2F;
    static const uint8_t INT1_CFG = 0x30;
    static const uint8_t INT1_SRC = 0x31;
    static const uint8_t INT1_THS = 0x32;
    static const uint8_t INT1_DURATION = 0x33;
    static const uint8_t INT2_CFG = 0x34;
    static const uint8_t INT2_SRC = 0x35;
    static const uint8_t INT2_THS = 0x36;
    static const uint8_t INT2_DURATION = 0x37;
    static const uint8_t CLICK_CFG = 0x38;
    static const uint8_t CLICK_SRC = 0x39;
    static const uint8_t CLICK_THS = 0x3A;
    static const uint8_t TIME_LIMIT = 0x3B;
    static const uint8_t TIME_LATENCY = 0x3C;
    static const uint8_t TIME_WINDOW = 0x3D;
    static const uint8_t ACT_THS = 0x3E;
    static const uint8_t ACT_DUR = 0x3F;

    // Multi-byte read flag in register address
    static const uint8_t MULTI_BYTE_READ_ADDR = 0x80;

    // CTRL_REG1 flags
    static const uint8_t CTRL_REG1_ODR_POWER_DOWN = 0x00;
    static const uint8_t CTRL_REG1_ODR_1HZ    = 0x10;
    static const uint8_t CTRL_REG1_ODR_10HZ   = 0x20;
    static const uint8_t CTRL_REG1_ODR_25HZ   = 0x30;
    static const uint8_t CTRL_REG1_ODR_50HZ   = 0x40;
    static const uint8_t CTRL_REG1_ODR_100HZ  = 0x50;
    static const uint8_t CTRL_REG1_ODR_200HZ  = 0x60;
    static const uint8_t CTRL_REG1_ODR_400HZ  = 0x70;
    static const uint8_t CTRL_REG1_ODR_1600HZ = 0x80;
    static const uint8_t CTRL_REG1_ODR_5376HZ = 0x90;
    static const uint8_t CTRL_REG1_ODR_LP_ENABLE = 0x08;
    static const uint8_t CTRL_REG1_ODR_Z_ENABLE  = 0x04;
    static const uint8_t CTRL_REG1_ODR_Y_ENABLE  = 0x02;
    static const uint8_t CTRL_REG1_ODR_X_ENABLE  = 0x01;
    static const uint8_t CTRL_REG1_ODR_XYZ_ENABLE  = 0x07; // Helper :D

    // TODO: Add other registers flags

    static const uint8_t WhoAmI = 0b00110011;

    LIS3DH::LIS3DH(I2C::I2CDevice *i2c) {
        this->m_state = Reset;
        this->m_i2c = i2c;

        uint8_t whoami;

        this->m_i2c->ReadReg(WHO_AM_I, &whoami);

        if(whoami != WhoAmI) {
            this->m_state = Error;
        }
    }


    void LIS3DH::Init() {
        if(this->m_state != Reset) {
            return;
        }

        this->m_i2c->WriteReg(CTRL_REG1, 
            CTRL_REG1_ODR_10HZ | 
            CTRL_REG1_ODR_LP_ENABLE | 
            CTRL_REG1_ODR_XYZ_ENABLE
        );

        this->m_state = Ready;
    }

   
    void LIS3DH::getAcceleration(AccelerationVector& vector) {
        uint8_t data[6];

        if(this->m_state != Ready) {
            vector.X = 0;
            vector.Y = 0;
            vector.Z = 0;
            return;
        }

        this->m_i2c->ReadReg(OUT_X_L | MULTI_BYTE_READ_ADDR, data, 6);

        vector.X  = data[0] << 0;
        vector.X |= data[1] << 8;
        vector.Y  = data[2] << 0;
        vector.Y |= data[3] << 8;
        vector.Z  = data[4] << 0;
        vector.Z |= data[5] << 8;
    }

    LIS3DH::State LIS3DH::getState() const {
        return m_state;
    }


    uint8_t LIS3DH::getAddress(const bool sda) {
        return sda ? 0b0011001 : 0b0011000;
    }

} // namespace Accelerometer


