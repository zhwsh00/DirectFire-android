#include "gamepagetitle.h"

GamePageTitle::GamePageTitle()
{
    m_refreshListener = 0;
    m_refreshFunc = 0;
    m_nameSortListener = 0;
    m_nameSortFunc = 0;
    m_numSortListener = 0;
    m_numSortFunc = 0;
    m_dfListener = 0;
    m_dfFunc = 0;
    m_towerListener = 0;
    m_towerFunc = 0;
    m_theme = "default";
    m_refreshImg = "titlebuttonbg";
    m_refreshWidget = 0;
    m_refreshing = 0;
}
GamePageTitle::~GamePageTitle()
{

}
void GamePageTitle::setRefreshCB(CCNode *node,SEL_CallFuncND func)
{
    m_refreshListener = node;
    m_refreshFunc = func;
}
void GamePageTitle::setDfModelCB(CCNode *node,SEL_CallFuncND func)
{
    m_dfListener = node;
    m_dfFunc = func;
}
void GamePageTitle::setTowerModelCB(CCNode *node,SEL_CallFuncND func)
{
    m_towerListener = node;
    m_towerFunc = func;
}
void GamePageTitle::setSortByMapNameCB(CCNode *node,SEL_CallFuncND func)
{
    m_nameSortListener = node;
    m_nameSortFunc = func;
}
void GamePageTitle::setSortByPlayerNumCB(CCNode *node,SEL_CallFuncND func)
{
    m_numSortListener = node;
    m_numSortFunc = func;
}
void GamePageTitle::setTitle(const std::string &title)
{
    m_title = title;
}
void GamePageTitle::setRefreshImg(const std::string &normal,const std::string &pressed)
{
    m_refreshImg = normal;
    m_refreshPressedImg = pressed;
}
void GamePageTitle::layoutCompleted()
{
    BorderWidget::layoutCompleted();

    BasButton *df = new BasButton;
    df->setButtonInfo("",m_theme,"dfmode",CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85),"");
    this->addChild(df);
    df->setLeft("parent",uilib::Left);
    df->setVertical("parent",0.5);
    df->setClickCB(m_dfListener,m_dfFunc);

    BasButton *tower = new BasButton;
    tower->setButtonInfo("",m_theme,"towermode",CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85),"");
    this->addChild(tower);
    tower->setLeft(df->getName(),uilib::Right);
    tower->setVertical("parent",0.5);
    tower->setLeftMargin(10);
    tower->setClickCB(m_towerListener,m_towerFunc);

    BasButton *nameSort = new BasButton;
    nameSort->setButtonInfo("",m_theme,"sortmapname",CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85),m_refreshPressedImg);
    this->addChild(nameSort);
    nameSort->setLeft(tower->getName(),uilib::Right);
    nameSort->setVertical("parent",0.5);
    nameSort->setLeftMargin(10);
    nameSort->setClickCB(m_nameSortListener,m_nameSortFunc);

    BasButton *numSort = new BasButton;
    numSort->setButtonInfo("",m_theme,"sortplayernum",CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85),m_refreshPressedImg);
    this->addChild(numSort);
    numSort->setLeft(nameSort->getName(),uilib::Right);
    numSort->setVertical("parent",0.5);
    numSort->setLeftMargin(10);
    numSort->setClickCB(m_numSortListener,m_numSortFunc);

    BasButton *refresh = new BasButton;
    refresh->setButtonInfo("",m_theme,m_refreshImg,CCSizeMake(m_anchorHeight * 0.85,m_anchorHeight * 0.85),m_refreshPressedImg);
    this->addChild(refresh);
    refresh->setVertical("parent",0.5);
    refresh->setLeft(numSort->getName(),uilib::Right);
    refresh->setLeftMargin(10);
    refresh->setClickCB(m_refreshListener,m_refreshFunc);

    CCSprite *r = CCSprite::createWithSpriteFrameName("refresh.png");
    BasNodeDelegateWidget *rdele =new BasNodeDelegateWidget(r,CCSizeMake(m_anchorHeight * 0.6,m_anchorHeight * 0.6));
    refresh->addChild(rdele);
    rdele->setCenterIn("parent");
    m_refreshWidget = rdele;
}
void GamePageTitle::setRefreshing(bool on)
{
    m_refreshing = on;
    startRefresh();
}
void GamePageTitle::startRefresh()
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
