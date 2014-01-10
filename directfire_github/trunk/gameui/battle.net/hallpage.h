#ifndef _hallpage_h_
#define _hallpage_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "baspage.h"
#include "uilib/uilib.h"
#include "gamecore/mascot/hallmascot.h"

using namespace uilib;
class MailWidget;
class GiftWidget;
class TaskWidget;
class AskFriendWidget;

class SocialPage;
class ChatWidget;

class AddFriendDialog;
class SendGiftDialog;
class SendMsgDialog;
class ServerInterface;

class ShopPage;
class SysPage;

class HallPage : public BasPage
{
public:
    HallPage(uilib::BasWidget *container = 0);
    virtual ~HallPage();
    virtual void moveinPage();
    virtual void moveoutPage();
    void thumbPortraitUpdate();
    void usePropReplyGot();
    void hallChatInfoGot();
    void headSettingClosed(int status);
    void onKeyPadBackClicked();
public:
    void giftUpdate();
    void mailUpdate();
    void askFriendUpdate();
    void taskUpdate();
protected:
    void chatInfoStep(float dt);
protected:
    void init(int dummy=0);
protected:
    void onHeadClicked(CCNode *node,void *data);
    void onPopButtonClicked(CCNode *node,void *data);
protected:
    void onHallMascotClicked(CCNode *node,void *data);
protected:
    void onSendMsgClicked();
    void onSendGiftClicked();
    void onAddFriendClicked();
protected:
    void onSendGiftCloseClicked(CCNode *node,void *data);
    void onSendGiftSendClicked(CCNode *node,void *data);
protected:
    void onSendMsgCloseClicked(CCNode *node,void *data);
    void onSendMsgSendClicked(CCNode *node,void *data);
protected:
    void onAddFriendCloseClicked(CCNode *node,void *data);
    void onAddFriendAddClicked(CCNode *node,void *data);
protected:
    void onShopPageCloseClicked(CCNode *node,void *data);
    void onSysPageCloseClicked(CCNode *node,void *data);
    void onSocialPageCloseClicked(CCNode *node,void *data);
protected:
    BasWidget *m_topWidget;
protected:
    SocialPage *m_socialPage;
    ChatWidget *m_chatWidget;
protected:
    int m_thumbNum;
    int m_footNum;
protected:
    CCLabelBMFont *m_thumbFont;
    CCLabelBMFont *m_footFont;
protected:
    ServerInterface *m_serverIFace;
    std::string m_userId;
protected:
    std::string m_headId;
    std::string m_headMail;
    std::string m_headNick;
    AddFriendDialog *m_addFriendDialog;
    SendGiftDialog *m_sendGiftDialog;
    SendMsgDialog *m_sendMsgDialog;
protected:
    MailWidget *m_mailWidget;
    GiftWidget *m_giftWidget;
    TaskWidget *m_taskWidget;
    AskFriendWidget *m_askFriendWidget;
protected:
    HallMascot *m_hallMascot;
protected:
    ShopPage *m_shopPage;
    SysPage *m_sysPage;
};

#endif
