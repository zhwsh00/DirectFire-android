#include "busydialog.h"
#include "../actions/absnodeaction.h"
#include "../base/fontutil.h"
#include "../base/uithemedef.h"
#include "../base/absanimsprite.h"

namespace uilib
{

SimpleBusyDialog::SimpleBusyDialog(CCNode *parent,const ccColor4B &color)
{
    if(color.r == 0 && color.g == 0 && color.b == 0 && color.a == 0){
    }else if(parent){
        CCLayerColor *realparent = CCLayerColor::create();
        realparent->initWithColor(color);
        parent->addChild(realparent);
        parent = realparent;
    }
    m_loadFinishedListener = 0;
    m_loadFinishedFunc = 0;
    m_moveInFinished = false;
    m_deleteLater = false;
    m_animDelegate = 0;
    m_labelDelegate = 0;
    m_theme = "default";
    m_bg = "inputbg";
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float width = size.width < size.height ? size.width : size.height;
    width *= 0.7;
    float height = width * 0.6;
    setWidth(width);
    setHeight(height);
    setAnchoredSize(width,height);
    setTouchPriority(HighestPriority);
    setBlockEvent(true);
    BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
    BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
    moveIn->setFinishCB(this,callfuncN_selector(SimpleBusyDialog::onMoveInActionFinished));
    moveOut->setFinishCB(this,callfuncN_selector(SimpleBusyDialog::onMoveOutActionFinished),this);
    moveIn->setEaseType(uilib::EaseSineInOut);
    moveIn->setMoveInType(uilib::ScaleIn);
    moveOut->setEaseType(uilib::EaseSineInOut);
    moveOut->setMoveOutType(uilib::ScaleYOut);
    moveOut->setActionTime(0.2);
    this->setMoveinAction(moveIn);
    this->setMoveoutAction(moveOut);
    if(parent){
        parent->addChild(this);
    }
    this->setAnchorPoint(ccp(0.5,0.5));
    this->setPosition(ccp(size.width / 2,size.height / 2));
}
SimpleBusyDialog::~SimpleBusyDialog()
{
    CCLayerColor *node = dynamic_cast<CCLayerColor*>(getParent());
    if(node){
        node->removeFromParentAndCleanup(true);
    }else{
        this->removeFromParentAndCleanup(true);
    }
}
void SimpleBusyDialog::setAnimationName(const std::string &name)
{
    BasAnimSprite *animFrame = UiThemeMgrProxy::getInstance()->getThemeMgr()->getAnimSpriteByName(name);
    if(animFrame){
        animFrame->setAnchorPoint(ccp(0.5,0.5));
        animFrame->playInLoop(-1);
        m_animDelegate = new BasNodeDelegateWidget(animFrame);
        this->addChild(m_animDelegate);
        if(m_labelDelegate == 0){
            m_animDelegate->setHorizontal("parent",0.5);
            m_animDelegate->setVertical("parent",0.5);
        }else{
            m_animDelegate->setHorizontal("parent",0.5);
            m_animDelegate->setBottom(m_labelDelegate->getName(),uilib::Top);
        }
    }
}
void SimpleBusyDialog::setBusyText(const std::string &text,
             const std::string &fontFamily,
             int fontSize,
             const ccColor3B &color)
{

    CCSize size = CCSizeMake(0,0);
    CCLabelTTF *label = 0;
    if (fontFamily.empty()) {
        label = CCLabelTTF::create(text.data(),getSystemFont(),fontSize,
                                   size,kCCTextAlignmentCenter);
    } else {
        label = CCLabelTTF::create(text.data(),fontFamily.data(),fontSize,
                                               size,kCCTextAlignmentCenter);
    }
    label->setColor(color);
    label->setAnchorPoint(ccp(0.5,0.5));
    m_labelDelegate = new BasNodeDelegateWidget(label,label->getTexture()->getContentSize());
    this->addChild(m_labelDelegate);
    if(m_animDelegate){
        m_labelDelegate->setHorizontal("parent",0.5);
        m_labelDelegate->setTop(m_animDelegate->getName(),uilib::Bottom);
    }else{
        m_labelDelegate->setHorizontal("parent",0.5);
        m_labelDelegate->setVertical("parent",0.55);
    }
}
void SimpleBusyDialog::exec()
{
    finish();
    layout();
}
void SimpleBusyDialog::deleteLater()
{
    if (m_moveInFinished) {
        m_moveInFinished = false;
        moveOut();
    } else {
        m_deleteLater = true;
    }
}
void SimpleBusyDialog::destory()
{
    m_moveInFinished = false;
    m_deleteLater = false;
    moveOut();
} 
void SimpleBusyDialog::setLoadFinishedCB(CCNode *listener,SEL_CallFuncN func)
{
    m_loadFinishedListener = listener;
    m_loadFinishedFunc = func;
}
void SimpleBusyDialog::onMoveInActionFinished(CCNode *node)
{
    m_moveInFinished = true;
    // run load finished callback first
    if(m_loadFinishedListener && m_loadFinishedFunc){
        (m_loadFinishedListener->*m_loadFinishedFunc)(this);
    }
    // delete later
    if (m_deleteLater) {
        destory();
    }
}
void SimpleBusyDialog::onMoveOutActionFinished(CCNode *pSender)
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

BusyDialog::BusyDialog(CCNode *parent,const ccColor4B &color)
    : SimpleBusyDialog(parent,color)
{
    m_edgeSize = 5;
}
BusyDialog::~BusyDialog()
{

}
void BusyDialog::setCancelButton(const std::string &text,
                     const std::string &fontfamily,
                     int fontSize,
                     const std::string &bgimg)
{
    std::vector<std::string> set;
    set.push_back(text);
    setButtons(set);
    set.clear();
    set.push_back(bgimg);
    setButtonThemes(set);
}
void BusyDialog::setCancelVisible(bool visible)
{
    BasButton *button = getButtonByIndex(0);
    if(button)
        button->setVisible(visible);
}
void BusyDialog::exec()
{
    SimpleBusyDialog::exec();
}

}
