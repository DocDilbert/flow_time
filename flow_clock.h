#ifndef FLOW_CLOCK_H
#define FLOW_CLOCK_H

#include <QLCDNumber>

class FlowClock : public QLCDNumber {
  Q_OBJECT

 public:
  FlowClock(QWidget *parent = nullptr);
};

#endif