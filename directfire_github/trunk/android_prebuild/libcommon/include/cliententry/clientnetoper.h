#ifndef _clientnetoper_h_
#define _clientnetoper_h_
#include "network/common/netcommon.h"
#include "gameclient/gameclient.h"
#include "gameclient/uxlistener.h"
#include "netoper/absnetoper.h"

class ClientNetOper : public BasNetOper,public UXListener
{
public:
    ClientNetOper();
    virtual ~ClientNetOper();
    virtual void setEvLoop(struct ev_loop *loop);
    virtual void messageChanged(const string&);
    virtual void gameClientChanged(int, NetMessage* msg=0, int msgType=0);
    virtual void handleServerMessage(int type,NetMessage* msg);
    GameClient *getGameClient() { return m_gameClient;}
    ClientInfoMessage *getClientInfo() { return m_clientInfoMessage;}
    RoomInfoMessage *getRoomInfo() { return m_roomInfoMessage;}
public:
    void requestTestPing();
protected:
    virtual void startGame(int playerIndex);
    virtual void pauseGame(int playerIndex);
    virtual void endGame(int playerIndex);
    virtual void resumeGame(int playerIndex);
    virtual void gameStarted();
    virtual void gameEnded();
    virtual void gameWon();
    virtual void gameLose();
protected:
    virtual void loginSuccess(FriendsInfoMessage *friends);
    virtual void loginFailed(int error);
    virtual void registerSuccess(const std::string &name,const std::string &passwd);
    virtual void registerFailed(int error);
    virtual void roomCreatedSuccess(PlayerInfoMessage *msg);
    virtual void roomCreatedFailed(int error);
    virtual void roomJoinWaiting();
    virtual void roomJoinSuccess(RoomInfoMessage *roomInfo);
    virtual void roomJoinFailed(int error);
    virtual void roomInfoUpdated(RoomInfoMessage &roomInfo);
    virtual void playerInfoUpdated(PlayerInfoMessage &playerInfo);
    virtual void roomOtherJoined(PlayerInfoMessage &playerInfo);
    virtual void roomOtherQuit(PlayerInfoMessage &playerInfo);
    virtual void gameSpeedChanged(int speed);
    virtual void playerTypeChanged(int type);
protected:
    virtual void userClickedGot(PlayerClickMessage *click);
    virtual void userPropUsedGot(PlayerPropMessage *prop);
    virtual void gameSyncGot(GameSyncMessage *sync);
protected:
    void requestAsObserver();
protected:
    GameClient *m_gameClient;
    ClientInfoMessage *m_clientInfoMessage;
    RoomInfoMessage *m_roomInfoMessage;
protected:
    long m_serverTimeSec;
    long m_serverTimeUSec;
};

#endif
