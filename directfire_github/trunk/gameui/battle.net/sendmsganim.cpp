#include "sendmsganim.h"
#include "gamecore/resource/resourcemgr.h"

SendMsgAnim::SendMsgAnim(CCNode *parent,const CCPoint &pos,const std::string &theme,const std::string &name)
{
    parent->addChild(this);
    m_pos = pos;
    m_theme = theme;
    m_animName = name;
}
SendMsgAnim::~SendMsgAnim()
{

}
void SendMsgAnim::setTheme(const std::string &theme,const std::string &anim)
{
    m_theme = theme;
    m_animName = anim;
}
void SendMsgAnim::exec()
{
    this->setAnchorPoint(ccp(0.5,0.5));
    this->setPosition(m_pos);

    UiThemeDef *def = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    std::string frameName;
    def->getNormalData()->getImg(m_animName,frameName);
    if(frameName.empty()){
        delete this;
        return;
    }
    initWithSpriteFrameName(frameName.data());
    this->setScale(4);
    CCPoint pos = this->getPosition();
    ccBezierConfig config;
    config.controlPoint_1 = ccp(pos.x + 400,pos.y);
    config.controlPoint_2 = ccp(pos.x,pos.y + 100);
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    config.endPosition = ccp(winsize.width,winsize.height);
    CCBezierTo *to = CCBezierTo::create(1,config);
    CCScaleTo *scale = CCScaleTo::create(1,0,0);
    CCFiniteTimeAction *action = CCSpawn::create(to,scale,0);
    this->runAction(CCSequence::create(action,CCCallFuncN::create(this,callfuncN_selector(SendMsgAnim::onActionFinished)),0));
}
void SendMsgAnim::onActionFinished(CCNode *node)
{
    node->removeFromParentAndCleanup(true);
}
