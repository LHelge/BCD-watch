#include "System.hpp"
#include "App.hpp"

#include "stm32l0xx_ll_rcc.h"
#include "stm32l0xx_ll_pwr.h"
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_system.h"
#include "stm32l0xx_ll_cortex.h"
#include "stm32l0xx_ll_utils.h"

namespace System {

    volatile uint32_t System::m_delayCounter = 0;
    bool System::m_resumed = false;

    void System::Initialize() {
        LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

        if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
        {
            while(1);
            // TODO
        }
        LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
        LL_RCC_HSI_Enable();

        /* Wait till HSI is ready */
        while(LL_RCC_HSI_IsReady() != 1) {}

        LL_RCC_HSI_SetCalibTrimming(16);

        // LSE/RTC
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
        LL_PWR_EnableBkUpAccess();
        // Check if LSE is already running
        if(LL_RCC_LSE_IsReady() == 0) {
            LL_RCC_ForceBackupDomainReset();
            LL_RCC_ReleaseBackupDomainReset();
            LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_HIGH);
            LL_RCC_LSE_Enable();

            /* Wait till LSE is ready */
            while(LL_RCC_LSE_IsReady() != 1) {}
        }
        LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
        LL_RCC_EnableRTC();

        // Configure system clock to 32 MHz from HSI/PLL
        LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLL_MUL_4, LL_RCC_PLL_DIV_2);
        LL_RCC_PLL_Enable();

        /* Wait till PLL is ready */
        while(LL_RCC_PLL_IsReady() != 1) {}

        LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
        LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
        LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
        LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

        /* Wait till System clock is ready */
        while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {}

        
        // Check if system aws resumed from standby
        System::m_resumed = false;
        if (LL_PWR_IsActiveFlag_SB() != 0)
        { 
            System::m_resumed = true;

            LL_PWR_ClearFlag_SB(); 
        }

        // Check and Clear the Wakeup flag
        if (LL_PWR_IsActiveFlag_WU() != 0)
        {
            LL_PWR_ClearFlag_WU();
        }


        LL_Init1msTick(32000000);
        LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
        LL_SetSystemCoreClock(32000000);
        
        LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2);
        LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_PCLK1);
        
        LL_SYSTICK_EnableIT();
        __enable_irq();
    }

    uint32_t System::GetCoreClock() {
        return 32000000;
    }

    void System::EnableClock(const ClockHW clock) {
        switch(clock) {
            case GpioA: LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA)   ;break;
            case GpioB: LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB)   ;break;
            case GpioC: LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC)   ;break;
            case GpioD: LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD)   ;break;
            case GpioE: LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOE)   ;break;
            case GpioH: LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOH)   ;break;
            case Tim2:  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2)  ;break;
            case Tim21: LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM21) ;break;
            case I2c1:  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1)  ;break;
            case Usart1: LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1) ;break;
            default:
                // TODO: Assert
                break;
        }
    }

    void System::Delay(const uint32_t milliseconds) {
        System::m_delayCounter = milliseconds;

        while(System::m_delayCounter > 0);
    }

    void System::Reset() {
        NVIC_SystemReset();
    }

    void System::Standby(const Wakeup wakeup) {
        // TODO: Remove this, temporary
        LL_DBGMCU_EnableDBGStandbyMode();


        /* Disable all used wakeup sources */
        LL_PWR_DisableWakeUpPin(wakeup);
  
        /* Clear all wake up Flag */
        LL_PWR_ClearFlag_WU();
  
        /* Enable wakeup pin */
        LL_PWR_EnableWakeUpPin(wakeup);
  
        /* As default User push-button state is high level, need to clear all wake up Flag again */
        LL_PWR_ClearFlag_WU();

        /* Enable ultra low power mode */
        LL_PWR_EnableUltraLowPower();

        /** Request to enter STANDBY mode
            * Following procedure describe in STM32L0xx Reference Manual
            * See PWR part, section Low-power modes, Standby mode
            */
        /* Set STANDBY mode when CPU enters deepsleep */
        LL_PWR_SetPowerMode(LL_PWR_MODE_STANDBY);
        
        /* Set SLEEPDEEP bit of Cortex System Control Register */
        LL_LPM_EnableDeepSleep();

        #if defined ( __CC_ARM)
            __force_stores();
        #endif
        
        /* Request Wait For Interrupt */
        __WFI();
    }


    bool System::IsResumed() {
        return System::m_resumed;
    }

    void System::SysTickInterrupt() {
        if(System::m_delayCounter > 0) 
            System::m_delayCounter--;

        App::Tick();
    }

}