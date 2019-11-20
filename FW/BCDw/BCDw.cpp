#include "BCDw.hpp"
#include "gpio.hpp"
#include "stm32l0xx_hal.h"
#include "main.h"

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
    GPIO::Output LED_H_02(GPIO::B, 8, true);
    GPIO::Output LED_H_03(GPIO::B, 9, true);
    GPIO::Output LED_H_10(GPIO::B, 4, true);
    GPIO::Output LED_H_11(GPIO::B, 5, true);
    GPIO::Output LED_H_12(GPIO::B, 6, true);
    GPIO::Output LED_H_13(GPIO::B, 7, true);
    GPIO::Output LED_S_0_Dim(GPIO::A, 2, false);
    GPIO::Output LED_S_1_Dim(GPIO::A, 3, false);
    GPIO::Output LED_M_0_Dim(GPIO::B, 13, false);
    GPIO::Output LED_M_1_Dim(GPIO::B, 14, false);
    GPIO::Output LED_H_0_Dim(GPIO::A, 15, false);
    GPIO::Output LED_H_1_Dim(GPIO::B, 3, false);
    GPIO::Input Button(GPIO::C, 13);


    LED_S_0_Dim.Reset();
    LED_S_1_Dim.Reset();
    LED_M_0_Dim.Reset();
    LED_M_1_Dim.Reset();
    LED_H_0_Dim.Reset();
    LED_H_1_Dim.Reset();

    LED_S_00.Set();
    LED_S_01.Set();
    LED_S_02.Set();
    LED_S_03.Set();
    LED_S_10.Set();
    LED_S_11.Set();
    LED_S_12.Set();
    LED_S_13.Set();
    LED_M_00.Set();
    LED_M_01.Set();
    LED_M_02.Set();
    LED_M_03.Set();
    LED_M_10.Set();
    LED_M_11.Set();
    LED_M_12.Set();
    LED_M_13.Set();
    LED_H_00.Set();
    LED_H_01.Set();
    LED_H_02.Set();
    LED_H_03.Set();
    LED_H_10.Set();
    LED_H_11.Set();
    LED_H_12.Set();
    LED_H_13.Set();

    while(1) {
        HAL_Delay(500);
        if(Button.IsSet()) {
            LED_S_00.Toggle();
            LED_S_01.Toggle();
            LED_S_02.Toggle();
            LED_S_03.Toggle();
            LED_S_10.Toggle();
            LED_S_11.Toggle();
            LED_S_12.Toggle();
            LED_S_13.Toggle();
            LED_M_00.Toggle();
            LED_M_01.Toggle();
            LED_M_02.Toggle();
            LED_M_03.Toggle();
            LED_M_10.Toggle();
            LED_M_11.Toggle();
            LED_M_12.Toggle();
            LED_M_13.Toggle();
            LED_H_00.Toggle();
            LED_H_01.Toggle();
            LED_H_02.Toggle();
            LED_H_03.Toggle();
            LED_H_10.Toggle();
            LED_H_11.Toggle();
            LED_H_12.Toggle();
            LED_H_13.Toggle();
        }
    }
}

