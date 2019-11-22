#include "BCDw.hpp"
#include "gpio.hpp"
#include "timer.hpp"
#include "stm32l0xx_hal.h"
#include "main.h"
#include "uart.hpp"

#define DEBUG_UART

class BCDw {
    public:
        void run(void);
};



void bcdw_run(void) {
    static BCDw watch;    
    watch.run();
}

void BCDw::run(void) {
    GPIO::Output LED_S_00(GPIO::B, 10, true);
    GPIO::Output LED_S_01(GPIO::B,  1, true);
    GPIO::Output LED_S_02(GPIO::A,  7, true);
    GPIO::Output LED_S_03(GPIO::A,  5, true);
    GPIO::Output LED_S_10(GPIO::B,  2, true);
    GPIO::Output LED_S_11(GPIO::B,  0, true);
    GPIO::Output LED_S_12(GPIO::A,  6, true);
    GPIO::Output LED_S_13(GPIO::A,  4, true);
    GPIO::Output LED_M_00(GPIO::A,  8, true);
    GPIO::Output LED_M_01(GPIO::B, 15, true);
    GPIO::Output LED_M_02(GPIO::H,  0, true);
    GPIO::Output LED_M_03(GPIO::H,  1, true);
    GPIO::Output LED_M_10(GPIO::B, 12, true);
    GPIO::Output LED_M_11(GPIO::B, 11, true);
    GPIO::Output LED_M_12(GPIO::A,  0, true);
    GPIO::Output LED_M_13(GPIO::A,  1, true);
    GPIO::Output LED_H_00(GPIO::A, 12, true);
    GPIO::Output LED_H_01(GPIO::A, 11, true);
    GPIO::Output LED_H_02(GPIO::B,  8, true);
    GPIO::Output LED_H_03(GPIO::B,  9, true);
    GPIO::Output LED_H_10(GPIO::B,  4, true);
    GPIO::Output LED_H_11(GPIO::B,  5, true);
    #ifndef DEBUG_UART
    GPIO::Output LED_H_12(GPIO::B,  6, true);
    GPIO::Output LED_H_13(GPIO::B,  7, true);
    #endif
    
    GPIO::Input Button(GPIO::C, 13);

    GPIO::Alternate LED_S_0_Dim(GPIO::A, 2, false, 2);
    GPIO::Alternate LED_S_1_Dim(GPIO::A, 3, false, 2);
    GPIO::Alternate LED_M_0_Dim(GPIO::B, 13, false, 6);
    GPIO::Alternate LED_M_1_Dim(GPIO::B, 14, false, 6);
    GPIO::Alternate LED_H_0_Dim(GPIO::A, 15, false, 5);
    GPIO::Alternate LED_H_1_Dim(GPIO::B, 3, false, 2);

    Timer::BaseTimer Timer2(Timer::TIMER2, 3);
    Timer::BaseTimer Timer21(Timer::TIMER21, 3);
    Timer::PWM PWM_S_0(&Timer2, Timer::CHANNEL_3, &LED_S_0_Dim);
    Timer::PWM PWM_S_1(&Timer2, Timer::CHANNEL_4, &LED_S_1_Dim);
    Timer::PWM PWM_M_0(&Timer21, Timer::CHANNEL_1, &LED_M_0_Dim);
    Timer::PWM PWM_M_1(&Timer21, Timer::CHANNEL_2, &LED_M_1_Dim);
    Timer::PWM PWM_H_0(&Timer2, Timer::CHANNEL_1, &LED_H_0_Dim);
    Timer::PWM PWM_H_1(&Timer2, Timer::CHANNEL_2, &LED_H_1_Dim);

    #ifdef DEBUG_UART
    GPIO::Alternate DebugTx(GPIO::B, 6, true, 0);
    GPIO::Alternate DebugRx(GPIO::B, 7, true, 0);
    UART::SerialPort Debug(UART::UART1, 115200, &DebugTx, &DebugRx);
    #endif


    LED_S_00.Set();
    LED_S_11.Set();
    LED_M_02.Set();
    LED_M_13.Set();
    LED_H_00.Set();
    LED_H_10.Set();
    LED_H_11.Set();
    // LED_H_12.Set();
    // LED_H_13.Set();

    uint8_t dutycycle = 0x10;
    PWM_S_0.SetDutyCycle(dutycycle);
    PWM_S_1.SetDutyCycle(dutycycle);
    PWM_M_0.SetDutyCycle(dutycycle);
    PWM_M_1.SetDutyCycle(dutycycle);
    PWM_H_0.SetDutyCycle(dutycycle);
    PWM_H_1.SetDutyCycle(0xFF);

    while(1) {
        if(Button) {
            Debug.Write("Hello World!\r\n");
            HAL_Delay(500);
        }
    }
}

