#include "cripto.h"


uint8_t*  Encoder::encrypt(std::string strp)
{
    uint8_t *p_crypt_data = ptr_xtea_lib.data_crypt((uint8_t*)strp.c_str(), key, strp.length() + 1);
    std::string res = (char*)p_crypt_data;
    return p_crypt_data;
}

std::string Encoder::decrypt(uint8_t* strp, int n)
{
    uint8_t *p_decrypt_data = ptr_xtea_lib.data_decrypt(strp, key, n);
	std::string res = (char*)p_decrypt_data;
    return res;
}
int Encoder::get_len()
{
    return ptr_xtea_lib.get_crypt_size();
}