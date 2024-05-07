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
#include "ClientDTO.h"
#include "../../database/src/databasecontroller.h"


#pragma once

class Server
{
public:
    int sockfd;//no
    int newsockfd;//no
    struct sockaddr_in servaddr;
    std::vector<std::thread> clientThreads;
    std::vector<QPair<in_addr,int>> sockets;
    DatabaseController db;
    void createSocket();
    bool listenMessage();
    int getMessage();
    void joinThreads();
    void start();
    void reg(QString FIO,QString ip);
private:
    const int port = 52002;
};
#endif
