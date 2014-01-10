#include "scaleeffectaction.h"
#include "../base/touchnode.h"
namespace uilib
{
ScaleEffectAction::ScaleEffectAction()
{

}
ScaleEffectAction::~ScaleEffectAction()
{

}
void ScaleEffectAction::doAction(TouchNode *node,bool enable)
{
    if(m_running == enable){
        return;
    }

    m_running = enable;
    if(m_running){
        float runtime = 0.5;
        CCScaleTo *scale1 = CCScaleTo::create(runtime,1.1);
        CCScaleTo *scale2 = CCScaleTo::create(runtime,1.0);
        CCAction *action = CCRepeatForever::create((CCActionInterval*)CCSequence::create(scale1,scale2,0));
        node->runAction(action);
    }else{
        node->setScale(1.0);
        node->stopAllActions();
    }
}
}
