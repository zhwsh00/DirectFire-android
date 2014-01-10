#ifndef _roomroleshow_h_
#define _roomroleshow_h_
#include "uilib/uilib.h"

#include "wonshow.h"

using namespace uilib;

#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

#include "gamecore/serverinterface.h"

#include "cliententry/uimsgevent.h"

class OnlineFriendsInviteDialog;
class RoomMainWidget;
class RoomRoleShow : public BorderWidget
{
public:
    friend class OnlineFriendsInviteDialog;
    RoomRoleShow(RoomMainWidget *owner);
    virtual ~RoomRoleShow();
    void init(int dummy=0);
    void otherJoined(int pindex);
    void otherQuit(int pindex);
    void seatIndexChanged(int pindex);
    void seatIndexChangedFail(int pindex);
    void seatNumChanged(int pindex);
    void seatNumChangedFail(int pindex);
    void seatClosed(int seatIndex);
    void seatOpened(int seatIndex);
    void tribeChanged(int pindex);
    void priaseUser(const std::string &sender,const std::string &receiver);
    void sneerUser(const std::string &sender,const std::string &receiver);
    bool canStartGame();
protected:
    void initHeadInfo(const std::string &id,int seatindex);
    int getRoleRowBySeatPos(int seatpos);
    void posingRoomHostSign(const std::string &hostid,int hostseatpos);
    void posingPlayerMedal(const std::string &id,int sindex,int level);
    void posingPlayerTextInfo(const std::string &id,int sindex,
                              const std::string &creditName,const std::string &nickName);
    void initWonInfo(const std::string &id,int sindex,
                     int won,int lost,int offline,int escape);
    void initPropInfo(const std::string &id,int sindex,
                      const std::vector<UiMsgEv::GiftPropEv> &props);
    void initTribeInfo(const std::string &id,int sindex,int tribe);
protected:
    void onTribeClicked(CCNode *node,void *data);
    void onHeadClicked(CCNode *node,void *data);
    void onSeatClicked(CCNode *node,void *data);
    void onMedalClicked(CCNode *node,void *data);
protected:
    void onInviteFriendClick();
    void onInviteFriendCloseClicked(CCNode *node,void *data);
    void onInviteFriendFriendClicked(CCNode *node,void *data);
    void onPopTribeClicked(CCNode *node,void *data);
    void onPopSeatClicked(CCNode *node,void *data);
    void onPopHeadClicked(CCNode *node,void *data);
protected:
    int getSeatIndexByUserId(const std::string &id);
protected:
    RoomMainWidget *m_owner;
protected:
    ServerInterface *m_serverIFace;
    UiThemeDef *m_uiDef;
protected:
    bool m_init;
protected:
    std::vector<BasNodeDelegateWidget *> m_rowFlags;
    std::vector<CCSprite *> m_indexSprite;
    std::vector<BasWidget *> m_indexWidget;
    std::vector<int> m_roleRows;
protected:
    std::map<std::string,BasNodeDelegateWidget *> m_headWidgetMap;
    std::map<std::string,BasNodeDelegateWidget *> m_playerMedalMap;
    std::map<std::string,BasWidget *> m_playerTextInfoMap;
    std::map<std::string,WonGameShow *> m_wonShowMap;
    std::map<std::string,HorScrollWidget*> m_playerPropsMap;
protected:
    std::map<std::string,BasNodeLimitWidget*> m_tribeWidgetMap;
protected:
    std::vector<FSizeWidgetContainer *> m_widgetContainer;
protected:
    BasWidget *m_roomHostSign;
    bool m_isHost;
    std::string m_id;
protected:
    float m_propW,m_propH;
protected:
    int m_popSeatIndex;
    std::string m_headUserId;
protected:
    OnlineFriendsInviteDialog *m_onlineFsDialog;
protected:
    BasWidget *m_parentWidget;
};
#endif
