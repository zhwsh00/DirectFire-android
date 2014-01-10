#include "friendspage.h"
#include "friendtitle.h"
#include "frienditem.h"
#include "sendmsganim.h"
#include "addfrienddialog.h"
#include "resource/resourcemgr.h"
#include "sounds/soundmgr.h"

#include "utils/ccutils.h"
#include <algorithm>
using namespace std;


FriendsPage::FriendsPage(uilib::BasWidget *container) : BasPage(container)
{
    m_title = new FriendTitle;
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    m_title->setTitle(lang->getStringById(StringEnum::FriendList));
    m_title->setAddCB(this,callfuncND_selector(FriendsPage::onTitleAddClick));
    m_title->setRefreshCB(this,callfuncND_selector(FriendsPage::onTitleRefreshClick));
    this->addChild(m_title);
    float srate = getAdaptResourceScale();
    m_title->setBottom("parent",uilib::Top);
    m_title->setLeft("parent",uilib::Left);
    m_title->setWidth(610 * srate);
    m_title->setLeftMargin(20);
    m_title->setRightMargin(20);
    m_title->setHeight(92 * srate);

    this->setTopMargin(30);

    m_scrollList = new VerScrollWidget("","");
    m_scrollList->setMargins(5);
    this->addChild(m_scrollList);
    m_scrollList->setLeft("parent",uilib::Left);
    m_scrollList->setRight("parent",uilib::Right);
    m_scrollList->setTop("parent",uilib::Top);
    m_scrollList->setTopMargin(10);
    m_scrollList->setBottom("parent",uilib::Bottom);
    m_scrollList->setSpacing(20);
    m_scrollList->setVerticalScrollPolicy(uilib::ScrollShow_Never);
    m_scrollList->setHorizontalScrollPolicy(uilib::ScrollShow_Never);
    m_init = false;
    m_serverIface = ServerInterface::getInstance();
    m_addFriendDialog = 0;
}
FriendsPage::~FriendsPage()
{

}
void FriendsPage::moveinPage()
{
    if(!m_init){
        const std::vector<std::string> &fs = m_serverIface->getFriends();
        std::vector<UiMsgEv::PlayerInfoEv*> evs;
        for(unsigned int i = 0;i < fs.size();i++){
            UiMsgEv::PlayerInfoEv *ev = m_serverIface->getPlayerInfoByUid(fs[i]);
            if(ev){
                evs.push_back(ev);
            }
        }
        std::string fid;
        while(m_serverIface->getAskFriendAccept(fid)){
            UiMsgEv::PlayerInfoEv *ev = m_serverIface->getPlayerInfoByUid(fid);
            if(ev){
                evs.push_back(ev);
            }
        }
        initFriends(evs);
        if(m_title)
            m_title->startRefresh();
    }
}
void FriendsPage::moveoutPage()
{

}
void FriendsPage::startRefreshing()
{
    if(m_title)
        m_title->setRefreshing(true);
}
void FriendsPage::endRefreshing()
{
    if(m_title)
        m_title->setRefreshing(false);
}
void FriendsPage::deleteItem(FriendItem *item)
{
    std::map<std::string,FSizeWidgetDelegate *>::iterator iter;
    iter = m_friendMap.find(item->userId());
    if(iter == m_friendMap.end())
        return;
    m_scrollList->delFixedSizeWidget(iter->second);
}
void FriendsPage::relayScroll()
{
    m_scrollList->layout(true);
}
void FriendsPage::addFriendItem(UiMsgEv::PlayerInfoEv *ev)
{
    float w = m_anchorWidth - m_scrollList->leftMargin() * 8;
    float h = 100;
    CCSize size = CCSizeMake(w,h);
    FriendItem *item = new FriendItem(this);
    item->setWidth(w);
    item->setHeight(h);
    item->setItemInfo(ev);
    FSizeWidgetDelegate *dele = new FSizeWidgetDelegate(item,size);
    m_friendMap.insert(std::make_pair(ev->m_userId,dele));
    m_scrollList->addFixedSizeWidget(dele);

    std::string *data;
    if(m_serverIface->getHeadPortrait(ev->m_userId,&data)){
        item->setHeadPortrait(*data);
    }
    std::vector<UiMsgEv::GiftPropEv> props;
    m_serverIface->getAllUnzeroProps(ev->m_userId,props);
    std::sort(props.begin(),props.end(),prop_sortByCount);
    for(unsigned int i = 0;i < props.size();i++){
        item->addProp(props[i].m_id,props[i].m_count);
    }
    item->finish();
}
bool FriendsPage::hasInit()
{
    return m_init;
}
void FriendsPage::initFriends(const std::vector<UiMsgEv::PlayerInfoEv*> &fs)
{
    for(unsigned int i = 0;i < fs.size();i++){
        addFriendItem(fs[i]);
    }
    m_init = true;
    m_scrollList->layout(true);
    updateOnlineFriend();
}
void FriendsPage::addFriend(const std::string &fid)
{
    if(!m_init)
        return;
    UiMsgEv::PlayerInfoEv *ev = m_serverIface->getPlayerInfoByUid(fid);
    if(ev == 0)
        return;
    //no debug
    std::map<std::string,FSizeWidgetDelegate *>::iterator iter;
    iter = m_friendMap.find(ev->m_userId);
    if(iter != m_friendMap.end()){
        FriendItem *item = (FriendItem*)(iter->second->getWidget());
        item->setItemInfo(ev);

        std::string *data;
        if(m_serverIface->getHeadPortrait(ev->m_userId,&data)){
            item->setHeadPortrait(*data);
        }
        std::vector<UiMsgEv::GiftPropEv> props;
        item->clearProp();
        m_serverIface->getAllUnzeroProps(ev->m_userId,props);
        std::sort(props.begin(),props.end(),prop_sortByCount);
        for(unsigned int i = 0;i < props.size();i++){
            item->addProp(props[i].m_id,props[i].m_count);
        }
        item->finish();
    }else{
        addFriendItem(ev);
    }
}
void FriendsPage::delFriend(const std::string &fid)
{
    //friend be deleted
    if(!m_init)
        return;
}
void FriendsPage::updateFriendProp(const std::string &uid)
{
    if(!m_init)
        return;
    std::map<std::string,FSizeWidgetDelegate *>::iterator iter;
    iter = m_friendMap.find(uid);
    if(iter != m_friendMap.end()){
        FriendItem *item = (FriendItem*)(iter->second->getWidget());
        std::vector<UiMsgEv::GiftPropEv> props;
        m_serverIface->getAllUnzeroProps(uid,props);
        std::sort(props.begin(),props.end(),prop_sortByCount);
        item->clearProp();
        for(unsigned int i = 0;i < props.size();i++){
            item->addProp(props[i].m_id,props[i].m_count);
        }
        item->updateProp();
    }
}
void FriendsPage::updateFriendPortrait(const std::string &uid,const std::string &head)
{
    if(!m_init || head.empty())
        return;
    std::map<std::string,FSizeWidgetDelegate *>::iterator iter;
    iter = m_friendMap.find(uid);
    if(iter != m_friendMap.end()){
        FriendItem *item = (FriendItem*)(iter->second->getWidget());
        item->updateFriendHead(head);
    }
}
void FriendsPage::updateFriendWonNum(const std::string &uid)
{
    if(!m_init)
        return;
    std::map<std::string,FSizeWidgetDelegate *>::iterator iter;
    iter = m_friendMap.find(uid);
    if(iter != m_friendMap.end()){
        FriendItem *item = (FriendItem*)(iter->second->getWidget());
        UiMsgEv::PlayerInfoEv *ev = m_serverIface->getPlayerInfoByUid(uid);
        if(ev)
            item->updateWonNum(ev);
    }
}
void FriendsPage::updateOnlineFriend()
{
    return;
    if(!m_init)
        return;
    const std::vector<std::string> &olf = m_serverIface->getOnlineFriends();
    for(unsigned int i = 0;i < olf.size();i++){
        std::map<std::string,FSizeWidgetDelegate *>::iterator iter;
        iter = m_friendMap.find(olf[i]);
        if(iter != m_friendMap.end()){
            FriendItem *item = (FriendItem*)(iter->second->getWidget());
            item->updateOnline(true);
        }
    }
}
void FriendsPage::onTitleAddClick(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_addFriendDialog != 0){
        m_addFriendDialog->destroy();
        m_addFriendDialog = 0;
    }
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_addFriendDialog == 0){
        m_addFriendDialog = new AddFriendDialog(root,ccc4(0,0,0,128));
        m_addFriendDialog->setCloseCB(this,callfuncND_selector(FriendsPage::onAddFriendDialogCloseClicked));
        m_addFriendDialog->setAddCB(this,callfuncND_selector(FriendsPage::onAddFriendDlalogAddClicked));
        m_addFriendDialog->exec();
    }
}
void FriendsPage::onTitleRefreshClick(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(!m_title->isRefreshing())
        m_serverIface->refreshFriendsInfo();
}
void FriendsPage::onAddFriendDialogCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_addFriendDialog != 0){
        m_addFriendDialog->destroy();
        m_addFriendDialog = 0;
    }
}
void FriendsPage::onAddFriendDlalogAddClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_addFriendDialog != 0){
        std::string id,word;
        m_addFriendDialog->getAskInfo(id,word);
        m_addFriendDialog->destroy();
        m_addFriendDialog = 0;
        if(!id.empty()){
            m_serverIface->addFriend(id,word);
            CCNode *root = this->getParent();
            while(root->getParent())
                root = root->getParent();
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            SendMsgAnim *anim = new SendMsgAnim(root,ccp(winSize.width / 2,winSize.height / 2));
            anim->exec();
        }
    }
}
