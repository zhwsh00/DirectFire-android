#include "systitle.h"

SysTitle::SysTitle()
{
    m_theme = "default";
    m_title = "System Setting";
    m_backListener = 0;
    m_backFunc = 0;
    m_backEnabled = false;
    m_backButton = 0;
    m_inited = false;
}
SysTitle::~SysTitle()
{

}
void SysTitle::setBackClickCB(CCNode *listener,SEL_CallFuncND func)
{
    m_backListener = listener;
    m_backFunc = func;
}
void SysTitle::setTitle(const std::string &title)
{
    m_title = title;
}
void SysTitle::setBackEnabled(bool can)
{
    m_backEnabled = can;
    if(m_backButton)
        m_backButton->setVisible(m_backEnabled);
}
void SysTitle::layoutCompleted()
{
    BorderWidget::layoutCompleted();
    if(m_inited)
        return;
    m_backButton = new BasButton;
    m_backButton->setButtonInfo("",m_theme,"sys_back",CCSizeMake(0,0));
    this->addChild(m_backButton);
    m_backButton->setCenterIn("parent");
    m_backButton->setClickCB(m_backListener,m_backFunc);
    m_backButton->setVisible(m_backEnabled);
}
