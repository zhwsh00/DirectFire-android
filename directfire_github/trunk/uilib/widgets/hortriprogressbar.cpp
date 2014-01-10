#include "hortriprogressbar.h"
#include "../base/uithemedef.h"
namespace uilib
{

HorTriProgressBar::HorTriProgressBar()
{
    m_progTimerHead = 0;
    m_progTimerTail = 0;
    m_progTimerCenter = 0;
    m_spriteHead = 0;
    m_spriteTail = 0;
    m_spriteCenter = 0;
    m_bgSprite = 0;

    m_headRate = 0;
    m_centerRate = 0;
    m_tailRate = 0;
}
HorTriProgressBar::~HorTriProgressBar()
{

}
void HorTriProgressBar::setTheme(const std::string &theme,const std::string &bg,const std::string &fg)
{
    m_theme = theme;
    m_bgSprite = new HTriWidget;
    m_bgSprite->setTheme(m_theme,bg);
    m_bgSprite->setSkinFillVer(m_skinFillVer);
    this->addChild(m_bgSprite);
    m_bgSprite->setFill("parent");
    std::string headimg,tailimg,bodyimg;
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    uiDef->getNormalData()->getImg(fg,bodyimg);
    uiDef->getNormalData()->getImg(fg + "head",headimg);
    uiDef->getNormalData()->getImg(fg + "tail",tailimg);
    if(headimg.empty() || tailimg.empty() || bodyimg.empty()){
        cout << "HorTriProgressBar::setTheme,can not get correct img!" << endl;
        return;
    }
    m_spriteHead = CCSprite::create();
    m_spriteHead->initWithSpriteFrameName(headimg.data());
    m_spriteCenter = CCSprite::create();
    m_spriteCenter->initWithSpriteFrameName(bodyimg.data());
    m_spriteTail = CCSprite::create();
    m_spriteTail->initWithSpriteFrameName(tailimg.data());

    m_progTimerHead = CCProgressTimer::create(m_spriteHead);
    m_progTimerHead->setType(kCCProgressTimerTypeBar);
    m_progTimerHead->setBarChangeRate(ccp(1,0));
    m_progTimerHead->setMidpoint(ccp(0,1));
    m_progTimerTail = CCProgressTimer::create(m_spriteTail);
    m_progTimerTail->setType(kCCProgressTimerTypeBar);
    m_progTimerTail->setBarChangeRate(ccp(1,0));
    m_progTimerTail->setMidpoint(ccp(0,1));
    m_progTimerCenter = CCProgressTimer::create(m_spriteCenter);
    m_progTimerCenter->setType(kCCProgressTimerTypeBar);
    m_progTimerCenter->setBarChangeRate(ccp(1,0));
    m_progTimerCenter->setMidpoint(ccp(0,1));

    this->CCNode::addChild(m_progTimerHead,1);
    this->CCNode::addChild(m_progTimerTail,1);
    this->CCNode::addChild(m_progTimerCenter,1);
}
void HorTriProgressBar::setProgressTo(float time,float percent)
{
    m_progTimerHead->stopAllActions();
    m_progTimerTail->stopAllActions();
    m_progTimerCenter->stopAllActions();
    m_destPercent = percent;
    m_actionTime = time;
    m_progTimerHead->setPercentage(0);
    m_progTimerTail->setPercentage(0);
    m_progTimerCenter->setPercentage(0);
    if(m_destPercent / 100 > m_headRate){
        CCProgressTo *to = CCProgressTo::create(time * m_headRate,100);
        m_progTimerHead->runAction(CCSequence::create(
                                        to,
                                       CCCallFuncN::create(this,callfuncN_selector(HorTriProgressBar::onHeadProgTimerFinished)),
                                       0));
    }else{
        CCProgressTo *to = CCProgressTo::create(time,percent);
        m_progTimerHead->runAction(to);
    }
}
void HorTriProgressBar::setProgressAdd(float time,float percent)
{
    m_actionTime = time;
}
void HorTriProgressBar::setBarChangeRate(const CCPoint &p)
{
    m_progTimerHead->setBarChangeRate(p);
    m_progTimerTail->setBarChangeRate(p);
    m_progTimerCenter->setBarChangeRate(p);
}
void HorTriProgressBar::setMidpoint(const CCPoint &p)
{
    m_progTimerHead->setMidpoint(p);
    m_progTimerTail->setMidpoint(p);
    m_progTimerCenter->setMidpoint(p);
}
void HorTriProgressBar::layoutCompleted()
{
    BasWidget::layoutCompleted();
    CCSize headsize = m_progTimerHead->getContentSize();
    CCSize tailsize = m_progTimerTail->getContentSize();
    CCSize csize = m_progTimerCenter->getContentSize();
    m_headRate = headsize.width / m_anchorWidth;
    m_tailRate = tailsize.width / m_anchorWidth;
    m_centerRate = 1 - m_headRate - m_tailRate;
    if(m_anchorWidth < (headsize.width + tailsize.width)){
        this->setVisible(false);
        return;
    }else{
        this->setVisible(true);
    }
    m_progTimerHead->setAnchorPoint(ccp(0,0));
    m_progTimerHead->setPosition(ccp(0,0));
    if(m_skinFillVer) m_progTimerHead->setScaleY(m_anchorHeight / headsize.height);

    m_progTimerTail->setAnchorPoint(ccp(1,0));
    m_progTimerTail->setPosition(ccp(m_anchorWidth,0));
    if(m_skinFillVer) m_progTimerTail->setScaleY(m_anchorHeight / tailsize.height);

    m_progTimerCenter->setAnchorPoint(ccp(0,0));
    m_progTimerCenter->setPosition(ccp(headsize.width,0));
    m_progTimerCenter->setScaleX((m_anchorWidth - headsize.width - tailsize.width) / csize.width);
    if(m_skinFillVer) m_progTimerCenter->setScaleY(m_anchorHeight / csize.height);
}
void HorTriProgressBar::onHeadProgTimerFinished(CCNode *sender,void *data)
{
    float leftp = m_destPercent - m_headRate * 100;
    if(leftp > m_centerRate * 100){
        CCProgressTo *to = CCProgressTo::create(m_actionTime * m_centerRate,100);
        m_progTimerCenter->runAction(CCSequence::create(to,
                                CCCallFuncN::create(this,callfuncN_selector(HorTriProgressBar::onCenterProgTimerFinished)),
                                0));
    }else{
        CCProgressTo *to = CCProgressTo::create(m_actionTime * m_centerRate,leftp / m_centerRate);
        m_progTimerCenter->runAction(to);
    }
}
void HorTriProgressBar::onCenterProgTimerFinished(CCNode *sender,void *data)
{
    float leftp = m_destPercent - m_headRate * 100 - m_centerRate * 100;
    if(leftp < 0) return;
    leftp /= m_tailRate;
    CCProgressTo *to = CCProgressTo::create(m_actionTime * m_tailRate,leftp);
    m_progTimerTail->runAction(to);
}
}
