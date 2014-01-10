#ifndef _giftwidget_h_
#define _giftwidget_h_
#include "uilib/uilib.h"

using namespace uilib;
#include "gamecore/serverinterface.h"

class RecGiftShow;
class SendGiftDialog;
class GiftWidget : public BasWidget
{
public:
    GiftWidget(BasWidget *parent);
    virtual ~GiftWidget();
    void giftUpdated();
    void setTheme(const std::string &theme,const std::string &has,const std::string &no);
    void finish();
    void layoutCompleted();
protected:
    virtual bool getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size);
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    void onGiftShowCloseClicked(CCNode *node,void *data);
    void onGiftShowSendMsgClicked(CCNode *node,void *data);
    void onSendGiftClicked(CCNode *node,void *data);
    void onAddFriendClicked(CCNode *node,void *data);
    void onGiftShowMoveOutFinished(CCNode *node);
    void onGiftShowMoveOutSendMsgFinished(CCNode *node);
protected:
    void onSendGiftSendClicked(CCNode *node,void *data);
    void onSendGiftDialogCloseClicked(CCNode *node,void *data);
protected:
    std::string m_theme;
    std::string m_hasImg;
    bool m_inited;
protected:
    CCSprite *m_hasSprite;
protected:
    bool m_has;
    ServerInterface *m_serverIface;
protected:
    std::string m_senderId;
    std::string m_senderName;
    int m_giftId;
    int m_giftCount;
    std::string m_giftName;
protected:
    RecGiftShow *m_giftShow;
    SendGiftDialog *m_sendGiftDialog;
};
#endif
