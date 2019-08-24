
#ifndef _CTimer_H_
#define _CTimer_H_

#include <handy/handy.h>
#include  <handy/event_base.h>
using namespace handy;

namespace reactor {
class CTimer{
public:
    CTimer(EventBase* base):mbase(base){}
    CTimer(){}
    ~CTimer(){}
    TimerId StartTimer(int ti, int type);
    void StopTimer(TimerId timeid);

    virtual int ProcessTimeOut(int type);

public:
    EventBase* mbase;
};

}
#endif