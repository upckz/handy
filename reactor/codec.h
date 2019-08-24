
#ifndef _CODEC_H_
#define _CODEC_H_

#include "xxtea-lib.h"
#include <string>
namespace reactor {

#define MAX_xxtea_len 1021*1024 

bool EnBinaryPackage(char* buf,  char* opensslEncrypted) {

    if(xxtea_setup(opensslEncrypted, strlen((char *)opensslEncrypted)) != XXTEA_STATUS_SUCCESS)
    {
        error("EnBinaryPackage Assignment Failed!");
        return nullptr;
    }
    uint8_t buffer[MAX_xxtea_len];
    int len = MAX_xxtea_len;  // - Initialize the Maximum buffer length
    if(xxtea_encrypt(buf, strlen((char*)buf), buffer, &len) != XXTEA_STATUS_SUCCESS)
    {
        error(" Encryption Failed!");
        return nullptr;
    }
    return buffer;
}    

bool DeBinaryPackage(char* buffer,  char* opensslEncrypted) {

    if(xxtea_setup(opensslEncrypted, strlen((char *)opensslEncrypted)) != XXTEA_STATUS_SUCCESS)
    {
        error("DeBinaryPackage Assignment Failed!");
        return nullptr;
    }
    int len = strlen((char *)buffer);

    if(xxtea_decrypt(buffer, len) != XXTEA_STATUS_SUCCESS)
    {
        error("Decryption Failed!");
        return;
    }
    return buffer;
}
}
#endif