#ifndef __NETDETECTLISTENER_H__
#define __NETDETECTLISTENER_H__

class NetDetectListener
{
public:
    typedef enum {
        NotReachable = 0,
        ReachableViaWiFi,
        ReachableViaWWAN
    } NetworkStatus;
    
    NetDetectListener(){};
    virtual ~NetDetectListener(){};
    
    virtual void reachabilityChanged(int netStatus, bool connectionRequired) = 0;
};

#endif /* __NETDETECTLISTENER_H__ */

