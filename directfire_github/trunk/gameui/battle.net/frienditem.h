#ifndef _frienditem_h_
#define _frienditem_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "baspage.h"
#include "wonshow.h"
#include "uilib/uilib.h"
using namespace uilib;
#include "cliententry/uimsgevent.h"

class SendGiftDialog;
class SendMsgDialog;
class DelFriendDialog;
class FriendsPage;
class FriendItem : public BorderWidget
{
public:
    FriendItem(FriendsPage *owner);
    virtual ~FriendItem();
    void setItemInfo(UiMsgEv::PlayerInfoEv *ev);
    void setHeadPortrait(const std::string &head);
    void clearProp();
    void addProp(int id,int count);
    void finish();
    const std::string &userId() { return m_info->m_userId;}
public:
    void updateFriendHead(const std::string &head);
    void updateProp();
    void updateWonNum(UiMsgEv::PlayerInfoEv *ev);
    void updateProperty(UiMsgEv::PlayerInfoEv *ev);
    void updateOnline(bool on);
    void updatePlayingGame(const std::string &name,const std::string &icon);
protected:
    void createFriendHead();
    void createFriendInfo();
    void createProperty();
    void createWonNum();
    void createProps();
    void createOnline();
    void createPlayingGame();
protected:
    void onHeadClicked(CCNode *node,void *data);
    void onPropClicked(CCNode *node,void *data);
    void onInfoClicked(CCNode *node,void *data);
protected:
    void onPopButtonsClicked(CCNode *node,void *data);
protected:
    void onSendMsgClicked();
    void onSendGiftClicked();
    void onDelFriendClicked();
protected:
    void onSendGiftCloseClicked(CCNode *node,void *data);
    void onSendGiftSendClicked(CCNode *node,void *data);
protected:
    void onSendMsgCloseClicked(CCNode *node,void *data);
    void onSendMsgSendClicked(CCNode *node,void *data);
protected:
    void onDelFriendCloseClicked(CCNode *node,void *data);
    void onDelFriendDelClicked(CCNode *node,void *data);
protected:
    int m_id;
    std::string m_headPortrait;
    UiMsgEv::PlayerInfoEv *m_info;
protected:
    bool m_init;
protected:
    CCSprite *m_headSprite;
    BasWidget *m_headWidget;
protected:
    WonGameShow *m_wonShow;
    float m_won,m_lost,m_offline,m_escape;
protected:
    std::vector<UiMsgEv::GiftPropEv> m_hasProps;
    HorScrollWidget *m_propWidget;
    HorScrollWidget *m_infoWidget;
    BasWidget *m_onlineWidget;
    bool m_online;
protected:
    FriendsPage *m_owner;
protected:
    SendGiftDialog *m_sendGiftDialog;
    SendMsgDialog *m_sendMsgDialog;
    DelFriendDialog *m_delFriendDialog;
};

#endif
