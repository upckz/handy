#include "CTimer.h"

using namespace std;
namespace reactor {

TimerId CTimer::StartTimer(int ti, int type) {
    return mbase->runAfter(ti, [=](){ProcessTimeOut(type);});
}

void  CTimer::StopTimer(TimerId timeid) {
    mbase->cancel(timeid);
}


int CTimer::ProcessTimeOut(int type) {
    return 0;
}
}