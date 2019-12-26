#ifndef _BCDWATCH_HPP
#define _BCDWATCH_HPP

#include "GPIO.hpp"
#include "Timer.hpp"
#include "Display.hpp"
#include "I2C.hpp"
#include "LIS3DH.hpp"
#include "UART.hpp"
#include "Debug.hpp"
#include "RTC.hpp"
#include "Button.hpp"

class BCDWatch {
public:
    BCDWatch();

    void Init();
private:
    GPIO::Pin LedS00;
    GPIO::Pin LedS01;
    GPIO::Pin LedS02;
    GPIO::Pin LedS03;
    GPIO::Pin LedS10;
    GPIO::Pin LedS11;
    GPIO::Pin LedS12;
    GPIO::Pin LedS13;
    GPIO::Pin LedM00;
    GPIO::Pin LedM01;
    GPIO::Pin LedM02;
    GPIO::Pin LedM03;
    GPIO::Pin LedM10;
    GPIO::Pin LedM11;
    GPIO::Pin LedM12;
    GPIO::Pin LedM13;
    GPIO::Pin LedH00;
    GPIO::Pin LedH01;
    GPIO::Pin LedH02;
    GPIO::Pin LedH03;
    GPIO::Pin LedH10;
    GPIO::Pin LedH11;
    GPIO::Pin LedH12_DTx;
    GPIO::Pin LedH13_DRx;
public:
    GPIO::Pin Wake;
private:
    GPIO::Pin PwmS0Pin;
    GPIO::Pin PwmS1Pin;
    GPIO::Pin PwmM0Pin;
    GPIO::Pin PwmM1Pin;
    GPIO::Pin PwmH0Pin;
    GPIO::Pin PwmH1Pin;

    // I2C
    GPIO::Pin I2cScl;
    GPIO::Pin I2cSda;

    Timer::Timer Timer2;
    Timer::Timer Timer21;
    GPIO::Pin *ColS0Pins[4];
    GPIO::Pin *ColS1Pins[4];
    GPIO::Pin *ColM0Pins[4];
    GPIO::Pin *ColM1Pins[4];
    GPIO::Pin *ColH0Pins[4];
    GPIO::Pin *ColH1Pins[4];

    Timer::PWMChannel *PwmS0;
    Timer::PWMChannel *PwmS1;
    Timer::PWMChannel *PwmM0;
    Timer::PWMChannel *PwmM1;
    Timer::PWMChannel *PwmH0;
    Timer::PWMChannel *PwmH1;

    Display::LedDisplayColumn ColS0;
    Display::LedDisplayColumn ColS1;
    Display::LedDisplayColumn ColM0;
    Display::LedDisplayColumn ColM1;
    Display::LedDisplayColumn ColH0;
    Display::LedDisplayColumn ColH1;
    Display::LedDisplayColumn *DispCols[6];

    I2C::I2C I2c;
    I2C::I2CDevice AccelI2c;

    UART::SerialPort DbgSerial;
public:
    Display::LedDisplay Display;
    Debug::Debug Debug;
    Accelerometer::LIS3DH Accelerometer;
    RealTimeClock::RealTimeClock Rtc;
    Button::PushButton Button;
    uint8_t Brightness;
};


#endif