#include "popbuttonsdialog.h"
#include "fsizewidgetdelegate.h"
#include "filltestwidget.h"
#include "../base/widget.h"
#include "../base/uithemedef.h"
#include "../skin/absskin.h"

namespace uilib
{
PopButtonsDialog::PopButtonsDialog(TouchNode *parent,const CCPoint &pos)
{
    m_edgeSize = 10;
    m_buttonIndex = 0;
    m_buttonListener = 0;
    m_buttonFunc = 0;
    m_theme = "default";
    m_bg = "putonbg";
    m_moveInTime = 0.5;
    m_moveOutTime = 0.2;
    setCanTouch(true);
    setBlockEvent(true);
    parent->addChild(this);
    m_pos = pos;
    setTouchPriority(uilib::TopPriority);

    BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
    BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
    moveIn->setFinishCB(this,callfuncN_selector(PopButtonsDialog::onMoveInFinished));
    moveOut->setFinishCB(this,callfuncN_selector(PopButtonsDialog::onMoveOutFinised));
    moveIn->setEaseType(uilib::EaseSineInOut);
    moveIn->setMoveInType(uilib::ScaleXIn);
    moveOut->setEaseType(uilib::EaseSineInOut);
    moveOut->setMoveOutType(uilib::ScaleYOut);
    this->setMoveinAction(moveIn);
    this->setMoveoutAction(moveOut);
    moveIn->setActionTime(m_moveInTime);
    moveOut->setActionTime(m_moveOutTime);

    m_verContainer = new VFSizeWidgetContainer;
    this->addChild(m_verContainer);
    m_verContainer->setCenterIn("parent");
}
PopButtonsDialog::~PopButtonsDialog()
{

}
void PopButtonsDialog::setTheme(const std::string &theme,const std::string &bg)
{
    m_theme = theme;
    m_bg = bg;
}
void PopButtonsDialog::addButton(const std::string &text,const CCSize &size)
{
    BasButton *button = new BasButton;
    button->setButtonInfo(text.data(),"fonts/uifont24.fnt","default","buttonbg",size);
    button->setButtonIndex(m_buttonIndex++);
    button->setClickCB(this,callfuncND_selector(PopButtonsDialog::onButtonClicked));
    CCSize ssize = size;
    if(ssize.width != 0 && ssize.height != 0){
        button->setWidth(ssize.width);
        button->setHeight(ssize.height);
    }else{
        button->getPreferedSize(ssize);
        button->setWidth(ssize.width);
        button->setHeight(ssize.height);
    }
    FSizeWidgetDelegate *delegate = new FSizeWidgetDelegate(button,ssize);
    m_verContainer->addFSizeWidget(delegate);
}
void PopButtonsDialog::addButton(BasButton *button,const CCSize &size)
{
    button->setButtonIndex(m_buttonIndex++);
    button->setClickCB(this,callfuncND_selector(PopButtonsDialog::onButtonClicked));
    CCSize ssize = size;
    if(ssize.width != 0 && ssize.height != 0){
        button->setWidth(ssize.width);
        button->setHeight(ssize.height);
    }else{
        button->getPreferedSize(ssize);
        button->setWidth(ssize.width);
        button->setHeight(ssize.height);
    }
    FSizeWidgetDelegate *delegate = new FSizeWidgetDelegate(button,ssize);
    m_verContainer->addFSizeWidget(delegate);
}
void PopButtonsDialog::setButtonCB(CCNode *sender,SEL_CallFuncND func)
{
    m_buttonListener = sender;
    m_buttonFunc = func;
}
void PopButtonsDialog::setMoveInTime(float time)
{
    m_moveInTime = time;
    getMoveinAction()->setActionTime(time);
}
void PopButtonsDialog::setMoveOutTime(float time)
{
    m_moveOutTime = time;
    getMoveoutAction()->setActionTime(time);
}
void PopButtonsDialog::setSpacing(float space)
{
    m_verContainer->setSpacing(space);
}
void PopButtonsDialog::exec()
{
    m_verContainer->exec();
    CCSize size;
    m_verContainer->getContainerFixedSize(size);
    setWidth(size.width + 2 * m_edgeSize);
    setHeight(size.height + 2 * m_edgeSize);
    layout(true);
    setAnchorPoint(ccp(0.5,0.5));
    setPosition(m_pos);
}
void PopButtonsDialog::onButtonClicked(CCNode *sender,void *data)
{
    if(m_buttonListener && m_buttonFunc)
        (m_buttonListener->*m_buttonFunc)(sender,data);
    moveOut();
}
void PopButtonsDialog::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(m_skin == 0 && !m_theme.empty() && !m_bg.empty()){
        CCSize size = CCSizeMake(m_anchorWidth,m_anchorHeight);
        UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
        BasSkin *skin = BorderImageSkin::create(size,uiDef,m_bg);
        setSkin(skin);
    }
}
void PopButtonsDialog::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{

}
void PopButtonsDialog::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{

}
void PopButtonsDialog::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    moveOut();
}
void PopButtonsDialog::onMoveInFinished(CCNode *node)
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
void PopButtonsDialog::onMoveOutFinised(CCNode *node)
{
     parent()->delChild(this);
}

}
