#ifndef CLIENTDTO_H
#define CLIENTDTO_H

#include <arpa/inet.h>

#define MESSAGE_SIZE 256

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

#endif // CLIENTDTO_H
