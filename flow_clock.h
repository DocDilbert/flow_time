#ifndef FLOW_CLOCK_H
#define FLOW_CLOCK_H

#include <qlcdnumber.h>

class FlowClock : public QLCDNumber
{
    Q_OBJECT
public:
    FlowClock(QWidget *parent = nullptr);
};

#endif