#ifndef __NETDETECT_H__
#define __NETDETECT_H__

#include <iostream>
#include <vector>
using namespace std;

class NetDetectListener;
class NetDetectImpl;
class NetDetect
{
private:
    NetDetect();
    virtual ~NetDetect();
    static NetDetect *m_instance;
public:
    static NetDetect *getInstance();
    
    void getCurrentReachability(int& netStatus, bool& connectionRequired);
    void reachabilityChanged(int netStatus, bool connectionRequired);
    
    void registerListener(NetDetectListener* netDetectListeners);
    void unRegisterListener(NetDetectListener* netDetectListeners);
    
protected:
    NetDetectImpl* m_netDetectImpl;
    vector<NetDetectListener*> m_netDetectListeners;
};

#endif /* __NETDETECT_H__ */

