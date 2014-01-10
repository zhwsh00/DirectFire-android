#include "mailwidget.h"
#include "sendmsganim.h"
#include "sendmsgdialog.h"

#include "gamecore/sounds/soundmgr.h"

MailWidget::MailWidget(BasWidget *parent)
{
    m_inited = false;
    m_theme = "default";
    m_mailImg = "mail_yes.png";
    m_mailSprite = 0;
    m_hasMail = false;
    m_mailDialog = 0;
    m_serverIface = ServerInterface::getInstance();
    parent->addChild(this);
    setCanTouch(true);
}
MailWidget::~MailWidget()
{

}
void MailWidget::mailUpdated()
{
    m_hasMail = m_serverIface->hasUnreadMail();
    if(m_hasMail){
        this->setEffectActionEnabled(true);
    }else{
        this->setEffectActionEnabled(false);
    }
}
void MailWidget::setTheme(const std::string &theme,const std::string &mail,const std::string &nomail)
{
    m_theme = theme;
    m_mailImg = mail;
}
void MailWidget::finish()
{
    m_mailSprite = CCSprite::create();
    m_mailSprite->initWithSpriteFrameName(m_mailImg.data());

    BasNodeLimitWidget *hasDele = new BasNodeLimitWidget(m_mailSprite);
    this->addChild(hasDele);
    hasDele->setFill("parent");

    BasNodeEffectAction *effectAction = UiNodeActionFactory::getInstance()->getEffectActionByName("scale");
    this->setEffectAction(effectAction);
    this->setEffectActionEnabled(false);
}
void MailWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(!m_inited){
        m_inited = true;
        finish();
    }
}
bool MailWidget::getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size)
{
    sprites.push_back(m_mailSprite);
    size = m_mailSprite->getContentSize();
    return true;
}
void MailWidget::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{

}
void MailWidget::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{

}
void MailWidget::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(!m_hasMail) return;
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    std::string title,body;
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_serverIface->getUnreadMail(m_senderId,m_senderName,title,body)){
        m_mailDialog = new SendMsgDialog(root,ccc4(0,0,0,128));
        m_mailDialog->setMsgInfo(title,body);
        std::string *data;
        if(m_serverIface->getHeadPortrait(m_senderId,&data)){
            m_mailDialog->setSenderInfo(m_senderId,m_senderName,*data);
            m_mailDialog->setRecInfo(m_senderId,m_senderName,*data);
        }else{
            m_mailDialog->setSenderInfo(m_senderId,m_senderName,"");
            m_mailDialog->setRecInfo(m_senderId,m_senderName,"");
        }
        m_mailDialog->setCanReply(true);
        m_mailDialog->setInitPage(true,true);
        m_mailDialog->setInitShowPage(false);

        m_mailDialog->setCloseCB(this,callfuncND_selector(MailWidget::onMailDialogCloseClicked));
        m_mailDialog->setSendCB(this,callfuncND_selector(MailWidget::onMailDialogSendClicked));
        m_mailDialog->exec();
    }
    if(!m_serverIface->hasUnreadMail()){
        mailUpdated();
    }
}
void MailWidget::onMailDialogCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_mailDialog != 0){
        m_mailDialog->destroy();
        m_mailDialog = 0;
        return;
    }
}
void MailWidget::onMailDialogSendClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_mailDialog){
        std::string title,word;
        m_mailDialog->getSendMsg(title,word);
        m_mailDialog->destroy();
        m_mailDialog = 0;
        if(word.size() != 0){
            ServerInterface::getInstance()->sendMail(m_senderId,title,word);
            CCNode *root = this->getParent();
            while(root->getParent())
                root = root->getParent();
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            SendMsgAnim *anim = new SendMsgAnim(root,ccp(winSize.width / 2,winSize.height / 2));
            anim->exec();
        }
    }
}
