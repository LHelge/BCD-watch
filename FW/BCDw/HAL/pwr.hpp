#ifndef _PWR_HPP
#define _PWR_HPP

namespace Power {
    class PowerControl {
    public:
        PowerControl();

        bool WokeFromStandby() const;
        void Standby();
    private:
        bool m_wokeFromStandby;
    };
}

#endif