#include <iostream>
#include <handy/handy.h>
using namespace handy;
using namespace std;

int ProcessTimeOut(int type) {
    switch (type) {
        case 1: 
            cout << "hello" << endl;
            break;
        default:
            cout << "oooo" << endl;
    }
}

class Test{
public:
    Test(EventBase* base):mbase(base){}
    Test(){}
    ~Test(){}
    TimerId StartTimer(int ti, int type);
    void StopTimer(TimerId timeid);

    virtual void ProcessTimeOut(int type);

public:
    EventBase* mbase;
};

TimerId Test::StartTimer(int ti, int type) {
    return mbase->runAfter(ti, [=](){ProcessTimeOut(type);});
}

void  Test::StopTimer(TimerId timeid) {
    mbase->cancel(timeid);
}


void Test::ProcessTimeOut(int type) {
     switch (type) {
        case 1: 
            cout << "0000000000" << endl;
            break;
        default:
            cout << "oooo" << endl;
    }
}

class Child : public Test {
public:
    Child(EventBase* base):Test(base){}
    ~Child(){}

    virtual void ProcessTimeOut(int type);

};


void Child::ProcessTimeOut(int type) {
     switch (type) {
        case 1: 
            cout << "hgjhgjgjghj" << endl;
            break;
        default:
            cout << "oooo" << endl;
    }
}


void startTimer(EventBase& base, int type) {
      base.runAfter(60000, [=]() { ProcessTimeOut(type); });
}


int main(int argc, const char *argv[]) {
  
    EventBase base;
    Signal::signal(SIGINT, [&] { base.exit(); });
    
    //int a = 100;

    //startTimer(base, 1);
    //base.safeCall([=]{cout <<a << endl;});


    Child a(&base);
    TimerId tiid= a.StartTimer(1000, 1);
    a.StopTimer(tiid);


    base.loop();
}