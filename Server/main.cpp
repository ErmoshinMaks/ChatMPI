
#include "engine.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    Server server = Server();
    server.createSocket();
    server.listenMessage();

    while(1)
    {
        server.getMessage();
    }


    return 0;
}
