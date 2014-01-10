#include "absnodeaction.h"
#include "moveinaction.h"
#include "moveoutaction.h"
#include "shineeffectaction.h"
#include "swayeffectaction.h"
#include "scaleeffectaction.h"
#include "animeffectaction.h"

namespace uilib
{
static CCActionEase  *s_createEaseAction(EaseType easeType)
{
    switch(easeType){
    case EaseNone:{
        return new CCEaseRateAction();
        break;
    }
    case EaseIn:{
        return new CCEaseIn();
        break;
    }
    case EaseOut:{
        return new CCEaseOut();
        break;
    }
    case EaseInOut:{
        return new CCEaseInOut();
        break;
    }
    case EaseExponentialIn:{
        return new CCEaseExponentialIn();
        break;
    }
    case EaseExponentialOut:{
        return new CCEaseExponentialOut();
        break;
    }
    case EaseExponentialInOut:{
        return new CCEaseExponentialInOut();
        break;
    }
    case EaseSineIn:{
        return new CCEaseSineIn();
        break;
    }
    case EaseSineOut:{
        return new CCEaseSineOut();
        break;
    }
    case EaseSineInOut:{
        return new CCEaseSineInOut();
        break;
    }
    case EaseElastic:{
        return new CCEaseElastic();
        break;
    }
    case EaseElasticIn:{
        return new CCEaseElasticIn();
        break;
    }
    case EaseElasticOut:{
        return new CCEaseElasticOut();
        break;
    }
    case EaseElasticInOut:{
        return new CCEaseElasticInOut();
        break;
    }
    case EaseBounce:{
        return new CCEaseBounce();
        break;
    }
    case EaseBounceIn:{
        return new CCEaseBounceIn();
        break;
    }
    case EaseBounceOut:{
        return new CCEaseBounceOut();
        break;
    }
    case EaseBounceInOut:{
        return new CCEaseBounceInOut();
        break;
    }
    case EaseBackIn:{
        return new CCEaseBackIn();
        break;
    }
    case EaseBackOut:{
        return new CCEaseBackOut();
        break;
    }
    case EaseBackInOut:{
        return new CCEaseBackInOut();
        break;
    }
    default:{
        break;
    }
    }
    return 0;
}

BasNodeEffectAction::BasNodeEffectAction()
{
    m_easeType = EaseBounceInOut;
    m_actionTime = 0.0;
    m_startTime = 0.0;
    m_finishFunc = 0;
    m_listener = 0;
    m_running = false;
}
BasNodeEffectAction::~BasNodeEffectAction()
{

}
void BasNodeEffectAction::finished()
{
    if(m_listener && m_finishFunc){
        (m_listener->*m_finishFunc)(this);
    }
}
void BasNodeEffectAction::setFinishCB(CCNode *listener,SEL_CallFuncN func)
{
    m_listener = listener;
    m_finishFunc = func;
}

BasNodeAction::BasNodeAction()
{
    m_actionRunNum = 0;
    m_delayTime = 0.05;
    m_easeType = EaseNone;
    m_actionTime = 0.5;
    m_startTime = 0.0;
    m_rate = 1.0;
    m_inType = HorizontalRightIn;
    m_outType = HorizontalRightOut;
    m_finishFunc = 0;
    m_listener = 0;
    m_actionNode = 0;
}
BasNodeAction::~BasNodeAction()
{

}
CCActionEase *BasNodeAction::createEaseAction()
{
    CCActionEase * ease = s_createEaseAction(m_easeType);
    if(ease){
        ease->autorelease();
        return ease;
    }else{
        return 0;
    }
}
void BasNodeAction::setFinishCB(CCNode *listener,SEL_CallFuncN func,CCNode *actionNode)
{
    m_listener = listener;
    m_finishFunc = func;
    m_actionNode = actionNode;
}
void BasNodeAction::finished()
{
    if(m_listener && m_finishFunc){
        (m_listener->*m_finishFunc)(m_actionNode);
    }
}

UiNodeActionFactory *UiNodeActionFactory::m_instance = 0;
UiNodeActionFactory::UiNodeActionFactory()
{

}
UiNodeActionFactory::~UiNodeActionFactory()
{

}
UiNodeActionFactory *UiNodeActionFactory::getInstance()
{
    if(m_instance == 0)
        m_instance = new UiNodeActionFactory;
    return m_instance;
}
BasNodeAction *UiNodeActionFactory::getMoveActionByName(const std::string &name)
{
    if(name == "movein"){
        return new MoveInNodeAction();
    }else if(name == "moveout"){
        return new MoveOutNodeAction();
    }else{
        return 0;
    }
}
BasNodeEffectAction *UiNodeActionFactory::getEffectActionByName(const std::string &name)
{
    if(name == "shine"){
        return new ShineEffectAction();
    }else if(name == "sway"){
        return new SwayEffectAction();
    }else if(name == "scale"){
        return new ScaleEffectAction();
    }else if(name == "anim"){
        return new AnimEffectAction();
    }else{
        return 0;
    }
}

}
