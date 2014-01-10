#include "querydialog.h"
#include "../actions/absnodeaction.h"
#include "../base/fontutil.h"
#include "../base/uithemedef.h"
#include "../lang/langdef.h"
#include "../lang/stringenum.h"

namespace uilib
{
QueryDialog::QueryDialog(CCNode *parent,const ccColor4B &color)
{
    m_okId = StringEnum::Ok;
    m_retryId = StringEnum::Retry;
    m_cancelId = StringEnum::Cancel;
    m_okListener = 0;
    m_okFunc = 0;
    m_retryListener = 0;
    m_retryFunc = 0;
    m_cancelListener = 0;
    m_cancelFunc = 0;
    if(color.r == 0 && color.g == 0 && color.b == 0 && color.a == 0){
    }else if(parent){
        CCLayerColor *realparent = CCLayerColor::create();
        realparent->initWithColor(color);
        parent->addChild(realparent);
        parent = realparent;
    }
    m_edgeSize = 15;
    m_theme = "default";
    m_bg = "dialog";
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float width = size.width < size.height ? size.width : size.height;
    width *= 0.9;
    float height = width * 0.8;
    setWidth(width);
    setHeight(height);
    setTouchPriority(HighestPriority);
    setBlockEvent(true);
    BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
    BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
    moveIn->setEaseType(uilib::EaseSineInOut);
    moveIn->setMoveInType(uilib::ScaleIn);
    moveOut->setEaseType(uilib::EaseSineInOut);
    moveOut->setMoveOutType(uilib::ScaleYOut);
    moveOut->setActionTime(0.2);
    this->setMoveinAction(moveIn);
    this->setMoveoutAction(moveOut);
    if(parent){
        parent->addChild(this);
        this->setAnchorPoint(ccp(0.5,0.5));
        this->setPosition(ccp(size.width / 2,size.height / 2));
    }
}
QueryDialog::~QueryDialog()
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
    CCLayerColor *node = dynamic_cast<CCLayerColor*>(getParent());
    if(node){
        node->removeFromParentAndCleanup(true);
    }else{
        this->removeFromParentAndCleanup(true);
    }
#else
    CCLayerColor *node = dynamic_cast<CCLayerColor*>(getParent());
    if(node){
        node->removeFromParentAndCleanup(true);
    }else{
        this->removeFromParentAndCleanup(true);
    }
#endif
}
void QueryDialog::setTextInfo(const std::string &text,const std::string &fontFamily,int fontSize,ccColor3B color)
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
    BasNodeDelegateWidget *delegate = new BasNodeDelegateWidget(label,label->getTexture()->getContentSize());
    delegate->setMaxWidthRefSize("parent",0.8);
    this->addChild(delegate);
    delegate->setHorizontal("parent",0.5);
    delegate->setVertical("parent",0.45);
}
void QueryDialog::exec()
{
    LangDef *lang = UiThemeMgrProxy::getInstance()->getThemeMgr()->getLangDef();
    if(m_okId > 0){
        m_buttonTexts.push_back(lang->getStringById(m_okId));
    }
    if(m_retryId > 0){
        m_buttonTexts.push_back(lang->getStringById(m_retryId));
    }
    if(m_cancelId > 0){
        m_buttonTexts.push_back(lang->getStringById(m_cancelId));
    }
    finish();
    for(unsigned int i = 0;i < m_buttons.size();i++){
        const std::string name = m_buttons[i]->getText();
        if(m_okId > 0 && name == lang->getStringById(m_okId)){
            m_buttons[i]->setButtonIndex(m_okId);
        }else if(m_retryId > 0 && name == lang->getStringById(m_retryId)){
            m_buttons[i]->setButtonIndex(m_retryId);
        }else if(m_cancelId > 0 && name == lang->getStringById(m_cancelId)){
            m_buttons[i]->setButtonIndex(m_cancelId);
        }
    }
    layout();
}
void QueryDialog::enableButtons(bool ok,bool retry,bool cancel)
{
    if(ok){
        m_okId = StringEnum::Ok;
    }else{
        m_okId = -1;
    }
    if(retry){
        m_retryId = StringEnum::Retry;
    }else{
        m_retryId = -1;
    }
    if(cancel){
        m_cancelId = StringEnum::Cancel;
    }else{
        m_cancelId = -1;
    }
}
void QueryDialog::close()
{
    BasNodeAction *moveout = getMoveoutAction();
    if(moveout){
        moveout->setFinishCB(this,callfuncN_selector(QueryDialog::onClosed),this);
        moveOut();
    }
}
BasButton *QueryDialog::getOkButton()
{
    if(!m_finished || m_okId < 0)
        return 0;
    for(unsigned int i = 0;i < m_buttons.size();i++){
        if(m_buttons[i]->getButtonIndex() == m_okId)
            return m_buttons[i];
    }
    return 0;
}
BasButton *QueryDialog::getRetryButton()
{
    if(!m_finished || m_retryId < 0)
        return 0;
    for(unsigned int i = 0;i < m_buttons.size();i++){
        if(m_buttons[i]->getButtonIndex() == m_retryId)
            return m_buttons[i];
    }
    return 0;
}
BasButton *QueryDialog::getCancelButton()
{
    if(!m_finished || m_cancelId < 0)
        return 0;
    for(unsigned int i = 0;i < m_buttons.size();i++){
        if(m_buttons[i]->getButtonIndex() == m_cancelId)
            return m_buttons[i];
    }
    return 0;
}
void QueryDialog::setOkClickCB(CCNode *node,SEL_CallFuncND func)
{
    m_okListener = node;
    m_okFunc = func;
}
void QueryDialog::setRetryClickCB(CCNode *node,SEL_CallFuncND func)
{
    m_retryListener = node;
    m_retryFunc = func;
}
void QueryDialog::setCancelClickCB(CCNode *node,SEL_CallFuncND func)
{
    m_cancelListener = node;
    m_cancelFunc = func;
}
void QueryDialog::onButtonClicked(CCNode *pSender,void *index)
{
    int id = *(int*)index;
    if(id == m_okId && m_okListener && m_okFunc){
        (m_okListener->*m_okFunc)(this,index);
    }else if(id == m_retryId && m_retryListener && m_retryFunc){
        (m_retryListener->*m_retryFunc)(this,index);
    }else if(id == m_cancelId && m_cancelListener && m_cancelFunc){
        (m_cancelListener->*m_cancelFunc)(this,index);
    }
    BasDialog::onButtonClicked(pSender,index);
}
void QueryDialog::onClosed(CCNode *pSender)
{
    if (!pSender) {
        return;
    }
    CCLayerColor *node = dynamic_cast<CCLayerColor*>(pSender->getParent());
    if(node){
        node->removeFromParentAndCleanup(true);
    }else{
        pSender->removeFromParentAndCleanup(true);
    }
}
}
