#ifndef _mainmenulayer_h_
#define _mainmenulayer_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include "uilib/uilib.h"
using namespace uilib;

#include "gamecore/serverinterface.h"
#include "gamecore/resource/resourcemgr.h"
#include "gamecore/userdata/userdata.h"

class MainMenuLayer : public CCLayer,public CCKeypadDelegate
{
public:
    MainMenuLayer();
    virtual ~MainMenuLayer();
    bool init();
    CREATE_FUNC(MainMenuLayer)
public:
    void serverListener(CCNode *sender,void *type);
protected:
    virtual void keyBackClicked();
    virtual void keyMenuClicked();
protected:
    void onQueryRoutesStart(CCNode *sender);
    void onSettingWidgetClicked(CCNode *sender,void *data);
    void onSettingClicked(CCNode *sender,void *data);
    void onBackClicked(CCNode *sender,void *data);
    void onSwitchRouteClicked(CCNode *sender,void *data);
    void onBattleClicked(CCNode *sender,void *data);
    void onQuickClicked(CCNode *sender,void *data);
    void onQuickStart(CCNode *sender);
    void onCampaignClicked(CCNode *sender,void *data);
    void onEndlessClicked(CCNode *sender,void *data);
    void onChangeBgMusicClicked(CCNode *sender,void *data);
    void onChangeGameMusicClicked(CCNode *sender,void *data);
    void onSwitchAccountClicked(CCNode *sender,void *data);
    void onCheckUpdateClicked(CCNode *sender,void *data);
    void onQuitGameClicked(CCNode *sender,void *data);
protected:
    void tryConnectLoginInfo();
protected:
    void onQuitGameOkClicked(CCNode *sender,void *data);
    void onQuitGameCancelClicked(CCNode *sender,void *data);
    void onQuitGameOkActionFinished(CCNode *sender);
    void onQuitGameCancelActionFinished(CCNode *sender);
protected:
    void onCancelLoginDialogClicked(CCNode *sender,void *data);
    void onCancelLoginDialogActionFinished(CCNode *sender);
    void onLoginDialogLoginClicked(CCNode *sender,void *data);
    void onLoginDialogLoginStart(CCNode *sender);
    void onLoginDialogRegClicked(CCNode *sender,void *data);
    void onLoginDialogRegStart(CCNode *sender);
protected:
    void startCheckUpdate();
    void stopCheckUpdate();
protected:
    void onLoginSuccess(CCNode *sender,void *data);
    void onQueryLoginServerFail(CCNode *sender,void *data);
    void onLoginGameServerFail(CCNode *sender,void *data);
    void onConGameServerSuccess(CCNode *sender,void *data);
    void onConGameServerFail(CCNode *sender,void *data);
    void onUpdateOkClicked(CCNode *sender,void *data);
    void onUpdateCancelClicked(CCNode *sender,void *data);
    void onRegSuccess(CCNode *sender,void *data);
    void onRegFail(CCNode *sender,void *data);
    void onIntoHall(CCNode *sender,void *data);
protected:
    void startGameTypeClickAnim();
protected:
    void onGameWaveFinished(CCNode *sender,void *data);
    void onTreeBallWaveFinished(CCNode *sender,void *data);
    CCWaves *m_gameWave;
    CCWaves *m_treeBallWave;
protected:
    void onCheckResourceLoad(float dt);
protected:
    BasNodeDelegateWidget *m_bgWidget;
    BasNodeDelegateWidget *m_titleWidget;
    BorderWidget *m_settingWidget;
    BasButton *m_settingButton;
    BasButton *m_backButton;
    BasLabel *m_swtichRouteLabel;
    CCSprite *m_bgSprite;
    BasWidget *m_enterAnim;
    BasButton *m_battleButton;
    BasButton *m_quickButton;
    BasButton *m_campButton;
    BasButton *m_endlessButton;
    BusyDialog *m_loginingDialog;
    BusyDialog *m_registeringDialog;
    BusyDialog *m_queryRoutesDialog;
    BusyDialog *m_waitingResourceDialog;
    BasWidget *m_quitWidget;
protected:
    LoginRegDialog *m_loginDialog;
private:
    ServerInterface *m_serverIface;
private:
    std::string m_loginAccount;
    std::string m_loginPassword;
    int m_route;
private:
    CCUserDefault *m_userSettings;
protected:
    int m_tryIndex;
    std::vector<UiMsgEv::LoginInfo> m_loginInfos;
};

#endif
