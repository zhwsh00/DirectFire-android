#include "horprogressbar.h"
#include "../base/uithemedef.h"

namespace uilib
{

HorProgressBar::HorProgressBar()
{
    m_progTimer = 0;
    m_bgSprite = 0;
}
HorProgressBar::~HorProgressBar()
{

}
void HorProgressBar::setTheme(const std::string &theme,const std::string &bg,const std::string &fg)
{
    m_theme = theme;
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    m_bgSprite = CCSprite::create();
    uiDef->getNormalData()->getImg(bg,m_bg);
    m_bgSprite->initWithSpriteFrameName(m_bg.data());
    CCSprite *fgSprite = CCSprite::create();
    uiDef->getNormalData()->getImg(fg,m_fg);
    fgSprite->initWithSpriteFrameName(m_fg.data());
    m_progTimer = CCProgressTimer::create(fgSprite);
    m_progTimer->setType(kCCProgressTimerTypeBar);
    m_progTimer->setBarChangeRate(ccp(1,0));
    m_progTimer->setMidpoint(ccp(0,1));
    this->CCNode::addChild(m_bgSprite);
    this->CCNode::addChild(m_progTimer);
    CCSize size = m_bgSprite->getContentSize();
    this->setPreferedSize(size);
}
void HorProgressBar::setProgressTo(float time,float percent)
{
    if(m_progTimer){
        CCProgressTo *to = CCProgressTo::create(time,percent);
        m_progTimer->runAction(to);
    }
}
void HorProgressBar::setProgressAdd(float time,float percent)
{
    if(m_progTimer){
        CCProgressTo *to = CCProgressTo::create(time,percent + m_progTimer->getPercentage());
        m_progTimer->runAction(to);
    }
}
void HorProgressBar::setBarChangeRate(const CCPoint &p)
{
    if(m_progTimer){
        m_progTimer->setBarChangeRate(p);
    }
}
void HorProgressBar::setMidpoint(const CCPoint &p)
{
    if(m_progTimer){
        m_progTimer->setMidpoint(p);
    }
}
void HorProgressBar::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(m_bgSprite){
        CCSize size = m_bgSprite->getContentSize();
        m_bgSprite->setAnchorPoint(ccp(0.5,0.5));
        m_bgSprite->setScaleX(m_anchorWidth / size.width);
        m_bgSprite->setScaleY(m_anchorHeight / size.height);
        m_bgSprite->setPosition(ccp(m_anchorWidth / 2,m_anchorHeight / 2));
    }
    if(m_progTimer){
        CCSize size = m_progTimer->getContentSize();
        m_progTimer->setAnchorPoint(ccp(0.5,0.5));
        m_progTimer->setScaleX(m_anchorWidth / size.width);
        m_progTimer->setScaleY(m_anchorHeight / size.height);
        m_progTimer->setPosition(ccp(m_anchorWidth / 2,m_anchorHeight / 2));
    }
}

}
