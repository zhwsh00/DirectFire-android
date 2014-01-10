#ifndef __NETDETECTIMPL_H__
#define __NETDETECTIMPL_H__

#include "netdetect.h"

class NetDetect;
class NetDetectImpl
{
public:
    NetDetectImpl(NetDetect *netDetect) : m_netDetect(netDetect){};
    virtual ~NetDetectImpl(){};
    
    virtual void getCurrentReachability(int& netStatus, bool& connectionRequired){};
    
protected:
    NetDetect* m_netDetect;
};
extern NetDetectImpl* __createNetDetect(NetDetect* netDetect);

#endif /* __NETDETECTIMPL_H__ */

