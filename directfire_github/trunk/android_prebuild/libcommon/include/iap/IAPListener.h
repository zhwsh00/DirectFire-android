#ifndef __IAPLISTENER_H__
#define __IAPLISTENER_H__

#include "cliententry/uimsgevent.h"

class IAPListener
{
public:
    IAPListener(){};
    virtual ~IAPListener(){};

    virtual void recordTransaction(UiMsgEv::IAPInfo& iapMsg) = 0;
    virtual void sendTransaction(UiMsgEv::IAPInfo& iapMsg) = 0;
    /*
     iap failed reason code
     0: unknow
     1: client is not allowed to issue the request, etc.
     2: user cancelled the request, etc.
     3: purchase identifier was invalid, etc.
     4: this device is not allowed to make the payment
     5: Product is not available in the current storefront
     */
    virtual void iapFailed(int reason) = 0;
};

#endif /* __IAPLISTENER_H__ */

