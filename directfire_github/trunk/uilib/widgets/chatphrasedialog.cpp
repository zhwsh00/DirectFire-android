#include "chatphrasedialog.h"
#include "../base/uithemedef.h"

namespace uilib
{
ChatPhraseDialog::ChatPhraseDialog(TouchNode *parent,const CCPoint &pos)
{
    parent->addChild(this);
    m_pos = pos;
    m_theme = "default";
    m_themeBg = "inputbg";
    m_clickListener = 0;
    m_clickFunc = 0;
    m_clickedIndex = -1;
    setCanTouch(true);
    setBlockEvent(true);
    setTouchPriority(uilib::TopPriority);
    init();
}
ChatPhraseDialog::~ChatPhraseDialog()
{

}
void ChatPhraseDialog::init(int dummy)
{
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    m_hasPhrases = uiDef->getPhrase();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float pw,ph;
    pw = ph = 0;
    std::vector<BasButton *> buttons;
    CCSize size;
    size.width = winSize.width;
    size.height = 40;
    for(unsigned int i = 0;i < m_hasPhrases.size();i++){
        BasButton *button = new BasButton;
        button->setButtonInfo("","","",size);
        button->setButtonIndex(i);
        button->setClickCB(this,callfuncND_selector(ChatPhraseDialog::onPhraseClicked));
        buttons.push_back(button);
        this->addChild(button);
        button->setLeftMargin(6);
        button->setRightMargin(6);
        ph += size.height;
        if(pw < size.width)
            pw = size.width;
        BasLabel *label = new BasLabel();
        label->setLabelInfo(m_hasPhrases[i],"","",CCSizeMake(0,0));
        button->addChild(label);
        label->setLeft("parent",uilib::Left);
        label->setVertical("parent",0.5);
    }
    setWidth(winSize.width);
    setHeight(ph);
    std::string topName;
    for(unsigned int i = 0;i < buttons.size();i++){
        BasButton *button = buttons[i];
        if(topName.empty()){
            button->setLeft("parent",uilib::Left);
            button->setRight("parent",uilib::Right);
            button->setTop("parent",uilib::Top);
        }else{
            button->setLeft("parent",uilib::Left);
            button->setRight("parent",uilib::Right);
            button->setTop(topName,uilib::Bottom);
        }
        topName = button->getName();
    }
    layout(true);
    setAnchorPoint(ccp(0,0));
    setPosition(ccp(0,m_pos.y));
}
void ChatPhraseDialog::show()
{
    setVisible(true);
}
void ChatPhraseDialog::hide()
{
    setVisible(false);
}
void ChatPhraseDialog::getUserClickedPhrase(std::string &face)
{
    if(m_clickedIndex >= 0 && m_clickedIndex < m_hasPhrases.size())
        face = m_hasPhrases[m_clickedIndex];
    else
        face.clear();
    m_clickedIndex = -1;
}
void ChatPhraseDialog::setPhraseClickCB(CCNode *node,SEL_CallFuncND func)
{
    m_clickListener = node;
    m_clickFunc = func;
}
void ChatPhraseDialog::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BorderWidget::touchPressEvent(pTouch,pEvent);
}
void ChatPhraseDialog::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BorderWidget::touchMoveEvent(pTouch,pEvent);
}
void ChatPhraseDialog::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    hide();
}
void ChatPhraseDialog::onPhraseClicked(CCNode *node,void *data)
{
    m_clickedIndex = *(int*)data;
    if(m_clickListener && m_clickFunc){
        (m_clickListener->*m_clickFunc)(this,0);
    }
}
}
