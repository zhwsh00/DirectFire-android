#include "herostitle.h"

HerosTitle::HerosTitle()
{
    m_typeListener = 0;
    m_typeFunc = 0;
    m_refreshListener = 0;
    m_refreshFunc = 0;
    m_theme = "default";
    m_refreshWidget = 0;
    m_refreshing = 0;
}
HerosTitle::~HerosTitle()
{

}
void HerosTitle::setTypeCB(CCNode *node,SEL_CallFuncND func)
{
    m_typeListener = node;
    m_typeFunc = func;
}
void HerosTitle::setRefreshCB(CCNode *node,SEL_CallFuncND func)
{
    m_refreshListener = node;
    m_refreshFunc = func;
}
void HerosTitle::setTitle(const std::string &title)
{
    m_title = title;
}
void HerosTitle::layoutCompleted()
{
    BorderWidget::layoutCompleted();
    if(m_refreshWidget != 0)
        return;
    BasButton *refreshbutton = new BasButton;
    refreshbutton->setButtonInfo("",m_theme,"titlebuttonbg",CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85));
    refreshbutton->setClickCB(m_refreshListener,m_refreshFunc);
    CCSprite *r = CCSprite::createWithSpriteFrameName("refresh.png");
    BasNodeDelegateWidget *rdele =new BasNodeDelegateWidget(r,CCSizeMake(m_anchorHeight * 0.6,m_anchorHeight * 0.6));
    refreshbutton->addChild(rdele);
    rdele->setCenterIn("parent");

    m_refreshWidget = rdele;

    BasWidget *typeWidget = new BasWidget;
    this->addChild(typeWidget);
    typeWidget->setLeft("parent",uilib::Left);
    typeWidget->setRight("parent",uilib::Right);
    typeWidget->setTop("parent",uilib::Top);
    typeWidget->setBottom("parent",uilib::Bottom);
    HorizontalLayout *lay = new HorizontalLayout;
    BasButton *typeButton;
    typeButton = new BasButton;
    typeButton->setButtonInfo("",m_theme,"herolevel",CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85));
    typeButton->setWidthHeightRate(1.0);
    typeButton->setClickCB(m_typeListener,m_typeFunc);
    typeButton->setButtonIndex(UiMsgEv::HeroLevel);
    lay->addWidget(typeButton);
    m_buttons.push_back(typeButton);

    typeButton = new BasButton;
    typeButton->setButtonInfo("",m_theme,"herocoin",CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85));
    typeButton->setWidthHeightRate(1.0);
    typeButton->setClickCB(m_typeListener,m_typeFunc);
    typeButton->setButtonIndex(UiMsgEv::HeroGold);
    lay->addWidget(typeButton);
    m_buttons.push_back(typeButton);

    typeButton = new BasButton;
    typeButton->setButtonInfo("",m_theme,"heroplayed",CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85));
    typeButton->setWidthHeightRate(1.0);
    typeButton->setClickCB(m_typeListener,m_typeFunc);
    typeButton->setButtonIndex(UiMsgEv::HeroPlayed);
    lay->addWidget(typeButton);
    m_buttons.push_back(typeButton);

    typeButton = new BasButton;
    typeButton->setButtonInfo("",m_theme,"herowin",CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85));
    typeButton->setWidthHeightRate(1.0);
    typeButton->setClickCB(m_typeListener,m_typeFunc);
    typeButton->setButtonIndex(UiMsgEv::HeroWon);
    lay->addWidget(typeButton);
    m_buttons.push_back(typeButton);

    typeButton = new BasButton;
    typeButton->setButtonInfo("",m_theme,"herolose",CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85));
    typeButton->setWidthHeightRate(1.0);
    typeButton->setClickCB(m_typeListener,m_typeFunc);
    typeButton->setButtonIndex(UiMsgEv::HeroLose);
    lay->addWidget(typeButton);
    m_buttons.push_back(typeButton);
    lay->addWidget(refreshbutton);

    lay->setChildAlign(0,uilib::Bottom);
    lay->setChildAlign(1,uilib::Bottom);
    lay->setChildAlign(2,uilib::Bottom);
    lay->setChildAlign(3,uilib::Bottom);
    lay->setChildAlign(4,uilib::Bottom);
    lay->setChildAlign(5,uilib::Bottom);

    lay->setAveraged(true);
    lay->setSpacing(0);
    lay->setRightMargin(20);
    this->setLayout(lay);
    m_currIndex = -1;
}
void HerosTitle::setRefreshing(bool on)
{
    m_refreshing = on;
    startRefresh();
}
void HerosTitle::setSelectIndex(int index)
{
    if(m_currIndex == index){
        m_buttons[m_currIndex - (int)UiMsgEv::HeroLevel]->setScale(1.2);
        return;
    }
    if(m_currIndex != -1)
        m_buttons[m_currIndex - (int)UiMsgEv::HeroLevel]->setScale(1.0);
    m_currIndex = index;
    m_buttons[m_currIndex - (int)UiMsgEv::HeroLevel]->setScale(1.2);
}
void HerosTitle::startRefresh()
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
