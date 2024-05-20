#include "engine.h"
#include <QDebug>

#define REGISTR_MES "registration"


void handleClient(int newsockfd, Server* server, in_addr cli_ip)
{
    int n;
    while(true)
    {
        ClientDTO data;
        // in_addr sender = 
        char buffer[sizeof(ClientDTO)];

        n = read(newsockfd, buffer, sizeof(ClientDTO));
        if(n <= 0)
            break;

        memcpy(&data, buffer, sizeof(ClientDTO));
        qDebug() <<"Принял сообщение: " << data.mes.data << " от: " << data.from;

        
        if (data.mes.type == mes_t::REGS){
            server->reg(QString(data.from), inet_ntoa(cli_ip));
            server->broadcast();
            continue;
        }
        else if(data.mes.type == mes_t::GETU){
            server->broadcast();
            // server->db.connection();
            // QVector<Client> r = server->db.selectAll();
            // server->db.closing();
            // QString res;
            // for(int i = 0; i < r.size(); ++i)
            //     res+= r[i].FIO+ ";";
            // memcpy(data.mes.data, res.toStdString().c_str(), MESSAGE_SIZE);
            // memcpy(buffer, &data, sizeof(data));
            // if(write(newsockfd, buffer, sizeof(buffer)) < 0){
            //     printf("---->Can\'t write, errno = %d\n", errno);
            //     close(newsockfd);
            // }            
            continue;
        }

        int toFd = newsockfd;
        in_addr toIp;

        server->db.connection();
        Client client = server->db.selectByFIO(data.to);
        server->db.closing();

        inet_pton(AF_INET, client.ip.toStdString().c_str(), &toIp);

        for(int i = 0; i < server->sockets.size();i++)
        {
            if(server->sockets[i].first.s_addr == toIp.s_addr)
            {
                toFd = server->sockets[i].second;
                toIp = server->sockets[i].first;
                break;
            }
        }
        if( (write(toFd, buffer, sizeof(buffer))) < 0){
            printf("Can\'t write, errno = %d\n", errno);
            close(newsockfd);
        }
    }

}


void Server::broadcast()
{
    ClientDTO data;
    data.mes.type = mes_t::GETU;
    char buffer[sizeof(ClientDTO)];
    db.connection();
    QVector<Client> r = db.selectAll();
    db.closing();
    QString res;
    for(int i = 0; i < r.size(); ++i)
        res+= r[i].FIO+ ";";
    
    for(int i = 0; i < sockets.size(); ++i){
        memcpy(data.mes.data, res.toStdString().c_str(), MESSAGE_SIZE);
        memcpy(buffer, &data, sizeof(data));
        if(write(sockets[i].second, buffer, sizeof(buffer)) < 0){
            printf("Can\'t write, errno = %d\n", errno);
            close(sockets[i].second);
        }   
    }         
}

void Server::createSocket()
{
    if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
    // if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
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

        std::thread(handleClient, newsockfd,this, cliaddr.sin_addr).detach();
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

void Server::reg(QString FIO,QString ip)
{
    db.connection();
    db.insert(FIO,ip);
    db.closing();
}



