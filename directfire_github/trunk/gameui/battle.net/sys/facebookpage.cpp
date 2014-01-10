#include "facebookpage.h"

FaceBookPage::FaceBookPage()
{
    m_itemInit = false;
}
FaceBookPage::~FaceBookPage()
{

}
void FaceBookPage::moveInItem()
{
    BasSysPage::moveInItem();
}
void FaceBookPage::moveOutItem()
{
    BasSysPage::moveOutItem();
}
void FaceBookPage::layoutCompleted()
{
    BasSysPage::layoutCompleted();
    if(!m_itemInit)
        initItem();
}
void FaceBookPage::initItem()
{
    BasButton *button = new BasButton;
    button->setButtonInfo("facebook");
    this->addChild(button);
    button->setCenterIn("parent");
}
