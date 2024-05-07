#ifndef CLIENTDTO_H
#define CLIENTDTO_H
#include <arpa/inet.h>


struct ClientDTO
{
   in_addr from;
   in_addr to;
   char message[256];
};

#endif // CLIENTDTO_H
