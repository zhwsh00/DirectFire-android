#include "widget.h"
#include "../skin/absskin.h"
#include "../actions/absnodeaction.h"
#include "../base/fontutil.h"
#include "../base/uithemedef.h"

namespace uilib
{

BasLayout::BasLayout()
{
    m_owner = 0;
    m_spacing = 10;
    m_averageSet = false;
    m_childsAction = 0;
    m_alignChildSize = false;
}
BasLayout::~BasLayout()
{

}
void BasLayout::addWidget(BasWidget *widget)
{
    TouchNode::addChild(widget);
    m_childs.push_back(widget);
}
void BasLayout::addLayout(BasLayout *layout)
{
    TouchNode::addChild(layout);
    m_childs.push_back(layout);
}
void BasLayout::setOwner(BasWidget *owner)
{
    if(m_owner){
        cout << "BasLayout::setOwner,more owner was set,please check!" << endl;
        return;
    }
    m_owner = owner;
}
void BasLayout::childLayoutStarted()
{
    if(m_alignChildSize){
        CCSize size;
        getChildMaxPreferedSize(size);
        if(size.width != 0 && size.height != 0){
            for(unsigned i = 0;i < m_childs.size();i++){
                m_childs[i]->setPreferedSize(size);
            }
        }
    }
}
void BasLayout::setChildAlign(int index,uilib::AnchorType type)
{

}

VerticalLayout::VerticalLayout()
{

}
VerticalLayout::~VerticalLayout()
{

}
void VerticalLayout::setChildAlign(int index,uilib::AnchorType type)
{
    if(index < 0 || index >= m_childs.size())
        return;
    if(type != uilib::Left && type != uilib::Right)
        return;
    ChildAlign align;
    align.index = index;
    align.type = type;
    m_childAligns.push_back(align);
}
/*
  this not work yet ,we need think a another
  way refactor children size

void VerticalLayout::getPreferedSize(CCSize &size)
{
    CCSize csize;
    if(isAnchored()){
        size.width = m_anchorWidth;
        size.height = m_anchorHeight;
        return;
    }else if(getWidth() > 0 && getHeight() > 0){
        size.width = getWidth();
        size.height = getHeight();
        return;
    }
    if(m_childs.size() == 0){
        BasLayout::getPreferedSize(size);
        return;
    }
    setPreferedSizeToChildMax(true);
    for(unsigned int i = 0;i < m_childs.size();i++){
        m_childs[i]->getPreferedSize(csize);
        if(size.width < csize.width)
            size.width = csize.width;
        size.height += csize.height;
        csize.width = 0;
        csize.height = 0;
    }
    size.width += m_leftMargin + m_rightMargin;
    size.height += m_childs.size() * m_spacing + m_topMargin + m_bottomMargin;
}
void VerticalLayout::getRefSize(const string &name, CCSize &size)
{
    if(name.size() == 0){
        size.width = 0;
        size.height = 0;
        return;
    }else{
        TouchNode *node = getAnchorNode(name);
        if(node){
            if(node->isAnchored()){
                float w,h;
                node->getAnchorSize(w,h);
                size.width = w;
                size.height = h;
            }else{
                size.width = 0;
                size.height = 0;
            }
        }
    }
}
*/
void VerticalLayout::childLayoutCompleted()
{
    if(m_childsAction)
        m_childsAction->doAction(m_childs);
}
void VerticalLayout::execLayout()
{
    if(m_childs.size() == 0)
        return;
    TouchNode *touchNode;
    BasLayout *layNode;
    std::vector<TouchNode*>::iterator iter;
    std::string abovename;
    if(!m_averageSet){
        for(iter = m_childs.begin();iter != m_childs.end();iter++){
            touchNode = *iter;
            touchNode->setMaxHeightRefSize("parent",1.0 / (m_childs.size() + 0.45));
            touchNode->setMaxWidthRefSize("parent",1.0);
            layNode = dynamic_cast<BasLayout*>(touchNode);
            if(layNode){
                layNode->setPreferedSizeToChildMax(true);
                layNode->setLeft("parent",uilib::Left);
                layNode->setRight("parent",uilib::Right);
                if(abovename.size() == 0){
                    layNode->setTop("parent",uilib::Top);
                }else{
                    layNode->setTop(abovename,uilib::Bottom);
                }
                abovename = layNode->getName();
                layNode->execLayout();
            }else{
                touchNode->setHorizontal("parent",0.5);
                if(abovename.size() == 0){
                    touchNode->setTop("parent",uilib::Top);
                }else{
                    touchNode->setTop(abovename,uilib::Bottom);
                }
                abovename = touchNode->getName();
            }
        }
    }else{
        int childnum = m_childs.size();
        float index = 1.0;
        for(iter = m_childs.begin();iter != m_childs.end();iter++){
            touchNode = *iter;
            touchNode->setMaxHeightRefSize("parent",1.0 / (m_childs.size() + 0.45));
            touchNode->setMaxWidthRefSize("parent",1.0);
            touchNode->setVertical("parent",index / (childnum * 2));
            index += 2.0;
            layNode = dynamic_cast<BasLayout*>(touchNode);
            if(layNode){
                layNode->setPreferedSizeToChildMax(false);
                layNode->setLeft("parent",uilib::Left);
                layNode->setRight("parent",uilib::Right);
                layNode->execLayout();
            }else{
                touchNode->setHorizontal("parent",0.5);
            }
        }
    }
    for(unsigned int i = 0;i < m_childAligns.size();i++){
        ChildAlign &align = m_childAligns[i];
        TouchNode *node = m_childs[align.index];
        node->setHorizontal("",0);
        if(align.type == uilib::Left)
            node->setLeft("parent",uilib::Left);
        else if(align.type == uilib::Right)
            node->setRight("parent",uilib::Right);
    }
}
HorizontalLayout::HorizontalLayout()
{

}
HorizontalLayout::~HorizontalLayout()
{

}
void HorizontalLayout::setChildAlign(int index,uilib::AnchorType type)
{
    if(index < 0 || index >= m_childs.size())
        return;
    if(type != uilib::Top && type != uilib::Bottom)
        return;
    ChildAlign align;
    align.index = index;
    align.type = type;
    m_childAligns.push_back(align);
}
/*
  same with vertical layout
void HorizontalLayout::getPreferedSize(CCSize &size)
{
    CCSize csize;
    if(isAnchored()){
        size.width = m_anchorWidth;
        size.height = m_anchorHeight;
        return;
    }else if(getWidth() > 0 && getHeight() > 0){
        size.width = getWidth();
        size.height = getHeight();
        return;
    }
    if(m_childs.size() == 0){
        BasLayout::getPreferedSize(size);
        return;
    }
    setPreferedSizeToChildMax(true);
    for(unsigned int i = 0;i < m_childs.size();i++){
        m_childs[i]->getPreferedSize(csize);
        if(size.height < csize.height)
            size.height = csize.height;
        size.width += csize.width;
        csize.width = 0;
        csize.height = 0;
    }
    size.width += m_childs.size() * m_spacing + m_leftMargin + m_rightMargin;
    size.height += m_topMargin + m_bottomMargin;
}
void HorizontalLayout::getRefSize(const string &name, CCSize &size)
{
    if(name.size() == 0){
        size.width = 0;
        size.height = 0;
        return;
    }else{
        TouchNode *node = getAnchorNode(name);
        if(node){
            if(node->isAnchored()){
                float w,h;
                node->getAnchorSize(w,h);
                size.width = w;
                size.height = h;
            }else{
                size.width = 0;
                size.height = 0;
            }
        }
    }
}
*/
void HorizontalLayout::childLayoutCompleted()
{
    if(m_childsAction)
        m_childsAction->doAction(m_childs);
}
void HorizontalLayout::execLayout()
{
    if(m_childs.size() == 0)
        return;
    TouchNode *touchNode;
    BasLayout *layNode;
    std::vector<TouchNode*>::iterator iter;
    std::string abovename;
    if(!m_averageSet){
        for(iter = m_childs.begin();iter != m_childs.end();iter++){
            touchNode = *iter;
            touchNode->setMaxWidthRefSize("parent",1.0 / (m_childs.size() + 0.45));
            touchNode->setMaxHeightRefSize("parent",1.0);
            layNode = dynamic_cast<BasLayout*>(touchNode);
            if(layNode){
                layNode->setPreferedSizeToChildMax(true);
                layNode->setTop("parent",uilib::Top);
                layNode->setBottom("parent",uilib::Bottom);
                if(abovename.size() == 0){
                    layNode->setLeft("parent",uilib::Left);
                }else{
                    layNode->setLeft(abovename,uilib::Right);
                }
                abovename = layNode->getName();
                layNode->execLayout();
            }else{
                touchNode->setVertical("parent",0.5);
                if(abovename.size() == 0){
                    touchNode->setLeft("parent",uilib::Left);
                }else{
                    touchNode->setLeft(abovename,uilib::Right);
                }
                abovename = touchNode->getName();
            }
        }
    }else{
        int childnum = m_childs.size();
        float index = 1.0;
        for(iter = m_childs.begin();iter != m_childs.end();iter++){
            touchNode = *iter;
            touchNode->setMaxWidthRefSize("parent",1.0 / (m_childs.size() + 0.45));
            touchNode->setMaxHeightRefSize("parent",1.0);
            touchNode->setHorizontal("parent",index / (childnum * 2));
            index += 2.0;
            layNode = dynamic_cast<BasLayout*>(touchNode);
            if(layNode){
                layNode->setPreferedSizeToChildMax(false);
                layNode->setTop("parent",uilib::Top);
                layNode->setBottom("parent",uilib::Bottom);
                layNode->execLayout();
            }else{
                touchNode->setVertical("parent",0.5);
            }
        }
    }
    for(unsigned int i = 0;i < m_childAligns.size();i++){
        ChildAlign &align = m_childAligns[i];
        TouchNode *node = m_childs[align.index];
        node->setVertical("",0);
        if(align.type == uilib::Top)
            node->setTop("parent",uilib::Top);
        else if(align.type == uilib::Bottom)
            node->setBottom("parent",uilib::Bottom);
    }
}
GridLayout::GridLayout(int row,int col)
{
    m_row = row;
    m_col = col;
}
GridLayout::~GridLayout()
{

}
void GridLayout::execLayout()
{
    if(m_childs.size() == 0)
        return;
    int childCount = m_childs.size();
    if(m_row * m_col < childCount)
        return;
    TouchNode *node;
    float maxWidth = 1.0 / m_col;
    float maxHeight = 1.0 / m_row;
    for(unsigned int i = 0;i < childCount;i++){
        node = m_childs[i];
        int prow = i / m_col;
        int pcol = i % m_col;
        node->setHorizontal("parent",(2 * pcol + 1) / (2.0 * m_col));
        node->setVertical("parent",(2 * prow + 1) / (2.0 * m_row));
        node->setMaxWidthRefSize("parent",maxWidth);
        node->setMaxHeightRefSize("parent",maxHeight);
        node->setMargins(m_spacing);
        BasLayout *lay = dynamic_cast<BasLayout*>(node);
        if(lay){
            lay->execLayout();
        }
    }
}
BasWidget::BasWidget()
{
    m_layout = 0;
    m_moveinAction = 0;
    m_moveoutAction = 0;
    m_layoutInAction = 0;
    m_layoutOutAction = 0;
    m_effectAction = 0;
    m_eActionEnabledACompleted = false;
}
BasWidget::~BasWidget()
{

}
void BasWidget::setLayout(BasLayout *layout)
{
    if(m_layout){
        cout << "BasWidget::setLayout,can not set multi-layout into BasWidget,please check!" << endl;
        return;
    }
    m_layout = layout;
    addChild(layout);
    m_layout->setLeft("parent",uilib::Left);
    m_layout->setRight("parent",uilib::Right);
    m_layout->setTop("parent",uilib::Top);
    m_layout->setBottom("parent",uilib::Bottom);
    m_layout->setOwner(this);
    m_layout->setSizeLimitedToParent();
    m_layout->execLayout();
}
BasLayout *BasWidget::getLayout()
{
    return m_layout;
}
void BasWidget::removeLayout()
{
    if(m_layout){
        this->delChild(m_layout);
        delete m_layout;
        m_layout = 0;
    }
}
BasLayout *BasWidget::takeLayout()
{
    BasLayout *rev = m_layout;
    if(m_layout){
        this->delChild(m_layout);
        m_layout = 0;
    }
    return rev;
}
/*
void BasWidget::getPreferedSize(CCSize &size)
{
    if(isAnchored()){
        size.width = m_anchorWidth;
        size.height = m_anchorHeight;
    }else if(getWidth() > 0 && getHeight() > 0){
        size.width = getWidth();
        size.height = getHeight();
    }else if(m_layout){
        m_layout->getPreferedSize(size);
    }else{
        BasFrame::getPreferedSize(size);
    }
}
*/
void BasWidget::layoutCompleted()
{
    if(m_moveinAction){
        moveIn();
    }else{
        TouchNode::layoutCompleted();
    }
    if(m_eActionEnabledACompleted && m_effectAction && !m_effectAction->isRunning())
        m_effectAction->doAction(this,true);
}
void BasWidget::moveIn()
{
    BasFrame::moveInStart();
    std::vector<TouchNode*> nodes;
    nodes.push_back(this);
    m_moveinAction->doAction(nodes);
}
void BasWidget::moveOut()
{
    BasFrame::moveOutStart();
    if(m_moveoutAction){
        std::vector<TouchNode*> nodes;
        nodes.push_back(this);
        m_moveoutAction->doAction(nodes);
    }
}
void BasWidget::childLayoutCompleted()
{
    if(m_layoutInAction && m_layout){
        std::vector<TouchNode*> nodes;
        nodes.push_back(m_layout);
        m_moveinAction->doAction(nodes);
    }else{
        TouchNode::childLayoutCompleted();
    }
}
void BasWidget::setEffectActionEnabled(bool enable)
{
    if(m_effectAction == 0){
        return;
    }else{
        m_effectAction->doAction(this,enable);
    }
}
void BasWidget::setEffectActionRunningLayoutCompleted()
{
    m_eActionEnabledACompleted = true;
}

BasButton::BasButton()
{
    m_buttonIndex = -1;
    m_normalSkin = 0;
    m_pressedSkin = 0;

    m_touchInListener = 0;
    m_touchOutListener = 0;
    m_touchInFunc = 0;
    m_touchOutFunc = 0;

    m_scaleRate = 0.1;
    m_enabled = true;
    setCanTouch(true);
}
BasButton::~BasButton()
{

}
void BasButton::setButtonInfo(const std::string &text,
                   const std::string &theme,
                   const std::string &buttonbg,
                   const CCSize &size,
                   const std::string &pressedButtonBg,
                   const std::string &fontFaimily,
                   int fontSize,
                   ccColor3B color)
{
    m_text = text;
    m_theme = theme;
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(theme);
    string fontName = fontFaimily;
    if (fontName.empty()) {
        fontName = getSystemFont();
    }
    m_normalSkin = ButtonTextImageSkin::create(text,size,uiDef,buttonbg,
                                                fontName,fontSize,color);
    setSkin(m_normalSkin);
    if(!pressedButtonBg.empty()){
        m_pressedSkin =  ButtonTextImageSkin::create(text,size,uiDef,pressedButtonBg,
                                                     fontName,fontSize,color);
    }
}
void BasButton::setButtonInfo(const char *text,const char *fontFile,
                   const std::string &theme,
                   const std::string &buttonbg,
                   const CCSize &size,ccColor3B color)
{
    m_text = text;
    m_theme = theme;
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(theme);
    m_normalSkin = ButtonTextImageSkin::create("",size,uiDef,buttonbg,
                                               "",0,ccBLACK);
    setSkin(m_normalSkin);
    CCLabelBMFont *font = CCLabelBMFont::create(text,fontFile);
    font->setColor(color);
    this->CCNode::addChild(font,1);
    font->setAnchorPoint(ccp(0.5,0.5));
    CCSize s;m_normalSkin->getPreferedSize(s);
    if(s.width == 0 && s.height == 0){
        m_normalSkin->setFrameSize(font->getContentSize());
        m_normalSkin->getPreferedSize(s);
    }
    font->setPosition(ccp(s.width / 2,s.height / 2));
}
void BasButton::setButtonInfoWithBorder(const char *text,const char *fontFile,
                                  const std::string &theme,
                                  const std::string &buttonbg,
                                  const CCSize &size,
                                  ccColor3B color)
{
    m_text = text;
    m_theme = theme;
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(theme);
    m_normalSkin = BorderImageSkin::create(size,uiDef,buttonbg);
    setSkin(m_normalSkin);
    CCLabelBMFont *font = CCLabelBMFont::create(text,fontFile);
    font->setColor(color);
    this->CCNode::addChild(font,1);
    font->setAnchorPoint(ccp(0.5,0.5));
    CCSize s;m_normalSkin->getPreferedSize(s);
    if(s.width == 0 && s.height == 0){
        m_normalSkin->setFrameSize(font->getContentSize());
        m_normalSkin->getPreferedSize(s);
    }
    font->setPosition(ccp(s.width / 2,s.height / 2));
}
const std::string &BasButton::getTheme()
{
    return m_theme;
}
const std::string &BasButton::getText()
{
    return m_text;
}
void BasButton::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_enabled) {
        return;
    }
    if(m_pressedSkin){
        replaceSkin(m_pressedSkin);
    }else{
        setScale(1.0 + m_scaleRate);
    }
    if(m_touchInListener && m_touchInFunc)
        (m_touchInListener->*m_touchInFunc)(this,&m_buttonIndex);
}
void BasButton::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_enabled) {
        return;
    }
}
void BasButton::touchMoveInEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_enabled) {
        return;
    }
    if(m_pressedSkin){
        replaceSkin(m_pressedSkin);
    }else{
        setScale(1.0 + m_scaleRate);
    }
}
void BasButton::touchMoveOutEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_enabled) {
        return;
    }
    if(m_pressedSkin && m_normalSkin){
        replaceSkin(m_normalSkin);
    }else{
        setScale(1.0);
    }
}
void BasButton::setTouchInCB(CCNode *listener,SEL_CallFuncND func)
{
    m_touchInListener = listener;
    m_touchInFunc = func;
}
void BasButton::setTouchOutCB(CCNode *listener,SEL_CallFuncND func)
{
    m_touchOutListener = listener;
    m_touchOutFunc = func;
}
void BasButton::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_enabled) {
        return;
    }
    if(m_pressedSkin && m_normalSkin){
        replaceSkin(m_normalSkin);
    }else{
        setScale(1.0);
    }
    if(underMouse() && m_clickListener && m_clickFunc){
        (m_clickListener->*m_clickFunc)(this,&m_buttonIndex);
    }
    if(m_touchOutListener && m_touchOutFunc)
        (m_touchOutListener->*m_touchOutFunc)(this,&m_buttonIndex);
}
void BasButton::setEnabled(bool enabled)
{
    m_enabled = enabled;
}
bool BasButton::isEnabled()
{
    return m_enabled;
}

BasLabel::BasLabel()
{
    m_labelIndex = -1;
    setCanTouch(false);
}
BasLabel::~BasLabel()
{

}
void BasLabel::setLabelInfo(const std::string &text,
                   const std::string &theme,
                   const std::string &labelbg,
                   const CCSize &size,
                   const std::string &fontFaimily,
                   int fontSize,
                   ccColor3B color)
{
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(theme);
    string fontName = fontFaimily;
    if (fontName.empty()) {
        fontName = getSystemFont();
    }
    BasSkin *skin = ButtonTextImageSkin::create(text,size,uiDef,labelbg,
                                                fontName,fontSize,color);
    setSkin(skin);
}
void BasLabel::setLabelInfo(const char *text,const char *fontFile,
                  const std::string &theme,
                  const std::string &labelbg ,
                  const CCSize &size,
                  ccColor3B color)
{
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(theme);
    BasSkin *skin = ButtonTextImageSkin::create("",size,uiDef,labelbg,
                                                "",0,ccBLACK);
    setSkin(skin);
    CCLabelBMFont *font = CCLabelBMFont::create(text,fontFile);
    font->setColor(color);
    this->CCNode::addChild(font,1);
    font->setAnchorPoint(ccp(0.5,0.5));
    CCSize s;skin->getPreferedSize(s);
    if(size.width == 0 && size.height == 0){
        skin->setFrameSize(font->getContentSize());
        skin->getPreferedSize(s);
    }
    font->setPosition(ccp(s.width / 2,s.height / 2));
}
void BasLabel::setLabelText(const std::string &text)
{
    if(m_skin){
        ButtonTextImageSkin *skin = (ButtonTextImageSkin*)m_skin;
        skin->updateText(text);
    }
}
const std::string &BasLabel::getTheme()
{
    return m_theme;
}
const std::string &BasLabel::getText()
{
    return m_text;
}

CheckBox::CheckBox()
{
    m_checked = false;
    m_checkIndex = -1;
    m_checkedSkin = 0;
    m_uncheckedSkin = 0;
    m_labelWidget = 0;
    m_iconWidget = 0;
    setCanTouch(true);
}
CheckBox::~CheckBox()
{
    if(m_checkedSkin)
        m_checkedSkin->removeFromParentAndCleanup(true);
    if(m_uncheckedSkin)
        m_uncheckedSkin->removeFromParentAndCleanup(true);
}
void CheckBox::setCheckInfo(const std::string &text,
                    const std::string &theme,
                    const std::string &bg,
                    const std::string &labelbg,
                    const CCSize &size,
                    const std::string &fontFaimily,
                    int fontSize,
                    ccColor3B color)
{
    setPreferedSize(size);
    m_theme = theme;
    m_text = text;
    m_bg = bg;
    m_setSize = size;
    m_iconWidget = new BasWidget;
    m_labelWidget = new BasLabel;
    m_labelWidget->setLeftMargin(10);
    this->addChild(m_labelWidget);
    this->addChild(m_iconWidget);
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(theme);
    CCSize labelSize;
    labelSize.width = size.width  - 80;
    labelSize.height = size.height;
    if(labelSize.width < 0) labelSize.width = 0;
    if(labelSize.height < 0) labelSize.height = 0;
    string fontName = fontFaimily;
    if (fontName.empty()) {
        fontName = getSystemFont();
    }
    m_labelWidget->setLabelInfo(text,"default",labelbg,labelSize,fontName,fontSize,color);
    m_checkedSkin = ButtonImageSkin::create(CCSizeMake(70,70),uiDef,"checkboxchecked");
    m_uncheckedSkin = ButtonImageSkin::create(CCSizeMake(70,70),uiDef,"checkboxuncheck");

    m_iconWidget->setVertical("parent",0.5);
    m_iconWidget->setLeft("parent",uilib::Left);
    m_labelWidget->setVertical("parent",0.5);
    m_labelWidget->setRight("parent",uilib::Right);
    if(size.width != 0 && size.height != 0){
        m_iconWidget->setSizeLimitedToParent();
        m_labelWidget->setSizeLimitedToParent();
    }
    setCheck(m_checked);
}
void CheckBox::setCheckInfo(const char *text,const char *fontFile,
                  const std::string &theme,
                  const std::string &bg,
                  const CCSize &size,
                  ccColor3B color)
{
    setPreferedSize(size);
    m_theme = theme;
    m_text = text;
    m_bg = bg;
    m_setSize = size;
    m_iconWidget = new BasWidget;
    this->addChild(m_iconWidget);
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(theme);
    CCSize labelSize;
    labelSize.width = size.width  - 80;
    labelSize.height = size.height;
    if(labelSize.width < 0) labelSize.width = 0;
    if(labelSize.height < 0) labelSize.height = 0;
    m_checkedSkin = ButtonImageSkin::create(CCSizeMake(80,80),uiDef,"checkboxchecked");
    m_uncheckedSkin = ButtonImageSkin::create(CCSizeMake(80,80),uiDef,"checkboxuncheck");

    m_iconWidget->setVertical("parent",0.5);
    m_iconWidget->setLeft("parent",uilib::Left);
    if(size.width != 0 && size.height != 0){
        m_iconWidget->setSizeLimitedToParent();
    }
    setCheck(m_checked);

    CCLabelBMFont *font = CCLabelBMFont::create(text,fontFile);
    font->setColor(color);
    this->CCNode::addChild(font,1);
    font->setAnchorPoint(ccp(0,0.5));
    CCSize s;this->getPreferedSize(s);
    font->setPosition(ccp(90.0,s.height / 2));
}
void CheckBox::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(m_skin == 0){
        UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
        CCSize size = CCSizeMake(m_anchorWidth,m_anchorHeight);
        if(uiDef && !m_bg.empty()){
            BasSkin *skin = ButtonImageSkin::create(size,uiDef,m_bg);
            setSkin(skin);
        }
    }
}
const std::string &CheckBox::getTheme()
{
    return m_theme;
}
const std::string &CheckBox::getText()
{
    return m_text;
}
void CheckBox::setCheck(bool check)
{
    m_checked = check;
    if(m_checked){
        m_iconWidget->replaceSkin(m_checkedSkin);
    }else{
        m_iconWidget->replaceSkin(m_uncheckedSkin);
    }
}
void CheckBox::getPreferedSize(CCSize &size)
{
    if(m_setSize.width != 0 || m_setSize.height != 0){
        BasFrame::getPreferedSize(size);
    }else{
        CCSize labelSize,iconSize;
        if(m_labelWidget)
            m_labelWidget->getSkinSize(labelSize);
        if(m_iconWidget)
            m_iconWidget->getSkinSize(iconSize);
        labelSize.width += iconSize.width;
        labelSize.height = labelSize.height > iconSize.height ? labelSize.height : iconSize.height;
        BasFrame::getPreferedSize(size);
        if(size.width < labelSize.width)
            size.width = labelSize.width;
        if(size.height < labelSize.height)
            size.height = labelSize.height;
    }
}
BasWidget *CheckBox::getLabelWidget()
{
    return m_labelWidget;
}
BasWidget *CheckBox::getIconWidget()
{
    return m_iconWidget;
}
void CheckBox::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    setScale(1.1);
}
void CheckBox::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{

}
void CheckBox::touchMoveInEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    setScale(1.1);
}
void CheckBox::touchMoveOutEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    setScale(1.0);
}
void CheckBox::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    setCheck(!m_checked);
    setScale(1.0);
    if(underMouse() && m_clickListener && m_clickFunc){
        (m_clickListener->*m_clickFunc)(this,&m_checkIndex);
    }
}
BorderWidget::BorderWidget()
{

}
BorderWidget::~BorderWidget()
{

}
void BorderWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(m_skin == 0 && !m_theme.empty() && !m_themeBg.empty()){
        CCSize size = CCSizeMake(m_anchorWidth,m_anchorHeight);
        UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
        BasSkin *skin = BorderImageSkin::create(size,uiDef,m_themeBg);
        setSkin(skin);
    }
}
void BorderWidget::setTheme(const std::string &theme,const std::string &bg)
{
    m_theme = theme;
    m_themeBg = bg;
}
const std::string &BorderWidget::getTheme()
{
    return m_theme;
}
const std::string &BorderWidget::getThemeBg()
{
    return m_themeBg;
}
HTriWidget::HTriWidget()
{
    m_themeSkin = 0;
}
HTriWidget::~HTriWidget()
{

}
void HTriWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    m_themeSkin->setSkinFillVer(m_skinFillVer);
    m_themeSkin->setSkinFillHor(m_skinFillHor);
    m_themeSkin->setFrameSize(CCSizeMake(m_anchorWidth,m_anchorHeight));
    setSkin(m_themeSkin);
}
void HTriWidget::setTheme(const std::string &theme,const std::string &bg)
{
    m_theme = theme;
    m_themeBg = bg;
    if(!m_theme.empty() && !m_themeBg.empty()){
        CCSize size = CCSizeMake(0,0);
        UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
        BasSkin *skin = HTrisectionImageSkin::create(size,uiDef,m_themeBg);
        skin->getPreferedSize(size);
        m_themeSkin = skin;
    }
}
const std::string &HTriWidget::getTheme()
{
    return m_theme;
}
const std::string &HTriWidget::getThemeBg()
{
    return m_themeBg;
}
VTriWidget::VTriWidget()
{
    m_themeSkin = 0;
}
VTriWidget::~VTriWidget()
{

}
void VTriWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    m_themeSkin->setFrameSize(CCSizeMake(m_anchorWidth,m_anchorHeight));
    setSkin(m_themeSkin);
}
void VTriWidget::setTheme(const std::string &theme,const std::string &bg)
{
    m_theme = theme;
    m_themeBg = bg;
    if(!m_theme.empty() && !m_themeBg.empty()){
        CCSize size = CCSizeMake(0,0);
        UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
        m_themeSkin = VTrisectionImageSkin::create(size,uiDef,m_themeBg);
        m_themeSkin->getPreferedSize(size);
        setWidth(size.width);
    }
}
const std::string &VTriWidget::getTheme()
{
    return m_theme;
}
const std::string &VTriWidget::getThemeBg()
{
    return m_themeBg;
}
BasNodeDelegateWidget::BasNodeDelegateWidget(CCNode *client,const CCSize &_size)
{
    m_node = client;
    m_size = _size;
    bool scale = true;
    if(m_size.width == 0 && m_size.height == 0){
        m_size = m_node->getContentSize();
        scale = false;
    }
    this->setPreferedSize(m_size);
    this->setContentSize(m_size);
    this->CCNode::addChild(m_node);
    m_node->setAnchorPoint(ccp(0.5,0.5));
    m_node->setPosition(ccp(m_size.width / 2,m_size.height / 2));
    if(scale){
        CCSize csize = m_node->getContentSize();
        m_node->setScaleX(m_size.width / csize.width);
        m_node->setScaleY(m_size.height / csize.height);
    }
}
BasNodeDelegateWidget::~BasNodeDelegateWidget()
{

}
BasNodeLimitWidget::BasNodeLimitWidget(CCNode *client,const CCSize &_size)
{
    m_node = client;
    m_nodeSize = _size;
    if(m_nodeSize.width == 0 && m_nodeSize.height == 0){
        m_nodeSize = m_node->getContentSize();
    }
    m_added = false;
}
BasNodeLimitWidget::~BasNodeLimitWidget()
{

}
void BasNodeLimitWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(!m_added){
        m_added = true;
        this->CCNode::addChild(m_node);
        m_node->setAnchorPoint(ccp(0.5,0.5));
        m_node->setPosition(ccp(m_anchorWidth / 2,m_anchorHeight / 2));
    }
    if(m_anchorWidth < m_nodeSize.width)
        m_node->setScaleX(m_anchorWidth / m_nodeSize.width);
    if(m_anchorHeight < m_nodeSize.height)
        m_node->setScaleY(m_anchorHeight / m_nodeSize.height);
}
SplashMessageWidget::SplashMessageWidget(TouchNode *parent,const std::string &text,const std::string &theme,const std::string &bg,
    const std::string &fontFamily,float fontSize,const ccColor3B &color)
{
    CCSize psize;
    parent->getAnchorSize(psize.width,psize.height);
    psize.width *= 0.8;
    psize.height = 0;
    BasLabel *label = new BasLabel;
    string fontName = fontFamily;
    if (fontName.empty()) {
        fontName = getSystemFont();
    }
    label->setLabelInfo(text,"","",psize,fontName,fontSize,color);
    CCSize lsize;
    label->getPreferedSize(lsize);
    this->addChild(label);
    label->setCenterIn("parent");
    psize.width = lsize.width * 1.1;
    psize.height = lsize.height * 1.1;
    if(psize.height < psize.width / 3)
        psize.height  = psize.width / 3;
    setWidth(psize.width);
    setHeight(psize.height);

    if(theme.size() != 0 && bg.size() != 0){
        BasSkin *skin = BorderImageSkin::create(psize,theme,bg);
        if(skin)
            setSkin(skin);
    }
    parent->getAnchorSize(psize.width,psize.height);
    this->setAnchorPoint(ccp(0.5,0.5));
    this->setPosition(ccp(psize.width / 2,psize.height / 2));
    parent->CCNode::addChild(this,10000);
    BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
    BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
    moveIn->setFinishCB(this,callfuncN_selector(SplashMessageWidget::onMoveInActionFinished));
    moveIn->setEaseType(uilib::EaseSineInOut);
    moveIn->setMoveInType(uilib::ScaleXIn);
    moveOut->setEaseType(uilib::EaseSineInOut);
    moveOut->setMoveOutType(uilib::ScaleYOut);
    this->setMoveinAction(moveIn);
    this->setMoveoutAction(moveOut);
    this->layout();
    m_delayTime = 0.5;
    m_finishedListener = 0;
    m_finishedFunc = 0;
}
SplashMessageWidget::~SplashMessageWidget()
{

}
void SplashMessageWidget::setDelayTime(float time)
{
    m_delayTime = time;
}
void SplashMessageWidget::setMoveInTime(float time)
{
    BasNodeAction *action = getMoveinAction();
    if(action){
        action->setActionTime(time);
    }
}
void SplashMessageWidget::setMoveOutTime(float time)
{
    BasNodeAction *action = getMoveoutAction();
    if(action){
        action->setActionTime(time);
    }
}
void SplashMessageWidget::setFinishedCB(CCNode *listener,SEL_CallFuncN func)
{
    m_finishedListener = listener;
    m_finishedFunc = func;
}
void SplashMessageWidget::onDelayFinished(CCNode *sender)
{
    BasNodeAction *moveOut = getMoveoutAction();
    if(moveOut){
        moveOut->setFinishCB(this,callfuncN_selector(SplashMessageWidget::onMoveOutActionFinished));
        this->moveOut();
    }else{
        onMoveOutActionFinished(this);
    }
}
void SplashMessageWidget::onMoveInActionFinished(CCNode *sender)
{
    BasNodeAction *moveOut = getMoveoutAction();
    if(moveOut){
        if(m_delayTime > 0){
            CCFiniteTimeAction *delay = CCDelayTime::create(m_delayTime);
            this->runAction(CCSequence::create(delay,
                            CCCallFuncN::create(this,callfuncN_selector(SplashMessageWidget::onDelayFinished)), 0));
        }else{
            moveOut->setFinishCB(this,callfuncN_selector(SplashMessageWidget::onMoveOutActionFinished));
            this->moveOut();
        }
    }else{
        onMoveOutActionFinished(this);
    }
}
void SplashMessageWidget::onMoveOutActionFinished(CCNode *sender)
{
    if(m_finishedListener && m_finishedFunc){
        (m_finishedListener->*m_finishedFunc)(this);
    }
    this->removeFromParentAndCleanup(true);
}

}
