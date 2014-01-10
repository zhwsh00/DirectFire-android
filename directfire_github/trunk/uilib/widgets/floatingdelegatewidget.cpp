#include "floatingdelegatewidget.h"
#include "../skin/absskin.h"
#include "../actions/absnodeaction.h"

namespace uilib
{
FloatingDelegateWidget::FloatingDelegateWidget(TouchNode *parent,BasWidget *widget,const CCSize &wsize,const CCPoint &pos,const std::string &theme,const std::string &bg)
{
    m_theme = theme;
    m_bg = bg;
    CCSize skinSize;
    if(m_theme.size() != 0 && m_bg.size() != 0){
        BasSkin *skin = BorderImageSkin::create(CCSizeMake(0,0),theme,bg);
        if(skin){
            setSkin(skin);
            skin->getPreferedSize(skinSize);
        }
    }
    CCSize size;
    if(wsize.width == 0 || wsize.height == 0){
        do{
            size.width = widget->getWidth();
            size.height = widget->getHeight();
            if(size.width > 0 && size.height > 0)
                break;
            widget->getPreferedSize(size);
            if(size.width <= 0 || size.height <= 0){
                size = CCDirector::sharedDirector()->getWinSize();
                if(size.width > size.height)
                    size.width = size.height;
                size.width *= 0.8;
                size.height = size.width * 0.6;
            }else{
                size.width *= 1.1;
                size.height *= 1.1;
            }
        }while(0);
    }else{
        size = wsize;
    }
    if(size.width < skinSize.width)
        size.width = skinSize.width;
    if(size.height < skinSize.height)
        size.height = skinSize.height;
    this->setWidth(size.width);
    this->setHeight(size.height);
    this->addChild(widget);
    widget->setCenterIn("parent");
    parent->addChild(this);
    setCanTouch(true);
    setBlockEvent(true);
    setTouchPriority(uilib::HighestPriority);
    BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
    BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
    moveIn->setFinishCB(this,callfuncN_selector(FloatingDelegateWidget::onMoveInActionFinished));
    moveOut->setFinishCB(this,callfuncN_selector(FloatingDelegateWidget::onMoveOutActionFinished));
    moveIn->setEaseType(uilib::EaseSineInOut);
    moveIn->setMoveInType(uilib::ScaleXIn);
    moveOut->setEaseType(uilib::EaseSineInOut);
    moveOut->setMoveOutType(uilib::ScaleYOut);
    this->setMoveinAction(moveIn);
    this->setMoveoutAction(moveOut);
    layout(true);
    if(pos.x != -1 && pos.y != -1){
        setPosition(pos);
    }else{
        CCSize winsize = CCDirector::sharedDirector()->getWinSize();
        setPosition(ccp(winsize.width,winsize.height));
    }
}
FloatingDelegateWidget::~FloatingDelegateWidget()
{

}
void FloatingDelegateWidget::setMoveInTime(float time)
{
    getMoveinAction()->setActionTime(time);
}
void FloatingDelegateWidget::setMoveOutTime(float time)
{
    getMoveoutAction()->setActionTime(time);
}
void FloatingDelegateWidget::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BasWidget::touchPressEvent(pTouch,pEvent);
}
void FloatingDelegateWidget::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BasWidget::touchMoveEvent(pTouch,pEvent);
}
void FloatingDelegateWidget::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BasWidget::touchReleaseEvent(pTouch,pEvent);
    moveOut();
}
void FloatingDelegateWidget::onMoveInActionFinished(CCNode *sender)
{
    bool move = false;
    float mx = 0,my = 0;
    CCSize size;
    getAnchorSize(size.width,size.height);
    CCPoint pos = getPosition();
    CCPoint apos = getAnchorPoint();
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    CCPoint lb = ccp(pos.x - size.width * apos.x,pos.y - size.height * apos.y);
    CCPoint rt = ccp(pos.x + size.width * apos.x,pos.y + size.height * apos.y);
    if(lb.x < 0){
        mx = -lb.x;
        move = true;
    }
    if(lb.y < 0){
        my = -lb.y;
        move = true;
    }
    if(rt.x > winsize.width){
        mx = winsize.width - rt.x;
        move = true;
    }
    if(rt.y > winsize.height){
        my = winsize.height - rt.y;
        move = true;
    }
    if(move){
        pos.x += mx;
        pos.y += my;
        CCAction *action = CCMoveTo::create(0.5,pos);
        this->runAction(action);
    }
}
void FloatingDelegateWidget::onMoveOutActionFinished(CCNode *sender)
{
    parent()->delChild(this);
}

}
