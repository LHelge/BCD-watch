#include "BCDWatch.hpp"

BCDWatch::BCDWatch() :
    LedS00(GPIO::Port::B, 10),
    LedS01(GPIO::Port::B,  1),
    LedS02(GPIO::Port::A,  7),
    LedS03(GPIO::Port::A,  5),
    LedS10(GPIO::Port::B,  2),
    LedS11(GPIO::Port::B,  0),
    LedS12(GPIO::Port::A,  6),
    LedS13(GPIO::Port::A,  4),
    LedM00(GPIO::Port::A,  8),
    LedM01(GPIO::Port::B, 15),
    LedM02(GPIO::Port::H,  0),
    LedM03(GPIO::Port::H,  1),
    LedM10(GPIO::Port::B, 12),
    LedM11(GPIO::Port::B, 11),
    LedM12(GPIO::Port::A,  0),
    LedM13(GPIO::Port::A,  1),
    LedH00(GPIO::Port::A, 12),
    LedH01(GPIO::Port::A, 11),
    LedH02(GPIO::Port::B,  8),
    LedH03(GPIO::Port::B,  9),
    LedH10(GPIO::Port::B,  4),
    LedH11(GPIO::Port::B,  5),
    LedH12_DTx(GPIO::Port::B,  6),
    LedH13_DRx(GPIO::Port::B,  7),
    Wake(GPIO::Port::C, 13),
    PwmS0Pin(GPIO::Port::A,  2),
    PwmS1Pin(GPIO::Port::A,  3),
    PwmM0Pin(GPIO::Port::B, 13),
    PwmM1Pin(GPIO::Port::B, 14),
    PwmH0Pin(GPIO::Port::A, 15),
    PwmH1Pin(GPIO::Port::B,  3),
    I2cScl(GPIO::Port::A,  9),
    I2cSda(GPIO::Port::A, 10),
    Timer2(Timer::TimerHW::Tim2, 2),
    Timer21(Timer::TimerHW::Tim21, 2),
    PwmS0(&Timer2.PWMChannel3),
    PwmS1(&Timer2.PWMChannel4),
    PwmM0(&Timer21.PWMChannel1),
    PwmM1(&Timer21.PWMChannel2),
    PwmH0(&Timer2.PWMChannel1),
    PwmH1(&Timer2.PWMChannel2),
    ColS0(ColS0Pins, PwmS0),
    ColS1(ColS1Pins, PwmS1),
    ColM0(ColM0Pins, PwmM0),
    ColM1(ColM1Pins, PwmM1),
    ColH0(ColH0Pins, PwmH0),
    ColH1(ColH1Pins, PwmH1),
    I2c(I2C::Number::I2C_1),
    AccelI2c(&I2c, Accelerometer::LIS3DH::getAddress(true)),
    DbgSerial(UART::Number::UART1),
    Display(DispCols),
    Debug(&DbgSerial),
    Accelerometer(&AccelI2c, &Wake),
    Button(&Wake) {

    ColS0Pins[0] = &LedS00;
    ColS0Pins[1] = &LedS01;
    ColS0Pins[2] = &LedS02;
    ColS0Pins[3] = &LedS03;
    ColS1Pins[0] = &LedS10;
    ColS1Pins[1] = &LedS11;
    ColS1Pins[2] = &LedS12;
    ColS1Pins[3] = &LedS13;
    ColM0Pins[0] = &LedM00;
    ColM0Pins[1] = &LedM01;
    ColM0Pins[2] = &LedM02;
    ColM0Pins[3] = &LedM03;
    ColM1Pins[0] = &LedM10;
    ColM1Pins[1] = &LedM11;
    ColM1Pins[2] = &LedM12;
    ColM1Pins[3] = &LedM13;
    ColH0Pins[0] = &LedH00;
    ColH0Pins[1] = &LedH01;
    ColH0Pins[2] = &LedH02;
    ColH0Pins[3] = &LedH03;
    ColH1Pins[0] = &LedH10;
    ColH1Pins[1] = &LedH11;
    ColH1Pins[2] = &LedH12_DTx;
    ColH1Pins[3] = &LedH13_DRx;

    DispCols[0] = &ColS0;
    DispCols[1] = &ColS1;
    DispCols[2] = &ColM0;
    DispCols[3] = &ColM1;
    DispCols[4] = &ColH0;
    DispCols[5] = &ColH1;

    Brightness = 0xFF;
}

void BCDWatch::Init(const bool debug) {
    // Init all led pins as outputs
    LedS00.InitOutput();
    LedS01.InitOutput();
    LedS02.InitOutput();
    LedS03.InitOutput();
    LedS10.InitOutput();
    LedS11.InitOutput();
    LedS12.InitOutput();
    LedS13.InitOutput();
    LedM00.InitOutput();
    LedM01.InitOutput();
    LedM02.InitOutput();
    LedM03.InitOutput();
    LedM10.InitOutput();
    LedM11.InitOutput();
    LedM12.InitOutput();
    LedM13.InitOutput();
    LedH00.InitOutput();
    LedH01.InitOutput();
    LedH02.InitOutput();
    LedH03.InitOutput();
    LedH10.InitOutput();
    LedH11.InitOutput();
    if(debug) {
        LedH12_DTx.InitAlternate(0, GPIO::Type::PushPull, GPIO::Speed::VeryHigh);
        LedH13_DRx.InitAlternate(0, GPIO::Type::PushPull, GPIO::Speed::VeryHigh);
        DbgSerial.Init(115200);
    }
    else {
        LedH12_DTx.InitOutput();
        LedH13_DRx.InitOutput();
    }

    // Init wakeup as input
    Wake.InitInput();

    // Init PWM outputs as Alternate Open drain
    PwmS0Pin.InitAlternate(2, GPIO::Type::OpenDrain, GPIO::Speed::VeryHigh);
    PwmS1Pin.InitAlternate(2, GPIO::Type::OpenDrain, GPIO::Speed::VeryHigh);
    PwmM0Pin.InitAlternate(6, GPIO::Type::OpenDrain, GPIO::Speed::VeryHigh);
    PwmM1Pin.InitAlternate(6, GPIO::Type::OpenDrain, GPIO::Speed::VeryHigh);
    PwmH0Pin.InitAlternate(5, GPIO::Type::OpenDrain, GPIO::Speed::VeryHigh);
    PwmH1Pin.InitAlternate(2, GPIO::Type::OpenDrain, GPIO::Speed::VeryHigh);

    // Init all PWM channels with inverted polarity
    PwmS0->Init(Timer::Polarity::Low);
    PwmS1->Init(Timer::Polarity::Low);
    PwmM0->Init(Timer::Polarity::Low);
    PwmM1->Init(Timer::Polarity::Low);
    PwmH0->Init(Timer::Polarity::Low);
    PwmH1->Init(Timer::Polarity::Low);

    
    I2cScl.InitAlternate(6, GPIO::Type::OpenDrain, GPIO::Speed::VeryHigh);
    I2cSda.InitAlternate(6, GPIO::Type::OpenDrain, GPIO::Speed::VeryHigh);
    I2c.Init();
    Accelerometer.Init();

    // prescalers for 32,768 Hz HSE
    Rtc.Init(127,255);
    if(Rtc.IsSet() == false) {
        RealTimeClock::Date date(19, 12, 24);
        RealTimeClock::Time time(13, 0, 0);

        Rtc.SetDate(date);
        Rtc.SetTime(time);
    }
}

