#include "BCDw.h"

class BCDw {
    public:
        void run(void);
};



void bcdw_run(void) {
    static BCDw watch;    
    watch.run();
}

void BCDw::run(void) {
    while(1) {
        // TODO: Do something
    }
}

