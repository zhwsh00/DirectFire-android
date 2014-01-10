#include "gamerulepage.h"

#include "gamecore/resource/resourcemgr.h"

GameRulePage::GameRulePage()
{
    m_scroll = 0;
}
GameRulePage::~GameRulePage()
{

}
void GameRulePage::moveInItem()
{
    BasSysPage::moveInItem();
    if(m_scroll)
        m_scroll->scrollToEnd(20,true);
}
void GameRulePage::moveOutItem()
{
    BasSysPage::moveOutItem();
    if(m_scroll)
        m_scroll->scrollToBegin(true);
}
void GameRulePage::layoutCompleted()
{
    BasSysPage::layoutCompleted();
    if(m_scroll == 0)
        initItem();
}
void GameRulePage::initItem()
{
    if(m_scroll != 0)
        return;
    m_scroll = new VerScrollWidget();
    this->addChild(m_scroll);
    m_scroll->setFill("parent");
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    CCLabelBMFont *label = CCLabelBMFont::create(lang->getStringById(StringEnum::GameRuleContent).data(),
                                                 "fonts/font40.fnt",m_anchorWidth * 0.9,kCCTextAlignmentLeft);
    FSizeCCNodeDelegate *dele = new FSizeCCNodeDelegate(label);
    m_scroll->addFixedSizeWidget(dele);
}
