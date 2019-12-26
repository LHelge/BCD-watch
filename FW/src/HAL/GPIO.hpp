#ifndef _GPIO_HPP
#define _GPIO_HPP

#include "stm32l0xx_ll_gpio.h"

namespace GPIO
{
    enum Port { A, B, C, D, E, H };
    
    enum Mode : uint32_t {
        Output = LL_GPIO_MODE_OUTPUT,
        Input = LL_GPIO_MODE_INPUT,
        Alternate = LL_GPIO_MODE_ALTERNATE,
        Analog = LL_GPIO_MODE_ANALOG,
        None
    };

    enum Type : uint32_t {
        PushPull = LL_GPIO_OUTPUT_PUSHPULL,
        OpenDrain = LL_GPIO_OUTPUT_OPENDRAIN
    };

    enum Speed : uint32_t {
        Low = LL_GPIO_SPEED_FREQ_LOW,
        Medium = LL_GPIO_SPEED_FREQ_MEDIUM,
        High = LL_GPIO_SPEED_FREQ_HIGH,
        VeryHigh = LL_GPIO_SPEED_FREQ_VERY_HIGH
    };

    enum Pull : uint32_t {
        No = LL_GPIO_PULL_NO,
        Up = LL_GPIO_PULL_UP,
        Down = LL_GPIO_PULL_DOWN
    };

    class Pin {
    public: 
        Pin(const Port port, const uint32_t pin);

        void InitOutput(const Type type = Type::PushPull, const Speed speed = Speed::Low);
        void InitInput(const Pull pull = Pull::No, const Speed speed = Speed::Low);
        void InitAlternate(uint8_t alternate, const Type type = Type::PushPull, const Speed speed = Speed::Low, const Pull pull = Pull::No);

        void Toggle();
        bool Get();
        void Set();
        void Reset();
    private:
        GPIO_TypeDef *m_port;
        uint32_t m_pin;
        Mode m_mode;
    };
} // namespace GPIO


#endif