#include "pwr.hpp"
#include "stm32l0xx_hal.h"


namespace Power {
    PowerControl::PowerControl() {
        if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET) {
            __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB); 
            this->m_wokeFromStandby = true;
        }
        else {
            this->m_wokeFromStandby = false;
        }
    }

    bool PowerControl::WokeFromStandby() const {
        return this->m_wokeFromStandby;
    }

    void PowerControl::Standby() {
        /* Disable all used wakeup sources: PWR_WAKEUP_PIN3 */
                HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN2);

                /* Clear all related wakeup flags*/
                __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
                    
                /* Enable WakeUp Pin PWR_WAKEUP_PIN3 connected to PA.02 (Arduino A7) */
                HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2);

                /* Enter the Standby mode */
                HAL_PWR_EnterSTANDBYMode();
    }
}