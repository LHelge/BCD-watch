#include "timer.hpp"

namespace Timer {

    BaseTimer::BaseTimer(const Number number, const uint32_t prescaler) {
        switch (number)
        {
        case TIMER2:
            __HAL_RCC_TIM2_CLK_ENABLE();
            this->m_handle.Instance = TIM2;
            break;
        
        case TIMER21:
            __HAL_RCC_TIM21_CLK_ENABLE();
            this->m_handle.Instance = TIM21;
        }

    
        TIM_MasterConfigTypeDef sMasterConfig = {0};
        TIM_ClockConfigTypeDef sClockSourceConfig = {0};

        this->m_handle.State = HAL_TIM_STATE_RESET;
        this->m_handle.Init.Prescaler = prescaler;
        this->m_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
        this->m_handle.Init.Period = 0xFF;
        this->m_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        this->m_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
        if (HAL_TIM_PWM_Init(&this->m_handle) != HAL_OK)
        {
            // TODO: Assert
        }
        sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
        sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
        if (HAL_TIMEx_MasterConfigSynchronization(&this->m_handle, &sMasterConfig) != HAL_OK)
        {
            // TODO: Assert
        }
        sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
        if (HAL_TIM_ConfigClockSource(&this->m_handle, &sClockSourceConfig) != HAL_OK)
        {
            // TODO: Assert
        }
    }


    PWM::PWM(BaseTimer *timer, const Channel channel, GPIO::Alternate *pin) {
        this->m_timer = timer;
        this->m_channel = channel;
        this->m_pin = pin; // Not really needed, but good check that it's configured
        
        this->SetDutyCycle(0);
    }

    void PWM::SetDutyCycle(const uint8_t dutycycle) {
        TIM_OC_InitTypeDef sConfigOC = {0};
        sConfigOC.OCMode = TIM_OCMODE_PWM1;
        sConfigOC.Pulse = dutycycle;
        sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
        sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
        if (HAL_TIM_PWM_ConfigChannel(&this->m_timer->m_handle, &sConfigOC, this->m_channel) != HAL_OK)
        {
            // TODO: Assert
        }
        HAL_TIM_OC_Start(&this->m_timer->m_handle, this->m_channel);
    }

}