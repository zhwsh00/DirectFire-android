#include "abssocialitem.h"
#include "socialpage.h"

BasSocialItem::BasSocialItem(SocialPage *owner)
{
    m_owner = owner;
    m_leftButton = 0;
    m_rightButton = 0;
    m_isFirst = false;
    m_isLast = false;
    m_index = 0;
    m_inited = false;
}
BasSocialItem::~BasSocialItem()
{

}
void BasSocialItem::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(!m_inited){
        initMe();
    }
    m_inited = true;
}
void BasSocialItem::setFirstLast(bool first,bool last)
{
    m_isFirst = first;
    m_isLast = last;
}
void BasSocialItem::initMe()
{
    if(!m_isFirst){
        m_leftButton = new BasButton;
        m_leftButton->setButtonInfo("","default","lefthand",CCSizeMake(80,30));
        m_leftButton->setClickCB(this,callfuncND_selector(BasSocialItem::onLeftClicked));
        this->addChild(m_leftButton);
        m_leftButton->setLeft("parent",uilib::Left);
        m_leftButton->setBottom("parent",uilib::Bottom);
        m_leftButton->setBottomMargin(15);
        m_leftButton->setLeftMargin(20);
    }
    if(!m_isLast){
        m_rightButton = new BasButton;
        m_rightButton->setButtonInfo("","default","righthand",CCSizeMake(80,30));
        m_rightButton->setClickCB(this,callfuncND_selector(BasSocialItem::onRightClicked));
        this->addChild(m_rightButton);
        m_rightButton->setRight("parent",uilib::Right);
        m_rightButton->setBottom("parent",uilib::Bottom);
        m_rightButton->setBottomMargin(15);
        m_rightButton->setRightMargin(20);
    }
}
void BasSocialItem::moveInItem()
{

}
void BasSocialItem::moveOutItem()
{

}
void BasSocialItem::onLeftClicked(CCNode *node,void *data)
{
    m_owner->leftHandClicked(m_index);
}
void BasSocialItem::onRightClicked(CCNode *node,void *data)
{
    m_owner->rightHandClicked(m_index);
}
