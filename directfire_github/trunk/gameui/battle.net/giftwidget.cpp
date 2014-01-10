#include "giftwidget.h"
#include "recgiftshow.h"
#include "sendmsganim.h"
#include "sendgiftdialog.h"
#include "iapgiftshow.h"

#include "gamecore/sounds/soundmgr.h"
#include "gamecore/resource/resourcemgr.h"
#include <algorithm>
using namespace std;

GiftWidget::GiftWidget(BasWidget *parent)
{
    m_inited = false;
    m_theme = "default";
    m_hasImg = "gift_yes.png";
    m_hasSprite = 0;
    m_has = false;
    m_giftShow = 0;
    m_sendGiftDialog = 0;
    m_serverIface = ServerInterface::getInstance();
    parent->addChild(this);
    setCanTouch(true);
}
GiftWidget::~GiftWidget()
{

}
void GiftWidget::giftUpdated()
{
    m_has = m_serverIface->hasUnreadGift();
    if(m_has){
        this->setEffectActionEnabled(true);
    }else{
        this->setEffectActionEnabled(false);
    }
}
void GiftWidget::setTheme(const std::string &theme,const std::string &has,const std::string &no)
{
    m_theme = theme;
    m_hasImg = has;
}
void GiftWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(!m_inited){
        m_inited = true;
        finish();
    }
}
void GiftWidget::finish()
{
    m_hasSprite = CCSprite::create();
    m_hasSprite->initWithSpriteFrameName(m_hasImg.data());

    BasNodeDelegateWidget *hasDele = new BasNodeDelegateWidget(m_hasSprite,CCSizeMake(m_anchorWidth,m_anchorHeight));
    this->addChild(hasDele);
    hasDele->setCenterIn("parent");

    BasNodeEffectAction *effectAction = UiNodeActionFactory::getInstance()->getEffectActionByName("scale");
    this->setEffectAction(effectAction);
    this->setEffectActionEnabled(false);
}
bool GiftWidget::getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size)
{
    sprites.push_back(m_hasSprite);
    size = m_hasSprite->getContentSize();
    return true;
}
void GiftWidget::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{

}
void GiftWidget::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{

}
void GiftWidget::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(!m_has)
        return;
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    std::vector<UiMsgEv::GiftPropEv> giftsMsg;
    std::string senderId;
    std::string senderName;
    std::string word;
    int reason = 0;
    m_serverIface->getReceivedGift(senderId,senderName,giftsMsg,word,reason);
    // 6: levelup.
    if(reason == 6) {
        IAPGiftShow *iapGiftShow = new IAPGiftShow(root);
        iapGiftShow->setTitleText(ResourceMgr::getInstance()->getLangDef()->getStringById(StringEnum::LevelUpSuccess));
        iapGiftShow->setGifts(giftsMsg);
        iapGiftShow->setCoinNum(0);
        iapGiftShow->exec();
    } else {
        if(m_giftShow == 0){
            m_giftShow = new RecGiftShow(root);
            m_giftShow->setCloseCB(this,callfuncND_selector(GiftWidget::onGiftShowCloseClicked));
            m_giftShow->setSendMsgCB(this,callfuncND_selector(GiftWidget::onGiftShowSendMsgClicked));
            m_giftShow->setSendGiftCB(this,callfuncND_selector(GiftWidget::onSendGiftClicked));
            m_giftShow->setAddFriendCB(this,callfuncND_selector(GiftWidget::onAddFriendClicked));
            if(1){
                //init giftshow
                std::string *head;
                std::vector<UiMsgEv::GiftPropEv> &gifts = m_giftShow->getGiftsContainer();
                gifts.clear();
                m_senderId = senderId;
                m_senderName = senderName;
                std::string name = senderName;
                if(senderName.empty())
                    name = senderId;
                bool isFriend = m_serverIface->isFriend(m_senderId);
                if(m_serverIface->getHeadPortrait(m_senderId,&head)){
                    m_giftShow->setSenderInfo(isFriend,name,word,*head);
                }else{
                    m_giftShow->setSenderInfo(isFriend,name,word);
                }
                m_giftShow->setSenderContent(giftsMsg);
            }
            m_giftShow->exec();
        }
    }
    if(!m_serverIface->hasUnreadGift()){
        giftUpdated();
    }
}
void GiftWidget::onGiftShowCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_giftShow){
        m_giftShow->getMoveoutAction()->setFinishCB(this,callfuncN_selector(GiftWidget::onGiftShowMoveOutFinished));
        m_giftShow->moveOut();
    }
}
void GiftWidget::onGiftShowSendMsgClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_giftShow){
        m_giftShow->getMoveoutAction()->setFinishCB(this,callfuncN_selector(GiftWidget::onGiftShowMoveOutSendMsgFinished));
        m_giftShow->moveOut();
    }
}
void GiftWidget::onSendGiftClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_giftShow){
        m_giftShow->getMoveoutAction()->setFinishCB(this,callfuncN_selector(GiftWidget::onGiftShowMoveOutFinished));
        m_giftShow->moveOut();
    }
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_sendGiftDialog == 0){
        m_sendGiftDialog = new SendGiftDialog(root,ccc4(0,0,0,128));
        m_sendGiftDialog->setCloseCB(this,callfuncND_selector(GiftWidget::onSendGiftDialogCloseClicked));
        m_sendGiftDialog->setSendCB(this,callfuncND_selector(GiftWidget::onSendGiftSendClicked));
        std::string name = m_senderName;
        if(name.empty())
            name = m_senderId;
        std::string *head;
        if(m_serverIface->getHeadPortrait(m_senderId,&head)){
            m_sendGiftDialog->setSendtoInfo(name,*head);
        }else{
            m_sendGiftDialog->setSendtoInfo(name,"");
        }
        std::vector<UiMsgEv::GiftPropEv> props;
        std::string id = m_serverIface->getLoginAccountInfo()->m_id;
        m_serverIface->getAllUnzeroProps(id,props);
        std::sort(props.begin(),props.end(),prop_sortbyId);
        for(unsigned int i = 0;i < props.size();i++){
            m_sendGiftDialog->addProp(props[i].m_id,props[i].m_count);
        }
        m_sendGiftDialog->exec();
    }
}
void GiftWidget::onAddFriendClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(!m_senderId.empty())
        m_serverIface->addFriend(m_senderId,"");
}
void GiftWidget::onGiftShowMoveOutFinished(CCNode *node)
{
    if(m_giftShow){
        delete m_giftShow;
        m_giftShow = 0;
    }
}
void GiftWidget::onGiftShowMoveOutSendMsgFinished(CCNode *node)
{
    if(m_giftShow){
        std::string title,word;
        m_giftShow->getReplyWord(title,word);
        delete m_giftShow;
        m_giftShow = 0;
        m_serverIface->sendMail(m_senderId,title,word);
        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        SendMsgAnim *anim = new SendMsgAnim(root,ccp(winSize.width / 2,winSize.height / 2));
        anim->exec();
    }
}
void GiftWidget::onSendGiftSendClicked(CCNode *node,void *data)
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
        m_serverIface->sendGift(m_senderId,word,gifts);
        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        SendMsgAnim *anim = new SendMsgAnim(root,ccp(winSize.width / 2,winSize.height / 2));
        anim->setTheme(m_theme,"uigiftsending");
        anim->exec();
    }
}
void GiftWidget::onSendGiftDialogCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_sendGiftDialog){
        m_sendGiftDialog->destroy();
        m_sendGiftDialog = 0;
    }
}
