#include "askfriendwidget.h"
#include "askasfrienddialog.h"
#include "addfrienddialog.h"
#include "sendmsganim.h"

#include "utils/sysutils.h"

#include "gamecore/sounds/soundmgr.h"

AskFriendWidget::AskFriendWidget(BasWidget *parent)
{
    m_inited = false;
    m_theme = "default";
    m_hasImg = "friendadd_yes.png";
    m_hasSprite = 0;
    m_hasWidget = 0;
    m_has = false;
    m_askDialog = 0;
    m_addDialog = 0;
    m_serverIface = ServerInterface::getInstance();
    parent->addChild(this);
    setCanTouch(true);
}
AskFriendWidget::~AskFriendWidget()
{

}
void AskFriendWidget::askFriendUpdated()
{
    m_has = m_serverIface->hasUnreadAskFriend();
    if(m_has){
        m_hasWidget->setEffectActionEnabled(true);
    }else{
        m_hasWidget->setEffectActionEnabled(false);
    }
}
void AskFriendWidget::setTheme(const std::string &theme,const std::string &has,const std::string &no)
{
    m_theme = theme;
    m_hasImg = has;
}
void AskFriendWidget::finish()
{
    m_hasSprite = CCSprite::create();
    m_hasSprite->initWithSpriteFrameName(m_hasImg.data());

    BasNodeLimitWidget *hasDele = new BasNodeLimitWidget(m_hasSprite);
    this->addChild(hasDele);
    hasDele->setFill("parent");
    m_hasWidget = hasDele;

    BasNodeEffectAction *effectAction = UiNodeActionFactory::getInstance()->getEffectActionByName("scale");
    m_hasWidget->setEffectAction(effectAction);
    m_hasWidget->setEffectActionEnabled(false);
}
void AskFriendWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(!m_inited){
        m_inited = true;
        finish();
    }
}
void AskFriendWidget::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{

}
void AskFriendWidget::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{

}
void AskFriendWidget::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(!m_has){
        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        if(m_addDialog == 0){
            m_addDialog = new AddFriendDialog(root,ccc4(0,0,0,128));
            m_addDialog->setCloseCB(this,callfuncND_selector(AskFriendWidget::onAddFriendCloseClicked));
            m_addDialog->setAddCB(this,callfuncND_selector(AskFriendWidget::onAddFriendAddClicked));
            m_addDialog->exec();
        }
        return;
    }
    UiMsgEv::AskFriendInfo *info = m_serverIface->getAskFriendInfo();
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_askDialog != 0){
        m_askDialog->destroy();
        m_askDialog = 0;
    }

    m_askDialog = new AskAsFriendDialog(root,ccc4(0,0,0,128));
    m_askDialog->setCloseCB(this,callfuncND_selector(AskFriendWidget::onAskDialogCloseClicked));
    m_askDialog->setOkCB(this,callfuncND_selector(AskFriendWidget::onAskDialogOkClicked));
    m_askDialog->setRejectCB(this,callfuncND_selector(AskFriendWidget::onAskDialogRejectClicked));
    std::string nick = info->m_friendNick;
    if(nick.empty()){
        mailToNickName(info->m_friendMail,nick);
    }
    std::string *head;
    if(m_serverIface->getHeadPortrait(info->m_friendId,&head)){
        m_askDialog->setAskInfo(info->m_friendId,nick,info->m_askWord,*head);
    }else{
        m_askDialog->setAskInfo(info->m_friendId,nick,info->m_askWord,"");
    }
    m_askDialog->exec();
    if(!m_serverIface->hasUnreadAskFriend()){
        askFriendUpdated();
    }
}
void AskFriendWidget::onAskDialogCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_askDialog->destroy();
    m_askDialog = 0;
}
void AskFriendWidget::onAskDialogOkClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_serverIface->acceptAskFriend(m_askDialog->getAskId());
    onAskDialogCloseClicked(0,0);
}
void AskFriendWidget::onAskDialogRejectClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_serverIface->rejectAskFriend(m_askDialog->getAskId());
    onAskDialogCloseClicked(0,0);
}
void AskFriendWidget::onAddFriendCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_addDialog){
        m_addDialog->destroy();
        m_addDialog = 0;
    }
}
void AskFriendWidget::onAddFriendAddClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_addDialog != 0){
        std::string id,word;
        m_addDialog->getAskInfo(id,word);
        m_addDialog->destroy();
        m_addDialog = 0;
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
