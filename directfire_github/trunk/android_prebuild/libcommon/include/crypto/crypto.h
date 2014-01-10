#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include "msgpack.hpp"

#define KM_CRYPTO_SALT         "$3ecXV4E7F3peagSDdL@bAB7hTy!noOc"

// 32bit len:-2147483648~2147483647
#define CRYPTO_HEAD_BLOCK_SIZE 8

using namespace std;

class Crypto {
public:
    enum CryptoType {
        CRYPTO_NONE = 0,
        CRYPTO_AES_128_CBC,
        CRYPTO_AES_256_CBC
    };

public:
    Crypto();
    Crypto(const string& inputKey, CryptoType type);
    virtual ~Crypto();
    virtual bool init() = 0;

    virtual void setInputKey(const string& inputKey){m_inputKey = inputKey;}
    virtual void setCryptoType(Crypto::CryptoType type){m_cryptoType = type;}

    virtual bool encrypt(const msgpack::sbuffer& sendBuffer, msgpack::sbuffer& cryptoBuffer) = 0;
    virtual bool decrypt(const msgpack::sbuffer& revBuffer, msgpack::sbuffer& decryptBuffer) = 0;

    static void dumpCryptoInfo(const unsigned char *msg, int len);

protected:
    string m_inputKey;
    CryptoType m_cryptoType;
};

#endif
