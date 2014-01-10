#include "mainmenulayer.h"
#include "gamecore/resource/resourcemgr.h"
#include "gamecore/userdata/userdata.h"
#include "gamecore/sounds/soundmgr.h"
#include "uistatus.h"
#include "uistatusenum.h"
#include "gamecore/sys/syssetting.h"
#include "battle.net/hallscene.h"
#include "utils/nwutils.h"
#include "utils/sysutils.h"
#include "utils/fileutils.h"
#include "utils/ccutils.h"
#include "gamecore/gamecore/gameboard.h"
#include "standalone/endlessscene.h"

#include "unistd.h"
#include "network/common/netmessage.h"

MainMenuLayer::MainMenuLayer()
{
    m_bgWidget = 0;
    m_titleWidget = 0;
    m_settingWidget = 0;
    m_settingButton = 0;
    m_backButton = 0;
    m_swtichRouteLabel = 0;
    m_bgSprite = 0;
    m_enterAnim = 0;
    m_battleButton = 0;
    m_quickButton = 0;
    m_campButton = 0;
    m_endlessButton = 0;

    m_loginDialog = 0;
    m_loginingDialog = 0;
    m_registeringDialog = 0;
    m_queryRoutesDialog = 0;
    m_waitingResourceDialog = 0;
    m_quitWidget = 0;

    m_route = -1;

    m_gameWave = 0;
    m_treeBallWave = 0;

    //keypad listener
    setKeypadEnabled(true);
    SoundMgr::getInstance()->playSoundBg(SoundEnum::MAINMENU_BG_SOUND);

    m_serverIface = ServerInterface::getInstance();
    m_serverIface->setMainMenuEvCB(this,callfuncND_selector(MainMenuLayer::serverListener));

    std::string ip,version,device;
    int port;
    SysSetting *set = ResourceMgr::getInstance()->getSysSetting();
    set->getLoginSever(ip);
    port = set->getLoginPort();
    set->getDevice(device);
    set->getVersion(version);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ip = "192.168.1.148";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    //ip = "192.168.1.129";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#else
    ip = getLocalIp();
    ip = "137.175.69.65"; //usa server ip
#endif
    m_serverIface->setClientInfo(device,version);
    m_loginInfos.push_back(UiMsgEv::LoginInfo(ip,port));
    m_tryIndex = 0;

    m_userSettings = ResourceMgr::getInstance()->getUserDataMgr()->getInstance();
    m_route = m_userSettings->getIntegerForKey("defaultRoute", -1);
}
MainMenuLayer::~MainMenuLayer()
{

}
void MainMenuLayer::serverListener(CCNode *sender,void *type)
{
    NetEventPackage *netEvent = (NetEventPackage*)type;
    switch(netEvent->eventId()){
        case UiMsgHandler::UiEv_backToMainMenu:{
            m_bgWidget->resetTouchPriority();
            break;
        }
        case UiMsgHandler::UiEv_loginInfoBroadCast:{
            std::vector<UiMsgEv::LoginInfo> *logins = m_serverIface->getBroadCastLoginInfo();
            for(unsigned int i = 0;i < logins->size();i++){
                UiMsgEv::LoginInfo &info = logins->at(i);
                m_loginInfos.push_back(UiMsgEv::LoginInfo(info.m_ip,info.m_port));
            }
            tryConnectLoginInfo();
            break;
        }
        case UiMsgHandler::UiEv_allRoutesGot:{
            UiMsgEv::RouteServerMap &servers = m_serverIface->getAllRoutes().servers();
            UiMsgEv::RouteServerMap::iterator it = servers.begin();
            // got route info
            if (it != servers.end()) {
                // first time to got routes info,
                // or before choosed route not existing
                if (m_route == -1 || servers.find(m_route) == servers.end()) {
                    UiMsgEv::BnServerInfo& server = it->second;
                    m_route = server.m_route;
                }
            } else {
                m_route = -1;
            }
            m_userSettings->setIntegerForKey("defaultRoute",m_route);
            // update swich route label
            LangDef *lang = ResourceMgr::getInstance()->getLangDef();
            m_swtichRouteLabel->setLabelText(lang->getStringById(StringEnum::RouteCNTelecom + m_route));

            if (m_queryRoutesDialog != 0) {
                m_queryRoutesDialog->destory();
                m_queryRoutesDialog = 0;
            }
            break;
        }
        case UiMsgHandler::UiEv_gameServerFailed:{
            int no = netEvent->param3();
            onLoginGameServerFail(this, &no);
            break;
        }
        case UiMsgHandler::UiEv_loginFailed:{
            int no = netEvent->param3();
            onQueryLoginServerFail(this, &no);
            break;
        }
        case UiMsgHandler::UiEv_intoHall:{
            onIntoHall(this, 0);
            break;
        }
        case UiMsgHandler::UiEv_regFailed:{
            int no = netEvent->param3();
            onRegFail(this, &no);
            break;
        }
        default:{
            break;
        }
    }
}
void MainMenuLayer::keyBackClicked()
{
    UiStatusMgr *uiSt = ResourceMgr::getInstance()->getUiStatusMgr();
    int uist = uiSt->frontUiStatus();
    if(uist == UiStatusEnum::UiSt_mainmenusetting && m_settingWidget){
        SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
        m_settingWidget->moveOut();
        m_settingWidget->setBlockEvent(false);
        uiSt->popUiStatus();
        return;
    }
    if(m_quitWidget == 0){
        onBackClicked(m_backButton,0);
    }else{
        onQuitGameCancelClicked(m_quitWidget,0);
    }
}
void MainMenuLayer::keyMenuClicked()
{
    //we do not need this
    //onSettingClicked(0,0);
}
bool MainMenuLayer::init()
{
    bool ret = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        float wholescale = getWholeScaleRate();
        float scale = getAdaptResourceScale();
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCSprite *bgSprite = CCSprite::createWithSpriteFrameName("mainbg.jpg");
        bgSprite->getTexture()->setAntiAliasTexParameters();
        m_bgWidget = new BasNodeDelegateWidget(bgSprite,size);
        m_bgWidget->setAnchorPoint(ccp(0,0));
        m_bgWidget->setPosition(ccp(0,0));
        m_bgWidget->setWidth(size.width);
        m_bgWidget->setHeight(size.height);
        this->addChild(m_bgWidget);
        //game type button
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        if(1){
            CCSprite *ropeSprite = CCSprite::createWithSpriteFrameName("loginrope.png");
            CCSize ropeSize = ropeSprite->getContentSize();
            m_enterAnim = new BasWidget;
            m_enterAnim->setWidth(ropeSize.width );
            m_enterAnim->setHeight(ropeSize.height);

            m_battleButton = new BasButton;
            m_battleButton->setScaleRate(0.01);
            m_battleButton->setButtonInfo(lang->getStringById(StringEnum::BattleGame).data(),"fonts/uifont35.fnt","default","battlein",CCSizeMake(0,0));

            m_enterAnim->addChild(m_battleButton);
            m_battleButton->setHorizontal("parent",0.5);
            m_battleButton->setVertical("parent",0.528);
            m_battleButton->setClickCB(this,callfuncND_selector(MainMenuLayer::onBattleClicked));

            m_quickButton = new BasButton;
            m_quickButton->setScaleRate(0.01);
            m_quickButton->setButtonInfo(lang->getStringById(StringEnum::QuickGame).data(),"fonts/uifont35.fnt","default","quickin",CCSizeMake(0,0));

            m_enterAnim->addChild(m_quickButton);
            m_quickButton->setHorizontal("parent",0.5);
            m_quickButton->setVertical("parent",0.773);
            m_quickButton->setClickCB(this,callfuncND_selector(MainMenuLayer::onQuickClicked));

            m_endlessButton = new BasButton;
            m_endlessButton->setScaleRate(0.01);
            m_endlessButton->setButtonInfo(lang->getStringById(StringEnum::EndlessTask).data(),"fonts/uifont35.fnt","default","endlessin",CCSizeMake(0,0));

            m_enterAnim->addChild(m_endlessButton);
            m_endlessButton->setHorizontal("parent",0.5);
            m_endlessButton->setVertical("parent",1.02);
            m_endlessButton->setClickCB(this,callfuncND_selector(MainMenuLayer::onEndlessClicked));

            BasNodeDelegateWidget *ropeDele = new BasNodeDelegateWidget(ropeSprite);
            m_enterAnim->addChild(ropeDele);
            ropeDele->setCenterIn("parent");

            m_bgWidget->addChild(m_enterAnim);
            m_enterAnim->setHorizontal("parent",0.5);
            m_enterAnim->setTop("parent",uilib::Top);
            if(wholescale >= 1.0)
                m_enterAnim->setTopMargin(-90);
            else
                m_enterAnim->setTopMargin(-90 * (1 + wholescale));
        }
        if(1){//title bg
            float scale = getHorAdaptResourceScale();
            CCSprite *sprite = CCSprite::createWithSpriteFrameName("logintitle.png");
            CCSize titlesize = sprite->getContentSize();
            m_titleWidget = new BasNodeDelegateWidget(sprite,CCSizeMake(scale * titlesize.width,scale * titlesize.height));
            m_bgWidget->addChild(m_titleWidget);
            m_titleWidget->setHorizontal("parent",0.5);
            m_titleWidget->setTop("parent",uilib::Top);
        }
        if(1){
            m_settingWidget = new BorderWidget;
            m_settingWidget->setTheme("default","dialog");
            m_settingWidget->setVertical("parent",0.5);
            m_settingWidget->setLeft("parent",uilib::Left);
            m_settingWidget->setLeftMargin(-20);
            m_settingWidget->setMaxWidthRefSize("parent",0.6);
            m_settingWidget->setMaxHeightRefSize("parent",0.7);
            m_settingWidget->setMinHeightRefSize("parent",0.6);
            m_settingWidget->setCanTouch(false);
            m_settingWidget->setBlockEvent(false);
            m_settingWidget->setClickCB(this,callfuncND_selector(MainMenuLayer::onSettingWidgetClicked));
            m_settingWidget->setTouchPriority(uilib::TopPriority);

            m_bgWidget->addChild(m_settingWidget);
            BasNodeAction *settingWidgetMoveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
            settingWidgetMoveIn->setEaseType(uilib::EaseBackInOut);
            settingWidgetMoveIn->setMoveInType(uilib::HorizontalLeftIn);
            m_settingWidget->setMoveinAction(settingWidgetMoveIn);
            BasNodeAction *settingWidgetMoveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
            settingWidgetMoveOut->setEaseType(uilib::EaseBackInOut);
            settingWidgetMoveOut->setMoveOutType(uilib::HorizontalLeftOut);
            m_settingWidget->setMoveoutAction(settingWidgetMoveOut);

            LangDef *lang = ResourceMgr::getInstance()->getLangDef();
            VerticalLayout *layout = new VerticalLayout();
            CheckBox *checkbox;
            BasButton *button;

            checkbox = new CheckBox();
            checkbox->setCheckInfo(lang->getStringById(StringEnum::CloseBgMusic).data(),"fonts/uifont35.fnt","default","",CCSizeMake(300 * wholescale,60 * wholescale),ccWHITE);
            checkbox->setClickCB(this,callfuncND_selector(MainMenuLayer::onChangeBgMusicClicked));
            checkbox->setCheck(SoundMgr::getInstance()->isBgSoundOn());
            layout->addWidget(checkbox);

            checkbox = new CheckBox();
            checkbox->setCheckInfo(lang->getStringById(StringEnum::CloseGameMusic).data(),"fonts/uifont35.fnt","default","",CCSizeMake(300 * wholescale,60 * wholescale),ccWHITE);
            checkbox->setClickCB(this,callfuncND_selector(MainMenuLayer::onChangeGameMusicClicked));
            checkbox->setCheck(SoundMgr::getInstance()->isGameSoundOn());
            layout->addWidget(checkbox);

            button = new BasButton;
            button->setButtonInfo("","","",CCSizeMake(300 * wholescale,60 * wholescale));
            if(1){
                BorderWidget *bg = new BorderWidget;
                bg->setTheme("default","buttonred");
                button->addChild(bg);
                bg->setFill("parent");
                BasLabel *label = new BasLabel;
                label->setLabelInfo(lang->getStringById(StringEnum::CheckUpdate).data(),"fonts/uifont35.fnt","default","",CCSizeMake(0,0),ccWHITE);
                button->addChild(label);
                label->setCenterIn("parent");
            }
            button->setClickCB(this,callfuncND_selector(MainMenuLayer::onCheckUpdateClicked));
            layout->addWidget(button);

            button = new BasButton;
            button->setButtonInfo("","","",CCSizeMake(300 * wholescale,60 * wholescale));
            if(1){
                BorderWidget *bg = new BorderWidget;
                bg->setTheme("default","button");
                button->addChild(bg);
                bg->setFill("parent");
                BasLabel *label = new BasLabel;
                label->setLabelInfo(lang->getStringById(StringEnum::QuitGame).data(),"fonts/uifont35.fnt","default","",CCSizeMake(0,0),ccWHITE);
                button->addChild(label);
                label->setCenterIn("parent");
            }
            button->setClickCB(this,callfuncND_selector(MainMenuLayer::onQuitGameClicked));
            layout->addWidget(button);

            layout->setAveraged(true);
            layout->setTopMargin(100);
            layout->setBottomMargin(100);
            m_settingWidget->setLayout(layout);

            BasNodeAction *layoutAction = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
            layoutAction->setStartTime(0.1);
            layoutAction->setEaseType(uilib::EaseNone);
            layoutAction->setMoveInType(uilib::ScaleYIn);
            layout->setChildsAction(layoutAction);
        }
        if(1){
            // setting & return back button
            m_settingButton = new BasButton;
            m_settingButton->setButtonInfo("","default","uimainsetting",CCSizeMake(200 * scale,128 * scale));
            m_settingButton->setTouchPriority(uilib::HighPriority);
            m_bgWidget->addChild(m_settingButton);
            m_settingButton->setLeft("parent",uilib::Left);
            m_settingButton->setBottom("parent",uilib::Bottom);
            m_settingButton->setClickCB(this,callfuncND_selector(MainMenuLayer::onSettingClicked));

            m_backButton = new BasButton;
            m_backButton->setButtonInfo("","default","uimainback",CCSizeMake(200 * scale,128 * scale));
            m_backButton->setTouchPriority(uilib::HighPriority);
            m_bgWidget->addChild(m_backButton);
            m_backButton->setRight("parent",uilib::Right);
            m_backButton->setBottom("parent",uilib::Bottom);
            m_backButton->setClickCB(this,callfuncND_selector(MainMenuLayer::onBackClicked));
            if(1){
                BasNodeAction *settingButtonMoveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
                settingButtonMoveIn->setEaseType(uilib::EaseNone);
                settingButtonMoveIn->setMoveInType(uilib::ScaleIn);
                m_backButton->setMoveinAction(settingButtonMoveIn);
                m_settingButton->setMoveinAction(settingButtonMoveIn);
            }

            m_swtichRouteLabel = new BasLabel;
            m_swtichRouteLabel->setCanTouch(true);
            m_swtichRouteLabel->setLabelInfo(lang->getStringById(StringEnum::RouteCNTelecom + m_route),"default","",CCSizeMake(300,50),getSystemFont(),30,ccBLUE);
            m_swtichRouteLabel->setTouchPriority(uilib::HighPriority);
            m_bgWidget->addChild(m_swtichRouteLabel);
            m_swtichRouteLabel->setHorizontal("parent",0.5);
            m_swtichRouteLabel->setBottom("parent",uilib::Bottom);
            m_swtichRouteLabel->setClickCB(this,callfuncND_selector(MainMenuLayer::onSwitchRouteClicked));

            BasLabel *tipLabel = new BasLabel;
            tipLabel->setCanTouch(true);
            tipLabel->setLabelInfo(lang->getStringById(StringEnum::SwitchRoute),"default","",CCSizeMake(300,50),getSystemFont(),30,ccWHITE);
            m_bgWidget->addChild(tipLabel);
            tipLabel->setHorizontal("parent",0.5);
            tipLabel->setBottom(m_swtichRouteLabel->getName(),uilib::Top);
            tipLabel->setClickCB(this,callfuncND_selector(MainMenuLayer::onSwitchRouteClicked));
        }
        m_bgWidget->layout();
        if(m_settingWidget){
            m_settingWidget->moveOut();
        }
        if(m_enterAnim){
            m_enterAnim->setScale(size.height / 1280);
            CCPoint pos = m_enterAnim->getDestPoint();
            m_enterAnim->setPosition(ccp(pos.x,pos.y + 600));
            CCMoveTo *move = CCMoveTo::create(1.0,pos);
            CCEaseBackInOut *ease = new CCEaseBackInOut;
            ease->autorelease();
            ease->initWithAction(move);
            m_enterAnim->runAction(ease);
            CCActionInterval *wave = CCWaves::create(1,4,false,true,ccg(8,8),5 + rand() % 5);
            CCRepeatForever *r1 = CCRepeatForever::create(wave);
            m_enterAnim->runAction(r1);
        }
        ResourceMgr::getInstance()->getUiStatusMgr()->pushUiStatus(UiStatusEnum::UiSt_mainmenuinit);

        // query routes from login server
        if (m_queryRoutesDialog == 0 && m_serverIface->getAllRoutes().servers().size() == 0) {
            LangDef *lang = ResourceMgr::getInstance()->getLangDef();
            m_queryRoutesDialog = new BusyDialog(this,ccc4(0,0,0,128));
            m_queryRoutesDialog->setBusyText(lang->getStringById(StringEnum::Loading));
            m_queryRoutesDialog->setAnimationName("uiloadinga");
            m_queryRoutesDialog->setLoadFinishedCB(this,callfuncN_selector(MainMenuLayer::onQueryRoutesStart));
            m_queryRoutesDialog->exec();
        }
        ret = true;
    }while(0);
    return ret;
}
void MainMenuLayer::tryConnectLoginInfo()
{
    if(m_tryIndex >= m_loginInfos.size()){
        //no more
        int no = EnumNetMessage::NetMessageId_timeout;
        onQueryLoginServerFail(this, &no);
    }else{
        UiMsgEv::LoginInfo &info = m_loginInfos[m_tryIndex];
        m_tryIndex++;
        m_serverIface->setLoginServerInfo(info.m_ip,info.m_port);
        m_serverIface->queryRouteList();
    }
}
void MainMenuLayer::onQueryRoutesStart(CCNode *sender)
{
    tryConnectLoginInfo();
}
void MainMenuLayer::onSettingWidgetClicked(CCNode *sender,void *data)
{
    m_settingWidget->setCanTouch(false);
    m_settingWidget->setBlockEvent(false);
    m_settingWidget->moveOut();
    UiStatusMgr *uiSt = ResourceMgr::getInstance()->getUiStatusMgr();
    uiSt->popUiStatus();
}
void MainMenuLayer::onSettingClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);

    if(m_settingWidget){
        m_settingWidget->setCanTouch(true);
        m_settingWidget->setBlockEvent(true);
        m_settingWidget->moveIn();
        ResourceMgr::getInstance()->getUiStatusMgr()->pushUiStatus(UiStatusEnum::UiSt_mainmenusetting);
    }
}
void MainMenuLayer::onBackClicked(CCNode *sender,void *data)
{
    UiStatusMgr *uiSt = ResourceMgr::getInstance()->getUiStatusMgr();
    int uist = uiSt->frontUiStatus();
    if(uist == UiStatusEnum::UiSt_null || uist == UiStatusEnum::UiSt_mainmenuinit){
        onQuitGameClicked(sender,data);
    }else if(uist == UiStatusEnum::UiSt_mainmenusetting && m_settingWidget){
        SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
        m_settingWidget->moveOut();
        m_settingWidget->setBlockEvent(false);
        uiSt->popUiStatus();
    } else {
        SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    }
}
void MainMenuLayer::onSwitchRouteClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);

    UiMsgEv::RouteServerMap &servers = m_serverIface->getAllRoutes().servers();
    UiMsgEv::RouteServerMap::iterator it = servers.find(m_route);
    // got game servers list
    if (it != servers.end()) {
        // loop to use next one route
        if (++it != servers.end()) {
            UiMsgEv::BnServerInfo& server = it->second;
            m_route = server.m_route;
        } else {
            it = servers.begin();
            UiMsgEv::BnServerInfo& server = it->second;
            m_route = server.m_route;
        }
        m_userSettings->setIntegerForKey("defaultRoute",m_route);
        // update swich route label
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        m_swtichRouteLabel->setLabelText(lang->getStringById(StringEnum::RouteCNTelecom + m_route));
    } else {
        // game servers list still empty, try to re-query login server
        if (m_queryRoutesDialog == 0) {
            LangDef *lang = ResourceMgr::getInstance()->getLangDef();
            m_queryRoutesDialog = new BusyDialog(this,ccc4(0,0,0,128));
            m_queryRoutesDialog->setBusyText(lang->getStringById(StringEnum::Loading));
            m_queryRoutesDialog->setAnimationName("uiloadinga");
            m_queryRoutesDialog->setLoadFinishedCB(this,callfuncN_selector(MainMenuLayer::onQueryRoutesStart));
            m_queryRoutesDialog->exec();
        }
    }
}
void MainMenuLayer::onBattleClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    startGameTypeClickAnim();
    if(m_loginDialog == 0){
        m_loginDialog = new LoginRegDialog(this,ccc4(0,0,0,128));
        m_loginDialog->setCancelClickListener(this,callfuncND_selector(MainMenuLayer::onCancelLoginDialogClicked));
        m_loginDialog->setLoginClickListener(this,callfuncND_selector(MainMenuLayer::onLoginDialogLoginClicked));
        m_loginDialog->setRegClickListener(this,callfuncND_selector(MainMenuLayer::onLoginDialogRegClicked));
        m_loginDialog->setDialogEnabled(true);
        m_loginDialog->exec();
    }else{
        m_loginDialog->setDialogEnabled(true);
        m_loginDialog->moveIn();
    }
    ResourceMgr::getInstance()->getUiStatusMgr()->pushUiStatus(UiStatusEnum::UiSt_showlogindialog);
}
void MainMenuLayer::onQuickClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    startGameTypeClickAnim();
    if(m_loginingDialog == 0){
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        m_loginingDialog = new BusyDialog(this,ccc4(0,0,0,128));
        m_loginingDialog->setBusyText(lang->getStringById(StringEnum::Logining));
        m_loginingDialog->setAnimationName("uiloadinga");
    }
    m_loginingDialog->setLoadFinishedCB(this,callfuncN_selector(MainMenuLayer::onQuickStart));
    m_loginingDialog->exec();
}
void MainMenuLayer::onQuickStart(CCNode *sender)
{
    // prefer to use latest login session
    UiMsgEv::AccountInfoEv *accountInfo = m_serverIface->getLatestLoginedInfo();
    if(!accountInfo->m_id.empty()) {
        m_serverIface->setLoginUser(accountInfo->m_id,"","",accountInfo->m_password,m_route);
        m_serverIface->loginInto();
    } else {
        // clear all cached account info and register a guest
        m_serverIface->setRegisterUser("","","","",m_route);
        m_serverIface->registerInto();
    }
}
void MainMenuLayer::startGameTypeClickAnim()
{
    CCPoint dest = m_enterAnim->getDestPoint();
    CCMoveTo *m1 = CCMoveTo::create(0.1,ccp(dest.x,dest.y + 20));
    CCMoveTo *m2 = CCMoveTo::create(0.8,dest);
    CCActionInterval *action = (CCActionInterval*)CCSequence::create(m1,m2,0);
    CCEaseBackInOut *ease = CCEaseBackInOut::create(action);
    m_enterAnim->runAction(ease);
}
void MainMenuLayer::onGameWaveFinished(CCNode *sender,void *data)
{

}
void MainMenuLayer::onTreeBallWaveFinished(CCNode *sender,void *data)
{

}
void MainMenuLayer::onCampaignClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
}
void MainMenuLayer::onEndlessClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_serverIface->initEndlessMode();
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    m_waitingResourceDialog = new BusyDialog(this,ccc4(0,0,0,64));
    m_waitingResourceDialog->setBusyText(lang->getStringById(StringEnum::Loading));
    m_waitingResourceDialog->setAnimationName("uiloadinga");
    m_waitingResourceDialog->exec();
    this->schedule(schedule_selector(MainMenuLayer::onCheckResourceLoad),2);
}
void MainMenuLayer::onCheckResourceLoad(float dt)
{
    bool init = ResourceMgr::getInstance()->isInit();
    if(!init)
        return;
    this->unschedule(schedule_selector(MainMenuLayer::onCheckResourceLoad));
    if(m_waitingResourceDialog){
        m_waitingResourceDialog->destory();
        m_waitingResourceDialog = 0;
    }
    // stop bg music
    SoundMgr::getInstance()->stopSoundBg();
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f,EndlessScene::create()));
}
void MainMenuLayer::onChangeBgMusicClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);

    CheckBox *check = dynamic_cast<CheckBox*>(sender);
    if(check){
        SoundMgr::getInstance()->switchBgSoundOn(check->isCheck());
    }
}
void MainMenuLayer::onChangeGameMusicClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);

    CheckBox *check = dynamic_cast<CheckBox*>(sender);
    if(check){
        SoundMgr::getInstance()->switchGameSoundOn(check->isCheck());
    }
}
void MainMenuLayer::onSwitchAccountClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);

}
void MainMenuLayer::onCheckUpdateClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCApplication::sharedApplication()->openURL("https://itunes.apple.com/us/app/direct-fire/id769216316?ls=1&mt=8");
#endif
}
void MainMenuLayer::onQuitGameClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);

    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    QueryDialog *quitDialog = new QueryDialog(this,ccc4(0,0,0,128));
    quitDialog->setTouchPriority(m_settingWidget->touchPriority() - 1);
    quitDialog->enableButtons(true,false,true);
    quitDialog->setOkClickCB(this,callfuncND_selector(MainMenuLayer::onQuitGameOkClicked));
    quitDialog->setCancelClickCB(this,callfuncND_selector(MainMenuLayer::onQuitGameCancelClicked));
    quitDialog->setTextInfo(lang->getStringById(StringEnum::AskForQuitGame),getSystemFont(),35,ccWHITE);
    quitDialog->exec();
    m_quitWidget = quitDialog;
}
void MainMenuLayer::onQuitGameOkClicked(CCNode *sender,void *data)
{
    QueryDialog *query = dynamic_cast<QueryDialog*>(sender);
    if(query){
        BasNodeAction *moveout = query->getMoveoutAction();
        if(moveout){
            moveout->setFinishCB(this,callfuncN_selector(MainMenuLayer::onQuitGameOkActionFinished),sender);
            query->moveOut();
        }else{
            onQuitGameOkActionFinished(sender);
        }
    }
}
void MainMenuLayer::onQuitGameCancelClicked(CCNode *sender,void *data)
{
    m_quitWidget = 0;
    QueryDialog *query = dynamic_cast<QueryDialog*>(sender);
    if(query){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        query->close();
#else
        BasNodeAction *moveout = query->getMoveoutAction();
        if(moveout){
            moveout->setFinishCB(this,callfuncN_selector(MainMenuLayer::onQuitGameCancelActionFinished),sender);
            query->moveOut();
        }else{
            onQuitGameCancelActionFinished(sender);
        }
#endif
    }
}
void MainMenuLayer::onQuitGameOkActionFinished(CCNode *sender)
{
    m_userSettings->flush();
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void MainMenuLayer::onQuitGameCancelActionFinished(CCNode *sender)
{
    QueryDialog *query = dynamic_cast<QueryDialog*>(sender);
    if(query == 0)
        return;
    delete query;
}
void MainMenuLayer::startCheckUpdate()
{

}
void MainMenuLayer::stopCheckUpdate()
{

}
void MainMenuLayer::onLoginSuccess(CCNode *sender,void *data)
{

}
void MainMenuLayer::onQueryLoginServerFail(CCNode *sender,void *data)
{
    if(m_queryRoutesDialog != 0){
        m_queryRoutesDialog->destory();
        m_queryRoutesDialog = 0;
    }
    m_route = -1;
    m_userSettings->setIntegerForKey("defaultRoute",m_route);
    LangDef *localLang = ResourceMgr::getInstance()->getLangDef();
    m_swtichRouteLabel->setLabelText(localLang->getStringById(StringEnum::RouteCNTelecom + m_route));
    int no = *(int*)data;
    LangDef *netLang = ResourceMgr::getInstance()->getNetLangDef();
    new SplashMessageWidget(m_bgWidget,netLang->getStringById(no));
}
void MainMenuLayer::onLoginGameServerFail(CCNode *sender,void *data)
{
    int no = *(int*)data;
    if(m_loginingDialog != 0){
        m_loginingDialog->destory();
        m_loginingDialog = 0;
    }
    LangDef *lang = ResourceMgr::getInstance()->getNetLangDef();
    new SplashMessageWidget(m_bgWidget,lang->getStringById(no));
}

void MainMenuLayer::onConGameServerSuccess(CCNode *sender,void *data)
{
}
void MainMenuLayer::onConGameServerFail(CCNode *sender,void *data)
{
    int no = *(int*)data;
    if(no == EnumNetMessage::NetMessageId_bngs_rejected_isonline && m_serverIface->isTryFirstTimes()) {
        // user is online, wait for 200ms and retry twice.
        usleep(200 * 1000);
        m_serverIface->loginInto();
        m_serverIface->setTryFirstTimes(false);
        return;
    }

    if(m_loginingDialog != 0){
        m_loginingDialog->destory();
        m_loginingDialog = 0;
    }

    if (no == EnumNetMessage::NetMessageId_wrong_client_version) {
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        QueryDialog *quitDialog = new QueryDialog(this,ccc4(0,0,0,128));
        quitDialog->setTouchPriority(m_settingWidget->touchPriority() - 1);
        quitDialog->enableButtons(true,false,true);
        quitDialog->setOkClickCB(this,callfuncND_selector(MainMenuLayer::onUpdateOkClicked));
        quitDialog->setCancelClickCB(this,callfuncND_selector(MainMenuLayer::onUpdateCancelClicked));
        quitDialog->setTextInfo(lang->getStringById(StringEnum::AskForUpdateVersion));
        quitDialog->exec();
    } else {
        LangDef *lang = ResourceMgr::getInstance()->getNetLangDef();
        new SplashMessageWidget(m_bgWidget,lang->getStringById(no));
    }
}
void MainMenuLayer::onUpdateOkClicked(CCNode *sender,void *data)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCApplication::sharedApplication()->openURL("http://itunes.apple.com/app/tap-tap-revenge-3/id326916014?mt=8");
#endif
    QueryDialog *query = dynamic_cast<QueryDialog*>(sender);
    if (query)
        query->close();
}
void MainMenuLayer::onUpdateCancelClicked(CCNode *sender,void *data)
{
    QueryDialog *query = dynamic_cast<QueryDialog*>(sender);
    if (query)
        query->close();
}
void MainMenuLayer::onRegSuccess(CCNode *sender,void *data)
{

}
void MainMenuLayer::onRegFail(CCNode *sender,void *data)
{
    int no = *(int*)data;
    if(m_registeringDialog != 0){
        m_registeringDialog->destory();
        m_registeringDialog = 0;
    }

    if(m_loginingDialog != 0){
        m_loginingDialog->destory();
        m_loginingDialog = 0;
    }

    if (no == EnumNetMessage::NetMessageId_wrong_client_version) {
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        QueryDialog *quitDialog = new QueryDialog(this,ccc4(0,0,0,128));
        quitDialog->setTouchPriority(m_settingWidget->touchPriority() - 1);
        quitDialog->enableButtons(true,false,true);
        quitDialog->setOkClickCB(this,callfuncND_selector(MainMenuLayer::onUpdateOkClicked));
        quitDialog->setCancelClickCB(this,callfuncND_selector(MainMenuLayer::onUpdateCancelClicked));
        quitDialog->setTextInfo(lang->getStringById(StringEnum::AskForUpdateVersion));
        quitDialog->exec();
    } else {
        LangDef *lang = ResourceMgr::getInstance()->getNetLangDef();
        new SplashMessageWidget(m_bgWidget,lang->getStringById(no));
    }
}
void MainMenuLayer::onIntoHall(CCNode *sender,void *data)
{
    if(m_loginDialog != 0)
    {
        m_loginDialog->destroy();
        m_loginDialog = 0;
    }

    if(m_loginingDialog != 0){
        m_loginingDialog->destory();
        m_loginingDialog = 0;
    }
    if(m_registeringDialog != 0){
        m_registeringDialog->destory();
        m_registeringDialog = 0;
    }

    // stop bg music
    SoundMgr::getInstance()->stopSoundBg();

    //switch to hallscene page
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.2f,HallScene::create()));
}
void MainMenuLayer::onCancelLoginDialogClicked(CCNode *sender,void *data)
{
    LoginRegDialog *login = dynamic_cast<LoginRegDialog*>(sender);

    if(login){
        BasNodeAction *action = login->getMoveoutAction();
        if(action){
            action->setFinishCB(this,callfuncN_selector(MainMenuLayer::onCancelLoginDialogActionFinished),sender);
            login->moveOut();
        }else{
            login->setDialogEnabled(false);
        }
    }
}
void MainMenuLayer::onCancelLoginDialogActionFinished(CCNode *sender)
{
    LoginRegDialog *login = dynamic_cast<LoginRegDialog*>(sender);
    if(login){
        login->setDialogEnabled(false);
    }
    ResourceMgr::getInstance()->getUiStatusMgr()->popUiStatus();
}
void MainMenuLayer::onLoginDialogLoginClicked(CCNode *sender,void *data)
{
    LoginRegDialog *login = dynamic_cast<LoginRegDialog*>(sender);
    if(login){
        m_loginDialog->getLoginInfo(m_loginAccount,m_loginPassword);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
        m_loginAccount = "a@qq.com";
        m_loginPassword = "13579";
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

        if(m_loginAccount.size() == 1){
            m_loginAccount = "a@qq.com";
            m_loginPassword = "13579";
        }else if(m_loginAccount.size() == 2){
            m_loginAccount = "t@qq.com";
            m_loginPassword = "13579";
        }
#endif
        if(m_loginAccount.empty() || m_loginPassword.empty())
            return;
        if(m_loginingDialog == 0){
            LangDef *lang = ResourceMgr::getInstance()->getLangDef();
            m_loginingDialog = new BusyDialog(this,ccc4(0,0,0,128));
            m_loginingDialog->setBusyText(lang->getStringById(StringEnum::Logining));
            m_loginingDialog->setAnimationName("uiloadinga");
        }
        if(m_loginDialog != 0)
        {
            m_loginDialog->destroy();
            m_loginDialog = 0;
        }
        m_loginingDialog->setLoadFinishedCB(this,callfuncN_selector(MainMenuLayer::onLoginDialogLoginStart));
        m_loginingDialog->exec();
    }
}
void MainMenuLayer::onLoginDialogLoginStart(CCNode *sender)
{
    if(isMailAddress(m_loginAccount))
        m_serverIface->setLoginUser("",m_loginAccount,"",m_loginPassword,m_route);
    else
        m_serverIface->setLoginUser(m_loginAccount,"","",m_loginPassword,m_route);
    m_serverIface->loginInto();
}
void MainMenuLayer::onLoginDialogRegClicked(CCNode *sender,void *data)
{
    LoginRegDialog *login = dynamic_cast<LoginRegDialog*>(sender);
    if(login){
        m_loginDialog->getRegInfo(m_loginAccount,m_loginPassword);
        if(m_loginAccount.empty() || m_loginPassword.empty())
            return;
        if(!isMailAddress(m_loginAccount)){
            LangDef *lang = ResourceMgr::getInstance()->getLangDef();
            new SplashMessageWidget(m_loginDialog,lang->getStringById(StringEnum::NeedMailAccount));
            return;
        }
        if(m_registeringDialog == 0){
            LangDef *lang = ResourceMgr::getInstance()->getLangDef();
            m_registeringDialog = new BusyDialog(this,ccc4(0,0,0,128));
            m_registeringDialog->setBusyText(lang->getStringById(StringEnum::Registering));
            m_registeringDialog->setAnimationName("uiloadinga");
        }
        if(m_loginDialog != 0)
        {
            m_loginDialog->destroy();
            m_loginDialog = 0;
        }
        m_registeringDialog->setLoadFinishedCB(this,callfuncN_selector(MainMenuLayer::onLoginDialogRegStart));
        m_registeringDialog->exec();
    }
}
void MainMenuLayer::onLoginDialogRegStart(CCNode *sender)
{
    m_serverIface->setRegisterUser("",m_loginAccount,"",m_loginPassword,m_route);
    m_serverIface->registerInto();
}
