#include "friendtitle.h"

FriendTitle::FriendTitle()
{
    m_addListener = 0;
    m_addFunc = 0;
    m_refreshListener = 0;
    m_refreshFunc = 0;
    m_refreshImg = "titlebuttonbg";
    m_addImg = "uiaddfriend";
    m_refreshWidget = 0;
    m_refreshing = 0;
}
FriendTitle::~FriendTitle()
{

}
void FriendTitle::setAddCB(CCNode *node,SEL_CallFuncND func)
{
    m_addListener = node;
    m_addFunc = func;
}
void FriendTitle::setRefreshCB(CCNode *node,SEL_CallFuncND func)
{
    m_refreshListener = node;
    m_refreshFunc = func;
}
void FriendTitle::setTitle(const std::string &title)
{
    m_title = title;
}
void FriendTitle::setAddImg(const std::string &normal,const std::string &pressed)
{
    m_addImg = normal;
    m_addPressedImg = pressed;
}
void FriendTitle::setRefreshImg(const std::string &normal,const std::string &pressed)
{
    m_refreshImg = normal;
    m_refreshPressedImg = pressed;
}
void FriendTitle::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(m_refreshWidget != 0)
        return;
    BasButton *add = new BasButton;
    add->setButtonInfo("","default",m_addImg,CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85),m_addPressedImg);
    this->addChild(add);
    add->setLeft("parent",uilib::Left);
    add->setVertical("parent",0.5);
    add->setClickCB(m_addListener,m_addFunc);

    BasButton *refresh = new BasButton;
    refresh->setButtonInfo("","default",m_refreshImg,CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85),m_refreshPressedImg);
    this->addChild(refresh);
    refresh->setVertical("parent",0.5);
    refresh->setLeft(add->getName(),uilib::Right);
    refresh->setLeftMargin(10);

    refresh->setClickCB(m_refreshListener,m_refreshFunc);
    CCSprite *r = CCSprite::createWithSpriteFrameName("refresh.png");
    BasNodeDelegateWidget *rdele =new BasNodeDelegateWidget(r,CCSizeMake(m_anchorHeight * 0.6,m_anchorHeight * 0.6));
    refresh->addChild(rdele);
    rdele->setCenterIn("parent");
    m_refreshWidget = rdele;
}
void FriendTitle::setRefreshing(bool on)
{
    m_refreshing = on;
    startRefresh();
}
void FriendTitle::startRefresh()
{
    if(m_refreshWidget){
        if(m_refreshing){
            CCActionInterval *to = CCRotateBy::create(1,360);
            m_refreshWidget->runAction(CCRepeatForever::create(to));
        }else{
            m_refreshWidget->stopAllActions();
        }
    }
}
