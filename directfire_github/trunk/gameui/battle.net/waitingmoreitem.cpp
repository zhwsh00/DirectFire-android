#include "waitingmoreitem.h"

#include "gamecore/resource/resourcemgr.h"

WaitingMoreItem::WaitingMoreItem(SocialPage *owner)
    : BasSocialItem(owner)
{
    m_itemInited = false;
    m_autoScroll = 0;
}
WaitingMoreItem::~WaitingMoreItem()
{

}
void WaitingMoreItem::moveInItem()
{
    if(!m_itemInited)
        init();
    if(m_autoScroll)
        m_autoScroll->scrollToEnd(5,true);
}
void WaitingMoreItem::moveOutItem()
{
    if(m_autoScroll)
        m_autoScroll->scrollToBegin(true);
}
void WaitingMoreItem::init(int dummy)
{
    if(m_itemInited)
        return;
    ResourceMgr *rgr = ResourceMgr::getInstance();
    LangDef *lang = rgr->getLangDef();
    CCLabelBMFont *font = CCLabelBMFont::create(lang->getStringById(StringEnum::WaitingMore).data(),
                                                "fonts/font20.fnt");
    FSizeCCNodeDelegate *dele = new FSizeCCNodeDelegate(font,font->getContentSize());
    this->addChild(dele);
    dele->setVertical("parent",0.5);
    dele->setHorizontal("parent",0.7);
    if(1){
        m_autoScroll = new VerAutoScrollWidget;
        m_autoScroll->setVerticalScrollPolicy(uilib::ScrollShow_Never);
        m_autoScroll->setHorizontalScrollPolicy(uilib::ScrollShow_Never);
        this->addChild(m_autoScroll);
        if(m_leftButton)
            m_autoScroll->setLeft(m_leftButton->getName(),uilib::Right);
        else
            m_autoScroll->setLeft("parent",uilib::Left);
        m_autoScroll->setRight(dele->getName(),uilib::Left);
        m_autoScroll->setTop("parent",uilib::Top);
        m_autoScroll->setBottom("parent",uilib::Bottom);
        m_autoScroll->setMargins(10);
        CCSprite *dev = CCSprite::createWithSpriteFrameName("dever.png");
        FSizeSpriteDelegate *devdele = new FSizeSpriteDelegate(dev);
        m_autoScroll->addFixedSizeWidget(devdele);
    }
    m_itemInited = true;
    this->layout(true);
}
