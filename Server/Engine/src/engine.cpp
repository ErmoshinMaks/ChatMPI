#include "engine.h"
#include <QDebug>
#define MESSAGE_SIZE 256
void handleClient(int newsockfd)
{
    char line[MESSAGE_SIZE];
    int n;

    while(true)
    {
        bzero(line,MESSAGE_SIZE);
        n = read(newsockfd, line, MESSAGE_SIZE);
        if(n <= 0)
            break;

        qDebug() << line;

        ClientDTO data;
        data.from = 1;
        data.to = 0;
        memcpy(data.message, line, sizeof(line));

        char buffer[sizeof(ClientDTO)];
        memcpy(buffer, &data, sizeof(ClientDTO));
        qDebug() <<"Message: " << buffer;

        if( (write(newsockfd,buffer, sizeof(buffer))) < 0){
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


        std::thread(handleClient, newsockfd).detach();
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


