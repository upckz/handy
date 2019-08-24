
#ifndef _CCSOcketHandler_H_
#define _CCSOcketHandler_H_


#include <handy/handy.h>
#include "CTimer.h"
#include  <handy/event_base.h>
using namespace handy;

#define HEART_TYPE_OUT 1



namespace reactor {

class CCSocketHandler: public TcpConn, public CTimer{

public:
    CCSocketHandler(EventBase* base, bool isSecert = false):secert_(isSecert){mbase = base;};
    CCSocketHandler(){}
    virtual ~CCSocketHandler(){};

    virtual void OnClose();
    virtual void OnConnect();

    virtual int OnPacketComplete(const char* data, int len);
    virtual int ProcessTimeOut(int type);

    void StartHeartTimer();
    void StopHeartTimer();

    int DoRecv(const char* data, int len);

public:
    bool isconnect_ = false;
    bool hasRecvFlag_ = false;
    bool secert_ = false;
    char secertKey_[32];

    int heartTime_ = 5;
    TimerId HeartTimerId;

    uint64_t privateKey_;
    uint64_t publicKey_;

};
}
#endif