#include "animeffectaction.h"
#include "../base/touchnode.h"
#include "../base/uithemedef.h"
#include "../base/absanimsprite.h"
namespace uilib
{
AnimEffectAction::AnimEffectAction()
{
    m_animSprite = 0;
}
AnimEffectAction::~AnimEffectAction()
{

}
void AnimEffectAction::doAction(TouchNode *node,bool enable)
{
    if(m_running == enable)
        return;
    if(m_animName.size() == 0)
        return;

    m_running = enable;
    if(m_running){
        if(m_animSprite == 0){
            m_animSprite = UiThemeMgrProxy::getInstance()->getThemeMgr()->getAnimSpriteByName(m_animName);
            node->CCNode::addChild(m_animSprite,-1);
            m_animSprite->setAnchorPoint(ccp(0.5,0));
            float w,h;
            node->getAnchorSize(w,h);
            m_animSprite->setPosition(ccp(w/2,0));
            m_animSprite->playInLoop(-1);
        }else{
            m_animSprite->setVisible(true);
            m_animSprite->end();
        }
    }else{
        if(m_animSprite){
            m_animSprite->stopAllActions();
            m_animSprite->setVisible(false);
        }
    }
}
}
