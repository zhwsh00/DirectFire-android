#ifndef _roommainwidget_h_
#define _roommainwidget_h_
#include "uilib/uilib.h"
using namespace uilib;
#include "cliententry/uimsgevent.h"

#include "gamecore/resource/resourcemgr.h"

#include "gamecore/serverinterface.h"

#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

class ChatWidget;
class RoomGameShow;
class RoomRoleShow;
class KickOutDialog;
class RoomMainWidget : public BasWidget
{
public:
    friend class ChatWidget;
    friend class RoomGameShow;
    friend class RoomRoleShow;
    RoomMainWidget();
    virtual ~RoomMainWidget();
    void resetRoom();
public:
    void serverListener(CCNode *sender,void *type);
    void intoRoom();
    void initRoom();
    void setChatTo(const std::string &id);
    void enableStartAfterSec(int sec = 8);
    void setChatBoxVisible(bool visible);
protected:
    void chatInfoStep(float dt);
protected:
    void onRoomQuitClicked(CCNode *sender,void *data);
    void onRoomStartClicked(CCNode *sender,void *data);
protected:
    void onKickedOutCloseClicked(CCNode *node,void *data);
protected:
    ServerInterface *m_serverIFace;
protected:
    ChatWidget *m_chatWidget;
    RoomGameShow *m_roomGameShow;
    RoomRoleShow *m_roomRoleShow;
protected:
    UiMsgEv::AccountInfoEv *m_accountInfo;
    UiMsgEv::RoomInfoEv *m_roomInfo;
protected:
    KickOutDialog *m_kickOutDialog;
};

#endif
