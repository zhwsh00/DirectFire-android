#include "twitterpage.h"

TwitterPage::TwitterPage()
{
    m_itemInit = false;
}
TwitterPage::~TwitterPage()
{

}
void TwitterPage::moveInItem()
{
    BasSysPage::moveInItem();
}
void TwitterPage::moveOutItem()
{
    BasSysPage::moveOutItem();
}
void TwitterPage::layoutCompleted()
{
    BasSysPage::layoutCompleted();
    if(!m_itemInit)
        initItem();
}
void TwitterPage::initItem()
{
    BasButton *button = new BasButton;
    button->setButtonInfo("twitter");
    this->addChild(button);
    button->setCenterIn("parent");
}
