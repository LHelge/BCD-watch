#include "LIS3DH.hpp"

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
    static const uint8_t MULTI_BYTE_READ_ADDR_FLAG = 0x80;

    // CTRL_REG1 flags
    static const uint8_t CTRL_REG1_ODR_POWER_DOWN  = 0x00;
    static const uint8_t CTRL_REG1_ODR_1HZ         = 0x10;
    static const uint8_t CTRL_REG1_ODR_10HZ        = 0x20;
    static const uint8_t CTRL_REG1_ODR_25HZ        = 0x30;
    static const uint8_t CTRL_REG1_ODR_50HZ        = 0x40;
    static const uint8_t CTRL_REG1_ODR_100HZ       = 0x50;
    static const uint8_t CTRL_REG1_ODR_200HZ       = 0x60;
    static const uint8_t CTRL_REG1_ODR_400HZ       = 0x70;
    static const uint8_t CTRL_REG1_ODR_1600HZ      = 0x80;
    static const uint8_t CTRL_REG1_ODR_5376HZ      = 0x90;
    static const uint8_t CTRL_REG1_LP_ENABLE       = 0x08;
    static const uint8_t CTRL_REG1_Z_ENABLE        = 0x04;
    static const uint8_t CTRL_REG1_Y_ENABLE        = 0x02;
    static const uint8_t CTRL_REG1_X_ENABLE        = 0x01;
    static const uint8_t CTRL_REG1_XYZ_ENABLE      = 0x07; // Helper :D
    static const uint8_t CTRL_REG1_RESET           = 0x07;

    // CTRL_REG2 flags
    static const uint8_t CTRL_REG2_HPM0    = 0x00;
    static const uint8_t CTRL_REG2_HPM1    = 0x40;
    static const uint8_t CTRL_REG2_HPM2    = 0x80;
    static const uint8_t CTRL_REG2_HPM3    = 0xC0;
    static const uint8_t CTRL_REG2_HPCF0   = 0x00;
    static const uint8_t CTRL_REG2_HPCF1   = 0x10;
    static const uint8_t CTRL_REG2_HPCF2   = 0x20;
    static const uint8_t CTRL_REG2_HPCF3   = 0x30;
    static const uint8_t CTRL_REG2_FDS     = 0x08;
    static const uint8_t CTRL_REG2_HPCLICK = 0x04;
    static const uint8_t CTRL_REG2_HP_IA2  = 0x02;
    static const uint8_t CTRL_REG2_HP_IA1  = 0x01;
    static const uint8_t CTRL_REG2_RESET   = 0x00;
    
    

    // CTRL_REG3 flags
    static const uint8_t CTRL_REG3_I1_CLICK   = 0x80;
    static const uint8_t CTRL_REG3_I1_IA1     = 0x40;
    static const uint8_t CTRL_REG3_I1_IA2     = 0x20;
    static const uint8_t CTRL_REG3_I1_ZYXDA   = 0x10;
    static const uint8_t CTRL_REG3_I1_321DA   = 0x08;
    static const uint8_t CTRL_REG3_I1_WTM     = 0x04;
    static const uint8_t CTRL_REG3_I1_OVERRUN = 0x02;
    static const uint8_t CTRL_REG3_RESET      = 0x00;

    // CTRL_REG4
    static const uint8_t CTRL_REG4_BDU       = 0x80;
    static const uint8_t CTRL_REG4_BLE       = 0x40;
    static const uint8_t CTRL_REG4_FS_2G     = 0x00;
    static const uint8_t CTRL_REG4_FS_4G     = 0x10;
    static const uint8_t CTRL_REG4_FS_8G     = 0x20;
    static const uint8_t CTRL_REG4_FS_16G    = 0x30;
    static const uint8_t CTRL_REG4_HR        = 0x08;
    static const uint8_t CTRL_REG4_ST_NORMAL = 0x00;
    static const uint8_t CTRL_REG4_ST_0      = 0x02;
    static const uint8_t CTRL_REG4_ST_1      = 0x04;
    static const uint8_t CTRL_REG4_SIM       = 0x01;
    static const uint8_t CTRL_REG4_RESET     = 0x00;


    // CTRL_REG5 flags
    static const uint8_t CTRL_REG5_BOOT     = 0x80;
    static const uint8_t CTRL_REG5_FIFO_EN  = 0x40;
    static const uint8_t CTRL_REG5_LIR_INT1 = 0x08;
    static const uint8_t CTRL_REG5_D4D_INT1 = 0x04;
    static const uint8_t CTRL_REG5_LIR_INT2 = 0x02;
    static const uint8_t CTRL_REG5_D4D_INT2 = 0x01;
    static const uint8_t CTRL_REG5_RESET    = 0x00;
    
    
    // CTRL_REG6 flags
    static const uint8_t CTRL_REG6_I2_CLICK     = 0x80;
    static const uint8_t CTRL_REG6_I2_IA1       = 0x40;
    static const uint8_t CTRL_REG6_I2_IA2       = 0x20;
    static const uint8_t CTRL_REG6_I2_BOOT      = 0x10;
    static const uint8_t CTRL_REG6_I2_ACT       = 0x04;
    static const uint8_t CTRL_REG6_INT_POLARITY = 0x02;
    static const uint8_t CTRL_REG6_RESET        = 0x00;



    // INT1_CFG flags
    static const uint8_t INT1_CFG_AOI  = 0x80;
    static const uint8_t INT1_CFG_6D   = 0x40;
    static const uint8_t INT1_CFG_ZHIE = 0x20;
    static const uint8_t INT1_CFG_ZLIE = 0x10;
    static const uint8_t INT1_CFG_YHIE = 0x08;
    static const uint8_t INT1_CFG_YLIE = 0x04;
    static const uint8_t INT1_CFG_XHIE = 0x02;
    static const uint8_t INT1_CFG_XLIE = 0x01;

    // TODO: Add other registers flags

    static const uint8_t WhoAmI = 0b00110011;

    LIS3DH::LIS3DH(I2C::I2CDevice *i2c, GPIO::Pin *intPin) {
        this->m_i2c = i2c;
        this->m_intPin = intPin;
        this->m_initialized = false;
    }


    void LIS3DH::Init() {
        uint8_t whoami;

        this->m_i2c->ReadReg(WHO_AM_I, &whoami);

        if(whoami != WhoAmI) {
            // TODO: Assert
            return;
        }
        else {
            // Read interrupt sources before resetting memory content
            this->m_i2c->ReadReg(INT1_SRC, &this->m_int1Src);
            this->m_i2c->ReadReg(INT2_SRC, &this->m_int2Src);

            // Reset control registers (if there was an interrupt)
            this->m_i2c->WriteReg(CTRL_REG1, CTRL_REG1_RESET);
            this->m_i2c->WriteReg(CTRL_REG2, CTRL_REG2_RESET);
            this->m_i2c->WriteReg(CTRL_REG3, CTRL_REG3_RESET);
            this->m_i2c->WriteReg(CTRL_REG4, CTRL_REG4_RESET);
            this->m_i2c->WriteReg(CTRL_REG5, CTRL_REG5_RESET);
            this->m_i2c->WriteReg(CTRL_REG6, CTRL_REG6_RESET);
        }

        // TODO: check these later

        // Low power mode @ 50 Hz, X, Y & Z enabled
        this->m_i2c->WriteReg(CTRL_REG1, 
            CTRL_REG1_ODR_50HZ | 
            CTRL_REG1_LP_ENABLE |
            CTRL_REG1_XYZ_ENABLE
        );

        this->m_i2c->WriteReg(CTRL_REG2,
            CTRL_REG2_RESET
        );

        this->m_i2c->WriteReg(CTRL_REG3,
            CTRL_REG3_RESET
        );

        this->m_i2c->WriteReg(CTRL_REG4,
            CTRL_REG4_RESET
        );

        this->m_i2c->WriteReg(CTRL_REG5,
            CTRL_REG5_RESET
        );

        this->m_i2c->WriteReg(CTRL_REG6,
            CTRL_REG6_RESET
        );

        this->m_initialized = true;
    }


    void LIS3DH::ActivateWakeUpInterrupt() {

        // TODO: Select a better interrupt, perhaps click/doubleclick or 6D

        this->m_i2c->WriteReg(CTRL_REG1, 
            CTRL_REG1_ODR_10HZ | 
            CTRL_REG1_LP_ENABLE | 
            CTRL_REG1_X_ENABLE |
            CTRL_REG1_Y_ENABLE 
        );

        this->m_i2c->WriteReg(CTRL_REG2, 0x00);

        this->m_i2c->WriteReg(CTRL_REG3, 
            CTRL_REG3_I1_IA1
        );

        this->m_i2c->WriteReg(CTRL_REG4, 0x00);

        // Latch interrupt until SRC reg is read
        this->m_i2c->WriteReg(CTRL_REG5,
            CTRL_REG5_LIR_INT1
        );
        
        // Threshold 
        this->m_i2c->WriteReg(INT1_THS, 0x15);

        // Duration instant
        this->m_i2c->WriteReg(INT1_DURATION, 0);


        this->m_i2c->WriteReg(INT1_CFG,
            INT1_CFG_XHIE |
            INT1_CFG_YHIE
        );
    }
   
    void LIS3DH::getAcceleration(AccelerationVector& vector) {
        vector.X = m_i2c->ReadReg<int16_t>(OUT_X_L | MULTI_BYTE_READ_ADDR_FLAG);
        vector.Y = m_i2c->ReadReg<int16_t>(OUT_Y_L | MULTI_BYTE_READ_ADDR_FLAG);
        vector.Z = m_i2c->ReadReg<int16_t>(OUT_Z_L | MULTI_BYTE_READ_ADDR_FLAG);

    }

    Events LIS3DH::Tick() {
        if(this->m_initialized == false) {
            return Events::None;
        }

        if(this->m_intPin->Get()) {
            this->m_i2c->ReadReg(INT1_SRC, &this->m_int1Src);
            this->m_i2c->ReadReg(INT2_SRC, &this->m_int2Src);

            // TODO: check for events.
        }

        return Events::None;
    }


    uint8_t LIS3DH::getAddress(const bool sda) {
        return sda ? 0b0011001 : 0b0011000;
    }

} // namespace Accelerometer


