#include "engine.h"
#include <QDebug>


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

char* Server::getMessage()
{
    struct sockaddr_in cliaddr;
    int n;
    char line[1000];
    socklen_t clilen = sizeof(cliaddr);

    if( (newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) < 0){
       printf("Can\'t accept connection, errno = %d\n", errno);
       close(sockfd);
    }

    qDebug() << "Connection with: " << inet_ntoa(cliaddr.sin_addr);

    bzero(line,1000);
    while( (n = read(newsockfd, line, 1000)) > 0){
        qDebug() << line;
    }

    return line;
}
