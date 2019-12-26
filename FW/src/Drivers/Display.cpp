#include "Display.hpp"

namespace Display
{
    static const uint16_t LogTable[256] = {
             0,    62,   124,   188,   251,   315,   380,   446,   512,   579,   646,   714,   783,   852,   922,   993, 
          1064,  1136,  1209,  1282,  1356,  1431,  1506,  1582,  1659,  1737,  1815,  1894,  1974,  2055,  2136,  2218, 
          2301,  2385,  2469,  2554,  2640,  2727,  2815,  2903,  2993,  3083,  3174,  3266,  3359,  3452,  3547,  3642, 
          3739,  3836,  3934,  4033,  4133,  4234,  4336,  4439,  4543,  4647,  4753,  4860,  4968,  5077,  5187,  5298, 
          5410,  5523,  5637,  5752,  5868,  5985,  6104,  6224,  6344,  6466,  6589,  6713,  6839,  6965,  7093,  7222, 
          7352,  7483,  7616,  7750,  7885,  8021,  8159,  8298,  8438,  8580,  8723,  8867,  9013,  9160,  9309,  9458, 
          9610,  9762,  9917, 10072, 10229, 10388, 10548, 10709, 10873, 11037, 11203, 11371, 11540, 11711, 11884, 12058, 
         12234, 12412, 12591, 12772, 12954, 13138, 13324, 13512, 13702, 13893, 14086, 14281, 14478, 14677, 14878, 15080, 
         15284, 15491, 15699, 15909, 16121, 16336, 16552, 16770, 16991, 17213, 17438, 17664, 17893, 18124, 18357, 18593, 
         18830, 19070, 19312, 19556, 19803, 20052, 20303, 20557, 20813, 21072, 21333, 21596, 21862, 22131, 22402, 22675, 
         22952, 23230, 23512, 23796, 24082, 24372, 24664, 24959, 25257, 25557, 25861, 26167, 26476, 26788, 27103, 27421, 
         27742, 28066, 28393, 28723, 29057, 29393, 29733, 30076, 30422, 30771, 31124, 31480, 31839, 32202, 32568, 32937, 
         33310, 33687, 34067, 34451, 34838, 35230, 35624, 36023, 36425, 36831, 37241, 37655, 38072, 38494, 38920, 39349, 
         39783, 40221, 40663, 41109, 41559, 42014, 42472, 42936, 43403, 43875, 44352, 44833, 45318, 45808, 46303, 46802, 
         47306, 47815, 48329, 48847, 49371, 49899, 50433, 50971, 51514, 52063, 52617, 53176, 53740, 54310, 54885, 55465, 
         56051, 56643, 57240, 57843, 58451, 59065, 59685, 60311, 60943, 61580, 62224, 62874, 63530, 64192, 64860, 65535
    };

    LedDisplayColumn::LedDisplayColumn(GPIO::Pin* leds[], Timer::PWMChannel *pwm) {
        this->m_leds = leds;
        this->m_pwm = pwm;
    }

    void LedDisplayColumn::SetValue(uint8_t bcd) {
        if(bcd >= 10) {
            // TODO: Assert
        }

        for(uint32_t i = 0; i < 4; i++) {
            if(bcd & (1 << i)) {
                this->m_leds[i]->Set();
            }
            else {
                this->m_leds[i]->Reset();
            }
        }
    }

    void LedDisplayColumn::SetDutycycle(uint8_t dutycycle) {
        // Make this logarithmic to better model led behavior
        this->m_pwm->SetDutyCycle(LogTable[dutycycle]);
    }


    LedDisplay::LedDisplay(LedDisplayColumn **cols) {
        // Check that column array is correctly initialized
        for(uint32_t i = 0; i < NUMBER_OF_COLUMNS; i++) {
            if(cols[i]->m_col != i) {
                // Todo: Assert
            }
        }

        this->m_cols = cols;
    }

    void LedDisplay::Set(const RealTimeClock::Time time) {
        this->m_cols[S0]->SetValue(time.S % 10);
        this->m_cols[S1]->SetValue(time.S / 10);
        this->m_cols[M0]->SetValue(time.M % 10);
        this->m_cols[M1]->SetValue(time.M / 10);
        this->m_cols[H0]->SetValue(time.H % 10);
        this->m_cols[H1]->SetValue(time.H / 10);
    }


    void LedDisplay::Set(const RealTimeClock::Date date) {
        // TODO
    }


    void LedDisplay::Dim(Column col, uint8_t dutycycle) {
        if(col >= NUMBER_OF_COLUMNS) {
            for(uint32_t i = 0; i < NUMBER_OF_COLUMNS; i++) {
                this->m_cols[i]->SetDutycycle(dutycycle);
            }
        }
        else {
            this->m_cols[col]->SetDutycycle(dutycycle);
        }
    }
    
} // namespace Display
