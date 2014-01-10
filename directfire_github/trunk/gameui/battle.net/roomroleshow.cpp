#include "roomroleshow.h"
#include "roommainwidget.h"

#include "cliententry/cliententry.h"

#include "utils/sysutils.h"
#include "prop/propdef.h"

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"

#include "chatwidget.h"
#include "roomgameshow.h"

#include "gamedata/gametype.h"

#include "sendmsganim.h"

enum ButtonDef{
    KickPlayer,
    SneerPlayer,
    PraisePlayer,
    CloseSeat,
    OpenSeat,
    ChatTo,
    SendGift,
    SendMsg,
    AddFriend,
    ChangePos,
    AskAsFriend
};

class OnlineFriendsInviteDialog : public BasShowDialog
{
public:
    OnlineFriendsInviteDialog(RoomRoleShow *owner,CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~OnlineFriendsInviteDialog();
    virtual void exec();
public:
    void finish();
    void onFriendClicked(CCNode *node,void *data);
    void setListener(CCNode *listener,SEL_CallFuncND func);
    const std::string &getClickFriend(){ return m_selectName;}
public:
    RoomRoleShow *m_owner;
    HorScrollWidget *m_horScroll;
    std::string m_selectName;
    CCNode *m_listener;
    SEL_CallFuncND m_func;
};
OnlineFriendsInviteDialog::OnlineFriendsInviteDialog(RoomRoleShow *owner,CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_owner = owner;
    m_listener = 0;
    m_func = 0;
    m_edgeSize = 20;
}
OnlineFriendsInviteDialog::~OnlineFriendsInviteDialog()
{

}
void OnlineFriendsInviteDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void OnlineFriendsInviteDialog::finish()
{
    UiThemeDef *def = UiThemeMgrProxy::getInstance()->getThemeByName("");
    m_horScroll = new HorScrollWidget();
    m_horScroll->setVerticalScrollPolicy(uilib::ScrollShow_Never);
    m_horScroll->setHorizontalScrollPolicy(uilib::ScrollShow_Need);
    this->addChild(m_horScroll);
    m_horScroll->setHeight(200);
    m_horScroll->setSpacing(20);
    m_horScroll->setVertical("parent",0.5);
    m_horScroll->setLeft("parent",uilib::Left);
    m_horScroll->setRight("parent",uilib::Right);
    m_horScroll->setLeftMargin(m_edgeSize);
    m_horScroll->setRightMargin(m_edgeSize);

    int showNum;
    const std::vector<std::string> &ofs = m_owner->m_serverIFace->getOnlineFriends();
    showNum = ofs.size();
    float width = 160;
    float height = 160;
    CCSize size = CCSizeMake(width,height);
    if(showNum == 0){
        const std::vector<std::string> &fs = m_owner->m_serverIFace->getFriends();
        int num = fs.size();
        if(num > 50) num = 50;
        for(unsigned int i = 0;i < fs.size();i++){
            UiMsgEv::PlayerInfoEv *ev = m_owner->m_serverIFace->getPlayerInfoByUid(fs[i]);
            if(ev == 0)
                continue;
            std::string *headPort;
            FSizeNullDelegate *null = new FSizeNullDelegate(size);
            new FillTestWidget(null);
            null->setName(fs[i]);
            null->setCanTouch(true);
            null->setClickCB(this,callfuncND_selector(OnlineFriendsInviteDialog::onFriendClicked));
            m_horScroll->addFixedSizeWidget(null);
            if(m_owner->m_serverIFace->getHeadPortrait(fs[i],&headPort)){
                CCImage *img = new CCImage;
                img->initWithImageData((void*)headPort->c_str(),headPort->size(),
                                       CCImage::kFmtUnKnown);
                CCTexture2D *texture = new CCTexture2D;
                texture->initWithImage(img);
                delete img;
                CCSprite *sprite = CCSprite::createWithTexture(texture);
                BasNodeLimitWidget *dele = new BasNodeLimitWidget(sprite);
                null->addChild(dele);
                dele->setFill("parent");
            }else{
                std::string img;
                def->getNormalData()->getImg("portraitdefault",img);
                CCSprite *sprite = CCSprite::createWithSpriteFrameName(img.data());
                BasNodeLimitWidget *dele = new BasNodeLimitWidget(sprite);
                null->addChild(dele);
                dele->setFill("parent");
            }
            if(1){
                //name
                std::string name = ev->m_nickName;
                if(name.empty())
                    mailToNickName(ev->m_userMail,name);
                BasLabel *label = new BasLabel();
                label->setLabelInfo(name,"","");
                null->addChild(label);
                label->setHorizontal("parent",0.5);
                label->setTop("parent",uilib::Bottom);
            }
        }
    }else{
        for(unsigned int i = 0;i < ofs.size();i++){
            UiMsgEv::PlayerInfoEv *ev = m_owner->m_serverIFace->getPlayerInfoByUid(ofs[i]);
            if(ev == 0)
                continue;
            std::string *headPort;
            FSizeNullDelegate *null = new FSizeNullDelegate(size);
            null->setName(ofs[i]);
            null->setCanTouch(true);
            null->setClickCB(this,callfuncND_selector(OnlineFriendsInviteDialog::onFriendClicked));
            m_horScroll->addFixedSizeWidget(null);
            if(m_owner->m_serverIFace->getHeadPortrait(ofs[i],&headPort)){
                CCImage *img = new CCImage;
                img->initWithImageData((void*)headPort->c_str(),headPort->size(),
                                       CCImage::kFmtUnKnown);
                CCTexture2D *texture = new CCTexture2D;
                texture->initWithImage(img);
                delete img;
                CCSprite *sprite = CCSprite::createWithTexture(texture);
                BasNodeLimitWidget *dele = new BasNodeLimitWidget(sprite);
                null->addChild(dele);
                dele->setFill("parent");
            }else{
                std::string img;
                def->getNormalData()->getImg("portraitdefault",img);
                CCSprite *sprite = CCSprite::createWithSpriteFrameName(img.data());
                BasNodeLimitWidget *dele = new BasNodeLimitWidget(sprite);
                null->addChild(dele);
                dele->setFill("parent");
            }
            if(1){
                //online mark
                BasLabel *label = new BasLabel;
                label->setLabelInfo("","default","playerol",CCSizeMake(0,0));
                null->addChild(label);
                label->setTop("parent",uilib::Top);
                label->setRight("parent",uilib::Right);
            }
            if(1){
                //name
                std::string name = ev->m_nickName;
                if(name.empty())
                    mailToNickName(ev->m_userMail,name);
                BasLabel *label = new BasLabel();
                label->setLabelInfo(name,"","");
                null->addChild(label);
                label->setHorizontal("parent",0.5);
                label->setTop("parent",uilib::Bottom);
            }
        }
    }
}
void OnlineFriendsInviteDialog::onFriendClicked(CCNode *node,void *data)
{
    m_selectName  = ((TouchNode*)node)->getName();
    if(m_listener && m_func){
        (m_listener->*m_func)(this,0);
    }
}
void OnlineFriendsInviteDialog::setListener(CCNode *listener,SEL_CallFuncND func)
{
    m_listener = listener;
    m_func = func;
}

RoomRoleShow::RoomRoleShow(RoomMainWidget *owner)
{
    m_owner = owner;
    m_init = false;
    m_isHost = false;
    m_roomHostSign = 0;
    m_propW = 28;
    m_propH = 28;
    m_onlineFsDialog = 0;
    m_parentWidget = new BasWidget;
    this->addChild(m_parentWidget);
    m_parentWidget->setHorizontal("parent",0.5);
    m_parentWidget->setVertical("parent",0.53);
    m_parentWidget->setMaxHeightRefSize("parent",0.82);
    m_parentWidget->setMinHeightRefSize("parent",0.82);
    m_parentWidget->setMaxWidthRefSize("parent",0.85);
    m_parentWidget->setMinWidthRefSize("parent",0.85);
    m_theme = "default";
    m_themeBg = "roomb1";
    m_serverIFace = ServerInterface::getInstance();
}
RoomRoleShow::~RoomRoleShow()
{

}
void RoomRoleShow::init(int dummy)
{
    m_uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    UiMsgEv::AccountInfoEv *ev = m_owner->m_accountInfo;
    UiMsgEv::RoomInfoEv *room = m_owner->m_roomInfo;
    m_isHost = room->m_hostIndex == room->m_userIndex;
    m_owner->m_roomGameShow->setIsHost(m_isHost);
    m_id = ev->m_id;

    int suppPlayer = room->m_suppNum;
    int suppAlign = room->m_alignNum;

    int teamNum = suppPlayer / suppAlign;
    for(int i = 0;i < suppAlign;i++){
        m_roleRows.push_back(teamNum);
    }
    int left = suppPlayer - m_roleRows.size() * teamNum;
    for(int i = 0;i < left;i++){
        m_roleRows[i] = m_roleRows[i] + 1;
    }
    int myseatpos = room->m_playerInfo[room->m_userIndex]->m_seatIndex;
    int myrow = getRoleRowBySeatPos(myseatpos);

    std::string selfflagimg,flagimg,nullTableImg,tableImg,invalidTable;
    m_uiDef->getNormalData()->getImg("flagself",selfflagimg);
    m_uiDef->getNormalData()->getImg("nulltable",nullTableImg);
    m_uiDef->getNormalData()->getImg("table",tableImg);
    m_uiDef->getNormalData()->getImg("invalidtable",invalidTable);
    std::stringstream ss;
    int seatIndex = 0;
    float anchorWidth,anchorHeight;
    m_parentWidget->getAnchorSize(anchorWidth,anchorHeight);
    for(int i = 0;i < suppAlign;i++){
        HFSizeWidgetContainer *container = new HFSizeWidgetContainer();
        m_widgetContainer.push_back(container);
        if(i == myrow){
            CCSprite *flagSprite = new CCSprite;
            flagSprite->initWithSpriteFrameName(selfflagimg.data());
            BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(flagSprite);
            m_rowFlags.push_back(dele);
        }else{
            ss.str("");
            ss << "flag" << i;
            m_uiDef->getNormalData()->getImg(ss.str(),flagimg);
            CCSprite *flagSprite = new CCSprite;
            flagSprite->initWithSpriteFrameName(flagimg.data());
            BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(flagSprite);
            m_rowFlags.push_back(dele);
        }
        float seatHeight = (anchorHeight - m_roleRows.size() * 20) / m_roleRows.size();
        //the first rows's num must be biggest
        float seatWidth = (anchorWidth - m_roleRows[0] * 20) / m_roleRows[0];
        if(seatWidth > seatHeight * 2)
            seatWidth = seatHeight * 2;
        //for squre set,test
        //seatHeight = seatHeight > seatWidth ? seatWidth : seatHeight;
        //seatWidth = seatHeight;
        for(int k = 0;k < m_roleRows[i];k++,seatIndex++){
            CCSprite *tableSprite = CCSprite::create();
            if(m_owner->m_serverIFace->getRoomSeatOpened(seatIndex))
                tableSprite->initWithSpriteFrameName(nullTableImg.data());
            else
                tableSprite->initWithSpriteFrameName(invalidTable.data());
            m_indexSprite.push_back(tableSprite);
            FSizeSpriteDelegate *dele = new FSizeSpriteDelegate(tableSprite,CCSizeMake(seatWidth,seatHeight));
            dele->setTag(seatIndex);
            dele->setCanTouch(true);
            dele->setClickCB(this,callfuncND_selector(RoomRoleShow::onSeatClicked));
            m_indexWidget.push_back(dele);
            container->addFSizeWidget(dele);
        }
    }
    VFSizeContainerLayer *vlayer = new VFSizeContainerLayer;
    for(unsigned int i = 0; i < m_widgetContainer.size();i++){
        FSizeWidgetContainer *container = m_widgetContainer[i];
        container->setAnchorType(uilib::Left);
        container->setSpacing(10);
        container->exec();
        vlayer->addContainer(container);
    }
    //put team flag by manual
    for(unsigned int i = 0;i < m_rowFlags.size();i++){
        BasNodeDelegateWidget *flag = m_rowFlags[i];
        vlayer->addChild(flag);
        FSizeWidgetContainer *container = m_widgetContainer[i];
        flag->setTop(container->getName(),uilib::Top);
        flag->setRight(container->getName(),uilib::Left);
    }
    vlayer->setSpacing(10);
    m_parentWidget->addChild(vlayer);
    vlayer->exec();
    vlayer->setCenterIn("parent");    
    //init player info & head
    std::vector<UiMsgEv::PlayerInfoEv *> *playerInfo = &room->m_playerInfo;
    for(unsigned int i = 0;i < playerInfo->size();i++){
        if(!playerInfo->at(i)->m_isValid)
            continue;
        std::string id = playerInfo->at(i)->m_userId;
        int seatIndex = playerInfo->at(i)->m_seatIndex;
        initHeadInfo(id,seatIndex);
    }
    //init room creator info
    if(1){
        std::string hostimg;
        m_uiDef->getNormalData()->getImg("hostsign",hostimg);
        CCSprite *sprite = CCSprite::createWithSpriteFrameName(hostimg.data());
        m_roomHostSign = new BasNodeDelegateWidget(sprite);
        posingRoomHostSign(room->m_hostId,playerInfo->at(room->m_hostIndex)->m_seatIndex);
    }
    //init medal
    if(1){
        for(unsigned int i = 0;i < playerInfo->size();i++){
            if(!playerInfo->at(i)->m_isValid)
                continue;
            UiMsgEv::PlayerInfoEv *ev = playerInfo->at(i);
            posingPlayerMedal(ev->m_userId,ev->m_seatIndex,ev->m_level);
        }
    }
    //init player nick name,creditname
    if(1){
        for(unsigned int i = 0;i < playerInfo->size();i++){
            if(!playerInfo->at(i)->m_isValid)
                continue;
            UiMsgEv::PlayerInfoEv *ev = playerInfo->at(i);
            std::string creditName = ev->m_creditName;
            std::string nickName = ev->m_nickName;
            if(nickName.empty())
                mailToNickName(ev->m_userMail,nickName);
            posingPlayerTextInfo(ev->m_userId,ev->m_seatIndex,creditName,nickName);
        }
    }
    //init won game show
    if(1){
        for(unsigned int i = 0;i < playerInfo->size();i++){
            if(!playerInfo->at(i)->m_isValid)
                continue;
            UiMsgEv::PlayerInfoEv *ev = playerInfo->at(i);
            initWonInfo(ev->m_userId,ev->m_seatIndex,ev->m_wonNum,ev->m_losedNum,ev->m_offlineNum,ev->m_escapeNum);
        }
    }
    //init players props
    if(1){
        for(unsigned int i = 0;i < playerInfo->size();i++){
            if(!playerInfo->at(i)->m_isValid)
                continue;
            UiMsgEv::PlayerInfoEv *ev = playerInfo->at(i);
            std::vector<UiMsgEv::GiftPropEv> props;
            props.clear();
            m_serverIFace->getAllUnzeroProps(ev->m_userId,props);
            std::sort(props.begin(),props.end(),prop_sortbyId);
            initPropInfo(ev->m_userId,ev->m_seatIndex,props);
        }
    }
    //init players tribe
    if(1){
        for(unsigned int i = 0;i < playerInfo->size();i++){
            if(!playerInfo->at(i)->m_isValid)
                continue;
            UiMsgEv::PlayerInfoEv *ev = playerInfo->at(i);
            initTribeInfo(ev->m_userId,ev->m_seatIndex,ev->m_tribe);
        }
    }
    //relayout at the end
    this->layout(true);
    m_init = true;
}
void RoomRoleShow::otherJoined(int pindex)
{
    UiMsgEv::PlayerInfoEv *ev = m_owner->m_roomInfo->m_playerInfo.at(pindex);
    BasWidget *seatwidget = m_indexWidget[ev->m_seatIndex];
    //init head
    initHeadInfo(ev->m_userId,ev->m_seatIndex);
    //init medal
    posingPlayerMedal(ev->m_userId,ev->m_seatIndex,ev->m_level);
    //init player nick name,creditname
    posingPlayerTextInfo(ev->m_userId,ev->m_seatIndex,ev->m_creditName,ev->m_nickName);
    //init won game show
    initWonInfo(ev->m_userId,ev->m_seatIndex,ev->m_wonNum,ev->m_losedNum,ev->m_offlineNum,ev->m_escapeNum);
    //init players props
    if(1){
        std::vector<UiMsgEv::GiftPropEv> props;
        m_serverIFace->getAllUnzeroProps(ev->m_userId,props);
        std::sort(props.begin(),props.end(),prop_sortbyId);
        initPropInfo(ev->m_userId,ev->m_seatIndex,props);
    }
    //init players tribe
    initTribeInfo(ev->m_userId,ev->m_seatIndex,ev->m_tribe);
    //init room creator info
    UiMsgEv::RoomInfoEv *room = m_owner->m_roomInfo;
    if(ev->m_userId == room->m_hostId){
        std::string hostimg;
        m_uiDef->getNormalData()->getImg("hostsign",hostimg);
        CCSprite *sprite = CCSprite::createWithSpriteFrameName(hostimg.data());
        m_roomHostSign = new BasNodeDelegateWidget(sprite);
        int hostSeat = room->m_playerInfo.at(room->m_hostIndex)->m_seatIndex;
        posingRoomHostSign(room->m_hostId,hostSeat);
    }
    m_owner->m_roomInfo->userJoin();
    seatwidget->layout(true);
}
void RoomRoleShow::otherQuit(int pindex)
{
    UiMsgEv::PlayerInfoEv *ev = m_owner->m_roomInfo->m_playerInfo.at(pindex);
    BasWidget *seatwidget = m_indexWidget[ev->m_seatIndex];
    std::string &id = ev->m_userId;
    m_headWidgetMap.erase(id);
    m_playerMedalMap.erase(id);
    m_playerTextInfoMap.erase(id);
    m_wonShowMap.erase(id);
    m_playerPropsMap.erase(id);
    m_tribeWidgetMap.erase(id);
    if(m_id == id){
        //for pos change
        seatwidget->delAllChild();
        CCSprite *sprite = m_indexSprite[ev->m_seatIndex];
        std::string nulltable;
        m_uiDef->getNormalData()->getImg("nulltable",nulltable);
        sprite->initWithSpriteFrameName(nulltable.data());
        m_owner->m_roomInfo->userQuit();
    }else if(ev->m_hostId == m_owner->m_roomInfo->m_hostId){
        //host no change,normal user quit
        seatwidget->delAllChild();
        CCSprite *sprite = m_indexSprite[ev->m_seatIndex];
        std::string nulltable;
        m_uiDef->getNormalData()->getImg("nulltable",nulltable);
        sprite->initWithSpriteFrameName(nulltable.data());
        m_owner->m_roomInfo->userQuit();
    }else{
        //host quit,new user change to host creator
        if(m_id == ev->m_hostId)
            m_isHost = true;        
        m_owner->m_roomGameShow->setIsHost(m_isHost);
        seatwidget->delAllChild();
        CCSprite *sprite = m_indexSprite[ev->m_seatIndex];
        std::string nulltable;
        m_uiDef->getNormalData()->getImg("nulltable",nulltable);
        sprite->initWithSpriteFrameName(nulltable.data());
        m_roomHostSign = 0;
        //init room creator info
        UiMsgEv::RoomInfoEv *room = m_owner->m_roomInfo;
        room->setNewHostId(ev->m_hostId);
        room->userQuit();
        if(1){
            std::string hostimg;
            m_uiDef->getNormalData()->getImg("hostsign",hostimg);
            CCSprite *sprite = CCSprite::createWithSpriteFrameName(hostimg.data());
            m_roomHostSign = new BasNodeDelegateWidget(sprite);
            int hostSeat = room->m_playerInfo.at(room->m_hostIndex)->m_seatIndex;
            posingRoomHostSign(room->m_hostId,hostSeat);
            BasWidget *hostSeatWidget = m_indexWidget[hostSeat];
            hostSeatWidget->layout(true);
        }
    }
    seatwidget->layout(true);
    //if the user is chat-object,clear
    if(m_owner->m_chatWidget->getRecId() == id){
        m_owner->m_chatWidget->clearRecInfo();
    }
}
void RoomRoleShow::seatIndexChanged(int pindex)
{
    UiMsgEv::PlayerInfoEv *ev = m_owner->m_roomInfo->m_playerInfo.at(pindex);
    int origSeat = ev->m_origSeatIndex;
    int newSeat = ev->m_seatIndex;
    ev->m_seatIndex = origSeat;
    otherQuit(pindex);
    ev->m_seatIndex = newSeat;
    otherJoined(pindex);
}
void RoomRoleShow::seatIndexChangedFail(int pindex)
{

}
void RoomRoleShow::seatNumChanged(int pindex)
{

}
void RoomRoleShow::seatNumChangedFail(int pindex)
{

}
void RoomRoleShow::seatClosed(int seatIndex)
{
    std::string invalid;
    m_uiDef->getNormalData()->getImg("invalidtable",invalid);
    if(!invalid.empty()){
        CCSprite *sprite = m_indexSprite[seatIndex];
        sprite->initWithSpriteFrameName(invalid.data());
    }
}
void RoomRoleShow::seatOpened(int seatIndex)
{
    std::string valid;
    m_uiDef->getNormalData()->getImg("nulltable",valid);
    if(!valid.empty()){
        CCSprite *sprite = m_indexSprite[seatIndex];
        sprite->initWithSpriteFrameName(valid.data());
    }
}
void RoomRoleShow::tribeChanged(int pindex)
{
    UiMsgEv::PlayerInfoEv *ev = m_owner->m_roomInfo->m_playerInfo.at(pindex);
    std::string tribeImg;
    ResourceMgr::getInstance()->getTribeName(ev->m_tribe,tribeImg);
    m_uiDef->getNormalData()->getImg(tribeImg,tribeImg);
    std::map<std::string,BasNodeLimitWidget*>::iterator iter;
    iter = m_tribeWidgetMap.find(ev->m_userId);
    if(iter != m_tribeWidgetMap.end()){
        CCSprite *tribe = (CCSprite*)iter->second->getClient();
        tribe->initWithSpriteFrameName(tribeImg.data());
    }
}
void RoomRoleShow::initHeadInfo(const std::string &id,int sindex)
{
    std::string tableImg;
    m_uiDef->getNormalData()->getImg("table",tableImg);
    CCSprite *seatbg = m_indexSprite[sindex];
    //set no table with people
    seatbg->initWithSpriteFrameName(tableImg.data());
    BasWidget *seatwidget = m_indexWidget[sindex];
    if(1){
        //head
        std::string *headdata;
        bool hashead = m_serverIFace->getHeadPortrait(id,&headdata);
        if(hashead && headdata->size() != 0){
            CCImage *img = new CCImage;
            img->initWithImageData((void*)headdata->c_str(),headdata->size(),
                                   CCImage::kFmtUnKnown);
            CCTexture2D *texture = new CCTexture2D;
            texture->initWithImage(img);
            delete img;
            CCSprite *headSprite = CCSprite::create();
            headSprite->initWithTexture(texture);
            BasNodeDelegateWidget *headWidget = new BasNodeDelegateWidget(headSprite,CCSizeMake(60,60));
            seatwidget->addChild(headWidget);
            headWidget->setVertical("parent",0.6);
            headWidget->setLeft("parent",uilib::Left);
            headWidget->setLeftMargin(10);
            m_headWidgetMap.insert(std::make_pair(id,headWidget));

            headWidget->setCanTouch(true);
            headWidget->setName(id);
            headWidget->setClickCB(this,callfuncND_selector(RoomRoleShow::onHeadClicked));
        }else{
            std::string defaultHead;
            m_uiDef->getNormalData()->getImg("portraitdefault",defaultHead);
            CCSprite *headSprite = CCSprite::create();
            headSprite->initWithSpriteFrameName(defaultHead.data());
            BasNodeDelegateWidget *headWidget = new BasNodeDelegateWidget(headSprite,CCSizeMake(60,60));
            seatwidget->addChild(headWidget);
            headWidget->setVertical("parent",0.6);
            headWidget->setLeft("parent",uilib::Left);
            headWidget->setLeftMargin(10);
            m_headWidgetMap.insert(std::make_pair(id,headWidget));

            headWidget->setCanTouch(true);
            headWidget->setName(id);
            headWidget->setClickCB(this,callfuncND_selector(RoomRoleShow::onHeadClicked));
        }
    }
}
int RoomRoleShow::getRoleRowBySeatPos(int seatpos)
{
    int sum = 0;
    for(int i = 0;i < m_roleRows.size();i++){
        sum += m_roleRows[i];
        if(seatpos < sum)
            return i;
    }
    return -1;
}
void RoomRoleShow::posingRoomHostSign(const std::string &hostid,int hostseatpos)
{
    if(m_roomHostSign->parent())
        m_roomHostSign->parent()->delChild(m_roomHostSign,false);
    std::map<std::string,BasNodeDelegateWidget *>::iterator iter;
    iter = m_headWidgetMap.find(hostid);
    if(iter == m_headWidgetMap.end())
        return;
    BasWidget *headWidget = iter->second;
    BasWidget *seatWidget = m_indexWidget[hostseatpos];
    if(headWidget == 0 || seatWidget == 0)
        return;
    seatWidget->addChild(m_roomHostSign);
    m_roomHostSign->setBottom(headWidget->getName(),uilib::Top);
    m_roomHostSign->setBottomMargin(-5);
    m_roomHostSign->setHorizontal(headWidget->getName(),0.5);
}
void RoomRoleShow::posingPlayerMedal(const std::string &id,int sindex,int level)
{
    std::stringstream ss;
    ss << "medal" << level << ".png";
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ss.str().data());
    if(frame == 0)
        return;
    std::map<std::string,BasNodeDelegateWidget *>::iterator iter;
    iter = m_playerMedalMap.find(id);
    if(iter == m_playerMedalMap.end()){
        iter = m_headWidgetMap.find(id);
        if(iter == m_headWidgetMap.end())
            return;
        BasWidget *headWidget = iter->second;
        CCSprite *sprite = CCSprite::create();
        sprite->initWithSpriteFrame(frame);
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(sprite,CCSizeMake(60,60));
        std::string name = id + "medal";
        dele->setName(name);
        dele->setCanTouch(true);
        dele->setClickCB(this,callfuncND_selector(RoomRoleShow::onMedalClicked));
        BasWidget *seatbg = m_indexWidget[sindex];
        seatbg->addChild(dele);
        dele->setLeft(headWidget->getName(),uilib::Right);
        dele->setTop(headWidget->getName(),uilib::Top);
        m_playerMedalMap.insert(std::make_pair(id,dele));
    }else{
        CCSprite *sprite = (CCSprite*)iter->second->getClient();
        sprite->initWithSpriteFrame(frame);
    }
}
void RoomRoleShow::posingPlayerTextInfo(const std::string &id,int sindex,
                          const std::string &creditName,const std::string &nickName)
{
    BasWidget *headWidget;
    std::map<std::string,BasNodeDelegateWidget *>::iterator diter;
    diter = m_headWidgetMap.find(id);
    if(diter == m_headWidgetMap.end())
        return;
    headWidget = diter->second;
    BasWidget *seatbg = m_indexWidget[sindex];
    std::map<std::string,BasWidget *>::iterator iter;
    iter = m_playerTextInfoMap.find(id);
    if(iter != m_playerTextInfoMap.end()){
        seatbg->delChild(iter->second);
        m_playerTextInfoMap.erase(iter);
    }
    std::string info = creditName;
    if(!info.empty()) info += "/";
    info += nickName;
    BasLabel *label = new BasLabel;
    m_playerTextInfoMap.insert(std::make_pair(id,label));
    label->setLabelInfo(info,"","",CCSizeMake(0,0),getSystemFont(),18,m_id == id ? ccGREEN : ccWHITE);
    seatbg->addChild(label);
    label->setHorizontal(headWidget->getName(),0.5);
    label->setBottom(headWidget->getName(),uilib::Bottom);
}
void RoomRoleShow::initWonInfo(const std::string &id,int sindex,
                      int won,int lost,int offline,int escape)
{
    BasWidget *seatbg = m_indexWidget[sindex];
    WonGameShow *show;
    std::map<std::string,WonGameShow *>::iterator iter;
    iter = m_wonShowMap.find(id);
    if(iter != m_wonShowMap.end()){
        show = iter->second;
        std::vector<float> rates;
        float sum = won + lost + offline + escape;
        if(sum >= 1){
            rates.push_back(won / sum);
            rates.push_back(lost / sum);
            rates.push_back(offline / sum);
            rates.push_back(escape / sum);
        }else{
            rates.push_back(0.25);
            rates.push_back(0.25);
            rates.push_back(0.25);
            rates.push_back(0.25);
        }
        show->resetWonBarLen(rates);
    }else{
        show = new WonGameShow;
        m_wonShowMap.insert(std::make_pair(id,show));
        std::vector<std::string> fgs;
        std::vector<float> rates;
        fgs.push_back("redhbar");
        fgs.push_back("bluehbar");
        fgs.push_back("greenhbar");
        fgs.push_back("grayhbar");
        float sum = won + lost + offline + escape;
        if(sum != 0){
            rates.push_back(won / sum);
            rates.push_back(lost / sum);
            rates.push_back(offline / sum);
            rates.push_back(escape / sum);
        }else{
            rates.push_back(0.25);
            rates.push_back(0.25);
            rates.push_back(0.25);
            rates.push_back(0.25);
        }
        for(unsigned i = 0;i < fgs.size();i++){
            WonGameShow::WonBarDef *def = new WonGameShow::WonBarDef;
            def->m_barBg = "hbarcolorbg";
            def->m_barFg =fgs[i];
            def->m_percent = rates[i];
            show->addWonBarDef(def);
        }
        seatbg->addChild(show);
        show->setBottom("parent",uilib::Bottom);
        show->setLeft("parent",uilib::Left);
        show->setRight("parent",uilib::Right);
        show->setLeftMargin(5);
        show->setRightMargin(5);
        show->setBottomMargin(5);
        show->setHeight(8);
    }
}
void RoomRoleShow::initPropInfo(const std::string &id,int sindex,
                  const std::vector<UiMsgEv::GiftPropEv> &props)
{
    BasWidget *seatbg = m_indexWidget[sindex];
    HorScrollWidget *scroll;
    std::map<std::string,HorScrollWidget*>::iterator iter;
    iter = m_playerPropsMap.find(id);
    if(iter != m_playerPropsMap.end()){
        scroll = iter->second;
        scroll->delAllChild();
    }else{
        scroll = new HorScrollWidget;
        scroll->setVerticalScrollPolicy(ScrollShow_Never);
        scroll->setHorizontalScrollPolicy(ScrollShow_Never);
        m_playerPropsMap.insert(std::make_pair(id,scroll));
        seatbg->addChild(scroll);
        scroll->setLeft("parent",uilib::Left);
        scroll->setTop("parent",uilib::Top);
        scroll->setRight("parent",uilib::Right);
        scroll->setLeftMargin(5);
        scroll->setRightMargin(5);
        scroll->setHeight(m_propH);
    }
    CCSize size = CCSizeMake(m_propW,m_propH);
    for(unsigned int i = 0;i < props.size();i++){
        std::string imgname;
        PropDef::getVirtualPropsName(props[i].m_id,imgname);
        if(imgname.empty())
            continue;
        imgname += ".png";
        CCSprite *imgsprite = CCSprite::createWithSpriteFrameName(imgname.data());
        FSizeSpriteDelegate *dele = new FSizeSpriteDelegate(imgsprite,size);
        scroll->addFixedSizeWidget(dele);
    }
}
void RoomRoleShow::initTribeInfo(const std::string &id,int sindex,int tribe)
{
    BasWidget *rightWidget;
    std::string tribeimg;
    ResourceMgr::getInstance()->getTribeName(tribe,tribeimg);
    m_uiDef->getNormalData()->getImg(tribeimg,tribeimg);
    BasWidget *seatbg = m_indexWidget[sindex];
    std::map<std::string,BasNodeDelegateWidget *>::iterator miter;
    miter = m_playerMedalMap.find(id);
    if(miter == m_playerMedalMap.end()){
        miter = m_headWidgetMap.find(id);
        if(miter == m_headWidgetMap.end())
            return;
        else
            rightWidget = miter->second;
    }else{
        rightWidget = miter->second;
    }
    std::map<std::string,BasNodeLimitWidget *>::iterator iter;
    iter = m_tribeWidgetMap.find(id);
    if(iter == m_tribeWidgetMap.end()){
        CCSprite *sprite = CCSprite::createWithSpriteFrameName(tribeimg.data());
        BasNodeLimitWidget *dele = new BasNodeLimitWidget(sprite,CCSizeMake(70,70));
        m_tribeWidgetMap.insert(std::make_pair(id,dele));
        seatbg->addChild(dele);
        dele->setLeft(rightWidget->getName(),uilib::Right);
        dele->setRight("parent",uilib::Right);
        dele->setRightMargin(10);
        dele->setVertical(rightWidget->getName(),0.5);
        dele->setMaxHeightRefSize("parent",0.6);

        if(m_id == id){
            //set touchable for self
            dele->setCanTouch(true);
            dele->setClickCB(this,callfuncND_selector(RoomRoleShow::onTribeClicked));
        }
    }else{
        CCSprite *sprite = (CCSprite*)(iter->second->getClient());
        sprite->initWithSpriteFrameName(tribeimg.data());
    }
}
void RoomRoleShow::onTribeClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    ResourceMgr *mgr = ResourceMgr::getInstance();
    std::vector<int> tribes;
    tribes.push_back(GameType::Tribe_human);
    tribes.push_back(GameType::Tribe_undead);
    tribes.push_back(GameType::Tribe_orc);
    tribes.push_back(GameType::Tribe_nightelf);
    tribes.push_back(GameType::Tribe_dragon);
    TouchNode *root = m_owner;
    CCPoint pos = root->convertToNodeSpace(*(CCPoint*)data);
    PopButtonsDialog *pop = new PopButtonsDialog(root,pos);
    std::string tribeImg;
    for(unsigned int i = 0;i < tribes.size();i++){
        mgr->getTribeName(tribes[i],tribeImg);
        BasButton *button = new BasButton;
        button->setButtonInfo("","default",tribeImg,CCSizeMake(0,0));
        pop->addButton(button);
    }
    pop->setButtonCB(this,callfuncND_selector(RoomRoleShow::onPopTribeClicked));
    pop->setSpacing(10);
    pop->setEdgeSize(20);
    pop->exec();
}
void RoomRoleShow::onHeadClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    TouchNode *touch = (TouchNode*)node;
    m_headUserId= touch->getName();
    if(m_headUserId == m_id)
        return;
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    TouchNode *root = m_owner;
    CCPoint pos = root->convertToNodeSpace(*(CCPoint*)data);
    PopButtonsDialog *pop = new PopButtonsDialog(root,pos);
    int num = m_serverIFace->getPropNumByUid(m_id,PropDef::Props_Staff);
    if(m_isHost || num > 0){
        BasButton *button = new BasButton;
        button->setButtonInfoWithBorder(lang->getStringById(StringEnum::RoomKickPlayer).data(),"fonts/uifont24.fnt","default","button");
        button->setTag(KickPlayer);
        pop->addButton(button);
    }
    num = m_serverIFace->getPropNumByUid(m_id,PropDef::Props_Clover);
    if(num > 0){
        BasButton *button = new BasButton;
        button->setButtonInfoWithBorder(lang->getStringById(StringEnum::RoomSneerPlayer).data(),"fonts/uifont24.fnt","default","button");
        button->setTag(SneerPlayer);
        pop->addButton(button);
    }
    num = m_serverIFace->getPropNumByUid(m_id,PropDef::Props_Rose);
    if(num > 0){
        BasButton *button = new BasButton;
        button->setButtonInfoWithBorder(lang->getStringById(StringEnum::RoomPriasePlayer).data(),"fonts/uifont24.fnt","default","button");
        button->setTag(PraisePlayer);
        pop->addButton(button);
    }
    if(1){
        BasButton *button = new BasButton;
        button->setButtonInfoWithBorder(lang->getStringById(StringEnum::RoomChatTo).data(),"fonts/uifont24.fnt","default","button");
        button->setTag(ChatTo);
        pop->addButton(button);
    }
    if(!m_serverIFace->isFriend(m_headUserId)){
        BasButton *button = new BasButton;
        button->setButtonInfoWithBorder(lang->getStringById(StringEnum::AddFriend).data(),"fonts/uifont24.fnt","default","button");
        button->setTag(AskAsFriend);
        pop->addButton(button);
    }

    pop->setButtonCB(this,callfuncND_selector(RoomRoleShow::onPopHeadClicked));
    pop->setSpacing(10);
    pop->setEdgeSize(20);
    pop->exec();
}
void RoomRoleShow::onSeatClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int addNum = 0;
    m_popSeatIndex = node->getTag();
    if(m_popSeatIndex == m_owner->m_roomInfo->m_playerInfo[m_owner->m_roomInfo->m_userIndex]->m_seatIndex)
        return;
    TouchNode *root = m_owner;
    CCPoint pos = root->convertToNodeSpace(*(CCPoint*)data);
    PopButtonsDialog *pop = new PopButtonsDialog(root,pos);
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    bool open = m_serverIFace->getRoomSeatOpened(m_popSeatIndex);
    if(m_isHost){
        if(open){
            BasButton *button = new BasButton;
            button->setButtonInfoWithBorder(lang->getStringById(StringEnum::RoomCloseSeat).data(),"fonts/uifont24.fnt","default","button");
            button->setTag(CloseSeat);
            pop->addButton(button);
            addNum++;
        }else{
            BasButton *button = new BasButton;
            button->setButtonInfoWithBorder(lang->getStringById(StringEnum::RoomOpenSeat).data(),"fonts/uifont24.fnt","default","button");
            button->setTag(OpenSeat);
            pop->addButton(button);
            addNum++;
        }
        int player = m_serverIFace->getRoomPlayerIndexBySeatIndex(m_popSeatIndex);
        if(!m_owner->m_roomInfo->m_playerInfo[player]->m_isValid && open){
            BasButton *button = new BasButton;
            button->setButtonInfoWithBorder(lang->getStringById(StringEnum::RoomChangePos).data(),"fonts/uifont24.fnt","default","button");
            button->setTag(ChangePos);
            pop->addButton(button);
            addNum++;
            const std::vector<std::string> &fs = m_serverIFace->getFriends();
            if(fs.size() != 0){
                BasButton *addFriend = new BasButton;
                addFriend->setButtonInfoWithBorder(lang->getStringById(StringEnum::RoomAddFriend).data(),"fonts/uifont24.fnt","default","button");
                addFriend->setTag(AddFriend);
                pop->addButton(addFriend);
                addNum++;
            }
        }
    }else{
        int player = m_serverIFace->getRoomPlayerIndexBySeatIndex(m_popSeatIndex);
        if(m_owner->m_roomInfo->m_playerInfo[player]->m_isValid)
            return;
        if(open){
            BasButton *button = new BasButton;
            button->setButtonInfoWithBorder(lang->getStringById(StringEnum::RoomChangePos).data(),"fonts/uifont24.fnt","default","button");
            button->setTag(ChangePos);
            pop->addButton(button);
            addNum++;
            const std::vector<std::string> &fs = m_serverIFace->getFriends();
            if(fs.size() != 0){
                BasButton *addFriend = new BasButton;
                addFriend->setButtonInfoWithBorder(lang->getStringById(StringEnum::RoomAddFriend).data(),"fonts/uifont24.fnt","default","button");
                addFriend->setTag(AddFriend);
                pop->addButton(addFriend);
                addNum++;
            }
        }
    }
    if(addNum != 0){
        pop->setButtonCB(this,callfuncND_selector(RoomRoleShow::onPopSeatClicked));
        pop->setSpacing(10);
        pop->setEdgeSize(20);
        pop->exec();
    }else{
        delete pop;
    }
}
void RoomRoleShow::onMedalClicked(CCNode *node,void *data)
{
    TouchNode *touch = (TouchNode*)node;
    const std::string &name = touch->getName();
    int size = name.size();
    std::string id = name.substr(0,size - 5);
    if(id.empty())
        return;
    UiMsgEv::PlayerInfoEv *ev = m_serverIFace->getPlayerInfoByUid(id);
    if(ev == 0)
        return;
    CCPoint *pos = (CCPoint*)(data);
    std::stringstream ss;
    ss << "Lv: " << ev->m_level;
    BasLabel *label = new BasLabel;
    label->setLabelInfo(ss.str().data(),"fonts/font30.fnt","","",CCSizeMake(0,0));
    new FloatingDelegateWidget(this->rootParent(),label,CCSizeMake(140,140),*pos);
}
void RoomRoleShow::onInviteFriendClick()
{
    if(m_onlineFsDialog != 0){
        m_onlineFsDialog->destroy();
        m_onlineFsDialog = 0;
    }
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    m_onlineFsDialog = new OnlineFriendsInviteDialog(this,root,ccc4(0,0,0,128));
    m_onlineFsDialog->setCloseCB(this,callfuncND_selector(RoomRoleShow::onInviteFriendCloseClicked));
    m_onlineFsDialog->setListener(this,callfuncND_selector(RoomRoleShow::onInviteFriendFriendClicked));
    m_onlineFsDialog->exec();
}
void RoomRoleShow::onInviteFriendCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_onlineFsDialog != 0){
        m_onlineFsDialog->destroy();
        m_onlineFsDialog = 0;
    }
}
void RoomRoleShow::onInviteFriendFriendClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_onlineFsDialog != 0){
        const std::string &fs = m_onlineFsDialog->getClickFriend();
        m_onlineFsDialog->destroy();
        m_onlineFsDialog = 0;
        m_serverIFace->invitePlayerToGame(m_id,fs);
    }
}
void RoomRoleShow::onPopTribeClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int tribe;
    int index = *(int*)data;
    switch(index){
    case 0:{
        tribe = GameType::Tribe_human;
        break;
    }
    case 1:{
        tribe = GameType::Tribe_undead;
        break;
    }
    case 2:{
        tribe = GameType::Tribe_orc;
        break;
    }
    case 3:{
        tribe = GameType::Tribe_nightelf;
        break;
    }
    case 4:{
        tribe = GameType::Tribe_dragon;
        break;
    }
    default:{
        return;
        break;
    }
    }
    m_serverIFace->requestChangePlayerTribe(m_id,tribe);
}
void RoomRoleShow::onPopSeatClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int tag = node->getTag();
    switch(tag){
    case ChangePos:{
        int oldSeat = m_owner->m_roomInfo->m_playerInfo[m_owner->m_roomInfo->m_userIndex]->m_seatIndex;
        int newSeat = m_popSeatIndex;
        m_serverIFace->requestChangeSeatIndex(m_id,oldSeat,newSeat);
        break;
    }
    case CloseSeat:{
        m_serverIFace->requestSeatToClose(m_id,m_popSeatIndex);
        break;
    }
    case OpenSeat:{
        m_serverIFace->requestSeatToOpen(m_id,m_popSeatIndex);
        break;
    }
    case AddFriend:{
        m_serverIFace->getOnlineFriends();
        onInviteFriendClick();
        break;
    }
    default:{
        break;
    }
    }
}
void RoomRoleShow::onPopHeadClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int tag = node->getTag();
    switch(tag){
    case KickPlayer:{
        m_serverIFace->kickUserInRoom(m_id,m_headUserId);
        break;
    }
    case PraisePlayer:{
        int seatIndex = getSeatIndexByUserId(m_headUserId);
        if(seatIndex >= 0){
            m_serverIFace->praiseUserInRoom(m_id,m_headUserId);
            priaseUser(m_id,m_headUserId);
        }
        break;
    }
    case SneerPlayer:{
        int seatIndex = getSeatIndexByUserId(m_headUserId);
        if(seatIndex >= 0){
            m_serverIFace->sneerUserInRoom(m_id,m_headUserId);
            sneerUser(m_id,m_headUserId);
        }
        break;
    }
    case ChatTo:{
        m_owner->setChatTo(m_headUserId);
        break;
    }
    case AskAsFriend:{
        std::string id,word;
        id = m_headUserId;
        if(!id.empty()){
            m_serverIFace->addFriend(id,word);
            CCNode *root = this->getParent();
            while(root->getParent())
                root = root->getParent();
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            SendMsgAnim *anim = new SendMsgAnim(root,ccp(winSize.width / 2,winSize.height / 2));
            anim->exec();
        }
        break;
    }
    default:{
        break;
    }
    }
}
int RoomRoleShow::getSeatIndexByUserId(const std::string &id)
{
    for(unsigned int i = 0;i < m_owner->m_roomInfo->m_playerInfo.size();i++){
        UiMsgEv::PlayerInfoEv *ev = m_owner->m_roomInfo->m_playerInfo[i];
        if(ev->m_isValid && ev->m_userId == id){
            return i;
        }
    }
    return -1;
}
void RoomRoleShow::priaseUser(const std::string &sender,const std::string &receiver)
{
    if(receiver.empty()){
        //for all room
    }else{
        int seatIndex = getSeatIndexByUserId(receiver);
        std::string anim,first;
        anim = "praiseuser";
        first = anim;
        if(ResourceMgr::getInstance()->getFrameSpriteFirstFrame(first)){
            BasAnimSprite *sprite = new BasAnimSprite(anim,first);
            sprite->setAutoRelease(true);
            BasWidget *seatBg = m_indexWidget[seatIndex];
            seatBg->CCNode::addChild(sprite,100);
            float width,height;
            seatBg->getAnchorSize(width,height);
            sprite->setPosition(ccp(width/2,height/2));
            if(1){
                int loops,totalFrame,frameNum;
                float totalTime;
                float scale;
                ResourceMgr::getFrameSpriteTotalFrame(anim,loops,totalFrame,frameNum,totalTime,scale);
                if(fabs(scale - 1.0) > 0.1){
                    sprite->setScale(scale);
                    sprite->getTexture()->setAliasTexParameters();
                    sprite->getTexture()->setAntiAliasTexParameters();
                }
            }
            sprite->start();
        }
    }
}
void RoomRoleShow::sneerUser(const std::string &sender,const std::string &receiver)
{
    if(receiver.empty()){
        //for all room
    }else{
        int seatIndex = getSeatIndexByUserId(receiver);

        std::string anim,first;
        anim = "sneeruser";
        first = anim;
        if(ResourceMgr::getInstance()->getFrameSpriteFirstFrame(first)){
            BasAnimSprite *sprite = new BasAnimSprite(anim,first);
            sprite->setAutoRelease(true);
            BasWidget *seatBg = m_indexWidget[seatIndex];
            seatBg->CCNode::addChild(sprite,100);
            float width,height;
            seatBg->getAnchorSize(width,height);
            sprite->setPosition(ccp(width/2,height/2));
            if(1){
                int loops,totalFrame,frameNum;
                float totalTime;
                float scale;
                ResourceMgr::getFrameSpriteTotalFrame(anim,loops,totalFrame,frameNum,totalTime,scale);
                if(fabs(scale - 1.0) > 0.1){
                    sprite->setScale(scale);
                    sprite->getTexture()->setAliasTexParameters();
                    sprite->getTexture()->setAntiAliasTexParameters();
                }
            }
            sprite->start();
        }
    }
}
bool RoomRoleShow::canStartGame()
{
    int pnum = m_owner->m_roomInfo->m_playerNum;
    if(pnum <= 1){
        return false;
    }
    std::vector<int> teams;
    int maxteamNum = m_owner->m_roomInfo->m_suppNum / m_owner->m_roomInfo->m_alignNum;
    int indexer = 0;
    int teamIndexer = 0;
    for(unsigned int i = 0;i < m_owner->m_roomInfo->m_playerInfo.size();i++){
        indexer++;
        if(indexer == maxteamNum){
            teams.push_back(teamIndexer++);
            indexer = 0;
        }else{
            teams.push_back(teamIndexer);
        }
    }
    std::vector<int> hasCamp;
    for(unsigned int i = 0;i < m_owner->m_roomInfo->m_playerInfo.size();i++){
        UiMsgEv::PlayerInfoEv *player = m_owner->m_roomInfo->m_playerInfo[i];
        if(player->m_isValid){
            hasCamp.push_back(teams[player->m_seatIndex]);
        }
    }
    if(hasCamp.size() <= 1){
        return false;
    }
    int camp1 = hasCamp[0];
    for(unsigned int i = 1;i < hasCamp.size();i++){
        int camp = hasCamp[i];
        if(camp != camp1){
            return true;
        }
    }
    return false;
}
