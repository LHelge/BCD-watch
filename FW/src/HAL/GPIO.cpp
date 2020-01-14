#include "GPIO.hpp"
#include "System.hpp"
#include "stm32l0xx_ll_bus.h"

namespace GPIO
{
    Pin::Pin(const Port port, const uint32_t pin) {

        switch(port) {
            case A:
                System::System::EnableClock(System::ClockHW::GpioA);
                this->m_port = GPIOA;
                break;
            case B:
                System::System::EnableClock(System::ClockHW::GpioB);
                this->m_port = GPIOB;
                break;
            case C:
                System::System::EnableClock(System::ClockHW::GpioC);
                this->m_port = GPIOC;
                break;
            case D:
                System::System::EnableClock(System::ClockHW::GpioD);
                this->m_port = GPIOD;
                break;
            case E:
                System::System::EnableClock(System::ClockHW::GpioE);
                this->m_port = GPIOE;
                break;
            case H:
                System::System::EnableClock(System::ClockHW::GpioH);
                this->m_port = GPIOH;
                break;
            default:
                // TODO: Assert
                break;
        }

        
        this->m_pin = 1 << pin;
        this->m_mode = Mode::None;
    }

    void Pin::InitOutput(const Type type, const Speed speed) {
        this->m_mode = Mode::Output;
        LL_GPIO_SetPinMode(this->m_port, this->m_pin, this->m_mode);
        LL_GPIO_SetPinOutputType(this->m_port, this->m_pin, type);
        LL_GPIO_SetPinSpeed(this->m_port, this->m_pin, speed);
        LL_GPIO_SetPinPull(this->m_port, this->m_pin, Pull::No);
    }


    void Pin::InitInput(const Pull pull, const Speed speed) {
        this->m_mode = Mode::Input;
        LL_GPIO_SetPinMode(this->m_port, this->m_pin, this->m_mode);
        LL_GPIO_SetPinSpeed(this->m_port, this->m_pin, speed);
        LL_GPIO_SetPinPull(this->m_port, this->m_pin, pull);
    }

    void Pin::InitAlternate(uint8_t alternate, const Type type, const Speed speed, const Pull pull) {
        this->m_mode = Mode::Alternate;
        LL_GPIO_SetPinMode(this->m_port, this->m_pin, this->m_mode);
        LL_GPIO_SetPinOutputType(this->m_port, this->m_pin, type);
        LL_GPIO_SetPinSpeed(this->m_port, this->m_pin, speed);
        LL_GPIO_SetPinPull(this->m_port, this->m_pin, Pull::No);
        if(this->m_pin & 0x00FF) {
            LL_GPIO_SetAFPin_0_7(this->m_port, this->m_pin, alternate);
        }
        else {
            LL_GPIO_SetAFPin_8_15(this->m_port, this->m_pin, alternate);
        }
    }

    void Pin::Toggle() {
        if(this->m_mode == Mode::Output) {
            LL_GPIO_TogglePin(this->m_port, this->m_pin);
        }        
    }

    bool Pin::Get() {
        if(this->m_mode == Mode::Input) {
            return LL_GPIO_IsInputPinSet(this->m_port, this->m_pin);
        }
        else if(this->m_mode == Mode::Output) {
            return LL_GPIO_IsOutputPinSet(this->m_port, this->m_pin);
        }

        return false;
    }

    void Pin::Set() {
        if(this->m_mode == Mode::Output) {
            LL_GPIO_SetOutputPin(this->m_port, this->m_pin);
        }
    }

    void Pin::Reset() {
        if(this->m_mode == Mode::Output) {
            LL_GPIO_ResetOutputPin(this->m_port, this->m_pin);
        }        
    }
} // namespace GPIO
