#ifndef _uimsghandler_h_
#define _uimsghandler_h_
#include <queue>
#include <string>
using namespace std;
#include <pthread.h>

static pthread_mutex_t UiMsgHandler_mutex = PTHREAD_MUTEX_INITIALIZER;
class NetEventPackage
{
public:
    NetEventPackage(int eventId,void *param1 = 0,void *param2 = 0,int param3 = 0,std::string param4 = "");
    ~NetEventPackage();
    int eventId() { return m_eventId;}
    void *param1() { return m_param1;}
    void *param2() { return m_param2;}
    int param3() { return m_param3;}
    const std::string& param4() { return m_param4;}
    void setReturnVal(int rev) { m_param3 = rev;}
    int getReturnVal() { return m_param3;}
protected:
    int m_eventId;
    void *m_param1;
    void *m_param2;
    int m_param3;
    std::string m_param4;
};

class GameEventPackage : public NetEventPackage
{
public:
    GameEventPackage(int frame,int eventId,void *param1 = 0,void *param2 = 0);
    ~GameEventPackage();
    int occurFrame() { return m_occurFrame;}
protected:
    int m_occurFrame;
};

class UiMsgHandler
{
public:
    enum UiEventType{
        UiEv_allRoutesGot,
        UiEv_loginSucc,
        UiEv_loginFailed,
        UiEv_gameServerFailed,
        UiEv_regSucc,
        UiEv_regFailed,
        UiEv_intoHall,
        UiEv_playerInfoGot,
        UiEv_friendInfoGot,
        UiEv_askAsFriendGot,
        UiEv_otherInfoGot,
        UiEv_validTaskGot,
        UiEv_unreadMailGot,
        UiEv_onlineFriendGot,
        UiEv_recentRecPropGot,
        Uiev_giftGot,
        Uiev_giftChange,
        Uiev_coinChange,
        UiEv_portraitGot,
        UiEv_allPropsGot,
        UiEv_ServerNoticeGot,
        UiEv_syncGot,
        UiEv_gameInit,
        UiEv_gameStart,
        UiEv_gameEnd,
        UiEv_gameWon,
        UiEv_gameLose,
        UiEv_userClick,
        UiEv_userProp,
        UiEv_startRefreshFriend,
        UiEv_endRefreshFriend,
        UiEv_hallRoomInfoGot,
        UiEv_startRefreshHallInfo,
        UiEv_endRefreshHallInfo,
        UiEv_startJoinRoom,
        UiEv_joinRoomWaiting,
        UiEv_joinRoomSucc,
        UiEv_joinRoomFailed,
        UiEv_cancelWaitingJoinSucc,
        UiEv_roomChatGot,
        UiEv_hallChatGot,
        UiEv_quitRoom,
        UiEv_otherJoinRoom,
        UiEv_otherQuitRoom,
        UiEv_createRoomStart,
        UiEv_createRoomSucc,
        UiEv_createRoomFailed,
        UiEv_quickGameStart,
        UiEv_acceptFriendReply,
        UiEv_rejectFriendReply,
        UiEv_askFriendAccepted,
        UiEv_askFriendRejected,
        UiEv_thumbPortraitGot,
        UiEv_usePropReply,
        UiEv_salePropRely,
        UiEv_salePropFailedRely,
        UiEv_buyPropRely,
        UiEv_buyPropFailedRely,
        UiEv_herosInfoGot,
        UiEv_startGetHerosInfo,
        UiEv_endGetHerosInfo,
        UiEv_playerRankInfoGot,
        UiEv_SeatIndexChanged,
        UiEv_SeatIndexChangedError,
        UiEv_SeatNumChanged,
        UiEv_SeatNumChangedError,
        UiEv_kickedByOther,
        UiEv_seatCloseed,
        UiEv_seatOpened,
        UiEv_tribeChanged,
        UiEv_inviteToGameGot,
        UiEv_spellNumChanged,
        UiEv_roomUsePropGot,
        UiEv_kickUserGot,
        UiEv_forceQuitGot,
        UiEv_gameResultSuccessGot,
        UiEv_gameResultFailedGot,
        UiEv_gameEndAndWon,
        UiEv_needPropsSelected,
        UiEv_ServerIAPVerifyGot,
        UiEv_netStatusChanged,
        UiEv_resetUserInfoFailed,
        UiEv_resetUserInfoSuc,
        UiEv_headSettingClosed,
        UiEv_buyActionGot,
        UiEv_iapFailed,
        UiEv_clearGame,
        UiEv_gameChange,
        UiEv_backToMainMenu,
        UiEv_loginInfoBroadCast
    };
    enum UiEvHandleResult{
        UiEv_wait,
        UiEv_used,
        UiEv_passed
    };
    UiMsgHandler();
    virtual ~UiMsgHandler();
    void addNetEvent(NetEventPackage *event);
    void addGameEvent(GameEventPackage *event);
    void clearNetEvent();
    void clearGameEvent();
protected:
    void lock() { pthread_mutex_lock(&UiMsgHandler_mutex); }
    void unlock() { pthread_mutex_unlock(&UiMsgHandler_mutex);}
    typedef std::queue<NetEventPackage*> NetEventQueue;
    typedef std::queue<GameEventPackage*> GameEventQueue;
    NetEventQueue m_netEventQueue;
    GameEventQueue m_gameEventQueue;
public: //support tower defence mode & endless mode
    void initGameEventVector(int size);
    void clearGameEventVector();
    void addGameEvent(int index,GameEventPackage *event);
protected:
    std::vector<GameEventQueue*> m_gameEventQueues;
};
#endif
