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


#pragma once

class Server
{
public:
    int port = 52002;
    int sockfd;
    int newsockfd;
    struct sockaddr_in servaddr;
    void createSocket();
    bool listenMessage();
    char* getMessage();
};
#endif
