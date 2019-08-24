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

void startTimer(EventBase& base, int type) {
      base.runAfter(600, [=]() { ProcessTimeOut(type); });
}

int main(int argc, const char *argv[]) {
  
    EventBase base;
    Signal::signal(SIGINT, [&] { base.exit(); });
    


    startTimer(base, 1);
    base.safeCall([](){cout <<"1111111" << endl;})
  
    base.loop();
    return 0;
}