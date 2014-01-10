#include "sinapage.h"

SinaPage::SinaPage()
{
    m_itemInit = false;
}
SinaPage::~SinaPage()
{

}
void SinaPage::moveInItem()
{
    BasSysPage::moveInItem();
}
void SinaPage::moveOutItem()
{
    BasSysPage::moveOutItem();
}
void SinaPage::layoutCompleted()
{
    BasSysPage::layoutCompleted();
    if(!m_itemInit)
        initItem();
}
void SinaPage::initItem()
{
    BasButton *button = new BasButton;
    button->setButtonInfo("Sina");
    this->addChild(button);
    button->setCenterIn("parent");
}
