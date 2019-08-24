#include <handy/handy.h>
#include "CCSocketHandler.h"
#include "CTimer.h"
#include "dh64.h"
using namespace handy;
using namespace reactor;
using namespace std;
namespace reactor {


void CCSocketHandler::OnConnect() {
     trace("connected %s fd %d", peer_.toString().c_str(), channel_->fd());
    StartHeartTimer();
}

void CCSocketHandler::OnClose() {
    trace("OnClose %s  fd %d", peer_.toString().c_str(), channel_->fd());

}


int CCSocketHandler::ProcessTimeOut(int type) {
    switch(type) {
        case HEART_TYPE_OUT:
            info("fd[%d] %s heartTimeout", channel_->fd(), peer_.toString().c_str());
            close();
            break;
        default:
            break;
    }

    return 0;
}

void  CCSocketHandler::StartHeartTimer(){
    if (base_ != nullptr) {
        HeartTimerId = this->StartTimer(heartTime_*1000, HEART_TYPE_OUT);
    }
}

void  CCSocketHandler::StopHeartTimer(){
    if (base_ != nullptr) {
        this->StopTimer(HeartTimerId);
    }
}



int CCSocketHandler::OnPacketComplete(const char* data, int len) {
   
    
    return 0;
}

int CCSocketHandler::DoRecv(const char* data, int len) {
    if (!hasRecvFlag_ && secert_) {
        int ack = net::ntoh(*(int32_t *) (data + 4));
        if (ack == 1) {
            KeyPair(privateKey_, publicKey_);
            string resp = util::format("%ld",publicKey_);
            sendMsg(resp);
        } else if (ack == 3) {
            uint64_t clientPublicKey = net::ntoh(*(uint64_t *) (data + 4));
            Secret(secertKey_, privateKey_, clientPublicKey);
            hasRecvFlag_ = true;

        } else {
            trace("tcp %s ack error", peer_.toString().c_str());
            close();
        }
    } else {
        int ret =  OnPacketComplete(data, len);
        if (ret != 0) {
            close();
        }
    }

    return 0;
}

}