#ifndef CRYPTOACTIONAES_H
#define CRYPTOACTIONAES_H

#include "cryptoaction.h"
class CryptoActionAES : public CryptoAction
{
public:
    CryptoActionAES(const string& inputKey, Crypto::CryptoType type);
    virtual ~CryptoActionAES();

    virtual bool sendDataPrepare(const msgpack::sbuffer& sendBuffer, msgpack::sbuffer& sendBufFinal);
    virtual msgpack::sbuffer& revDataFinal();
private:
    Crypto *m_crypto;
};

#endif // CRYPTOACTIONAES_H
