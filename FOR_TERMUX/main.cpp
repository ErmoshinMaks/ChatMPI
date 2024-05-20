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

#include "cripto.h"

#define MESSAGE_SIZE 256

const int PORT = 52002;
const char* SERVER_IP = "192.168.177.89";
char FIO_from[MESSAGE_SIZE] = "termux";
char FIO_to[MESSAGE_SIZE] = "Step";

enum class mes_t 
{
   POST = 0, 
   REGS = 1,
   GETU = 2 
};

struct Mes
{
   char data[MESSAGE_SIZE];
   int len;
   mes_t type;
};

struct ClientDTO
{
   char from[MESSAGE_SIZE];
   char to[MESSAGE_SIZE];
   Mes mes;
};

void receiveMessages(int sockfd) {
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
        std::cout << "Received from '" << data.from << "' : " << data.mes.data << std::endl;
    }
}

void sendMessages(int sockfd,sockaddr_in servaddr,sockaddr_in servaddr_to) {
    std::string msg;
    ClientDTO data;
    Encoder enc;

    while(true) {
        std::getline(std::cin, msg);

        uint8_t* secret_mes = enc.encrypt(msg);
        memcpy(data.mes.data, secret_mes, enc.get_len());
        data.mes.len = enc.get_len();

        data.mes.type = mes_t::POST;
        memcpy(data.from,FIO_from,MESSAGE_SIZE);
        memcpy(data.to,FIO_to,MESSAGE_SIZE);
        
        char buffer[sizeof(data)];
        memcpy(buffer, &data, sizeof(data));

        int n = write(sockfd, buffer, sizeof(buffer));
        if(n < 0) {
            std::cerr << "Error writing to socket" << std::endl;
            break;
        }
    }
}

int main() {
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

    std::thread receiver(receiveMessages, sockfd);
    std::thread sender(sendMessages, sockfd,servaddr,servaddr_to);

    receiver.join();
    sender.join();

    close(sockfd);

    return 0;
}