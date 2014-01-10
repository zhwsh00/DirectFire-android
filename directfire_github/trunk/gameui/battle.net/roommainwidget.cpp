#include "roommainwidget.h"
#include "chatwidget.h"
#include "roomgameshow.h"
#include "roomroleshow.h"
#include "kickoutdialog.h"

#include "invitetoroomdialog.h"

#include "utils/sysutils.h"

#include "gamecore/sounds/soundmgr.h"

RoomMainWidget::RoomMainWidget()
{
    if(1){
        //init room bg
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSprite *bgSprite = CCSprite::createWithSpriteFrameName("hallbg.jpg");
        BasNodeDelegateWidget *bgWidget = new BasNodeDelegateWidget(bgSprite,winSize);
        this->addChild(bgWidget);
        bgWidget->setCenterIn("parent");
    }

    m_serverIFace = ServerInterface::getInstance();
    m_accountInfo = 0;
    m_roomInfo = 0;
    m_kickOutDialog = 0;

    m_serverIFace->setRoomEvCB(this,callfuncND_selector(RoomMainWidget::serverListener));
    m_chatWidget = new ChatWidget();
    m_roomGameShow = new RoomGameShow(this);
    m_roomRoleShow = new RoomRoleShow(this);
    this->addChild(m_roomRoleShow);
    this->addChild(m_roomGameShow);
    this->addChild(m_chatWidget);

    m_roomRoleShow->setLeft("parent",uilib::Left);
    m_roomRoleShow->setRight("parent",uilib::Right);
    m_roomRoleShow->setTop("parent",uilib::Top);
    m_roomRoleShow->setMaxHeightRefSize("parent",0.39);
    m_roomRoleShow->setMinHeightRefSize("parent",0.39);

    m_roomGameShow->setLeft("parent",uilib::Left);
    m_roomGameShow->setRight("parent",uilib::Right);
    m_roomGameShow->setTop(m_roomRoleShow->getName(),uilib::Bottom);
    m_roomGameShow->setMaxHeightRefSize("parent",0.21);
    m_roomGameShow->setMinHeightRefSize("parent",0.21);

    m_chatWidget->setLeft("parent",uilib::Left);
    m_chatWidget->setRight("parent",uilib::Right);
    m_chatWidget->setBottom("parent",uilib::Bottom);
    m_chatWidget->setBottom("parent",uilib::Bottom);
    m_chatWidget->setTop(m_roomGameShow->getName(),uilib::Bottom);

    m_roomGameShow->setQuitCB(this,callfuncND_selector(RoomMainWidget::onRoomQuitClicked));
    m_roomGameShow->setStartCB(this,callfuncND_selector(RoomMainWidget::onRoomStartClicked));

    if(1){
        //room link with roleshow
        CCSprite *link1 = CCSprite::createWithSpriteFrameName("roomlink.png");
        CCSprite *link2 = CCSprite::createWithSpriteFrameName("roomlink.png");
        BasNodeDelegateWidget *dele1 = new BasNodeDelegateWidget(link1);
        BasNodeDelegateWidget *dele2 = new BasNodeDelegateWidget(link2);
        this->addChild(dele1);
        this->addChild(dele2);
        dele1->setVertical(m_roomGameShow->getName(),0.0);
        dele1->setHorizontal("parent",0.05);
        dele2->setVertical(m_roomGameShow->getName(),0.0);
        dele2->setHorizontal("parent",0.95);
    }
}
RoomMainWidget::~RoomMainWidget()
{
    m_serverIFace->setRoomEvCB(0,0);
}
void RoomMainWidget::resetRoom()
{
    m_roomGameShow->reset();
}
void RoomMainWidget::serverListener(CCNode *sender,void *type)
{
    NetEventPackage *netEvent = (NetEventPackage*)type;
    switch(netEvent->eventId()){
    case UiMsgHandler::UiEv_roomChatGot:{
        this->schedule(schedule_selector(RoomMainWidget::chatInfoStep),1.0);
        break;
    }
    case UiMsgHandler::UiEv_otherJoinRoom:{
        m_roomRoleShow->otherJoined(netEvent->param3());
        if(m_roomInfo->m_hostIndex == m_roomInfo->m_userIndex){
            //is host,board spell num out
            m_serverIFace->requestChangeSpellNum("",m_roomGameShow->getSpellNum());
        }
        break;
    }
    case UiMsgHandler::UiEv_otherQuitRoom:{
        m_roomRoleShow->otherQuit(netEvent->param3());
        break;
    }
    case UiMsgHandler::UiEv_SeatIndexChanged:{
        m_roomRoleShow->seatIndexChanged(netEvent->param3());
        break;
    }
    case UiMsgHandler::UiEv_SeatIndexChangedError:{
        m_roomRoleShow->seatIndexChangedFail(netEvent->param3());
        break;
    }
    case UiMsgHandler::UiEv_SeatNumChanged:{
        m_roomRoleShow->seatNumChanged(netEvent->param3());
        break;
    }
    case UiMsgHandler::UiEv_SeatNumChangedError:{
        m_roomRoleShow->seatNumChangedFail(netEvent->param3());
        break;
    }
    case UiMsgHandler::UiEv_kickedByOther:{
        cout << "kick out by others" << endl;
        break;
    }
    case UiMsgHandler::UiEv_seatCloseed:{
        m_roomRoleShow->seatClosed(netEvent->param3());
        break;
    }
    case UiMsgHandler::UiEv_seatOpened:{
        m_roomRoleShow->seatOpened(netEvent->param3());
        break;
    }
    case UiMsgHandler::UiEv_tribeChanged:{
        m_roomRoleShow->tribeChanged(netEvent->param3());
        break;
    }
    case UiMsgHandler::UiEv_gameInit:{
        cout << "RoomMainWidget::serverListener,game init got" << endl;
        break;
    }
    case UiMsgHandler::UiEv_inviteToGameGot:{
        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        InviteToRoomDialog *dialog = new InviteToRoomDialog(root,ccc4(0,0,0,128));
        UiMsgEv::AccountInfoEv *ev = (UiMsgEv::AccountInfoEv*)netEvent->param1();
        dialog->setInviter(ev->m_id,ev->m_mail,ev->m_name);
        dialog->exec();
        break;
    }
    case UiMsgHandler::UiEv_spellNumChanged:{
        m_roomGameShow->updateSpellNum(netEvent->param3());
        break;
    }
    case UiMsgHandler::UiEv_needPropsSelected:{
        int num;
        std::vector<std::string> props;
        m_roomGameShow->getSpellSelected(num,props);
        m_serverIFace->setSelectedProps(num,props);
        break;
    }
    case UiMsgHandler::UiEv_roomUsePropGot:{
        UiMsgEv::RoomUsePropDef *useProp = (UiMsgEv::RoomUsePropDef*)netEvent->param1();
        if(useProp->m_type == PropDef::Props_Rose)
            m_roomRoleShow->priaseUser(useProp->m_sender,useProp->m_receiver);
        else if(useProp->m_type == PropDef::Props_Clover)
            m_roomRoleShow->sneerUser(useProp->m_sender,useProp->m_receiver);
        break;
    }
    case UiMsgHandler::UiEv_kickUserGot:{
        UiMsgEv::KickOutInfo *kick = (UiMsgEv::KickOutInfo*)netEvent->param1();
        std::string kname,oname;
        if(!kick->m_kickerNick.empty())
            kname = kick->m_kickerNick;
        else
            mailToNickName(kick->m_kickerMail,kname);
        if(!kick->m_outerNick.empty())
            oname = kick->m_outerNick;
        else
            mailToNickName(kick->m_outerMail,oname);
        if(kick->m_outerId == m_accountInfo->m_id){
            //kick out by other
            CCNode *root = this->getParent();
            m_kickOutDialog = new KickOutDialog(root,ccc4(0,0,0,128));
            std::string *head;
            if(m_serverIFace->getHeadPortrait(kick->m_kickerId,&head)){
                m_kickOutDialog->setKickerInfo(kname,head);
            }else{
                m_kickOutDialog->setKickerInfo(kname,0);
            }
            m_kickOutDialog->setCloseCB(this,callfuncND_selector(RoomMainWidget::onKickedOutCloseClicked));
            m_kickOutDialog->setOkCB(this,callfuncND_selector(RoomMainWidget::onKickedOutCloseClicked));
            m_kickOutDialog->exec();
        }else{
            //other's kick
            LangDef *lang = ResourceMgr::getInstance()->getLangDef();
            UiMsgEv::ChatInfo chat;
            chat.m_senderNickName = "sys";
            chat.m_chatType = UiMsgEv::MsgToRoomAll;
            chat.m_chatContent += kname;
            chat.m_chatContent += " ";
            chat.m_chatContent += lang->getStringById(StringEnum::RoomKickOut);
            chat.m_chatContent +=  " ";
            chat.m_chatContent += oname;
            chat.m_chatContent += "!";
            m_chatWidget->addChatInfo(&chat);
        }
        break;
    }
    case UiMsgHandler::UiEv_usePropReply:{
        //do nothing
        break;
    }
    default:{
        cout << "RoomMainWidget::serverListener,get unkown event type = " << netEvent->eventId() << endl;
        return;
    }
    }
}
void RoomMainWidget::intoRoom()
{
    m_accountInfo = m_serverIFace->getLoginAccountInfo();
    m_roomInfo = m_serverIFace->getRoomInfo();
    m_roomGameShow->setMapInfo(m_roomInfo->m_mapId,m_roomInfo->m_mapName,m_roomInfo->m_mapAbbrevName);
    if(m_chatWidget)
        m_chatWidget->setChaterInfo(m_accountInfo->m_id,m_accountInfo->m_mail,m_accountInfo->m_name);
    initRoom();
}
void RoomMainWidget::initRoom()
{
    m_roomRoleShow->init();
}
void RoomMainWidget::setChatTo(const std::string &id)
{
    for(unsigned int i = 0;i < m_roomInfo->m_playerInfo.size();i++){
        UiMsgEv::PlayerInfoEv *ev = m_roomInfo->m_playerInfo[i];
        if(ev->m_isValid && ev->m_userId == id){
            m_chatWidget->setRecInfo(ev->m_userId,ev->m_userMail,ev->m_nickName);
            std::string *head;
            if(m_serverIFace->getHeadPortrait(id,&head)){
                m_chatWidget->setRecHead(head);
            }
        }
    }
}
void RoomMainWidget::enableStartAfterSec(int sec)
{
    m_roomGameShow->enableStartAfterSec(sec);
}
void RoomMainWidget::setChatBoxVisible(bool visible)
{
    m_chatWidget->setChatBoxVisible(visible);
}
void RoomMainWidget::chatInfoStep(float dt)
{
    UiMsgEv::ChatInfo *chat = m_serverIFace->getRoomChatInfo();
    if(chat){
        m_chatWidget->addChatInfo(chat,0);
    }else{
        this->unschedule(schedule_selector(RoomMainWidget::chatInfoStep));
    }
}
void RoomMainWidget::onRoomQuitClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_serverIFace->quitRoom();
}
void RoomMainWidget::onRoomStartClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    bool can = m_roomRoleShow->canStartGame();
    if(!can){
        new SplashMessageWidget(this,ResourceMgr::getInstance()->getLangDef()->getStringById(StringEnum::AtLeastOneOpponent));
        return;
    }
    m_serverIFace->startRoomGame();
}
void RoomMainWidget::onKickedOutCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_serverIFace->leaveRoom();
    m_kickOutDialog->destroy();
    m_kickOutDialog = 0;
}
