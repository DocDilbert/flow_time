#include "flow_clock.h"

   FlowClock::FlowClock(QWidget *parent ) : QLCDNumber(parent) {
        display("17:00");
    }