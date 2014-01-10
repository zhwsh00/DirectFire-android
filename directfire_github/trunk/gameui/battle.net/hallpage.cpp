#include "hallpage.h"
#include "chatwidget.h"
#include "socialpage.h"

#include "sendmsgdialog.h"
#include "sendgiftdialog.h"
#include "addfrienddialog.h"
#include "sendmsganim.h"

#include "utils/sysutils.h"
#include "mailwidget.h"

#include "giftwidget.h"
#include "taskwidget.h"
#include "askfriendwidget.h"

#include "utils/ccutils.h"

#include "gamecore/serverinterface.h"
#include "gamecore/sounds/soundmgr.h"

#include "gamecore/resource/resourcemgr.h"

#include "shoppage.h"
#include "syspage.h"

HallPage::HallPage(uilib::BasWidget *container) : BasPage(container)
{
    m_topWidget = 0;
    m_socialPage = 0;
    m_chatWidget = 0;

    m_thumbNum = 0;
    m_footNum = 0;
    m_thumbFont = 0;
    m_footFont = 0;
    m_serverIFace = ServerInterface::getInstance();
    m_addFriendDialog = 0;
    m_sendGiftDialog = 0;
    m_sendMsgDialog = 0;

    m_shopPage = 0;
    m_sysPage = 0;
    init();
}
HallPage::~HallPage()
{

}
void HallPage::moveinPage()
{
    if(m_hallMascot)
        m_hallMascot->moveIn();
}
void HallPage::moveoutPage()
{
    if(m_hallMascot)
        m_hallMascot->moveOut();
}
void HallPage::thumbPortraitUpdate()
{
    if(m_socialPage)
        m_socialPage->thumbPortraitUpdate();
}
void HallPage::usePropReplyGot()
{
    if(m_socialPage)
        m_socialPage->usePropReplyGot();
}
void HallPage::hallChatInfoGot()
{
    this->schedule(schedule_selector(HallPage::chatInfoStep),1.0);
}
void HallPage::headSettingClosed(int status)
{
    if (status == 0) {
        m_chatWidget->setChatBoxVisible(false);
    } else {
        m_chatWidget->setChatBoxVisible(true);
    }
}
void HallPage::onKeyPadBackClicked()
{
    CCLog("11111111111");
}
void HallPage::chatInfoStep(float dt)
{
    UiMsgEv::ChatInfo *chat = m_serverIFace->getHallChatInfo();
    if(chat){
        if(m_userId != chat->m_senderId)
            m_chatWidget->addChatInfo(chat,0);
    }else{
        this->unschedule(schedule_selector(HallPage::chatInfoStep));
    }
}
void HallPage::init(int dummy)
{
    if(1){
        //chat widget
        m_chatWidget = new ChatWidget();
        m_chatWidget->setChatType(UiMsgEv::MsgToHallAll);
        m_chatWidget->setHeadCanClick(true);
        m_chatWidget->setHeadClickCB(this,callfuncND_selector(HallPage::onHeadClicked));
        UiMsgEv::AccountInfoEv *accEv = m_serverIFace->getLoginAccountInfo();
        m_chatWidget->setChaterInfo(accEv->m_id,accEv->m_mail,accEv->m_name);
        m_userId = accEv->m_id;
        m_chatWidget->setLeft("parent",uilib::Left);
        m_chatWidget->setRight("parent",uilib::Right);
        m_chatWidget->setBottom("parent",uilib::Bottom);
        m_chatWidget->setTop("parent",uilib::Top);
        m_chatWidget->setTopMargin(24);
    }
    this->addChild(m_chatWidget);

    if(1){ //for beta2 ,this all moved to usershow bottom
        float srate = getAdaptResourceScale();
        BasWidget *leftWidget = new BasWidget;
        if(1){
            this->addChild(leftWidget);
            leftWidget->setLeft("parent",uilib::Left);
            leftWidget->setVertical("parent",0.0);
            leftWidget->setWidth(1);
            leftWidget->setHeight(10);
        }
        if(1){
            //add friend widget
            m_askFriendWidget = new AskFriendWidget(this);
            m_askFriendWidget->setVertical(leftWidget->getName(),0.5);
            m_askFriendWidget->setLeft(leftWidget->getName(),uilib::Right);
            m_askFriendWidget->setWidth(77 * srate);
            m_askFriendWidget->setHeight(77 * srate);
            m_askFriendWidget->setLeftMargin(10);

            leftWidget = m_askFriendWidget;
        }
        if(1){
            //mail widget
            m_mailWidget = new MailWidget(this);
            m_mailWidget->setVertical(leftWidget->getName(),0.5);
            m_mailWidget->setLeft(leftWidget->getName(),uilib::Right);
            m_mailWidget->setWidth(77 * srate);
            m_mailWidget->setHeight(77 * srate);
            m_mailWidget->setLeftMargin(10);

            leftWidget = m_mailWidget;
        }
        if(1){
            //gift widget
            m_giftWidget = new GiftWidget(this);
            m_giftWidget->setVertical(leftWidget->getName(),0.5);
            m_giftWidget->setLeft(leftWidget->getName(),uilib::Right);
            m_giftWidget->setWidth(77 * srate);
            m_giftWidget->setHeight(77 * srate);
            m_giftWidget->setLeftMargin(10);

            leftWidget = m_giftWidget;
        }
        if(1){
            //task widget
            m_taskWidget = new TaskWidget(this);
            m_taskWidget->setVertical(leftWidget->getName(),0.5);
            m_taskWidget->setLeft(leftWidget->getName(),uilib::Right);
            m_taskWidget->setWidth(77 * srate);
            m_taskWidget->setHeight(77 * srate);
            m_taskWidget->setLeftMargin(10);

            leftWidget = m_taskWidget;
        }
    }
    if(1){
        //hall mascot
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        m_hallMascot = new HallMascot;
        this->addChild(m_hallMascot);
        m_hallMascot->addButton(lang->getStringById(StringEnum::ShopPage));
        m_hallMascot->addButton(lang->getStringById(StringEnum::SysPage));
        m_hallMascot->addButton(lang->getStringById(StringEnum::SocialPage));
        m_hallMascot->setButtonCB(this,callfuncND_selector(HallPage::onHallMascotClicked));
        m_hallMascot->finish();
    }
}
void HallPage::onHeadClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_headId.clear();
    m_headMail.clear();
    m_headNick.clear();
    CCPoint pos;
    m_chatWidget->getHeadInfo(m_headId,m_headMail,m_headNick,pos);
    if(m_headId.empty())
        return;
    if(m_userId == m_headId)
        return;
    TouchNode *root = this;
    pos = root->convertToNodeSpace(pos);
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    PopButtonsDialog *pop = new PopButtonsDialog(root,pos);
    pop->setButtonCB(this,callfuncND_selector(HallPage::onPopButtonClicked));

    pop->addButton(lang->getStringById(StringEnum::SendMsg));
    pop->addButton(lang->getStringById(StringEnum::SendGift));
    if(!m_serverIFace->isFriend(m_userId))
        pop->addButton(lang->getStringById(StringEnum::AddFriend));
    pop->setSpacing(10);
    pop->setEdgeSize(20);
    pop->exec();
}
void HallPage::onPopButtonClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data;
    switch(index){
    case 0:{
        onSendMsgClicked();
        break;
    }
    case 1:{
        onSendGiftClicked();
        break;
    }
    case 2:{
        onAddFriendClicked();
        break;
    }
    default:{
        break;
    }
    }
}
void HallPage::onHallMascotClicked(CCNode *node,void *data)
{
    // disable hall chat/feedback input box
    ServerInterface::getInstance()->headSettingClosed(false);
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data;
    if(index == 0){
        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        m_shopPage = new ShopPage(root,ccc4(0,0,0,64));
        m_shopPage->setCloseCB(this,callfuncND_selector(HallPage::onShopPageCloseClicked));
        m_shopPage->exec();
    }else if(index == 1){
        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        m_sysPage = new SysPage(root,ccc4(0,0,0,64));
        m_sysPage->setCloseCB(this,callfuncND_selector(HallPage::onSysPageCloseClicked));
        m_sysPage->exec();
    }else if(index == 2){
        //social page
        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        m_socialPage = new SocialPage(root,ccc4(0,0,0,128));
        m_socialPage->setCloseCB(this,callfuncND_selector(HallPage::onSocialPageCloseClicked));
        m_socialPage->exec();
    }
}

void HallPage::onShopPageCloseClicked(CCNode *node,void *data)
{
    // enable hall chat/feedback input box
    ServerInterface::getInstance()->headSettingClosed(true);
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_shopPage != 0){
        m_shopPage->destroy();
        m_shopPage = 0;
        return;
    }
}
void HallPage::onSysPageCloseClicked(CCNode *node,void *data)
{
    // enable hall chat/feedback input box
    ServerInterface::getInstance()->headSettingClosed(true);
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_sysPage != 0){
        m_sysPage->destroy();
        m_sysPage = 0;
        return;
    }
}
void HallPage::onSocialPageCloseClicked(CCNode *node,void *data)
{
    // enable hall chat/feedback input box
    ServerInterface::getInstance()->headSettingClosed(true);
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_socialPage){
        m_socialPage->destroy();
        m_socialPage = 0;
        return;
    }
}
void HallPage::onSendMsgClicked()
{
    if(m_sendMsgDialog != 0){
        m_sendMsgDialog->destroy();
        m_sendMsgDialog = 0;
    }
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_sendMsgDialog == 0){
        m_sendMsgDialog = new SendMsgDialog(root,ccc4(0,0,0,128));
        m_sendMsgDialog->setCloseCB(this,callfuncND_selector(HallPage::onSendMsgCloseClicked));
        m_sendMsgDialog->setSendCB(this,callfuncND_selector(HallPage::onSendMsgSendClicked));
        m_sendMsgDialog->setInitShowPage(true);
        m_sendMsgDialog->setInitPage(true,false);
        std::string name = m_headNick;
        if(name.empty())
            mailToNickName(m_headMail,name);
        m_sendMsgDialog->setRecInfo(m_headId,name,"");
        m_sendMsgDialog->exec();
    }
}
void HallPage::onSendGiftClicked()
{
    if(m_sendGiftDialog != 0){
        m_sendGiftDialog->destroy();
        m_sendGiftDialog = 0;
    }
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_sendGiftDialog == 0){
        m_sendGiftDialog = new SendGiftDialog(root,ccc4(0,0,0,128));
        m_sendGiftDialog->setCloseCB(this,callfuncND_selector(HallPage::onSendGiftCloseClicked));
        m_sendGiftDialog->setSendCB(this,callfuncND_selector(HallPage::onSendGiftSendClicked));
        std::string name = m_headNick;
        if(name.empty())
            mailToNickName(m_headMail,name);

        std::vector<UiMsgEv::GiftPropEv> props;
        m_serverIFace->getAllUnzeroProps(m_userId,props);
        std::sort(props.begin(),props.end(),prop_sortbyId);
        for(unsigned int i = 0;i < props.size();i++){
            m_sendGiftDialog->addProp(props[i].m_id,props[i].m_count);
        }
        m_sendGiftDialog->exec();
    }
}
void HallPage::onAddFriendClicked()
{
    if(m_sendGiftDialog != 0){
        m_sendGiftDialog->destroy();
        m_sendGiftDialog = 0;
    }
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_addFriendDialog == 0){
        m_addFriendDialog = new AddFriendDialog(root,ccc4(0,0,0,128));
        m_addFriendDialog->setCloseCB(this,callfuncND_selector(HallPage::onAddFriendCloseClicked));
        m_addFriendDialog->setAddCB(this,callfuncND_selector(HallPage::onAddFriendAddClicked));
        m_addFriendDialog->setAddId(m_headId);
        m_addFriendDialog->exec();
    }
}
void HallPage::onSendGiftCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_sendGiftDialog){
        m_sendGiftDialog->destroy();
        m_sendGiftDialog = 0;
    }
}
void HallPage::onSendGiftSendClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    std::vector<UiMsgEv::GiftPropEv> gifts;
    std::string word;
    if(m_sendGiftDialog){
        m_sendGiftDialog->getSendProp(gifts,word);
        m_sendGiftDialog->destroy();
        m_sendGiftDialog = 0;
        if(word.empty() && gifts.size() == 0)
            return;
        ServerInterface::getInstance()->sendGift(m_headId,word,gifts);
        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        SendMsgAnim *anim = new SendMsgAnim(root,ccp(winSize.width / 2,winSize.height / 2));
        anim->setTheme("default","uigiftsending");
        anim->exec();
    }
}
void HallPage::onSendMsgCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_sendMsgDialog){
        m_sendMsgDialog->destroy();
        m_sendMsgDialog = 0;
    }
}
void HallPage::onSendMsgSendClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_sendMsgDialog){
        std::string title,word;
        m_sendMsgDialog->getSendMsg(title,word);
        m_sendMsgDialog->destroy();
        m_sendMsgDialog = 0;
        if(word.size() != 0){
            ServerInterface::getInstance()->sendMail(m_headId,title,word);
            CCNode *root = this->getParent();
            while(root->getParent())
                root = root->getParent();
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            SendMsgAnim *anim = new SendMsgAnim(root,ccp(winSize.width / 2,winSize.height / 2));
            anim->exec();
        }
    }
}
void HallPage::onAddFriendCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_addFriendDialog){
        m_addFriendDialog->destroy();
        m_addFriendDialog = 0;
    }
}
void HallPage::onAddFriendAddClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_addFriendDialog != 0){
        std::string id,word;
        m_addFriendDialog->getAskInfo(id,word);
        m_addFriendDialog->destroy();
        m_addFriendDialog = 0;
        if(!id.empty()){
            m_serverIFace->addFriend(id,word);
            CCNode *root = this->getParent();
            while(root->getParent())
                root = root->getParent();
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            SendMsgAnim *anim = new SendMsgAnim(root,ccp(winSize.width / 2,winSize.height / 2));
            anim->exec();
        }
    }
}
void HallPage::giftUpdate()
{
    if(m_giftWidget)
        m_giftWidget->giftUpdated();
}
void HallPage::mailUpdate()
{
    if(m_mailWidget)
        m_mailWidget->mailUpdated();
}
void HallPage::askFriendUpdate()
{
    if(m_askFriendWidget)
        m_askFriendWidget->askFriendUpdated();
}
void HallPage::taskUpdate()
{
    if(m_taskWidget)
        m_taskWidget->taskUpdated();
}
