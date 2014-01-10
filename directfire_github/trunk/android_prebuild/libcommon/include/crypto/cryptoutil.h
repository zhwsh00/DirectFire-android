#ifndef CRYPTOUTIL_H
#define CRYPTOUTIL_H

#include "ev++.h"

#include "cryptoaction.h"

class CryptoUtil
{
public:
    CryptoUtil();

    static void sendCacheEnable(CryptoAction& cryptoAction, ev::io& evIo);
};

#endif // CRYPTOUTIL_H
