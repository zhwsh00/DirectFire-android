#ifndef _cliententry_h_
#define _cliententry_h_
#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

#include "uimsghandler.h"
#include "uimsgevent.h"
#include "iap/IAPListener.h"
#include "netdetect/netdetectlistener.h"
#include "photo/photolistener.h"
#include "prop/propdef.h"

#include "gamedata/gamemodel.h"

class ClientEntryPrivate;
class ClientEntry : public IAPListener, public NetDetectListener, public PhotoListener
{
public:
    friend class ClientEntryPrivate;
    ClientEntry();
    virtual ~ClientEntry();
    void setRemoteMD5(const std::string& md5);
    void setLocalDbInfo(const std::string &dir,const std::string &name);
    void initLocalDb();
    bool initLocalDbSuccess();
    bool needRestoreTransaction();
    bool getRestoreTransactions(vector<UiMsgEv::IAPInfo>& iapMsgs);
    // IAPListener
    virtual void recordTransaction(UiMsgEv::IAPInfo& iapMsg);
    virtual void sendTransaction(UiMsgEv::IAPInfo& iapMsg);
    virtual void iapFailed(int reason);
    void buySuccess(PropDef::VirtualProps type,int num);
    void buyProduct(int index);
    // NetDetectListener
    virtual void reachabilityChanged(int netStatus, bool connectionRequired);
    void getCurrentReachability(int& netStatus, bool& connectionRequired);
    bool isNetActived();
    bool isNetConning();
    bool isWifi();
    bool is3G();
    // PhotoListener
    virtual void takePhotoFinished(const char* imageData, int len, const char* imageDataHq, int lenHq);
    virtual void takePhotoFailed();
    virtual void takePhotoCanceled();
    // db settings
    void setLocalSettingDbInfo(const std::string &path);
    void initLocalSettingDb();
    bool isInitLocalSettingDbSuccess();
    void setLoginServerInfo(const std::string &ip,int port);
    void setClientInfo(const std::string &device,const std::string &clientVersion);
    void setTimeOut(float time);
    /* called this each frame */
    void frameUpdate();
    virtual void handleNetEvent(NetEventPackage *event) = 0;
    virtual UiMsgHandler::UiEvHandleResult handleGameEvent(GameEventPackage *event) = 0;
    int getNetEventCount();
    int getGameEventCount();
    /* the api for login
      */
    UiMsgEv::AccountInfoEv *getLatestLoginedInfo();
    void queryRouteList();
    UiMsgEv::RoutesInfo& getAllRoutes();
    void setLoginUser(const std::string &userId,const std::string &userMail,
                      const std::string &userName,const std::string &passWord,int route);
    void loginInto();
    void netPosExitServer();
    void netPosExitRoom();
    void backToMainMenu();
    void tryReLogin();
    void setTryFirstTimes(bool firstTimes);
    bool isTryFirstTimes();
    void reLoginFromSleep();
    void cancelLogin();
    bool isLogined();
    void setIsLogined(bool logined);
    void disconnectGameServer();
    std::vector<UiMsgEv::LoginInfo> *getBroadCastLoginInfo();
    // user info reset
    void resetUserInfo(const string& mail, const string& pwd, const string& nickName, short sex);
    void headSettingClosed(bool isVisible);
    /* the api for register
      */
    void setRegisterUser(const std::string &userId,const std::string &userMail,
                         const std::string &userName,const std::string &passwd,int route);
    void registerInto();
    void cancelRegister();
    bool isInMainMenu();
    bool isInRoom();
    bool isInHall();
    bool isInGame();
    void sendMail(const std::string &uid,const std::string &title,const std::string &content,int type = UiMsgEv::MsgToUser);
    void sendGift(const std::string &uid,const std::string &word,const std::vector<UiMsgEv::GiftPropEv> &gifts);
    void getRandHQPortraits(int count);
    void thumbPlayer(const std::string &id);
    void footPlayer(const std::string &id);
    UiMsgEv::ThumbPortrait *getThumbPortrait();
    void gainPropAction(const std::string &uid,int reason,const std::vector<UiMsgEv::PropDef> &props);
    void usePropAction(const std::string &uid,int reason,const std::vector<UiMsgEv::PropDef> &props);
    void salePropAction(const std::string &uid,const std::vector<UiMsgEv::PropDef> &props);
    void buyPropAction(const std::string &uid,const std::vector<UiMsgEv::PropDef> &props);
    const std::vector<UiMsgEv::PropExchangeRule> *getPropExchangeRule();
    bool getPropExchangeRuleByPropType(int propType, UiMsgEv::PropExchangeRule& outRule);
    void getAllHeros();
    const UiMsgEv::HerosInfo *getHerosDataByType(UiMsgEv::HerosType type);
    void getUserAllRank();
    const std::vector<UiMsgEv::UserRank> *getUserRankInfo();
    //feedback
    void sendFeedback(const std::string &feed);
    //game run model set
    void setGameModel(GameType::RunType model);
    GameType::RunType getGameModel();
    bool isBattleModel();
    bool isTdModel();
    bool isTollModel();
    bool isEndLessModel();
    bool isSuchModel(GameType::RunType model);
    //endless mode relative
    void initEndlessMode();
    void startEndlessMode();
    void finishEndlessMode();
public:
    void save();
    UiMsgEv::AccountInfoEv *getLoginAccountInfo();
    UiMsgEv::PlayerInfoEv *getPlayerInfoByUid(const std::string &uid = "");
    int getPropNumByUid(const std::string &uid,int propid);
    void getAllProps(const std::string &uid,std::vector<UiMsgEv::GiftPropEv> &props);
    void getAllUnzeroProps(const std::string &uid,std::vector<UiMsgEv::GiftPropEv> &props);
    void initLevelMgr();
    void getLevelExpInfo(int level,int &expstart,int &expend);
    bool hasUnreadMail();
    bool getUnreadMail(std::string &id,std::string &uid,std::string &title,std::string &body);
    bool hasUnreadSystemNotice();
    bool getSystemNotice(std::string &title,std::string &body);
    bool hasUnreadGift();
    bool getReceivedGift(std::string &uid,std::string &uname,std::vector<UiMsgEv::GiftPropEv> &gifts,std::string &word,int& reason);
    bool hasUnreadAskFriend();
    bool getReceivedBuyInfo(std::vector<UiMsgEv::GiftPropEv> &gifts,std::string &word);
    bool hasUnreadBuyInfo();
    UiMsgEv::AskFriendInfo *getAskFriendInfo();
    void acceptAskFriend(const std::string &id);
    void rejectAskFriend(const std::string &id);
    bool hasUnreadAskFriendAccept();
    bool getAskFriendAccept(std::string &id);
    bool hasUnreadTask();
    void resumeOneTask();
    UiMsgEv::AwardTaskInfo *getAwardTaskInfo();
    void submitTaskRule(const std::string &taskkey);
    bool hasHeadPortrait(const std::string &uid);
    bool getHeadPortrait(const std::string &uid,std::string **head);
    void setPortraitWaitingConfirm(std::string *head);
    bool isFriend(const std::string &fid);
    const std::vector<std::string> &getFriends();
    void addFriend(const std::string &fid,const std::string &word);
    void delFriend(const std::string &fid);
    void requestOnlineFriends();
    const std::vector<std::string> &getOnlineFriends();
    void refreshFriendsInfo();
    void refreshHallInfo(int infoType = GameType::RunType_Battle);
    void getHallRoomInfo(std::vector<UiMsgEv::RoomMapInfoEv> &room);
    const std::vector<UiMsgEv::MapInfo> *getMapsInfo();
    void createRoomPrepare(UiMsgEv::RoomMapInfoEv *ev);
    void createRoom();
    void quickGamePrepare(UiMsgEv::RoomMapInfoEv *ev);
    void quickGame();
    void joinRoomPrepare(int mapId);
    void joinRoom();
    void cancelWaitingJoinRoom();
    void quitRoom();
    void quitGameForce();
    void leaveRoom();
    void leaveGame();
    bool getRoomSeatOpened(int seatIndex);
    int getRoomPlayerIndexBySeatIndex(int seatIndex);
    void invitePlayerToGame(const std::string &id,const std::string &fid);
    void acceptInvitedToGame(const std::string &inviter);
    void rejectInvitedToGame(const std::string &inviter);
    void requestChangePlayerTribe(const std::string &id,int tribe);
    void requestChangeSpellNum(const std::string &id,int num);
    void requestChangeSeatIndex(const std::string &id,int oldSeat,int newSeat);
    void requestSeatToClose(const std::string &id,int seatIndex);
    void requestSeatToOpen(const std::string &id,int seatIndex);
    void kickUserInRoom(const std::string &id,const std::string &obj);
    void praiseUserInRoom(const std::string &id,const std::string &obj);
    void sneerUserInRoom(const std::string &id,const std::string &obj);
    long getDelayMSec();
    UiMsgEv::RoomInfoEv *getRoomInfo();
    bool hasRoomChatInfo();
    UiMsgEv::ChatInfo *getRoomChatInfo();
    bool hasHallChatInfo();
    UiMsgEv::ChatInfo *getHallChatInfo();
    void startRoomGame();
    void pauseGame();
    void resumeGame();
    void sendGameResult(const std::vector<UiMsgEv::GameResultInfo> &results);
    UiMsgEv::GameInitInfo *getGameInitInfo();
    void setSelectedProps(int num,const std::vector<std::string> &props);
    const UiMsgEv::PropsSelected &getSelectedProps();
    void handleClientClickAction(float x,float y,int clientCurrFrame,int attach);
    void handleClientPropAction(float x,float y,float rotation,const std::string &type,int clientCurrFrame,int attach);
    void handleBallColorChange(int userIndex,int attach,int orig,int change);
protected:
    ClientEntryPrivate *m_p;
};

class ClientEntryProxy
{
public:
    static ClientEntryProxy *getInstance(ClientEntry *client = 0);
    ClientEntry *getClientEntry();
private:
    ClientEntryProxy(ClientEntry *client);
    ~ClientEntryProxy();
    static ClientEntryProxy *m_instance;
    ClientEntry *m_entry;
};

#endif
