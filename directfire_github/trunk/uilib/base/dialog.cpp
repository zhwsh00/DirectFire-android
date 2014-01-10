#include "dialog.h"
#include "scrollarea.h"
#include "../skin/absskin.h"
#include "../actions/absnodeaction.h"
#include "../widgets/filltestwidget.h"
#include "../base/fontutil.h"
#include "../base/uithemedef.h"
namespace uilib
{

BasDialog::BasDialog()
{
    m_dialogListener = 0;
    m_dialogFunc = 0;
    m_contentWidget = 0;
    m_titleWidget = 0;
    m_finished = false;
    m_layout = new HorizontalLayout;
    m_edgeSize = 0;
    m_buttonThemes.push_back("button");
    m_buttonThemes.push_back("buttongreen");
    m_buttonThemes.push_back("buttonred");
    setDialogInfo();
}
BasDialog::~BasDialog()
{

}
bool BasDialog::finish()
{
    if(m_finished)
        return true;
    //base
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    BasSkin *skin = BorderImageSkin::create(m_dialogSize,uiDef,m_bg);
    if(skin) setSkin(skin);
    //button
    std::string btext,btheme;
    m_layout->setAveraged(true);
    for(unsigned int i = 0;i < m_buttonTexts.size();i++){
        btext = m_buttonTexts[i];
        if(i < m_buttonThemes.size())
            btheme = m_buttonThemes[i];
        else
            btheme = "button";
        BasButton *button = new BasButton;
        button->setButtonIndex(i);
        button->setClickCB(this,callfuncND_selector(BasDialog::onButtonClicked));
        button->setButtonInfoWithBorder(btext.data(),"fonts/uifont35.fnt",m_theme,btheme,CCSizeMake(160,60));
        m_layout->addWidget(button);
        m_layout->setChildAlign(i,uilib::Bottom);
        m_buttons.push_back(button);
    }
    BasWidget *bwidget = new BasWidget;
    bwidget->setLeft("parent",uilib::Left);
    bwidget->setRight("parent",uilib::Right);
    bwidget->setBottom("parent",uilib::Bottom);
    bwidget->setHeight(80);
    bwidget->setLayout(m_layout);
    bwidget->setBottomMargin(m_edgeSize);
    this->addChild(bwidget);
    //title
    if(m_titleText.size() != 0){
        m_titleWidget = new BasButton;
        m_titleWidget->setCanTouch(false);
        m_titleWidget->setButtonInfo(m_titleText,m_theme,m_titleBg,CCSizeMake(0,0),"","",30,ccWHITE);
        m_titleWidget->setHorizontal("parent",0.5);
        m_titleWidget->setTop("parent",uilib::Top);
        m_titleWidget->setMaxHeightRefSize("parent",0.15);
        m_titleWidget->setTopMargin(m_edgeSize);
        this->addChild(m_titleWidget);
    }
    if(m_contentWidget){
        m_contentWidget->setLeft("parent",uilib::Left);
        m_contentWidget->setRight("parent",uilib::Right);
        if(m_titleWidget)
            m_contentWidget->setTop(m_titleWidget->getName(),uilib::Bottom);
        else
            m_contentWidget->setTop("parent",uilib::Top);
        m_contentWidget->setBottom(bwidget->getName(),uilib::Top);
        m_contentWidget->setLeftMargin(m_edgeSize);
        m_contentWidget->setRightMargin(m_edgeSize);
        m_contentWidget->setTopMargin(m_edgeSize / 4);
        m_contentWidget->setBottomMargin(m_edgeSize / 4);
        this->addChild(m_contentWidget);
    }
    return true;
}
void BasDialog::setDialogInfo(const std::string &theme ,
                   const std::string &bg,
                   const CCSize &size)
{
    m_theme = theme;
    m_bg = bg;
    m_dialogSize = size;
    setWidth(m_dialogSize.width);
    setHeight(m_dialogSize.height);
    m_titleBg = "buttonbg";
}
void BasDialog::setButtons(const std::vector<std::string> &buttons)
{
    m_buttonTexts = buttons;
}
void BasDialog::setButtonThemes(const std::vector<std::string> &themes)
{
    m_buttonThemes = themes;
}
void BasDialog::setContentWidget(BasWidget *content)
{
    m_contentWidget = content;
}
void BasDialog::setTitle(const std::string &title,const std::string &titlebg)
{
    m_titleText = title;
    m_titleBg = titlebg;
}
void BasDialog::setClickCallBack(CCNode *listener,SEL_CallFuncND func)
{
    m_dialogListener = listener;
    m_dialogFunc = func;
}
BasButton *BasDialog::getButtonByIndex(int index)
{
    if(index < m_buttons.size())
        return m_buttons[index];
    else
        return 0;
}
void BasDialog::onButtonClicked(CCNode *pSender,void *index)
{
    if(m_dialogListener && m_dialogFunc){
        (m_dialogListener->*m_dialogFunc)(this,index);
    }
}
void BasDialog::exec()
{
    this->finish();
    this->layout();
}

MessageDialog::MessageDialog()
{
    m_scrollArea = new TextScrollArea;
    m_scrollArea->setTheme(m_theme,"");
    setContentWidget(m_scrollArea);
    std::vector<std::string> buttons;
    buttons.push_back("Ok");
    setButtons(buttons);
}
MessageDialog::~MessageDialog()
{

}
void MessageDialog::setTextInfo(const std::string &text,const std::string &fontfamily,int fontSize,ccColor3B color)
{
    if (fontfamily.empty()) {
        m_scrollArea->setTextInfo(text,getSystemFont(),fontSize,color);
    } else {
        m_scrollArea->setTextInfo(text,fontfamily,fontSize,color);
    }
}

}
