#include "socialpage.h"

#include "waitingmoreitem.h"
#include "thumbfootitem.h"
#include "turnplateitem.h"
#include "guessspellitem.h"

#include "gamecore/sounds/soundmgr.h"

SocialPage::SocialPage(CCNode *parent,const ccColor4B &color) :
    BasShowDialog(parent,color)
{
    // reset size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    setWidth(size.width);
    setHeight(230);
    this->setPosition(ccp(size.width / 2,size.height * 0.66));
}
SocialPage::~SocialPage()
{

}
void SocialPage::initSocialPage()
{
    m_items.push_back(new GuessSpellItem(this));
    m_items.push_back(new ThumbFootItem(this));
    m_items.push_back(new TurnPlateItem(this));

    BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
    moveIn->setEaseType(uilib::EaseNone);
    moveIn->setMoveInType(uilib::HorizontalRightIn);

    BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
    moveOut->setEaseType(uilib::EaseNone);
    moveOut->setMoveOutType(uilib::HorizontalRightOut);

    for(unsigned int i = 0;i < m_items.size();i++){
        BasSocialItem *item = m_items[i];
        this->addChild(item);
        item->setIndex(i);
        item->setLeft("parent",uilib::Left);
        item->setRight("parent",uilib::Right);
        item->setTop("parent",uilib::Top);
        item->setBottom("parent",uilib::Bottom);
        item->setMoveinAction(moveIn);
        item->setMoveoutAction(moveOut);
    }
    m_items[0]->setFirstLast(true,false);
    m_items[m_items.size() - 1]->setFirstLast(false,true);
}
void SocialPage::thumbPortraitUpdate()
{
    ThumbFootItem *item = (ThumbFootItem*)m_items[1];
    item->thumbPortraitUpdate();
}
void SocialPage::usePropReplyGot()
{
    TurnPlateItem *item = (TurnPlateItem*)m_items[2];
    item->usePropReplyGot();
}
void SocialPage::childLayoutCompleted()
{
    BasShowDialog::childLayoutCompleted();
    for(unsigned int i = 1;i < m_items.size();i++){
        m_items[i]->setVisible(false);
    }
}
void SocialPage::onMoveoutFinished(CCNode *node)
{
    BasSocialItem *touch = dynamic_cast<BasSocialItem*>(node);
    if(touch){
        touch->setVisible(false);
    }
}
void SocialPage::leftHandClicked(int index)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(index == 0)
        return;
    BasSocialItem *curr = m_items[index];
    BasSocialItem *show = m_items[index - 1];
    BasNodeAction *moveOut = curr->getMoveoutAction();
    BasNodeAction *moveIn = curr->getMoveinAction();
    moveOut->setMoveOutType(uilib::HorizontalRightOut);
    moveOut->setFinishCB(this,callfuncN_selector(SocialPage::onMoveoutFinished),curr);
    moveIn->setMoveInType(uilib::HorizontalLeftIn);

    curr->moveOut();
    show->moveIn();
    show->setVisible(true);

    curr->moveOutItem();
    show->moveInItem();
}
void SocialPage::rightHandClicked(int index)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(index == (m_items.size() - 1))
        return;
    BasSocialItem *curr = m_items[index];
    BasSocialItem *show = m_items[index + 1];
    BasNodeAction *moveOut = curr->getMoveoutAction();
    moveOut->setFinishCB(this,callfuncN_selector(SocialPage::onMoveoutFinished),curr);
    BasNodeAction *moveIn = curr->getMoveinAction();
    moveOut->setMoveOutType(uilib::HorizontalLeftOut);
    moveIn->setMoveInType(uilib::HorizontalRightIn);

    curr->moveOut();
    show->moveIn();
    show->setVisible(true);

    curr->moveOutItem();
    show->moveInItem();
}
void SocialPage::exec()
{
    initSocialPage();
    BasShowDialog::exec();
}
void SocialPage::childLayoutStarted()
{
    BasShowDialog::childLayoutStarted();
    m_closeButton->setRightMargin(-10);
}
