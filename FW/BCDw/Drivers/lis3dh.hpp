#ifndef _LIS3DH_HPP
#define _LIS3DH_HPP

#include "i2c.hpp"

namespace Accelerometer
{
    struct AccelerationVector {
        int16_t X, Y, Z;
    };

    class LIS3DH {
    public:
        enum State {
            Reset = 0,
            PreInit,
            Ready,
            Error
        };

        LIS3DH(I2C::I2CDevice *i2c);

        
        void Init();
        void getAcceleration(AccelerationVector& vector);
        State getState() const;

        
        static uint8_t getAddress(const bool sda);
    private:
        I2C::I2CDevice *m_i2c;
        State m_state;
    };
} // namespace Accelerometer



#endif