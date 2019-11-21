#ifndef _GPIO_HPP
#define _GPIO_HPP

#include "stdint.h"
#include "stdbool.h"
#include "stm32l0xx_hal.h"

namespace GPIO
{
    enum Port {A, B, C, H};
    enum State {RESET = 0, SET = 1};



    class Pin {
    public:
        Pin(const Port port, const uint8_t pin);

        operator bool() const;

    protected:
        virtual State GetState() const = 0;
        virtual void SetState(const State state) = 0;
        GPIO_TypeDef *m_gpioPort;
        uint16_t m_gpioPin;
    };


    class Output : public Pin {
    public:
        Output(const Port port, const uint8_t pin, const bool pushpull);

        void Set();
        void Reset();
        void Toggle();
    protected:
        State GetState() const override;
        void SetState(const State state) override;
    private:
        State m_state;
    };


    class Input : public Pin {
    public:
        Input(const Port port, const uint8_t pin);

        bool IsSet();
    protected:
        State GetState() const override;
        void SetState(const State state) override;
    };


    class Alternate : public Pin {
    public:
        Alternate(const Port port, const uint8_t pin, const bool pushpull, const uint8_t alternate);
    protected:
        State GetState() const override;
        void SetState(const State state) override;
    };

} // namespace GPIO

#endif

