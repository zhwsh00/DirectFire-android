#ifndef CRYPTOAES_H
#define CRYPTOAES_H

#include <openssl/evp.h>
#include <openssl/aes.h>

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>

#include "crypto.h"

using namespace std;

class CryptoAES : public Crypto{
public:
    CryptoAES();
    CryptoAES(const string& inputKey, Crypto::CryptoType type);
    virtual ~CryptoAES();
    virtual bool init();

    virtual bool encrypt(const msgpack::sbuffer& sendBuffer, msgpack::sbuffer& cryptoBuffer);
    virtual bool decrypt(const msgpack::sbuffer& revBuffer, msgpack::sbuffer& decryptBuffer);

private:
    void cleanUp();

    EVP_CIPHER_CTX *m_aesEncryptCtx;
    EVP_CIPHER_CTX *m_aesDecryptCtx;
    const EVP_CIPHER *m_cipher;

    unsigned char *m_aesKey;
    unsigned char *m_aesIV;
    int m_aesKeyLen;
};
#endif // CRYPTOAES_H
