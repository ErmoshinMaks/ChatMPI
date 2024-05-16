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
#define MESSAGE_SIZE 256

const int PORT = 52002;
const char* SERVER_IP = "127.0.0.1";
char FIO_from[MESSAGE_SIZE] = "C";
char FIO_to[MESSAGE_SIZE] = "A";

enum class mes_t {
   POST = 0, 
   REGS = 1,
   GETU = 2 
};

struct ClientDTO
{
   char from[MESSAGE_SIZE];
   char to[MESSAGE_SIZE];
   char message[MESSAGE_SIZE];
   mes_t type;
};

void receiveMessages(int sockfd) {
    char sendline[MESSAGE_SIZE];

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
        std::cout << "Received: " << data.message << std::endl;
    }
}

void sendMessages(int sockfd,sockaddr_in servaddr,sockaddr_in servaddr_to) {
    std::string message;

    ClientDTO data;

    while(true) {
        std::getline(std::cin, message);

        data.type = mes_t::POST;
        memcpy(data.from,FIO_from,MESSAGE_SIZE);
        memcpy(data.to,FIO_to,MESSAGE_SIZE);
        memcpy(data.message, message.c_str(), sizeof(message));
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