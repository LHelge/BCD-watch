#ifndef _LIS3DH_HPP
#define _LIS3DH_HPP

#include "I2C.hpp"
#include "GPIO.hpp"
#include "Events.hpp"
#include "Task.hpp"
#include "Queue.hpp"
#include "Timer.hpp"

namespace Accelerometer
{
    struct AccelerationVector {
        int16_t X, Y, Z;
    };


    class LIS3DH : public FreeRTOS::Task<1024>  {
    public:
        LIS3DH(I2C::I2CDevice *i2c, GPIO::Pin *intPin, FreeRTOS::Queue<Events, EventQueueLength> *eventQueue);

        void ActivateWakeUpInterrupt();
        void getAcceleration(AccelerationVector& vector);

        void Run() override;

        static uint8_t getAddress(const bool sda);
    private:
        bool m_initialized;
        I2C::I2CDevice *m_i2c;
        GPIO::Pin *m_intPin;
        uint8_t m_int1Src;
        uint8_t m_int2Src;
        FreeRTOS::Queue<Events, EventQueueLength> *m_eventQueue;
    };
} // namespace Accelerometer



#endif