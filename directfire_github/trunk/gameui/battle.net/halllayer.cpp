#include "halllayer.h"
#include "hallmainwidget.h"
#include "usershow.h"
#include "hallpage.h"
#include "gamepage.h"
#include "shoppage.h"
#include "friendspage.h"
#include "herospage.h"
#include "syspage.h"
#include "giftwidget.h"
#include "okdialog.h"
#include "gameui/menuscene.h"
#include "gamecore/sounds/soundmgr.h"

#include "cliententry/uimsgevent.h"
#include "cliententry/uimsghandler.h"
#include "prop/propdef.h"

#include "utils/ccutils.h"

#include "roomscene.h"

#include "invitetoroomdialog.h"
#include "network/common/netmessage.h"

HallLayer::HallLayer()
{
    m_mainWidget = 0;
    m_baseWidget = 0;
    m_userShow = 0;
    m_notifyWidget = 0;
    m_serverIface = ServerInterface::getInstance();
    m_serverIface->setHallEvCB(this,callfuncND_selector(HallLayer::serverListener));
    m_waitingDialog = 0;
    m_quitDialog = 0;
    setKeypadEnabled(true);
}
HallLayer::~HallLayer()
{

}
bool HallLayer::init()
{
    bool ret = false;
    float srate = getAdaptResourceScale();
    float hrate = getHorAdaptResourceScale();
    do {
        CC_BREAK_IF(!CCLayer::init());
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSprite *bgSprite = CCSprite::createWithSpriteFrameName("hallbg.jpg");
        m_baseWidget = new BasNodeDelegateWidget(bgSprite,winSize);
        m_baseWidget->setWidth(winSize.width);
        m_baseWidget->setHeight(winSize.height);
        m_baseWidget->setAnchorPoint(ccp(0,0));
        m_baseWidget->setPosition(ccp(0,0));
        this->addChild(m_baseWidget);

        CCSprite *userBgSprite = CCSprite::createWithSpriteFrameName("userbg.png");
        CCSize userBgSize = userBgSprite->getContentSize();
        BasNodeDelegateWidget *userBgDele = new BasNodeDelegateWidget(userBgSprite,CCSizeMake(userBgSize.width * hrate,userBgSize.height * hrate));
        m_userShow = new UserShow(m_baseWidget);
        m_userShow->setLeft("parent",uilib::Left);
        m_userShow->setRight("parent",uilib::Right);
        m_userShow->setTop("parent",uilib::Top);
        m_userShow->setHeight(userBgSize.height * hrate);
        m_userShow->addChild(userBgDele);
        userBgDele->setCenterIn("parent");
        m_userShow->finish();

        m_mainWidget = new HallMainWidget;
        m_baseWidget->addChild(m_mainWidget);
        m_mainWidget->setLeft("parent",uilib::Left);
        m_mainWidget->setRight("parent",uilib::Right);
        m_mainWidget->setTop(m_userShow->getName(),uilib::Bottom);
        m_mainWidget->setBottom("parent",uilib::Bottom);

        HallMainWidget::HallPageDef *page;
        //add hall page
        page = new HallMainWidget::HallPageDef;
        page->m_img = "hallicon";
        page->m_pressedImg = "";
        page->m_page = new HallPage(0);
        m_mainWidget->addPage(page);
        //add game page
        page = new HallMainWidget::HallPageDef;
        page->m_img = "gameicon";
        page->m_pressedImg = "";
        page->m_page = new GamePage(0);
        m_mainWidget->addPage(page);
        //add friends page
        page = new HallMainWidget::HallPageDef;
        page->m_img = "friendicon";
        page->m_pressedImg = "";
        page->m_page = new FriendsPage(0);
        m_mainWidget->addPage(page);
        //add heros page
        page = new HallMainWidget::HallPageDef;
        page->m_img = "herosicon";
        page->m_pressedImg = "";
        page->m_page = new HerosPage(0);
        m_mainWidget->addPage(page);
        //add page finish

        m_mainWidget->finish();

        m_baseWidget->layout();
        startWaitServerInfo();
        ret = true;
    }while(0);
    return ret;
}
void HallLayer::serverListener(CCNode *sender,void *type)
{
    NetEventPackage *netEvent = (NetEventPackage*)type;
    switch(netEvent->eventId()){
    case UiMsgHandler::UiEv_netStatusChanged:{
        onNetChangedInHall(this, 0);
        break;
    }
    case UiMsgHandler::UiEv_gameServerFailed:{
        int no = netEvent->param3();
        onConGameServerFail(this, &no);
        break;
    }
    case UiMsgHandler::UiEv_playerInfoGot:{
        UiMsgEv::PlayerInfoEv *ev = (UiMsgEv::PlayerInfoEv*)netEvent->param1();
        if(!m_serverIface->isInHall())
            break;
        if(m_uid.empty() || ev->m_userId == m_uid){
            //the info is for me
            m_uid = ev->m_userId;
            m_mail = ev->m_userMail;
            m_nickName = ev->m_nickName;
            m_userShow->setAccountId(ev->m_userId);
            if(!ev->m_nickName.empty())
                m_userShow->setNickName(ev->m_nickName);
            else if(!ev->m_userMail.empty())
                m_userShow->setNickName(ev->m_userMail);
            int expstart,expend;
            m_serverIface->getLevelExpInfo(ev->m_level,expstart,expend);
            m_userShow->setLevelExp(ev->m_level,ev->m_exp,expstart,expend);
            std::string *data;
            if(m_serverIface->getHeadPortrait(m_uid,&data)){
                m_userShow->portraitUpdated(data);
            }
            m_userShow->upThumbFoot(ev->m_thumb,ev->m_foot);
            endWaiting();
        }else{
            //the info is for others
            cout << "get info of id=" << ev->m_userId << endl;
        }
        break;
    }
    case UiMsgHandler::UiEv_portraitGot:{
        UiMsgEv::AccountInfoEv *ev = (UiMsgEv::AccountInfoEv*)netEvent->param1();
        if(ev){
            if(ev->m_id == m_uid){
                //this is for me
                std::string *data;
                if(m_serverIface->getHeadPortrait(m_uid,&data)){
                    m_userShow->portraitUpdated(data);
                }
            }else{
                //this is for others
                FriendsPage *page = dynamic_cast<FriendsPage *>(m_mainWidget->getPageByIndex(2));
                if(page){
                    std::string *data;
                    if(m_serverIface->getHeadPortrait(ev->m_id,&data)){
                        page->updateFriendPortrait(ev->m_id,*data);
                    }
                }
            }
        }
        break;
    }
    case UiMsgHandler::UiEv_thumbPortraitGot:{
        HallPage *page = dynamic_cast<HallPage*>(m_mainWidget->getPageByIndex(0));
        if(page){
            page->thumbPortraitUpdate();
        }
        break;
    }
    case UiMsgHandler::UiEv_allPropsGot:{
        string evUid;
        if (netEvent->param1() == 0) {
            evUid = netEvent->param4();
        } else {
            UiMsgEv::SocialPropEv *ev = (UiMsgEv::SocialPropEv*)netEvent->param1();
            evUid = ev->m_uid;
        }
        if(evUid == m_uid){
            //this is for myself
            int num = m_serverIface->getPropNumByUid(m_uid,PropDef::Props_Coin);
            if(num >= 0)
                m_userShow->setUserPropNum(PropDef::Props_Coin,num);
            num = m_serverIface->getPropNumByUid(m_uid,PropDef::Props_Gold);
            if(num >= 0)
                m_userShow->setUserPropNum(PropDef::Props_Gold,num);

            num = m_serverIface->getPropNumByUid(m_uid,PropDef::Props_Rose);
            if(num >= 0)
                m_userShow->setUserPropNum(PropDef::Props_Rose,num);
            num = m_serverIface->getPropNumByUid(m_uid,PropDef::Props_Clover);
            if(num >= 0)
                m_userShow->setUserPropNum(PropDef::Props_Clover,num);
            num = m_serverIface->getPropNumByUid(m_uid,PropDef::Props_Staff);
            if(num >= 0)
                m_userShow->setUserPropNum(PropDef::Props_Staff,num);
        }else{
            //this is for myfriend
            FriendsPage *page = dynamic_cast<FriendsPage*>(m_mainWidget->getPageByIndex(2));
            if(page){
                page->updateFriendProp(evUid);
            }
        }
        break;
    }
    case UiMsgHandler::UiEv_usePropReply:{
        HallPage *page = dynamic_cast<HallPage*>(m_mainWidget->getPageByIndex(0));
        if(page){
            page->usePropReplyGot();
        }
        break;
    }
    case UiMsgHandler::UiEv_hallChatGot:{
        HallPage *page = dynamic_cast<HallPage*>(m_mainWidget->getPageByIndex(0));
        if(page){
            page->hallChatInfoGot();
        }
        break;
    }
    case UiMsgHandler::UiEv_onlineFriendGot:{
        //online friend got
        FriendsPage *page = dynamic_cast<FriendsPage *>(m_mainWidget->getPageByIndex(2));
        if(page){
            page->updateOnlineFriend();
        }
        break;
    }
    case UiMsgHandler::UiEv_playerRankInfoGot:{
        HerosPage *page = dynamic_cast<HerosPage *>(m_mainWidget->getPageByIndex(3));
        if(page){
            page->updateUserInfo();
        }
        break;
    }
    case UiMsgHandler::UiEv_startGetHerosInfo:{
        HerosPage *page = dynamic_cast<HerosPage *>(m_mainWidget->getPageByIndex(3));
        if(page){
            page->startGetHerosInfo();
        }
        break;
    }
    case UiMsgHandler::UiEv_endGetHerosInfo:{
        HerosPage *page = dynamic_cast<HerosPage *>(m_mainWidget->getPageByIndex(3));
        if(page){
            page->endGetHerosInfo();
        }
        break;
    }
    case UiMsgHandler::UiEv_herosInfoGot:{
        //heros sort info got
        HerosPage *page = dynamic_cast<HerosPage *>(m_mainWidget->getPageByIndex(3));
        if(page){
            page->updateHeroInfo();
        }
        break;
    }
    case UiMsgHandler::UiEv_unreadMailGot:{
        HallPage *page = dynamic_cast<HallPage*>(m_mainWidget->getPageByIndex(0));
        if(page)
            page->mailUpdate();
        break;
    }
    case UiMsgHandler::UiEv_askAsFriendGot:{
        HallPage *page = dynamic_cast<HallPage*>(m_mainWidget->getPageByIndex(0));
        if(page)
            page->askFriendUpdate();
        break;
    }
    case UiMsgHandler::UiEv_askFriendAccepted:
    case UiMsgHandler::UiEv_acceptFriendReply:{
        FriendsPage *page = dynamic_cast<FriendsPage *>(m_mainWidget->getPageByIndex(2));
        if(page && page->hasInit()){
            std::string fid;
            while(m_serverIface->getAskFriendAccept(fid))
                page->addFriend(fid);
            page->relayScroll();
        }
        break;
    }
    case UiMsgHandler::UiEv_rejectFriendReply:{
        break;
    }
    case UiMsgHandler::UiEv_askFriendRejected:{
        break;
    }
    case UiMsgHandler::UiEv_validTaskGot:{
        HallPage *page = dynamic_cast<HallPage*>(m_mainWidget->getPageByIndex(0));
        if(page)
            page->taskUpdate();
        break;
    }
    case UiMsgHandler::UiEv_inviteToGameGot:{
        InviteToRoomDialog *dialog = new InviteToRoomDialog(this,ccc4(0,0,0,128));
        UiMsgEv::AccountInfoEv *ev = (UiMsgEv::AccountInfoEv*)netEvent->param1();
        dialog->setInviter(ev->m_id,ev->m_mail,ev->m_name);
        dialog->exec();
        break;
    }
    case UiMsgHandler::UiEv_ServerNoticeGot:{
        LabelMessageDialog *msg = new LabelMessageDialog(this);
        msg->setOnClosed(this, callfuncN_selector(HallLayer::onSystemNoticeClosed));
        msg->setSpacing(5);
        float w = msg->getWidth() * 0.8;
        bool need = false;
        for(;1;){
            std::string title,body;
            title.clear();
            body.clear();
            if(!m_serverIface->getSystemNotice(title,body))
                break;
            need = true;
            if(title.empty()) title = ".";
            CCLabelTTF *label = CCLabelTTF::create(title.data(),getSystemFont(),30,CCSizeMake(w,0),kCCTextAlignmentCenter);
            label->setColor(ccWHITE);
            FSizeLabelDelegate *delegate = new FSizeLabelDelegate(label);
            msg->addFixedSizeWidget(delegate);
            label = CCLabelTTF::create(body.data(),getSystemFont(),30,CCSizeMake(w,0),kCCTextAlignmentLeft);
            label->setColor(ccBLACK);
            delegate = new FSizeLabelDelegate(label);
            msg->addFixedSizeWidget(delegate);
        }
        if(!need){
            delete msg;
            return;
        }
        msg->exec();
        m_notifyWidget = msg;
        msg->setAnchorPoint(ccp(0.5,0.5));
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        msg->setPosition(ccp(size.width / 2,size.height / 2));
        break;
    }
    case UiMsgHandler::Uiev_giftGot:{
        HallPage *hallPage = dynamic_cast<HallPage*>(m_mainWidget->getPageByIndex(0));
        if(hallPage)
            hallPage->giftUpdate();
        break;
    }
    case UiMsgHandler::Uiev_giftChange:{
        //refresh some key Num
        int num;
        num = m_serverIface->getPropNumByUid(m_uid,PropDef::Props_Gold);
        if(num >= 0)
            m_userShow->setUserPropNum(PropDef::Props_Gold,num);

        num = m_serverIface->getPropNumByUid(m_uid,PropDef::Props_Rose);
        if(num >= 0)
            m_userShow->setUserPropNum(PropDef::Props_Rose,num);
        num = m_serverIface->getPropNumByUid(m_uid,PropDef::Props_Clover);
        if(num >= 0)
            m_userShow->setUserPropNum(PropDef::Props_Clover,num);
        num = m_serverIface->getPropNumByUid(m_uid,PropDef::Props_Staff);
        if(num >= 0)
            m_userShow->setUserPropNum(PropDef::Props_Staff,num);
        break;
    }
    case UiMsgHandler::Uiev_coinChange:{
        //refresh coin
        int num;
        num = m_serverIface->getPropNumByUid(m_uid,PropDef::Props_Coin);
        if(num >= 0)
            m_userShow->setUserPropNum(PropDef::Props_Coin,num);
        break;
    }
    case UiMsgHandler::UiEv_friendInfoGot:{
        //friend info got,do nothing here
        //,when user move into friend page,start the init
        break;
    }
    case UiMsgHandler::UiEv_startRefreshFriend:{
        FriendsPage *page = dynamic_cast<FriendsPage *>(m_mainWidget->getPageByIndex(2));
        if(page){
            page->startRefreshing();
        }
        break;
    }
    case UiMsgHandler::UiEv_endRefreshFriend:{
        FriendsPage *page = dynamic_cast<FriendsPage *>(m_mainWidget->getPageByIndex(2));
        if(page){
            page->endRefreshing();
        }
        break;
    }
    case UiMsgHandler::UiEv_startRefreshHallInfo:{
        GamePage *page = dynamic_cast<GamePage *>(m_mainWidget->getPageByIndex(1));
        if(page){
            page->startRefreshing();
        }
        break;
    }
    case UiMsgHandler::UiEv_endRefreshHallInfo:{
        GamePage *page = dynamic_cast<GamePage *>(m_mainWidget->getPageByIndex(1));
        if(page){
            page->endRefreshing();
        }
        break;
    }
    case UiMsgHandler::UiEv_hallRoomInfoGot:{
        GamePage *page = dynamic_cast<GamePage *>(m_mainWidget->getPageByIndex(1));
        if(page){
            page->resetHallInfo();
        }
        break;
    }
    case UiMsgHandler::UiEv_createRoomFailed:{
        endWaiting();
        int code = netEvent->param3();
        new SplashMessageWidget(m_baseWidget,ResourceMgr::getInstance()->getNetLangDef()->getStringById(code));
        break;
    }
    case UiMsgHandler::UiEv_createRoomSucc:{
        endWaiting();
        enterRoom();
        break;
    }
    case UiMsgHandler::UiEv_createRoomStart:{
        startWaitCreateRoom();
        break;
    }
    case UiMsgHandler::UiEv_quickGameStart:{
        startWaitQuickGame();
        break;
    }
    case UiMsgHandler::UiEv_startJoinRoom:{
        startWaitJoinRoom();
        break;
    }
    case UiMsgHandler::UiEv_joinRoomSucc:{
        endWaiting();
        enterRoom();
        break;
    }
    case UiMsgHandler::UiEv_joinRoomFailed:{
        endWaiting();
        int code = netEvent->param3();
        new SplashMessageWidget(m_baseWidget,ResourceMgr::getInstance()->getNetLangDef()->getStringById(code));
        break;
    }
    case UiMsgHandler::UiEv_joinRoomWaiting:{
        enableCancelWaitJoinRoom();
        break;
    }
    case UiMsgHandler::UiEv_cancelWaitingJoinSucc:{
        endWaiting();
        break;
    }
    case UiMsgHandler::UiEv_quitRoom:{
        CCDirector::sharedDirector()->popScene();
        // restore fps
        CCDirector::sharedDirector()->setAnimationInterval(1.0/30.0);
        m_baseWidget->resetTouchPriority();
        break;
    }
    case UiMsgHandler::UiEv_headSettingClosed:{
        int status = netEvent->param3();
        HallPage *hallPage = dynamic_cast<HallPage*>(m_mainWidget->getPageByIndex(0));
        hallPage->headSettingClosed(status);
        /* beta2 fix
        SysPage *sysPage = dynamic_cast<SysPage*>(m_mainWidget->getPageByIndex(5));
        if(sysPage)
            sysPage->headSettingClosed(status);
        break;
        */
    }
    default:{
        break;
    }
    }
}
void HallLayer::keyBackClicked()
{
    if(m_notifyWidget != 0){
        m_notifyWidget->close();
    }else if(m_userShow->onKeyPadBackClicked()){
    }else if(m_mainWidget->onKeyPadBackClicked()){
    }else{
        if(m_quitDialog == 0)
            onQuitGameClicked();
        else
            onQuitGameCancelClicked(m_quitDialog,0);
    }
}
void HallLayer::keyMenuClicked()
{
    //do nothing
}
void HallLayer::startWaitServerInfo()
{
    if(m_waitingDialog == 0){
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        m_waitingDialog = new BusyDialog(this,ccc4(0,0,0,0));
        m_waitingDialog->setBusyText(lang->getStringById(StringEnum::Loading));
        m_waitingDialog->setAnimationName("uiloadinga");
        m_waitingDialog->exec();
    }
}
void HallLayer::startWaitJoinRoom()
{
    if(m_waitingDialog == 0){
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        m_waitingDialog = new BusyDialog(this,ccc4(0,0,0,128));
        m_waitingDialog->setBusyText(lang->getStringById(StringEnum::JoiningGame));
        m_waitingDialog->setAnimationName("uiloadinga");
        m_waitingDialog->setCancelButton("Cancel");
        m_waitingDialog->setClickCallBack(this,callfuncND_selector(HallLayer::cancelWaitingJoinRoom));
        m_waitingDialog->setLoadFinishedCB(this,callfuncN_selector(HallLayer::onJoinRoomStart));
        m_waitingDialog->exec();
        m_waitingDialog->setCancelVisible(false);
    }
}
void HallLayer::onJoinRoomStart(CCNode* sender)
{
    m_serverIface->joinRoom();
}
void HallLayer::enableCancelWaitJoinRoom()
{
    if(m_waitingDialog != 0){
        m_waitingDialog->setCancelVisible(true);
    }
}
void HallLayer::enterRoom()
{
    //switch to roomscene page
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.2f,RoomScene::create()));
}
void HallLayer::cancelWaitingJoinRoom()
{
    m_serverIface->cancelWaitingJoinRoom();
}
void HallLayer::startWaitCreateRoom()
{
    if(m_waitingDialog == 0){
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        m_waitingDialog = new BusyDialog(this,ccc4(0,0,0,128));
        m_waitingDialog->setBusyText(lang->getStringById(StringEnum::CreatingGame));
        m_waitingDialog->setAnimationName("uiloadinga");
        m_waitingDialog->setLoadFinishedCB(this,callfuncN_selector(HallLayer::onCreateRoomStart));
        m_waitingDialog->exec();
    }
}
void HallLayer::onCreateRoomStart(CCNode* sender)
{
    m_serverIface->createRoom();
}
void HallLayer::enableCancelWaitCreateRoom()
{

}
void HallLayer::cancelWaitingCreateRoom()
{

}
void HallLayer::startWaitQuickGame()
{
    if(m_waitingDialog == 0){
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        m_waitingDialog = new BusyDialog(this,ccc4(0,0,0,128));
        m_waitingDialog->setBusyText(lang->getStringById(StringEnum::QuickingGame));
        m_waitingDialog->setAnimationName("uiloadinga");
        m_waitingDialog->setLoadFinishedCB(this,callfuncN_selector(HallLayer::onQuickGameStart));
        m_waitingDialog->exec();
    }
}
void HallLayer::onQuickGameStart(CCNode* sender)
{
    m_serverIface->quickGame();
}
void HallLayer::endWaiting()
{
    if(m_waitingDialog != 0){
        m_waitingDialog->destory();
        m_waitingDialog = 0;
    }
}
void HallLayer::onSystemNoticeClosed(CCNode *sender)
{
    m_notifyWidget = 0;
    if (m_nickName.empty() && m_userShow) {
        m_userShow->notifyResetUserInfo();
    }
}
void HallLayer::onQuitGameClicked()
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);

    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    m_quitDialog = new QueryDialog(this,ccc4(0,0,0,128));
    m_quitDialog->setTouchPriority(uilib::TopPriority - uilib::SafePriorityGap);
    m_quitDialog->enableButtons(true,false,true);
    m_quitDialog->setOkClickCB(this,callfuncND_selector(HallLayer::onQuitGameOkClicked));
    m_quitDialog->setCancelClickCB(this,callfuncND_selector(HallLayer::onQuitGameCancelClicked));
    m_quitDialog->setTextInfo(lang->getStringById(StringEnum::AskForQuitGame),getSystemFont(),35,ccWHITE);
    m_quitDialog->exec();
}
void HallLayer::onQuitGameOkClicked(CCNode *sender,void *data)
{
    QueryDialog *query = dynamic_cast<QueryDialog*>(sender);
    if(query){
        BasNodeAction *moveout = query->getMoveoutAction();
        if(moveout){
            moveout->setFinishCB(this,callfuncN_selector(HallLayer::onQuitGameOkActionFinished),sender);
            query->moveOut();
        }else{
            onQuitGameOkActionFinished(sender);
        }
    }
}
void HallLayer::onQuitGameCancelClicked(CCNode *sender,void *data)
{
    m_quitDialog = 0;
    QueryDialog *query = dynamic_cast<QueryDialog*>(sender);
    if(query){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        query->close();
#else
        BasNodeAction *moveout = query->getMoveoutAction();
        if(moveout){
            moveout->setFinishCB(this,callfuncN_selector(HallLayer::onQuitGameCancelActionFinished),sender);
            query->moveOut();
        }else{
            onQuitGameCancelActionFinished(sender);
        }
#endif
    }
}
void HallLayer::onQuitGameOkActionFinished(CCNode *sender)
{
    ResourceMgr::getInstance()->getUserDataMgr()->getInstance()->flush();
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void HallLayer::onQuitGameCancelActionFinished(CCNode *sender)
{
    QueryDialog *query = dynamic_cast<QueryDialog*>(sender);
    if(query == 0)
        return;
    delete query;
}
void HallLayer::onConGameServerSuccess(CCNode *sender,void *data)
{
}
void HallLayer::onConGameServerFail(CCNode *sender,void *data)
{
    popRoomSceneToHall();
    int errorNo = *(int*)data;
    if(errorNo == EnumNetMessage::NetMessageId_client_fire_disconnect_server) {
        // user logout, client fire disconnect with game server
        backMainMenuPageNoEffect();
    } else if(m_serverIface->isTryFirstTimes()) {
        m_serverIface->tryReLogin();
    } else {
        // quit login and back to main menu page
        backMainMenuPageWithDialog();
    }
}
void HallLayer::backMainMenuPageWithDialog()
{
    // display ok dialog, notify user network error
    OkDialog *dialog = new OkDialog(this,ccc4(0,0,0,128));
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    dialog->setDialogContent(lang->getStringById(StringEnum::CommWithServerFailed));
    dialog->setOnOkClickedCB(this,callfuncND_selector(HallLayer::onBackMainMenuOkClicked));;
    dialog->exec();
}
void HallLayer::onBackMainMenuOkClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    backMainMenuPageNoEffect();
}
void HallLayer::backMainMenuPageNoEffect()
{
    this->scheduleOnce(schedule_selector(HallLayer::doBackToMainMenu),0.5);
}
void HallLayer::onNetChangedInHall(CCNode *sender,void *data)
{
    popRoomSceneToHall();
    m_serverIface->disconnectGameServer();
}
void HallLayer::popRoomSceneToHall()
{
    if (m_serverIface->isInRoom() || m_serverIface->isInGame()) {
        CCDirector::sharedDirector()->popScene();
        m_baseWidget->resetTouchPriority();
        m_serverIface->netPosExitRoom();
    }
}
void HallLayer::doBackToMainMenu(float dt)
{
    m_serverIface->netPosExitServer();
    m_serverIface->setIsLogined(false);
    m_serverIface->backToMainMenu();
    CCDirector::sharedDirector()->popScene();
}

