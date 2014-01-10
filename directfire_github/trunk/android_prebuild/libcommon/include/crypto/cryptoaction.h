#ifndef CRYPTOACTION_H
#define CRYPTOACTION_H

#include "crypto.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <errno.h>
#include <iostream>
#include <queue>
#include <pthread.h>
#include "msgpack.hpp"

#include "network/common/netcommon.h"

using namespace std;

// 32 byte
#define CRYPTOACTION_STATIC_KEY "~7@So9^&4-z1J8hx5A$-X@i!sH7fu-%I"

// CRYPTO_ACTION_INIT_BUFFER_SIZE 8KB
#define CRYPTO_ACTION_INIT_BUFFER_SIZE 8192
// MAX BUFFER 8KB*(2^11)=16MB
#define CRYPTO_ACTION_MAX_BUFFER_BULK 11

#ifdef __APPLE__
#define MSG_NOSIGNAL 0
#endif

class CryptoAction
{
public:
    typedef struct CachedData{
        int m_fd;
        int m_flags;
        ssize_t m_handled;
        msgpack::sbuffer m_sbuf;
        CachedData() {
            clear();
        }
        void clear() {
            m_fd = 0;
            m_flags = 0;
            m_handled = 0;
            m_sbuf.clear();
        }
    } CachedData;
public:
    CryptoAction();
    CryptoAction(const string& inputKey, Crypto::CryptoType type);
    virtual ~CryptoAction();

    // socket high real-time flag
    virtual void setRealTime(bool on);
    virtual bool getRealTime();

    virtual ssize_t cryptoSend(int fd, int flags, const msgpack::sbuffer& sendBuffer);
    virtual msgpack::sbuffer& cryptoRev(int fd, int flags, bool& ok);

    bool sendCachedData();
    bool hasCache4Send();

protected:
    // insert the head to send data
    virtual bool sendDataPrepare(const msgpack::sbuffer& sendBuffer, msgpack::sbuffer& sendBufFinal);

    // send cache data to socket
    // send new buffer to socket
    // save new buffer or cache data to queue if sent not completed
    virtual ssize_t sendDataFinal(int fd, int flags, const msgpack::sbuffer& sendBuffer);

    // restore cached data
    // insert front of the received data
    virtual bool revDataPrepare(int fd, int flags);

    // remove head of the received data
    // save the received half data to cache
    virtual msgpack::sbuffer& revDataFinal();

    void writeSendDataCache(int fd, int flags, const msgpack::sbuffer& sendBuffer, ssize_t handled);
    void writeRevDataCache(const msgpack::sbuffer& revBuffer, ssize_t handled);

protected:
    std::queue<CachedData*> m_sendDataCache;
    CachedData* m_revDataCache;
    msgpack::sbuffer m_revBuffer;
    msgpack::sbuffer m_revBufFinal;
    msgpack::sbuffer m_sendBufFinal;
    bool m_preRevSocketError;
    bool m_realTime;

private:
    void init();

    int m_alloced;
    int m_bulk;
    char *m_tmpbuf;
};

#endif // CRYPTOACTION_H
