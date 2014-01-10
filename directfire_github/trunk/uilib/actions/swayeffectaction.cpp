#include "swayeffectaction.h"
#include "../base/touchnode.h"
namespace uilib
{
SwayEffectAction::SwayEffectAction()
{

}
SwayEffectAction::~SwayEffectAction()
{

}
void SwayEffectAction::doAction(TouchNode *node,bool enable)
{
    if(m_running == enable)
        return;

    m_running = enable;
    if(m_running){
        float runTime = 0.5;
        CCRotateTo *rotate1 = CCRotateTo::create(runTime,10);
        CCRotateTo *rotate2 = CCRotateTo::create(runTime,0);
        CCRotateTo *rotate3 = CCRotateTo::create(runTime,-10);
        CCRotateTo *rotate4 = CCRotateTo::create(runTime,0);
        CCAction *action = CCRepeatForever::create((CCActionInterval*)CCSequence::create(rotate1,rotate2
                                             ,rotate3,rotate4,0));
        node->runAction(action);
    }else{
        node->stopAllActions();
    }
}
}
