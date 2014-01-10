#include "inputbox.h"
#include "../actions/absnodeaction.h"
#include "../skin/absskin.h"
#include "../base/fontutil.h"

namespace uilib
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
static CCRect getRect(CCNode *pNode)
{
    CCPoint p1,pos,anchor;
    CCSize size = pNode->getContentSize();
    pos = pNode->getPosition();
    anchor = pNode->getAnchorPoint();
    p1.x = pos.x - size.width * anchor.x;
    p1.y = pos.y - size.height * anchor.y;
    p1 = pNode->convertToWorldSpace(p1);
    CCRect rc;
    rc.size = size;
    rc.origin = p1;
    return rc;
}
InputNotificationLayer::InputNotificationLayer(InputBox *owner)
{
    m_maxLength = 20;
    m_pTrackNode = 0;
    m_owner = owner;
    m_touchPriority = m_owner->getHighestAncestorPriority() - 1;
    m_fontName = "Thonburi";
    m_fontSize = 36;
    m_fontColor = ccBLACK;
    m_phFontName = getSystemFont();
    m_phFontSize = 36;
    m_phFontColor = ccGRAY;
    m_placeAndHolder = "<click here for input>";
    m_attach = false;
    setTouchEnabled(true);
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this,m_touchPriority,false);
}
void InputNotificationLayer::registerWithTouchDispatcher()
{
    //CCDirector* pDirector = CCDirector::sharedDirector();
    //pDirector->getTouchDispatcher()->addTargetedDelegate(this,m_touchPriority,false);
}
void InputNotificationLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    return;
}
bool InputNotificationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(m_attach){
		onClickTrackNode(false);
        m_attach = false;
        CCNode *root = m_owner->rootParent();
        CCMoveTo *moveTo = CCMoveTo::create(0.1,m_rootOrigPos);
        root->runAction(moveTo);
		return false;
	}
    m_beginPos = pTouch->getLocation();
    CCNode *parent = this->getParent();
    CCPoint pos = parent->convertToNodeSpace(pTouch->getLocation());
    CCRect rect = this->boundingBox();
    pos.x += rect.size.width/2;
    pos.y += rect.size.height/2;
    if(rect.containsPoint(pos)){
        return true;
    }else{
        return false;
    }
}

void InputNotificationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_pTrackNode)
    {
        return;
    }
    // decide the trackNode is clicked.
    CCNode *parent = this->getParent();
    CCPoint pos = parent->convertToNodeSpace(pTouch->getLocation());
    CCRect rect = this->boundingBox();
    pos.x += rect.size.width/2;
    pos.y += rect.size.height/2;
    m_attach = rect.containsPoint(pos);
    onClickTrackNode(m_attach);
    if(m_attach){
        TouchNode *root = m_owner->rootParent();
        m_rootOrigPos = root->getPosition();
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSize mysize = this->getContentSize();
        CCPoint mypos = this->getPosition();
        mypos.x -= mysize.width / 2;
        mypos.y -= mysize.height / 2;
        mypos = parent->convertToWorldSpace(mypos);
        if(mypos.y < winSize.height / 2){
            CCAction *move = CCMoveTo::create(0.1,CCPoint(m_rootOrigPos.x,m_rootOrigPos.y + winSize.height / 2
                                                          - mypos.y + 20));
            root->runAction(move);
        }
    }
}
void InputNotificationLayer::setText(const std::string &text)
{

}
const char *InputNotificationLayer::getText()
{
    return 0;
}
InputFieldTTFDefault::InputFieldTTFDefault(InputBox *owner) : InputNotificationLayer(owner)
{
    m_touchPriority = m_owner->touchPriority() - 1;
}
InputFieldTTFDefault::~InputFieldTTFDefault()
{

}
void InputFieldTTFDefault::onClickTrackNode(bool bClicked)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;
    if (bClicked)
    {
        pTextField->attachWithIME();
    }
    else
    {
        pTextField->detachWithIME();
    }
}

void InputFieldTTFDefault::onEnter()
{
    InputNotificationLayer::onEnter();

    // add CCTextFieldTTF
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCTextFieldTTF * pTextField = CCTextFieldTTF::textFieldWithPlaceHolder(m_placeAndHolder.data(),
        m_phFontName.data(),
        m_phFontSize);
    pTextField->setColor(m_phFontColor);
    addChild(pTextField);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // on android, CCTextFieldTTF cannot auto adjust its position when soft-keyboard pop up
    // so we had to set a higher position to make it visable
    pTextField->setPosition(ccp(s.width / 2, s.height/2 + 50));
#else
    pTextField->setPosition(ccp(s.width / 2, s.height / 2));
    pTextField->setAnchorPoint(ccp(0,0));
    pTextField->setPosition(ccp(0,0));
#endif

    m_pTrackNode = pTextField;
}

InputFieldTTFAction::InputFieldTTFAction(InputBox *owner) : InputNotificationLayer(owner)
{
    m_pTextField = 0;
    m_pTextFieldAction = 0;
    m_nCharLimit = 200;
}
InputFieldTTFAction::~InputFieldTTFAction()
{
    if(m_attach){
        this->detachWithIME();
    }
}
void InputFieldTTFAction::callbackRemoveNodeWhenDidAction(CCNode * pNode)
{
    this->removeChild(pNode,true);
}
void InputFieldTTFAction::onClickTrackNode(bool bClicked)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;
    if (bClicked)
    {
        pTextField->attachWithIME();
    }
    else
    {
        pTextField->detachWithIME();
    }
}
void InputFieldTTFAction::onEnter()
{
    InputNotificationLayer::onEnter();
    m_bAction = false;
    if(m_pTextFieldAction == 0){
        m_pTextFieldAction = CCRepeatForever::create(
            (CCActionInterval*)CCSequence::create(
                CCFadeOut::create(0.25),
                CCFadeIn::create(0.25),
                0
            ));
        m_pTextFieldAction->retain();
    }

    if(m_pTextField == 0){
        CCSize dimsize;
        m_pTextField = CCTextFieldTTF::textFieldWithPlaceHolder("<click here for input>",
            dimsize,
            kCCTextAlignmentLeft,
            m_phFontName.data(),
            m_phFontSize);
        m_pTextField->setColor(m_phFontColor);
        m_pTextField->setAnchorPoint(ccp(0.5,0.5));
        m_owner->CCNode::addChild(m_pTextField);
        m_pTextField->setDelegate(this);

        CCSize ownerSize;
        m_owner->getAnchorSize(ownerSize.width,ownerSize.height);
        m_pTextField->setPosition(ccp(ownerSize.width / 2, ownerSize.height / 2));
        m_pTrackNode = m_pTextField;
    }
}
void InputFieldTTFAction::onExit()
{
    InputNotificationLayer::onExit();
}
bool InputFieldTTFAction::onTextFieldAttachWithIME(CCTextFieldTTF *pSender)
{
    if(!m_bAction){
        m_pTextField->runAction(m_pTextFieldAction);
        m_bAction = true;
    }
    return false;
}
bool InputFieldTTFAction::onTextFieldDetachWithIME(CCTextFieldTTF *pSender)
{
    if(m_bAction){
        m_pTextField->stopAction(m_pTextFieldAction);
        m_pTextField->setOpacity(255);
        m_bAction = false;
    }
    return false;
}
bool InputFieldTTFAction::onTextFieldInsertText(CCTextFieldTTF *pSender,const char *text,int nLen)
{
    // if insert enter, treat as default to detach with ime
    if ('\n' == *text){
        return false;
    }
    // if the textfield's char count more than m_nCharLimit, doesn't insert text anymore.
    if(pSender->getCharCount() >= m_nCharLimit){
        return true;
    }
    pSender->setColor(m_fontColor);
    // create a insert text sprite and do some action
    CCSize ownerSize;
    m_owner->getAnchorSize(ownerSize.width,ownerSize.height);
    CCLabelTTF *label = CCLabelTTF::create(text,m_fontName.data(),m_fontSize);
    label->setColor(ccGRAY);
    m_owner->CCNode::addChild(label);
    label->setAnchorPoint(ccp(0.5,0.5));
    label->setPosition(ccp(ownerSize.width / 2,ownerSize.height / 2));
    float duration = 0.5;
    CCAction * seq = CCSequence::create(
        CCSpawn::create(
            CCScaleTo::create(duration, 4),
            CCFadeOut::create(duration),
        0),
        CCCallFuncN::create(this, callfuncN_selector(InputFieldTTFAction::callbackRemoveNodeWhenDidAction)),
        0);
    label->runAction(seq);
    return false;
}
bool InputFieldTTFAction::onTextFieldDeleteBackward(CCTextFieldTTF *pSender, const char *delText,int nLen)
{
    // create a delete text sprite and do some action
    CCLabelTTF * label = CCLabelTTF::create(delText,m_fontName.data(),m_fontSize);
    label->setColor(m_fontColor);
    m_owner->CCNode::addChild(label);
    CCSize ownersize;
    m_owner->getAnchorSize(ownersize.width,ownersize.height);
    label->setAnchorPoint(ccp(0.5,0.5));
    label->setPosition(ccp(ownersize.width / 2,ownersize.height / 2));
    label->setScale(8);
    CCAction * seq = CCSequence::create(
        CCSpawn::create(
            CCScaleTo::create(0.5,0.0),
            CCFadeOut::create(0.5),
        0),
        CCCallFuncN::create(this, callfuncN_selector(InputFieldTTFAction::callbackRemoveNodeWhenDidAction)),
        0);
    label->runAction(seq);
    return false;
}
bool InputFieldTTFAction::onDraw(CCTextFieldTTF *pSender)
{
    return false;
}
void InputFieldTTFAction::setText(const std::string &text)
{
    if(m_pTextField)
        m_pTextField->setString(text.data());
}
const char* InputFieldTTFAction::getText()
{
    if(m_pTextField)
        return m_pTextField->getString();
    else
        return "";
}
#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
EditBoxDelegate::EditBoxDelegate(InputBox *owner,TouchNode *parent)
: NullFrame(parent)
, m_eEditBoxInputMode(kEditBoxInputModeSingleLine)
, m_eEditBoxInputFlag(kEditBoxInputFlagDisableCapsWord)
, m_eKeyboardReturnType(kKeyboardReturnTypeDefault)
, m_colText(ccWHITE)
, m_nMaxLength(0)
, m_isVisible(false)
, m_enabled(true)
{
    m_owner = owner;
    setCanTouch(true);
    m_editBox = 0;
}
EditBoxDelegate::~EditBoxDelegate()
{
}
void EditBoxDelegate::layoutCompleted()
{
    NullFrame::layoutCompleted();
}
void EditBoxDelegate::initEditBox()
{
    if(!m_editBox) {
        m_editBox = CCEditBox::create(CCSizeMake(m_anchorWidth, m_anchorHeight), CCScale9Sprite::create());
        m_editBox->setDelegate(this);
        CCNode *root = this->getParent();
        while (root->getParent()) {
            root = root->getParent();
        }
        root->addChild(m_editBox, 10000);

        float width,height;
        CCPoint destpos = this->getDestPoint();
        this->getAnchorSize(width,height);
        destpos.x -= width / 2;
        destpos.y -= height / 2;
        TouchNode *parent = this->parent();
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        while(parent->parent()){
            float w,h;
            CCPoint pos = parent->getDestPoint();
            parent->getAnchorSize(w,h);
            if (pos.x != 0 || pos.y != 0 || w != winSize.width || h != winSize.height) {
                pos.x -= w/2;
                pos.y -= h/2;
                destpos.x += pos.x;
                destpos.y += pos.y;
            }
            parent = parent->parent();
        }
        if(parent){
            float w,h;
            CCPoint pos = parent->getDestPoint();
            parent->getAnchorSize(w,h);
            if (pos.x != 0 || pos.y != 0 || w != winSize.width || h != winSize.height) {
                pos.x -= w/2;
                pos.y -= h/2;
                destpos.x += pos.x;
                destpos.y += pos.y;
            }
        }
        CCNode *nodeParent = parent->getParent();
        destpos = nodeParent->convertToWorldSpace(destpos);
        this->getAnchorSize(width,height);
        destpos.x += width/2;
        destpos.y += height/2;
        // FIXME: modify position because input area not in center of widget
        destpos.y -= 5.0;
        m_editBox->setPosition(destpos);

        setText(m_strText);
        setFontColor(m_colText);
        setPlaceholderFontColor(m_colText);
        setPlaceHolder(m_strPlaceHolder);
        setInputMode(m_eEditBoxInputMode);
        setMaxLength(m_nMaxLength);
        setInputFlag(m_eEditBoxInputFlag);
        setReturnType(m_eKeyboardReturnType);
    }
    setVisible(true);
    setEnabled(m_enabled);
}
void EditBoxDelegate::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_editBox)
        m_editBox->ccTouchBegan(pTouch,pEvent);
}
void EditBoxDelegate::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_editBox)
        m_editBox->ccTouchMoved(pTouch,pEvent);
}
void EditBoxDelegate::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_editBox)
        m_editBox->ccTouchEnded(pTouch,pEvent);
}
void EditBoxDelegate::editBoxReturn(CCEditBox* editBox){
    m_owner->editBoxReturn(editBox);
}
void EditBoxDelegate::moveInStart()
{
    initEditBox();
}
void EditBoxDelegate::moveOutStart()
{
    setText("");
    setVisible(false);
    if(m_editBox) {
        m_editBox->removeFromParentAndCleanup(true);
        m_editBox = 0;
    }
}
void EditBoxDelegate::setText(const std::string& strText)
{
    m_strText = strText;
    if (m_editBox != NULL)
    {
        m_editBox->setText(m_strText.data());
    }
}
void EditBoxDelegate::setText(const char* pText)
{
    if (pText != NULL)
    {
        m_strText = pText;
        if (m_editBox != NULL)
        {
            m_editBox->setText(pText);
        }
    }
}
const char* EditBoxDelegate::getText(void)
{
    if (m_editBox != NULL)
    {
        return m_editBox->getText();
    }

    return "";
}
void EditBoxDelegate::setFontColor(const ccColor3B& color)
{
    m_colText = color;
    if (m_editBox != NULL)
    {
        m_editBox->setFontColor(color);
    }
}
void EditBoxDelegate::setPlaceholderFontColor(const ccColor3B& color)
{
    m_colText = color;
    if (m_editBox != NULL)
    {
        m_editBox->setPlaceholderFontColor(color);
    }
}
void EditBoxDelegate::setPlaceHolder(const std::string& strPlaceHolder)
{
    m_strPlaceHolder = strPlaceHolder;
    if (m_editBox != NULL)
    {
        m_editBox->setPlaceHolder(strPlaceHolder.data());
    }
}
void EditBoxDelegate::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        m_strPlaceHolder = pText;
        if (m_editBox != NULL)
        {
            m_editBox->setPlaceHolder(pText);
        }
    }
}
const char* EditBoxDelegate::getPlaceHolder(void)
{
    return m_strPlaceHolder.c_str();
}
void EditBoxDelegate::setInputMode(EditBoxInputMode inputMode)
{
    m_eEditBoxInputMode = inputMode;
    if (m_editBox != NULL)
    {
        m_editBox->setInputMode(inputMode);
    }
}
void EditBoxDelegate::setMaxLength(int maxLength)
{
    m_nMaxLength = maxLength;
    if (m_editBox != NULL)
    {
        m_editBox->setMaxLength(maxLength);
    }
}
int EditBoxDelegate::getMaxLength()
{
    return m_nMaxLength;
}
void EditBoxDelegate::setInputFlag(EditBoxInputFlag inputFlag)
{
    m_eEditBoxInputFlag = inputFlag;
    if (m_editBox != NULL)
    {
        m_editBox->setInputFlag(inputFlag);
    }
}
void EditBoxDelegate::setReturnType(KeyboardReturnType returnType)
{
    m_eKeyboardReturnType = returnType;
    if (m_editBox != NULL)
    {
        m_editBox->setReturnType(returnType);
    }
}
void EditBoxDelegate::setVisible(bool isVisible)
{
    m_isVisible = isVisible;
    if (m_editBox != NULL)
    {
        m_editBox->setVisible(isVisible);
    }
}
bool EditBoxDelegate::visible()
{
    return m_isVisible;
}
void EditBoxDelegate::setEnabled(bool enabled)
{
    m_enabled = enabled;
    if (m_editBox != NULL)
    {
        m_editBox->setEnabled(enabled);
    }
}
bool EditBoxDelegate::enabled()
{
    return m_enabled;
}
#endif

InputBox::InputBox()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate = new EditBoxDelegate(this, this);
    m_editBoxDelegate->setFill("parent");
    m_returnListener = 0;
    m_returnFunc = 0;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    m_editBox = 0;
#else
    m_editBox = 0;
#endif
}
InputBox::~InputBox()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    if(m_editBox != 0){
        m_editBox->removeFromParentAndCleanup(true);
    }
#endif
}
void InputBox::moveInStart()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    initEditBox();
#endif
}
void InputBox::moveOutStart()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->moveOutStart();
#endif
}
void InputBox::layoutCompleted()
{
    BasWidget::layoutCompleted();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    initEditBox();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    if(m_editBox == 0){
        m_editBox = new InputFieldTTFAction(this);
        this->CCNode::addChild(m_editBox);
        m_editBox->setAnchorPoint(ccp(0.5,0.5));
        m_editBox->setContentSize(CCSizeMake(m_anchorWidth,m_anchorHeight));
        m_editBox->setPosition(ccp(m_anchorWidth/2,m_anchorHeight/2));
    }
#else
    if(m_editBox == 0){
        m_editBox = new InputFieldTTFAction(this);
        this->CCNode::addChild(m_editBox);
        m_editBox->setAnchorPoint(ccp(0.5,0.5));
        m_editBox->setContentSize(CCSizeMake(m_anchorWidth,m_anchorHeight));
        m_editBox->setPosition(ccp(m_anchorWidth/2,m_anchorHeight/2));
    }
#endif
}
void InputBox::initEditBox()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->setVisible(true);
    float moveInTime = getParentMoveInTime();
    CCAction *completeAction = CCSequence::createWithTwoActions(CCDelayTime::create(moveInTime),
                                                                CCCallFunc::create(this, callfunc_selector(InputBox::parentMoveInCB)));
    this->runAction(completeAction);
#endif
}
void InputBox::parentMoveInCB()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->moveInStart();
#endif
}
void InputBox::childLayoutCompleted()
{
    BasWidget::childLayoutCompleted();
}
float InputBox::getParentMoveInTime()
{
    float time = 0;
    BasNodeAction *moveIn;
    TouchNode *parent = this->parent();
    while(parent){
        BasWidget *widget = dynamic_cast<BasWidget*>(parent);
        if(widget){
            moveIn = widget->getMoveinAction();
            if(moveIn){
                float atime = moveIn->getActionTime();
                if(atime > time)
                    time = atime;
            }
        }
        parent = parent->parent();
    }
    return time;
}
float InputBox::getParentMoveOutTime()
{
    float time = 0;
    BasNodeAction *moveOut;
    TouchNode *parent = this->parent();
    while(parent){
        BasWidget *widget = dynamic_cast<BasWidget*>(parent);
        if(widget){
            moveOut = widget->getMoveoutAction();
            if(moveOut){
                float atime = moveOut->getActionTime();
                if(atime > time)
                    time = atime;
            }
        }
        parent = parent->parent();
    }
    return time;
}
void InputBox::setTheme(const std::string &theme,const std::string &bg)
{
    if(m_skin == 0){
        BasSkin *skin = BorderImageSkin::create(CCSizeMake(0,0),theme,bg);
        setSkin(skin);
    }
}
void InputBox::setDelegate(CCEditBoxDelegate *pDelegate)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)

#else
#endif
}
void InputBox::setText(const std::string &text)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->setText(text);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    if(m_editBox)
        m_editBox->setText(text.data());
#else
    if(m_editBox)
        m_editBox->setText(text.data());
#endif
}
void InputBox::appendText(const std::string &text)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string has = m_editBoxDelegate->getText();
    has.append(text);
    m_editBoxDelegate->setText(has);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    if(m_editBox){
        std::string has = m_editBox->getText();
        has.append(text);
        m_editBox->setText(has);
    }
#else
    if(m_editBox){
        std::string has = m_editBox->getText();
        has.append(text);
        m_editBox->setText(has);
    }
#endif
}
const char *InputBox::getText()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return m_editBoxDelegate->getText();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    if(m_editBox)
        return m_editBox->getText();
    else
        return "";
#else
    if(m_editBox)
        return m_editBox->getText();
    else
        return "";
#endif
}
void InputBox::setPlaceHolder(const std::string &text)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->setPlaceHolder(text);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    if(m_editBox)
        m_editBox->setPlaceAndHolder(text);
#else
    if(m_editBox)
        m_editBox->setPlaceAndHolder(text);
#endif
}
void InputBox::setFontColor(const ccColor3B &color)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->setFontColor(color);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    if(m_editBox)
        m_editBox->setFontColor(color);
#else
    if(m_editBox)
        m_editBox->setFontColor(color);
#endif
}
void InputBox::setPlaceholderFontColor(const ccColor3B &color)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->setPlaceholderFontColor(color);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    if(m_editBox)
        m_editBox->setPhFontColor(color);
#else
    if(m_editBox)
        m_editBox->setPhFontColor(color);
#endif
}
void InputBox::setInputMode(EditBoxInputMode inputMode)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->setInputMode(inputMode);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)

#else
#endif
}
void InputBox::setMaxLength(int maxLength)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->setMaxLength(maxLength);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)

#else
#endif
}
int InputBox::getMaxLength()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return m_editBoxDelegate->getMaxLength();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)

#else
#endif
    return 40;
}
void InputBox::setInputFlag(EditBoxInputFlag inputFlag)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->setInputFlag(inputFlag);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)

#else
#endif
}
void InputBox::setReturnType(KeyboardReturnType returnType)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->setReturnType(returnType);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)

#else
#endif
}
void InputBox::setVisible(bool isVisible)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->setVisible(isVisible);
#else
#endif
}
void InputBox::setEnabled(bool enabled)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_editBoxDelegate->setEnabled(enabled);
#else
#endif
}
bool InputBox::enabled()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return m_editBoxDelegate->enabled();
#else
#endif
    return true;
}
void InputBox::editBoxReturn(CCEditBox* editBox)
{
    if(m_returnListener && m_returnFunc){
        (m_returnListener->*m_returnFunc)(this);
    }
}
void InputBox::setOnReturned(CCNode *listener, SEL_CallFuncN func)
{
    m_returnListener = listener;
    m_returnFunc = func;
}
}
