#include "abssyspage.h"

BasSysPage::BasSysPage()
{
    BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
    BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
    moveIn->setEaseType(uilib::EaseSineInOut);
    moveIn->setMoveInType(uilib::HorizontalRightIn);
    moveOut->setEaseType(uilib::EaseSineInOut);
    moveOut->setMoveOutType(uilib::HorizontalRightOut);
    moveOut->setFinishCB(this,callfuncN_selector(BasSysPage::onMoveoutFinished),0);
    this->setMoveinAction(moveIn);
    this->setMoveoutAction(moveOut);
}
BasSysPage::~BasSysPage()
{

}
void BasSysPage::moveInItem()
{
    this->setVisible(true);
}
void BasSysPage::moveOutItem()
{

}
void BasSysPage::onMoveoutFinished(CCNode *node)
{
    this->setVisible(false);
}
