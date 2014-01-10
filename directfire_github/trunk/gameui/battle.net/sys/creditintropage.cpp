#include "creditintropage.h"

CreditInfoPage::CreditInfoPage()
{
    m_itemInit = false;
}
CreditInfoPage::~CreditInfoPage()
{

}
void CreditInfoPage::moveInItem()
{
    BasSysPage::moveInItem();
}
void CreditInfoPage::moveOutItem()
{
    BasSysPage::moveOutItem();
}
void CreditInfoPage::layoutCompleted()
{
    BasSysPage::layoutCompleted();
    if(!m_itemInit)
        initItem();
}
void CreditInfoPage::initItem()
{
    m_scroll = new VerScrollWidget;
    m_scroll->setHorizontalScrollPolicy(uilib::ScrollShow_Never);
    m_scroll->setVerticalScrollPolicy(uilib::ScrollShow_Never);
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("dever.png");
    FSizeCCNodeDelegate *dele = new FSizeCCNodeDelegate(sprite);
    CCSize size;
    dele->getFixedSize(size);
    m_scroll->setWidth(size.width * 1.2);
    m_scroll->setHeight(m_anchorHeight);
    m_scroll->addFixedSizeWidget(dele);
    this->addChild(m_scroll);
    m_scroll->setCenterIn("parent");
    m_itemInit = true;
}
