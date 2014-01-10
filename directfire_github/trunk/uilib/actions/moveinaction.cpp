#include "moveinaction.h"
#include "../base/touchnode.h"

namespace uilib
{

MoveInNodeAction::MoveInNodeAction()
{

}
MoveInNodeAction::~MoveInNodeAction()
{

}
void MoveInNodeAction::doAction(const std::vector<TouchNode*> &nodes)
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
        switch(m_inType){
        case HorizontalRightIn:{
            touchnode->setPosition(parentsize.width + nodesize.width,destPos.y);
            CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,destPos);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            break;
        }
        case HorizontalLeftIn:{
            touchnode->setPosition(-nodesize.width,destPos.y);
            CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,destPos);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            break;
        }
        case HorizontalBothIn:{
            if((i+1) % 2){
                touchnode->setPosition(parentsize.width + nodesize.width,destPos.y);
                CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,destPos);
                inAction = (CCActionInterval*)CCSequence::create(
                            CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
                break;
            }else{
                touchnode->setPosition(-nodesize.width,destPos.y);
                CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,destPos);
                inAction = (CCActionInterval*)CCSequence::create(
                            CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
                break;
            }
            break;
        }
        case VerticalTopIn:{
            touchnode->setPosition(destPos.x,parentsize.height + nodesize.height);
            CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,destPos);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            break;
        }
        case DropScaleIn:{
            touchnode->setPosition(destPos.x,parentsize.height + nodesize.height);
            touchnode->setScale(0.0);
            CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,destPos);
            CCScaleTo *scaleTo = CCScaleTo::create(m_actionTime,1.0);
            CCActionInterval *spawn = (CCActionInterval*)CCSpawn::create(moveTo,scaleTo,0);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),spawn,finishCB(isLast),0);
            break;
        }
        case VerticalBottomIn:{
            touchnode->setPosition(destPos.x,-nodesize.height);
            CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,destPos);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            break;
        }
        case VerticalBothin:{
            if((i+1) % 2){
                touchnode->setPosition(destPos.x,-nodesize.height);
                CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,destPos);
                inAction = (CCActionInterval*)CCSequence::create(
                            CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            }else{
                touchnode->setPosition(destPos.x,parentsize.height + nodesize.height);
                CCMoveTo *moveTo = CCMoveTo::create(m_actionTime,destPos);
                inAction = (CCActionInterval*)CCSequence::create(
                            CCDelayTime::create(delay),moveTo,finishCB(isLast),0);
            }
            break;
        }
        case ScaleIn:{
            touchnode->setPosition(destPos);
            touchnode->setScale(0.0);
            CCScaleTo *scaleTo = CCScaleTo::create(m_actionTime,1.0);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),scaleTo,finishCB(isLast),0);
            break;
        }
        case ScaleXIn:{
            touchnode->setPosition(destPos);
            touchnode->setScaleX(0.00);
            CCScaleTo *scaleTo = CCScaleTo::create(m_actionTime,1.0,1.0);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),scaleTo,finishCB(isLast),0);
            break;
        }
        case ScaleYIn:{
            touchnode->setPosition(destPos);
            touchnode->setScaleY(0.00);
            CCScaleTo *scaleTo = CCScaleTo::create(m_actionTime,1.0,1.0);
            inAction = (CCActionInterval*)CCSequence::create(
                        CCDelayTime::create(delay),scaleTo,finishCB(isLast),0);
            break;
        }
        case SwayIn:{
            touchnode->setPosition(destPos);
            break;
        }
        case RotateIn:{
            touchnode->setPosition(destPos);
            break;
        }
        case BlinkIn:{
            touchnode->setPosition(destPos);
            break;
        }
        case ReelIn:{
            touchnode->setPosition(destPos);
            break;
        }
        case FireIn:{
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
        }else{
            touchnode->setPosition(destPos);
        }
    }
}
}
