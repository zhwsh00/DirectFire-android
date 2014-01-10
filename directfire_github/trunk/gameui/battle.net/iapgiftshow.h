#ifndef _iapgiftshow_h_
#define _iapgiftshow_h_
#include "uilib/uilib.h"
#include "cliententry/uimsgevent.h"

using namespace uilib;
#include <string>
#include <vector>
using namespace std;

#include "cocos2d.h"
using namespace std;

class IAPGiftShow : public BasShowDialog
{
public:
    IAPGiftShow(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~IAPGiftShow();
    void exec();
    void setTitleText(const std::string& titleText) {m_titleText = titleText;}
    void setGifts(std::vector<UiMsgEv::GiftPropEv>& gifts) {
        m_gifts.clear();
        m_gifts = gifts;
    }
    void setCoinNum(int num) { m_coinNum = num;}
public:
    std::vector<UiMsgEv::GiftPropEv>& gifts() {return m_gifts;}
protected:
    void finished();
protected:
    void onCloseClicked(CCNode *sender,void *data);
protected:
    std::vector<UiMsgEv::GiftPropEv> m_gifts;
protected:
    std::string m_titleText;
    int m_coinNum;
};

#endif
