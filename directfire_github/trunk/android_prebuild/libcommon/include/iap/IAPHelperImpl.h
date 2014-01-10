#ifndef __IAPHELPERIMPL_H__
#define __IAPHELPERIMPL_H__

#include "IAPHelper.h"

class IAPHelper;
class IAPHelperImpl
{
public:
    IAPHelperImpl(IAPHelper *iapHelper) : m_iapHelper(iapHelper){};
    virtual ~IAPHelperImpl(){};
    
    virtual void buyProduct(int index){};
    
protected:
    IAPHelper* m_iapHelper;
};
extern IAPHelperImpl* __createIAPHelper(IAPHelper* iapHelper);

#endif /* __IAPHELPERIMPL_H__ */

