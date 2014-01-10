#include "moveoutaction.h"
#include "../base/touchnode.h"

namespace uilib
{

MoveOutNodeAction::MoveOutNodeAction()
{

}
MoveOutNodeAction::~MoveOutNodeAction()
{

}
void MoveOutNodeAction::doAction(const std::vector<TouchNode*> &nodes)
{
#define finishCB(last) last ? CCCallFuncN::create(this,callfuncN_selector(BasNodeAction::finished)) : 0
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    CCSize parentsize,nodesize;
    CCPoint destPos;
    float delay = m_startTime;
    TouchNode *touchnode;
    for(unsigned int i  = 0;i < nodes.size();i++){
        bool isLast = (i == (nodes.size() - 1));
        touchnode = nodes[i];
        if(touchnode->parent()){
            touchnode->parent()->getAnchorSize(parentsize.width,parentsize.height);
        }else{
            parentsize = winsize;
        }
        touchnode->getAnchorSize(nodesize.width,nodesize.height);
        destPos = touchnode->getDestPoint();
        CCActionInterval *inAction = 0;
        CCActionEase *easeAction = createEaseAction();
        switch(m_outType){
        case HorizontalRightOut:{
            CCPoint pos = ccp(parentsize.width + nodesize.width,destPos.y);
            CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,pos);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            break;
        }
        case HorizontalLeftOut:{
            CCPoint pos = ccp(-nodesize.width,destPos.y);
            CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,pos);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            break;
        }
        case HorizontalBothOut:{
            if((i+1) % 2){
                CCPoint pos = ccp(parentsize.width + nodesize.width,destPos.y);
                CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,pos);
                inAction = (CCActionInterval*)CCSequence::create(
                            CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
                break;
            }else{
                CCPoint pos = ccp(-nodesize.width,destPos.y);
                CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,pos);
                inAction = (CCActionInterval*)CCSequence::create(
                            CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
                break;
            }
            break;
        }
        case VerticalTopOut:{
            CCPoint pos = ccp(destPos.x,parentsize.height - nodesize.height/2);
            CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,pos);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            break;
        }
        case VerticalBottomOut:{
            CCPoint pos = ccp(destPos.x,nodesize.height/2);
            CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,pos);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            break;
        }
        case VerticalBothOut:{
            if((i+1) % 2){
                CCPoint pos = ccp(destPos.x,nodesize.height/2);
                CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,pos);
                inAction = (CCActionInterval*)CCSequence::create(
                            CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            }else{
                CCPoint pos = ccp(destPos.x,parentsize.height - nodesize.height/2);
                CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,pos);
                inAction = (CCActionInterval*)CCSequence::create(
                            CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            }
            break;
        }
        case ScaleOut:{
            touchnode->setScale(1.0);
            CCScaleTo *scaleTo = CCScaleTo::create(m_actionTime,0.0);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),scaleTo,finishCB(isLast),0);
            break;
        }
        case ScaleXOut:{
            touchnode->setScale(1.0);
            CCScaleTo *scaleTo = CCScaleTo::create(m_actionTime,0.0,1.0);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),scaleTo,scaleTo,finishCB(isLast),0);
            break;
        }
        case ScaleYOut:{
            touchnode->setScale(1.0);
            CCScaleTo *scaleTo = CCScaleTo::create(m_actionTime,1.0,0.0);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),scaleTo,finishCB(isLast),0);
            break;
        }
        case SwayOut:{
            touchnode->setPosition(destPos);
            break;
        }
        case RotateOut:{
            touchnode->setPosition(destPos);
            break;
        }
        case BlinkOut:{
            touchnode->setPosition(destPos);
            break;
        }
        case ReelOut:{
            touchnode->setPosition(destPos);
            break;
        }
        case FireOut:{
            touchnode->setPosition(destPos);
            break;
        }
        default:{
            break;
        }
        }
        delay += m_delayTime;
        if(easeAction && inAction){
            CCEaseRateAction *rateAction = dynamic_cast<CCEaseRateAction*>(easeAction);
            if(rateAction){
                rateAction->initWithAction(inAction,m_rate);
                touchnode->runAction(rateAction);
            }else{
                easeAction->initWithAction(inAction);
                touchnode->runAction(easeAction);
            }
        }else if(inAction){
            touchnode->runAction(inAction);
        }
    }
}
}

