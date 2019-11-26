#include "BCDw.hpp"
#include "gpio.hpp"
#include "timer.hpp"
#include "stm32l0xx_hal.h"
#include "main.h"
#include "uart.hpp"
#include "i2c.hpp"
#include "Debug.hpp"
#include "lis3dh.hpp"
#include "rtc.hpp"
#include "display.hpp"

class BCDw {
    public:
        void Run(void);
        void Tick(void);
    private:
        RealTimeClock::Clock m_clock;
};

static BCDw watch;


void bcdw_run(void) {
    
    watch.Run();
}

void bcdw_tick(void) {
    watch.Tick();
}

void BCDw::Run(void) {
    Debug::Debug *debug;

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
    #ifdef DEBUG
    GPIO::Dummy LED_H_12(GPIO::RESET);
    GPIO::Dummy LED_H_13(GPIO::RESET);
    #else
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

    Timer::BaseTimer Timer2(Timer::TIMER2, 2);
    Timer::BaseTimer Timer21(Timer::TIMER21, 2);
    Timer::PWM PWM_S0(&Timer2, Timer::CHANNEL_3, &LED_S_0_Dim);
    Timer::PWM PWM_S1(&Timer2, Timer::CHANNEL_4, &LED_S_1_Dim);
    Timer::PWM PWM_M0(&Timer21, Timer::CHANNEL_1, &LED_M_0_Dim);
    Timer::PWM PWM_M1(&Timer21, Timer::CHANNEL_2, &LED_M_1_Dim);
    Timer::PWM PWM_H0(&Timer2, Timer::CHANNEL_1, &LED_H_0_Dim);
    Timer::PWM PWM_H1(&Timer2, Timer::CHANNEL_2, &LED_H_1_Dim);

    GPIO::Pin* LED_S0[] = {&LED_S_00, &LED_S_01, &LED_S_02, &LED_S_03};
    GPIO::Pin* LED_S1[] = {&LED_S_10, &LED_S_11, &LED_S_12, &LED_S_13};
    GPIO::Pin* LED_M0[] = {&LED_M_00, &LED_M_01, &LED_M_02, &LED_M_03};
    GPIO::Pin* LED_M1[] = {&LED_M_10, &LED_M_11, &LED_M_12, &LED_M_13};
    GPIO::Pin* LED_H0[] = {&LED_H_00, &LED_H_01, &LED_H_02, &LED_H_03};
    GPIO::Pin* LED_H1[] = {&LED_H_10, &LED_H_11, &LED_H_12, &LED_H_13};
    Display::LedDisplayColumn S0(Display::S0, LED_S0, &PWM_S0);
    Display::LedDisplayColumn S1(Display::S1, LED_S1, &PWM_S1);
    Display::LedDisplayColumn M0(Display::M0, LED_M0, &PWM_M0);
    Display::LedDisplayColumn M1(Display::M1, LED_M1, &PWM_M1);
    Display::LedDisplayColumn H0(Display::H0, LED_H0, &PWM_H0);
    Display::LedDisplayColumn H1(Display::H1, LED_H1, &PWM_H1);
    Display::LedDisplayColumn* Cols[] = {&S0, &S1, &M0, &M1, &H0, &H1};
    Display::LedDisplay Display(Cols);
    
    #ifdef DEBUG
    GPIO::Alternate DebugTx(GPIO::B, 6, true, 0);
    GPIO::Alternate DebugRx(GPIO::B, 7, true, 0);
    UART::SerialPort DebugUart(UART::UART1, 115200, &DebugTx, &DebugRx);
    Debug::SerialDebug SerialDebug(&DebugUart);
    debug = &SerialDebug;
    #else
    Debug::Debug DummyDebug;
    debug = &DummyDebug;
    #endif

    GPIO::Alternate I2C1SCL(GPIO::A, 9, false, 6);
    GPIO::Alternate I2C1SDA(GPIO::A, 10, false, 6);
    I2C::I2CDevice AccI2C(I2C::I2C_1, Accelerometer::LIS3DH::getAddress(true), &I2C1SCL, &I2C1SDA);
    Accelerometer::LIS3DH Accelerometer(&AccI2C);
    Accelerometer.Init();
    
    if(Accelerometer.getState() == Accelerometer.Error) {
        debug->WriteLine("Error: Accelerometer initialization error!");
    }


    Accelerometer::AccelerationVector AccVector;
    RealTimeClock::Time Time;
    RealTimeClock::Date Date;

    uint32_t counter = 0;
    while(1) {
        if(counter++ == 50) {
            counter = 0;

            this->m_clock.GetTime(Time);
            this->m_clock.GetDate(Date);
            
            if(Button) {
                
                debug->Write(Date);
                debug->Write(" ");
                debug->Write(Time);
                debug->NewLine();
            }

            Accelerometer.getAcceleration(AccVector);

            debug->Write("Acc x=");
            debug->Write(AccVector.X);
            debug->Write(", Y=");
            debug->Write(AccVector.Y);
            debug->Write(", Z=");
            debug->Write(AccVector.Z);
            debug->NewLine();

            Display.Set(Time);
        }

        if(counter <= 5) Display.Dim(Display::ALL, 50 * counter);
        else if( counter >= 45) Display.Dim(Display::ALL, 50 * (50 - counter));

        HAL_Delay(20);
    }
}

void BCDw::Tick() {
    this->m_clock.Tick();
}
