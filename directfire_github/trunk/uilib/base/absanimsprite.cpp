#include "absanimsprite.h"

namespace uilib {

BasAnimSprite::BasAnimSprite(const std::string &animName,const std::string &firstFrame)
{
    m_autoRelease = 0;
    m_finishListener = 0;
    m_finishFunc = 0;
    m_animName = animName;
    m_firstFrame = firstFrame;
    m_isRunning = false;
    m_animAction = 0;
    autorelease();
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_firstFrame.data());
    if(pFrame != 0){
        initWithSpriteFrame(pFrame);
        m_animation = CCAnimationCache::sharedAnimationCache()->animationByName(m_animName.data());
    }else{
        m_animation = 0;
    }
}
BasAnimSprite::~BasAnimSprite()
{

}
void BasAnimSprite::playInLoop(int loop)
{
    if(m_animation){
        m_animation->setLoops(loop);
        start();
    }
}
void BasAnimSprite::start()
{
    stopAllActions();
    if(m_animation){
        m_animAction = this->runAction(CCSequence::create(
                CCAnimate::create(m_animation),
                CCCallFuncN::create(this, callfuncN_selector(BasAnimSprite::animFinish)),
                0
            ));
        m_isRunning = true;
    }
}
void BasAnimSprite::end()
{
    stopAllActions();
    m_isRunning = false;
}
void BasAnimSprite::setAnimFinishCB(CCNode *listener,SEL_CallFuncND func)
{
    m_finishListener = listener;
    m_finishFunc = func;
}
void BasAnimSprite::animFinish(CCNode *node)
{
    m_isRunning = false;
    if(m_finishListener && m_finishFunc){
        (m_finishListener->*m_finishFunc)(this,0);
    }else if(m_autoRelease){
        stopAllActions();
        this->removeFromParentAndCleanup(true);
    }
}

}