#ifndef ENGINE_H
#define ENGINE_H

#include <QDebug>
#include <vector>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include "ClientDTO.h"



#pragma once

class Server
{
public:
    int port = 52002;
    int sockfd;
    int newsockfd;
    struct sockaddr_in servaddr;
    std::vector<std::thread> clientThreads;
    void createSocket();
    bool listenMessage();
    int getMessage();
    void joinThreads();
    void start();
//private:
//    void handleClient(int newsockfd,int treadInd);
};
#endif
