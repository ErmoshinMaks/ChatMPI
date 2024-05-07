#include "engine.h"
#include <QDebug>
#define MESSAGE_SIZE 256
void handleClient(int newsockfd,Server* server)
{
    int n;

    while(true)
    {
        ClientDTO data;
        char buffer[sizeof(ClientDTO)];

        n = read(newsockfd, buffer, MESSAGE_SIZE);
        if(n <= 0)
            break;

        memcpy(&data, buffer, sizeof(data));
        qDebug() <<"Принял сообщение: " << data.message ;

        int toFd = newsockfd;
        in_addr toIp;
        for(int i = 0; i < server->sockets.size();i++)
        {
            if(server->sockets[i].first.s_addr == data.to.s_addr)
            {
                toFd = server->sockets[i].second;
                toIp = server->sockets[i].first;
                break;
            }
        }
        //qDebug() <<"Отправил сообщение: "<< toIp;
        if( (write(toFd,buffer, sizeof(buffer))) < 0){
                  printf("Can\'t write, errno = %d\n", errno);
                  close(newsockfd);
               }

    }

}



void Server::createSocket()
{
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
         printf("Can\'t create socket, errno = %d\n", errno);
      }
}


bool Server::listenMessage()
{
    bzero(&servaddr, sizeof(servaddr));
       servaddr.sin_family      = AF_INET;
       servaddr.sin_port        = htons(port);
       servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
       printf("Can\'t bind socket, errno = %d\n", errno);
       close(sockfd);
    }

    qDebug() << "My ip: " << inet_ntoa(servaddr.sin_addr);

    if(listen(sockfd, 5) < 0){
       printf("Can\'t change state of socket to listen state, errno = %d\n", errno);
       close(sockfd);
       return false;
    }

    return true;
}

int Server::getMessage()
{
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    while(true)
    {
        if( (newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) < 0){
            printf("Can\'t accept connection, errno = %d\n", errno);
            close(sockfd);
        }

        qDebug() << "Connection with: " << inet_ntoa(cliaddr.sin_addr);

        sockets.push_back(qMakePair(cliaddr.sin_addr,newsockfd));

        std::thread(handleClient, newsockfd,this).detach();
    }

    return newsockfd;
}

void Server::joinThreads()
{
    for(int i = 0; i < clientThreads.size();i++)
            clientThreads[i].join();

}

void Server::start()
{
    int newsockfd;
    createSocket();
    listenMessage();


    newsockfd = getMessage();


    joinThreads();

}


