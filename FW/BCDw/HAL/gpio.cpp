#include "gpio.hpp"

namespace GPIO
{
    
    Pin::Pin(const Port port, const uint8_t pin) {
        this->m_gpioPin = 1 << pin; // TODO: assert on bad input

        switch(port) {
            case Port::A: 
                __HAL_RCC_GPIOA_CLK_ENABLE(); 
                this ->m_gpioPort = GPIOA;
                break;
            case Port::B: 
                __HAL_RCC_GPIOB_CLK_ENABLE(); 
                this ->m_gpioPort = GPIOB;
                break;
            case Port::C: 
                __HAL_RCC_GPIOC_CLK_ENABLE(); 
                this ->m_gpioPort = GPIOC;
                break;
            case Port::H: 
                __HAL_RCC_GPIOH_CLK_ENABLE(); 
                this ->m_gpioPort = GPIOH;
                break;
            case Port::None:
                this->m_gpioPort = nullptr;
                break;
        }
    }

    Pin::operator bool() const {
        return this->GetState() == SET;
    }

    void Pin::Set() {
        this->SetState(State::SET);
    }


    void Pin::Reset() {
        this->SetState(State::RESET);
    }

    void Pin::Toggle() {
        this->SetState(this->IsSet() ? State::RESET : State::SET);
    }

    bool Pin::IsSet() {
        return this->GetState() == State::SET;
    }

    Output::Output(const Port port, const uint8_t pin, const bool pushpull) : Pin(port, pin) {
        this->SetState(State::RESET);

        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = this->m_gpioPin;
        GPIO_InitStruct.Mode = pushpull ? GPIO_MODE_OUTPUT_PP : GPIO_MODE_OUTPUT_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(this->m_gpioPort, &GPIO_InitStruct);
    }


    State Output::GetState() const {
        return this->m_state;
    }

    void Output::SetState(const State state) {
        HAL_GPIO_WritePin(this->m_gpioPort, this->m_gpioPin, state == State::SET ? GPIO_PIN_SET : GPIO_PIN_RESET);
        this->m_state = state;
    }




    Input::Input(const Port port, const uint8_t pin) : Pin(port, pin) {

        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = this->m_gpioPin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(this->m_gpioPort, &GPIO_InitStruct);
    }

    State Input::GetState() const {
        return HAL_GPIO_ReadPin(this->m_gpioPort, this->m_gpioPin) == GPIO_PIN_SET ? State::SET : State::RESET;
    }

    void Input::SetState(const State state) {
        // Not relevant
    }



    Alternate::Alternate(const Port port, const uint8_t pin, const bool pushpull, const uint8_t alternate) : Pin(port, pin) {

        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = this->m_gpioPin;
        GPIO_InitStruct.Mode = pushpull ? GPIO_MODE_AF_PP : GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = alternate;
        HAL_GPIO_Init(this->m_gpioPort, &GPIO_InitStruct);
    }

    State Alternate::GetState() const {
        return RESET; // Not relevant
    }

    void Alternate::SetState(const State state) {
        // Not relevant
    }


    Dummy::Dummy(const State initState) : Pin(None, 0) {
        this->m_state = initState;
    }

    State Dummy::GetState() const {
        return this->m_state;
    }

    void Dummy::SetState(const State state) {
        this->m_state = state;
    }

} // namespace GPIO