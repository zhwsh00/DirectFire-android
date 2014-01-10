#include "absshowdialog.h"
#include "../actions/absnodeaction.h"
#include "../base/uithemedef.h"
#include "../base/uithemedef.h"
#include "../skin/absskin.h"

namespace uilib
{
BasShowDialog::BasShowDialog(CCNode *parent,const ccColor4B &color)
{
    m_theme = "default";
    m_bg = "dialog";
    m_closeImg = "uiexit";
    m_closeListener = 0;
    m_closeFunc = 0;
    m_edgeSize = 5;
    m_moveInTime = 0.5;
    m_moveOutTime = 0.2;
    m_fillHEdge = 25;
    m_fillVEdge = 25;
    if(color.r == 0 && color.g == 0 && color.b == 0 && color.a == 0){
    }else if(parent){
        CCLayerColor *realparent = CCLayerColor::create();
        realparent->initWithColor(color);
        parent->addChild(realparent);
        parent = realparent;
    }
    m_edgeSize = 5;
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float width = size.width < size.height ? size.width : size.height;
    width *= 0.9;
    float height = width * 0.8;
    setWidth(width);
    setHeight(height);
    setTouchPriority(TopPriority);
    setBlockEvent(true);

    BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
    BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
    moveIn->setEaseType(uilib::EaseSineInOut);
    moveIn->setMoveInType(uilib::ScaleIn);
    moveOut->setEaseType(uilib::EaseSineInOut);
    moveOut->setMoveOutType(uilib::ScaleYOut);
    moveIn->setActionTime(m_moveInTime);
    moveOut->setActionTime(m_moveOutTime);
    moveIn->setFinishCB(this,callfuncN_selector(BasShowDialog::onMoveInActionFinished));
    moveOut->setFinishCB(this,callfuncN_selector(BasShowDialog::onMoveOutActionFinished),this);
    this->setMoveinAction(moveIn);
    this->setMoveoutAction(moveOut);
    if(parent){
        parent->addChild(this,100);
        this->setAnchorPoint(ccp(0.5,0.5));
        this->setPosition(ccp(size.width / 2,size.height / 2));
    }
}
BasShowDialog::~BasShowDialog()
{
    CCLayerColor *node = dynamic_cast<CCLayerColor*>(getParent());
    if(node){
        node->removeFromParentAndCleanup(true);
    }else{
        this->removeFromParentAndCleanup(true);
    }
}
void BasShowDialog::setTheme(const std::string &theme,const std::string &bg)
{
    m_theme = theme;
    m_bg = bg;
}
void BasShowDialog::setEdgeSize(float h,float v)
{
    m_fillHEdge = h;
    m_fillVEdge = v;
}
void BasShowDialog::setFillPattern(const std::string &pattern)
{
    m_fillPattern = pattern;
}
void BasShowDialog::setCloseImg(const std::string &normal,const std::string &pressed)
{
    m_closeImg = normal;
    m_closePressedImg = pressed;
}
void BasShowDialog::setCloseCB(CCNode *node,SEL_CallFuncND func)
{
    m_closeListener = node;
    m_closeFunc = func;
}
void BasShowDialog::exec()
{
    finish();
    layout();
}
void BasShowDialog::destroy()
{
    moveOut();
}
void BasShowDialog::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(!m_fillPattern.empty()){
        /* the texture must be standalone,so we left here,
          if the image need to tiled show,we can save the
          image file alone
          */
        CCSize size;
        size.width = m_anchorWidth - m_fillHEdge * 2;
        size.height = m_anchorHeight - m_fillVEdge * 2;
        CCSprite *sprite = CCSprite::create(m_fillPattern.c_str());
        ccTexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
        sprite->getTexture()->setTexParameters(&tp);
        sprite->setPosition(ccp(m_anchorWidth/2,m_anchorHeight/2));
        this->CCNode::addChild(sprite,0);
    }
}
void BasShowDialog::finish()
{
    //init bg
    CCSize dialogSize = CCSizeMake(m_anchorWidth,m_anchorHeight);
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    BasSkin *skin = BorderImageSkin::create(dialogSize,uiDef,m_bg);
    if(skin) setSkin(skin);
    if(1){
        //close widget
        BasButton *closeWidget = new BasButton();
        closeWidget->setButtonInfo("",m_theme,m_closeImg,CCSizeMake(0,0),m_closePressedImg);
        closeWidget->setClickCB(m_closeListener,m_closeFunc);
        this->addChild(closeWidget);
        closeWidget->setTop("parent",uilib::Top);
        closeWidget->setRight("parent",uilib::Right);
        CCSize closeSize;
        closeWidget->getPreferedSize(closeSize);
        closeWidget->setTopMargin(-closeSize.height / 2);
        closeWidget->setRightMargin(-closeSize.width / 2);
        m_closeButton = closeWidget;
    }
}
void BasShowDialog::onMoveInActionFinished(CCNode *node)
{

}
void BasShowDialog::onMoveOutActionFinished(CCNode *pSender)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
    delete this;
#else
    if (!pSender) {
        return;
    }
    CCLayerColor *node = dynamic_cast<CCLayerColor*>(pSender->getParent());
    if(node){
        node->removeFromParentAndCleanup(true);
    }else{
        pSender->removeFromParentAndCleanup(true);
    }
#endif
}
}
