#ifndef _absnetthread_h_
#define _absnetthread_h_
#include "msgpack.hpp"
#include "absthread.h"
class NetMessage;
class BasNetThread : public BasThread
{
public:
	BasNetThread();
	~BasNetThread();
    // free all memory
    virtual void finish(){}
    // only pause thread
    virtual void stop(){}
    // restart thread after stop, same as asyncInvoke(NetMessage::CommandInfo_ClientRestart, sbuf)
    virtual void restart(){}
    virtual void packAsyncInvokeMessage(short type,NetMessage *messages,msgpack::sbuffer &sbuf){}
    virtual void handleAsyncInvokeMessagePack(const msgpack::sbuffer &sbuf){}
    virtual void asyncInvoke(int type, const msgpack::sbuffer& sbuf){}
    virtual void registerInfo(){}
    virtual void run() = 0;
	virtual void handleCommand(short type) = 0;
	virtual NetMessage *getNetMessage(short type) = 0;
	virtual short getCurrUseNetMessageType() = 0;
};
#endif
