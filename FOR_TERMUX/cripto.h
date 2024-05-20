#ifndef CRIPTO_H
#define CRIPTO_H

#include "lib/xtea3.h"
#include <string>

class Encoder
{
public:
    uint8_t* encrypt(std::string str);
    std::string decrypt(uint8_t* strp, int n);
    int get_len();
    
private:
    xtea3 ptr_xtea_lib;
    uint32_t key[8] = {0x11, 0x55, 0xAA, 0x88, 0x12, 0x55, 0x77, 0x12};

};

#endif
