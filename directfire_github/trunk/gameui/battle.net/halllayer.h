#ifndef _halllayer_h_
#define _halllayer_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "uilib/uilib.h"
#include "gamecore/serverinterface.h"

using namespace uilib;

class HallMainWidget;
class UserShow;

class HallLayer : public CCLayer
{
public:
    HallLayer();
    virtual ~HallLayer();
    bool init();
    CREATE_FUNC(HallLayer)
public:
    void serverListener(CCNode *sender,void *type);
protected:
    virtual void keyBackClicked();
    virtual void keyMenuClicked();
protected:
    void onConGameServerSuccess(CCNode *sender,void *data);
    void onConGameServerFail(CCNode *sender,void *data);
    void backMainMenuPageWithDialog();
    void onBackMainMenuOkClicked(CCNode *sender,void *data);
    void backMainMenuPageNoEffect();
    void popRoomSceneToHall();
protected:
    void doBackToMainMenu(float dt);
protected:
    void onNetChangedInHall(CCNode *sender,void *data);
protected:
    void startWaitServerInfo();
    void startWaitJoinRoom();
    void onJoinRoomStart(CCNode* sender);
    void enableCancelWaitJoinRoom();
    void cancelWaitingJoinRoom();
protected:
    void enterRoom();
protected:
    void startWaitCreateRoom();
    void onCreateRoomStart(CCNode* sender);
    void enableCancelWaitCreateRoom();
    void cancelWaitingCreateRoom();
protected:
    void startWaitQuickGame();
    void onQuickGameStart(CCNode* sender);
protected:
    void endWaiting();
protected:
    void onSystemNoticeClosed(CCNode *sender);
protected:
    void onQuitGameClicked();
    void onQuitGameOkClicked(CCNode *sender,void *data);
    void onQuitGameCancelClicked(CCNode *sender,void *data);
    void onQuitGameOkActionFinished(CCNode *sender);
    void onQuitGameCancelActionFinished(CCNode *sender);
private:
    BusyDialog *m_waitingDialog;
protected:
    HallMainWidget *m_mainWidget;
    BasNodeDelegateWidget *m_baseWidget;
    UserShow *m_userShow;
    LabelMessageDialog *m_notifyWidget;
    QueryDialog *m_quitDialog;
protected:
    std::string m_theme;
    std::string m_themeBg;
    ServerInterface *m_serverIface;
protected:
    std::string m_uid;
    std::string m_mail;
    std::string m_nickName;
};

#endif
