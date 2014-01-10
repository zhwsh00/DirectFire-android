#include "roomlayer.h"
#include "roommainwidget.h"

RoomLayer::RoomLayer()
{
    m_mainWidget = 0;
}
RoomLayer::~RoomLayer()
{
    if(m_mainWidget)
        delete m_mainWidget;
}
bool RoomLayer::init()
{
    bool ret = false;

    do {
        CC_BREAK_IF(!CCLayer::init());
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        m_mainWidget = new RoomMainWidget;
        m_mainWidget->setWidth(winSize.width);
        m_mainWidget->setHeight(winSize.height);
        m_mainWidget->setAnchorPoint(ccp(0,0));
        m_mainWidget->setPosition(ccp(0,0));
        this->addChild(m_mainWidget);
        m_mainWidget->layout();
        m_mainWidget->intoRoom();
        ret = true;
    }while(0);
    return ret;
}
void RoomLayer::setEnable(bool enable)
{
    m_mainWidget->setVisible(enable);
    m_mainWidget->setChatBoxVisible(enable);
    m_mainWidget->enableStartAfterSec(6);
    m_mainWidget->resetRoom();
}
