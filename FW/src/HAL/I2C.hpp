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
        void ReadReg(const uint8_t reg, uint8_t *data, const uint32_t length = 1);
        // ReadReg template for reading arbitrary types. Since the template
        // typename cannot be resolved by parameters it needs to be explicitly
        // instantiated. E.g.:
        //
        //   uint32_t my_val = i2c->ReadReg<uint32_t>(REG_ID1);
        //   uint64_t huge_val = i2c->ReadReg<uint16_t>(REG_ID2);
        //
        template<typename T>
        T ReadReg(uint8_t reg) {
            uint8_t byte_data[sizeof(T)];
            ReadReg(reg, byte_data, sizeof(T));

            T result = 0;
            for (size_t i = 0; i < sizeof(T); i++) {
                result |= byte_data[i] << 8*i;
            }
            return result;
        }

        // ReadReg template for reading arrays of arbitrarily typed data. As
        // the compiler can derive T from the parameter, can be called like so:
        //
        //   int16_t v[3];
        //   ReadReg(OUT_X_L | MULTI_BYTE_READ_ADDR, v, 3);
        //   AccelerationVector vector;
        //   vector.X = v[0];
        //   vector.Y = v[1];
        //   vector.Z = v[2];
        //
        template<typename T>
        bool ReadReg(uint8_t reg, T *data, uint32_t length) {
            if (sizeof(T) * length > UINT32_MAX) {
                // Trying to read more data than LL supports.
                return false;
            }

            uint32_t size = sizeof(T) * length;
            uint8_t byte_data[size];
            ReadReg(reg, byte_data, size);
            for (uint32_t i = 0; i < length; i++) {
                data[i] = 0;
                for (size_t j = 0; j < sizeof(T); j++) {
                    data[i] |= byte_data[i * sizeof(T) + j] << 8*j;
                }
            }
        }
    private:
        I2C *m_i2c;
        uint8_t m_txAddr;
        uint8_t m_rxAddr;
    };
}

#endif
