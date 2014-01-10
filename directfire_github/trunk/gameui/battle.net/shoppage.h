#ifndef _shoppage_h_
#define _shoppage_h_

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "uilib/uilib.h"

#include "gamecore/serverinterface.h"

using namespace uilib;

class PropExDialog;
class PropSynDialog;
class Coin2GoldDialog;
class Prop2GoldDialog;

class ShopPage : public BasShowDialog
{
public:
    ShopPage(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~ShopPage();
    virtual void exec();
public:
    void serverListener(CCNode *sender,void *type);
protected:
    void onShopButtonClicked(CCNode *node,void *data);
    void onShopStart(CCNode *sender);
    void onPropExClicked(CCNode *node,void *data);
    void onPropSynClicked(CCNode *node,void *data);
    void onCoin2GoldClicked(CCNode *node,void *data);
    void onProp2GoldClicked(CCNode *node,void *data);
protected:
    void onPropExCloseClicked(CCNode *node,void *data);
    void onPropSynCloseClicked(CCNode *node,void *data);
    void onCoin2GoldCloseClicked(CCNode *node,void *data);
    void onProp2GoldCloseClicked(CCNode *node,void *data);
protected:
    void initItem();
    bool m_itemInit;
protected:
    BasWidget *m_shopWidget;
    BusyDialog *m_iapLoadingDialog;
protected:
    PropExDialog *m_exDialog;
    PropSynDialog *m_synDialog;
    Coin2GoldDialog *m_coin2Gold;
    Prop2GoldDialog *m_prop2Gold;
private:
    int m_iapIndex;
};
#endif
