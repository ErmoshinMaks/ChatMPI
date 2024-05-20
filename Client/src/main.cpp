#include <QtCore>
#include <QApplication>
#include <QInputDialog>

#include "threadsqueue.hpp"
#include "mainwindow.h"
#include "cripto.h"

#include <iostream>
#include <thread>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

const int PORT = 52002;
const char* SERVER_IP = "192.168.177.117";
char FIO_from[MESSAGE_SIZE] = "A";
char FIO_to[MESSAGE_SIZE] = "C";



void receiveMessages(int sockfd, ThreadSafeQueue<ClientDTO>* queue) {
    
    char sendline[MESSAGE_SIZE];
    Encoder enc;

    while(true) {
        memset(sendline, 0, sizeof(sendline));
        ClientDTO data;
        char buffer[sizeof(ClientDTO)];

        int n = read(sockfd, buffer, sizeof(ClientDTO));
        if(n < 0) {
            std::cerr << "Error reading from socket" << std::endl;
            break;
        }
        if(n == 0) {
            std::cout << "Server disconnected" << std::endl;
            break;
        }
        memcpy(&data, buffer, sizeof(data));

        if(data.mes.type == mes_t::POST){
            uint8_t* g = (uint8_t*)(&data.mes.data);   
            std::string res = enc.decrypt(g, data.mes.len).c_str();
            memcpy(data.mes.data, res.c_str(), MESSAGE_SIZE);
        }

        queue->push(data);
        std::cout << "Received: " << data.mes.data << std::endl;
    }
}

void sendMessages(int sockfd,sockaddr_in servaddr,sockaddr_in servaddr_to, ThreadSafeQueue<ClientDTO>* queue) {
    ClientDTO data;
    Encoder enc;
    while(true) {
        if (queue->empty())
            continue;
        if (queue->try_pop(data)){
            // ENCRYPTION
            std::string mes = data.mes.data;
            uint8_t* secret_mes = enc.encrypt(mes);
            memcpy(data.mes.data, secret_mes, enc.get_len());
            data.mes.len = enc.get_len();
            // memcpy(data.mes.len, enc.get_len(), sizeof(int));

            // SENDING
            char buffer[sizeof(data)];
            memcpy(buffer, &data, sizeof(data));

            int n = write(sockfd, buffer, sizeof(buffer));
            if(n < 0) {
                std::cerr << "Error writing to socket" << std::endl;
                break;
            }
        }
    }
}

int drawMessages(int argc, char *argv[], ThreadSafeQueue<ClientDTO>* q_send, ThreadSafeQueue<ClientDTO>* q_rcv)
{
    QApplication a(argc, argv);
    bool ok = 0;
    ClientDTO data;
    while(!ok){
        QString text = QInputDialog::getText(nullptr, "Авторизация", "Введите имя:", QLineEdit::Normal, QString(), &ok,Qt::WindowFlags() ,Qt::ImhNone);
        if (ok && !text.isEmpty()){
            qDebug() << "Введенный логин: " << text;
            memcpy(data.from, text.toStdString().c_str(), sizeof(text.toStdString().c_str()));
            memcpy(data.mes.data, REGISTR_MES, sizeof(REGISTR_MES));
            data.mes.type = mes_t::REGS;
            q_send->push(data);
            data.mes.type = mes_t::GETU;
            q_send->push(data);
        }
    }

    MainWindow w;
    // w.connect_waiter(&bell);
    w.get_queues(q_send, q_rcv);
    w.login(data.from);
    w.show();
 
    return a.exec();
}


int main(int argc, char *argv[])
{
    ThreadSafeQueue<ClientDTO> queue_send;
    ThreadSafeQueue<ClientDTO> queue_rcv;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        std::cerr << "Error opening socket" << std::endl;
        return 1;
    }

    struct sockaddr_in servaddr;
    struct sockaddr_in servaddr_to;//test

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr);

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    std::thread receiver(receiveMessages, sockfd, &queue_rcv);
    std::thread sender(sendMessages, sockfd,servaddr,servaddr_to, &queue_send);
    std::thread gui(drawMessages, argc, argv, &queue_send, &queue_rcv);

    receiver.join();
    sender.join();
    gui.join();
    
    close(sockfd);


    
    // ClientDTO data;
    // memcpy(data.message, "1sfhjhjdcbhjdsbhj!!!!!!", MESSAGE_SIZE);
    // std::string a = data.message;
    
    // uint8_t* k = enc.encrypt(a);
    // memcpy(data.message, k, enc.get_len());

    // uint8_t* g = (uint8_t*)(&data.message);   
    // qDebug() << enc.decrypt(g, 40).c_str();
    return 0;
}