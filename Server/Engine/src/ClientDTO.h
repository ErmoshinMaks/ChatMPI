#ifndef CLIENTDTO_H
#define CLIENTDTO_H
#include <arpa/inet.h>


struct ClientDTO
{
   char from[256];
   char to[256];
   char message[256];
};

#endif // CLIENTDTO_H
