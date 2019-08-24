#include <handy/handy.h>
#include <map>
#include "CCSocketHandler.h"
#include "dh64.h"
using namespace std;
using namespace handy;
using namespace reactor;

typedef std::shared_ptr<CCSocketHandler> SocketHandlerConnPtr;

int main(int argc, const char *argv[]) {
    setloglevel("TRACE");
    EventBase base;
    Signal::signal(SIGINT, [&] { base.exit(); });

    TcpServerPtr chat = TcpServer::startServer(&base, "192.168.56.102", 2099);
    exitif(chat == NULL, "start tcpserver failed");
    chat->onConnCreate([&] {
        SocketHandlerConnPtr con(new CCSocketHandler(&base, false));
        con->onState([&](const TcpConnPtr &con) {
                if (con->getState() == CCSocketHandler::Connected) {
                    con->OnConnect();
                } else if (con->getState() == CCSocketHandler::Closed) {
                    con->OnClose();
                }
            });
        con->onMsg(new LengthCodec, [&](const TcpConnPtr &con, Slice msg) {
            if (msg.size() == 0) {  //忽略空消息
                return;
            }
            con->DoRecv((char *) msg.data(), (int)msg.size());
                
        });
        return con;
    });
    base.loop();
    info("program exited");
    return 0;
}