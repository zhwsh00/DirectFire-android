#ifndef __IAPHELPER_H__
#define __IAPHELPER_H__

#include <iostream>
#include <vector>
using namespace std;

#define ProductID_IAP0p99 "com.km.directfire.1_99usd_10coin"
#define ProductID_IAP2p99 "com.km.directfire.2_99usd_20coin"
#define ProductID_IAP5p99 "com.km.directfire.5_99usd_50coin"
#define ProductID_IAP9p99 "com.km.directfire.9_99usd_90coin"
#define ProductID_IAP12p99 "com.km.directfire.12_99usd_130coin"
#define ProductID_IAP16p99 "com.km.directfire.16_99usd_180coin"

class IAPListener;
class IAPHelperImpl;
class IAPHelper
{
private:
    IAPHelper();
    virtual ~IAPHelper();
    static IAPHelper *m_instance;
public:
    static IAPHelper *getInstance();
    int getCoinNumByProductId(int id);
    int getCoinNumByProductId(const std::string &id);
    void registerListener(IAPListener* iapListener);
    void unRegisterListener(IAPListener* iapListener);
    
    void buyProduct(int index);
    void recordTransaction(int quantity,
                           int verifyStatus,
                           const std::string& receipt,
                           const std::string& productId,
                           const std::string& transactionId,
                           const std::string& purchaseDate);
    void sendTransaction(int quantity,
                         int verifyStatus,
                         const std::string& receipt,
                         const std::string& productId,
                         const std::string& transactionId,
                         const std::string& purchaseDate);
    void iapFailed(int reason);
    
protected:
    IAPHelperImpl* m_iapHelperImpl;
    vector<IAPListener*> m_iapListeners;
};

#endif /* __IAPHELPER_H__ */

