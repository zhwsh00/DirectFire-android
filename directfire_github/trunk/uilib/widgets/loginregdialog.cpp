#include "loginregdialog.h"
#include "../base/uithemedef.h"
#include "../skin/absskin.h"
#include "../actions/absnodeaction.h"
#include "../lang/langdef.h"
#include "../lang/stringenum.h"

namespace uilib
{

LoginRegDialog::LoginRegDialog(CCNode *parent,const ccColor4B &color)
{
    clear();
    if(color.r == 0 && color.g == 0 && color.b == 0 && color.a == 0){
    }else if(parent){
        CCLayerColor *realparent = CCLayerColor::create();
        realparent->initWithColor(color);
        parent->addChild(realparent);
        parent = realparent;
    }
    m_edgeSize = 20;
    m_theme = "default";
    m_bg = "dialog";
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float width = size.width < size.height ? size.width : size.height;
    width *= 0.9;
    float height = width * 0.8;
    setAnchoredSize(width,height);
    setTouchPriority(HighPriority);

    BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
    BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
    moveIn->setEaseType(uilib::EaseSineInOut);
    moveIn->setMoveInType(uilib::ScaleIn);
    moveOut->setEaseType(uilib::EaseSineInOut);
    moveOut->setMoveOutType(uilib::ScaleYOut);
    moveOut->setActionTime(0.2);
    moveOut->setFinishCB(this,callfuncN_selector(LoginRegDialog::onMoveOutFinished));
    this->setMoveinAction(moveIn);
    this->setMoveoutAction(moveOut);
    if(parent){
        parent->addChild(this);
        this->setAnchorPoint(ccp(0.5,0.5));
        this->setPosition(ccp(size.width / 2,size.height / 2));
    }
}
LoginRegDialog::~LoginRegDialog()
{
    CCLayerColor *node = dynamic_cast<CCLayerColor*>(getParent());
    if(node){
        node->removeFromParentAndCleanup(true);
    }else{
        this->removeFromParentAndCleanup(true);
    }
}
void LoginRegDialog::setTheme(const std::string &theme,const std::string &bg)
{
    m_theme = theme;
    m_bg = bg;
}
void LoginRegDialog::setTitleBg(const std::string &bg)
{
    m_titleBg = bg;
}
void LoginRegDialog::setLoginClickListener(CCNode *node,SEL_CallFuncND func)
{
    m_loginListener = node;
    m_loginFunc = func;
}
void LoginRegDialog::setCancelClickListener(CCNode *node,SEL_CallFuncND func)
{
    m_cancelListener = node;
    m_cancelFunc = func;
}
void LoginRegDialog::setRegClickListener(CCNode *node,SEL_CallFuncND func)
{
    m_regListener = node;
    m_regFunc = func;
}
void LoginRegDialog::setLoginInfo(const std::string &account,const std::string &passwd)
{
    m_account = account;
    m_passwd = passwd;
}
void LoginRegDialog::getLoginInfo(std::string &account,std::string &passwd)
{
    account = m_accountBox->getText();
    passwd = m_passwdBox->getText();
}
void LoginRegDialog::getRegInfo(std::string &account,std::string &passwd)
{
    account = m_accountBox->getText();
    passwd = m_passwdBox->getText();
}
void LoginRegDialog::clearLoginInfo()
{
    m_account.clear();
    m_passwd.clear();
    //clear inputbox
    if(m_accountBox)
        m_accountBox->setText("");
    if(m_passwdBox)
        m_passwdBox->setText("");
}
void LoginRegDialog::setLoginImg(const std::string &normal,const std::string &pressed)
{
    m_loginImg = normal;
    m_loginPressedImg = pressed;
}
void LoginRegDialog::setCancelImg(const std::string &normal,const std::string &pressed)
{
    m_cancelImg = normal;
    m_cancelPressedImg = pressed;
}
void LoginRegDialog::setLoginRegImg(const std::string &normal,const std::string &pressed)
{
    m_loginRegImg = normal;
    m_loginRegPressedImg = pressed;
}
void LoginRegDialog::setRegImg(const std::string &normal,const std::string &pressed)
{
    m_regImg = normal;
    m_regPressedImg = pressed;
}
void LoginRegDialog::setRegBackImg(const std::string &normal,const std::string &pressed)
{
    m_regBackImg = normal;
    m_regBackPressedImg = pressed;
}
void LoginRegDialog::setAccountLimitLen(int len)
{
    m_accountLimitLen = len;
    if(m_accountBox)
        m_accountBox->setMaxLength(m_accountLimitLen);
}
void LoginRegDialog::setPasswdLimitLen(int len)
{
    m_passwdLimitLen = len;
    if(m_passwdBox)
        m_passwdBox->setMaxLength(m_passwdLimitLen);
}
void LoginRegDialog::setDialogEnabled(bool enable)
{
    CCLayerColor *node = dynamic_cast<CCLayerColor*>(getParent());
    if(node){
        node->setVisible(enable);
    }
    this->setVisible(enable);
    this->setBlockEvent(enable);
}
void LoginRegDialog::exec()
{
    finished();
    layout();
}
void LoginRegDialog::destroy()
{
    moveOut();
}
void LoginRegDialog::onMoveOutFinished(CCNode *node)
{
    delete this;
}
void LoginRegDialog::onButtonClicked(CCNode *pSender,void *index)
{
    int id = *(int*)index;
    switch(id){
    case LoginButton:{
        std::string account = m_accountBox->getText();
        if(account.empty()){
            m_accountBox->setVisible(false);
            m_passwdBox->setVisible(false);
            SplashMessageWidget *splash = new SplashMessageWidget(this,UiThemeMgrProxy::getInstance()->getThemeMgr()->getLangDef()->getStringById(StringEnum::InputAccountName));
            splash->setFinishedCB(this,callfuncN_selector(LoginRegDialog::onFailedSplashFinished));
            return;
        }
        std::string passwd = m_passwdBox->getText();
        if(passwd.empty()){
            m_accountBox->setVisible(false);
            m_passwdBox->setVisible(false);
            SplashMessageWidget *splash = new SplashMessageWidget(this,UiThemeMgrProxy::getInstance()->getThemeMgr()->getLangDef()->getStringById(StringEnum::InputPasswd));
            splash->setFinishedCB(this,callfuncN_selector(LoginRegDialog::onFailedSplashFinished));
            return;
        }
        if(m_loginListener && m_loginFunc){
            (m_loginListener->*m_loginFunc)(this,0);
        }
        break;
    }
    case LoginCancelButton:{
        if(m_cancelListener && m_cancelFunc){
            (m_cancelListener->*m_cancelFunc)(this,0);
        }
        break;
    }
    case LoginRegButton:{
        //switch to reg page
        if(m_loginWidget->isEnabled()){
            m_loginTitleWidget->setVisible(false);
            m_regTitleWidget->setVisible(true);
            m_loginWidget->setEnabled(false);
            m_loginWidget->moveOut();
            m_regWidget->setVisible(true);
            m_regWidget->setEnabled(true);
            m_regWidget->moveIn();
            m_accountBox->setText("");
            m_passwdBox->setText("");
        }
        break;
    }
    case RegButton:{
        std::string account = m_accountBox->getText();
        if(account.empty()){
            m_accountBox->setVisible(false);
            m_passwdBox->setVisible(false);
            SplashMessageWidget *splash = new SplashMessageWidget(this,UiThemeMgrProxy::getInstance()->getThemeMgr()->getLangDef()->getStringById(StringEnum::InputAccountName));
            splash->setFinishedCB(this,callfuncN_selector(LoginRegDialog::onFailedSplashFinished));
            return;
        }
        std::string passwd = m_passwdBox->getText();
        if(passwd.empty()){
            m_accountBox->setVisible(false);
            m_passwdBox->setVisible(false);
            SplashMessageWidget *splash = new SplashMessageWidget(this,UiThemeMgrProxy::getInstance()->getThemeMgr()->getLangDef()->getStringById(StringEnum::InputPasswd));
            splash->setFinishedCB(this,callfuncN_selector(LoginRegDialog::onFailedSplashFinished));
            return;
        }
        if(m_regListener && m_regFunc){
            (m_regListener->*m_regFunc)(this,0);
        }
        break;
    }
    case RegRsetButton:{
        //reset account passwd box
        if(m_accountBox)
            m_accountBox->setText("");
        if(m_passwdBox)
            m_passwdBox->setText("");
        break;
    }
    case RegBackButton:{
        //switch to login pageelse
        if(!m_loginWidget->isEnabled()){
            m_loginTitleWidget->setVisible(true);
            m_regTitleWidget->setVisible(false);
            m_loginWidget->setEnabled(true);
            m_loginWidget->moveIn();
            m_regWidget->setEnabled(false);
            m_regWidget->moveOut();
            m_accountBox->setText("");
            m_passwdBox->setText("");
        }
        break;
    }
    default:{
        return;
    }
    }
}
void LoginRegDialog::onFailedSplashFinished(CCNode* sender)
{
    if (m_accountBox) {
        m_accountBox->setVisible(true);
    }
    if (m_passwdBox) {
        m_passwdBox->setVisible(true);
    }
}
void LoginRegDialog::finished()
{
    //init bg
    CCSize dialogSize = CCSizeMake(m_anchorWidth,m_anchorHeight);
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    BasSkin *skin = BorderImageSkin::create(dialogSize,uiDef,m_bg);
    if(skin) setSkin(skin);

    LangDef *lang = UiThemeMgrProxy::getInstance()->getThemeMgr()->getLangDef();
    if(1){ // title
        m_loginTitleWidget = new BasButton;
        m_loginTitleWidget->setCanTouch(false);
        m_loginTitleWidget->setButtonInfo("","fonts/uifont35.fnt",m_theme,m_titleBg);
        m_loginTitleWidget->setHorizontal("parent",0.5);
        m_loginTitleWidget->setTop("parent",uilib::Top);
        m_loginTitleWidget->setMaxHeightRefSize("parent",0.15);
        m_loginTitleWidget->setTopMargin(m_edgeSize);

        m_regTitleWidget = new BasButton;
        m_regTitleWidget->setCanTouch(false);
        m_regTitleWidget->setButtonInfo("","fonts/uifont35.fnt",m_theme,m_titleBg);
        m_regTitleWidget->setHorizontal("parent",0.5);
        m_regTitleWidget->setTop("parent",uilib::Top);
        m_regTitleWidget->setMaxHeightRefSize("parent",0.15);
        m_regTitleWidget->setTopMargin(m_edgeSize);
    }
    if(1){//buttons
        m_loginWidget = new BasWidget;
        HorizontalLayout *hlay;
        hlay = new HorizontalLayout;
        m_loginButton = new BasButton;
        m_loginButton->setCanTouch(true);
        m_loginButton->setButtonInfo(lang->getStringById(StringEnum::Login).data(),"fonts/uifont35.fnt",m_theme,m_loginImg,CCSizeMake(0,0),ccWHITE);
        m_loginButton->setButtonIndex(LoginButton);
        m_loginButton->setClickCB(this,callfuncND_selector(LoginRegDialog::onButtonClicked));

        m_loginCancelButton = new BasButton;
        m_loginCancelButton->setCanTouch(true);
        m_loginCancelButton->setButtonInfo(lang->getStringById(StringEnum::Cancel).data(),"fonts/uifont35.fnt",m_theme,m_cancelImg,CCSizeMake(0,0),ccWHITE);
        m_loginCancelButton->setButtonIndex(LoginCancelButton);
        m_loginCancelButton->setClickCB(this,callfuncND_selector(LoginRegDialog::onButtonClicked));

        m_loginRegButton = new BasButton;
        m_loginRegButton->setCanTouch(true);
        m_loginRegButton->setButtonInfo(lang->getStringById(StringEnum::Register).data(),"fonts/uifont35.fnt",m_theme,m_loginRegImg,CCSizeMake(0,0),ccWHITE);
        m_loginRegButton->setButtonIndex(LoginRegButton);
        m_loginRegButton->setClickCB(this,callfuncND_selector(LoginRegDialog::onButtonClicked));

        hlay->addWidget(m_loginButton);
        hlay->addWidget(m_loginCancelButton);
        hlay->addWidget(m_loginRegButton);
        hlay->setAlignChildsSize(true);
        hlay->setAveraged(true);

        m_loginWidget->setLayout(hlay);
        m_loginWidget->setLeft("parent",uilib::Left);
        m_loginWidget->setRight("parent",uilib::Right);
        m_loginWidget->setBottom("parent",uilib::Bottom);
        m_loginWidget->setMaxHeightRefSize("parent",0.2);
        m_loginWidget->setBottomMargin(m_edgeSize);
        m_loginWidget->setLeftMargin(m_edgeSize);
        m_loginWidget->setRightMargin(m_edgeSize);

        m_regWidget = new BasWidget;
        hlay = new HorizontalLayout;
        m_regButton = new BasButton;
        m_regButton->setCanTouch(true);
        m_regButton->setButtonInfo(lang->getStringById(StringEnum::Register).data(),"fonts/uifont35.fnt",m_theme,m_regImg,CCSizeMake(0,0),ccWHITE);
        m_regButton->setButtonIndex(RegButton);
        m_regButton->setClickCB(this,callfuncND_selector(LoginRegDialog::onButtonClicked));

        m_regBackButton = new BasButton;
        m_regBackButton->setCanTouch(true);
        m_regBackButton->setButtonInfo(lang->getStringById(StringEnum::Back).data(),"fonts/uifont35.fnt",m_theme,m_regBackImg,CCSizeMake(0,0),ccWHITE);
        m_regBackButton->setButtonIndex(RegBackButton);
        m_regBackButton->setClickCB(this,callfuncND_selector(LoginRegDialog::onButtonClicked));

        hlay->addWidget(m_regButton);
        hlay->addWidget(m_regBackButton);
        hlay->setAlignChildsSize(true);
        hlay->setAveraged(true);

        m_regWidget->setLayout(hlay);
        m_regWidget->setLeft("parent",uilib::Left);
        m_regWidget->setRight("parent",uilib::Right);
        m_regWidget->setBottom("parent",uilib::Bottom);
        m_regWidget->setMaxHeightRefSize("parent",0.2);
        m_regWidget->setBottomMargin(m_edgeSize);
        m_regWidget->setLeftMargin(m_edgeSize);
        m_regWidget->setRightMargin(m_edgeSize);

        //actions
        BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
        BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
        moveIn->setEaseType(uilib::EaseSineInOut);
        moveIn->setMoveInType(uilib::ScaleYIn);
        moveOut->setEaseType(uilib::EaseSineInOut);
        moveOut->setMoveOutType(uilib::ScaleYOut);
        moveOut->setActionTime(0.2);
        moveIn->setStartTime(0.2);
        m_loginWidget->setMoveinAction(moveIn);
        m_loginWidget->setMoveoutAction(moveOut);
        m_regWidget->setMoveinAction(moveIn);
        m_regWidget->setMoveoutAction(moveOut);
    }
    this->addChild(m_loginTitleWidget);
    this->addChild(m_regTitleWidget);
    this->addChild(m_loginWidget);
    this->addChild(m_regWidget);
    m_regWidget->setEnabled(false);
    m_regWidget->setVisible(false);
    m_regTitleWidget->setVisible(false);
    if(1){//content widget
        m_contentWidget = new BasWidget;
        m_contentWidget->setLeft("parent",uilib::Left);
        m_contentWidget->setRight("parent",uilib::Right);
        m_contentWidget->setLeftMargin(m_edgeSize);
        m_contentWidget->setRightMargin(m_edgeSize);
        m_contentWidget->setTopMargin(m_edgeSize / 4);
        m_contentWidget->setBottomMargin(m_edgeSize / 4);
        m_contentWidget->setTop(m_loginTitleWidget->getName(),uilib::Bottom);
        m_contentWidget->setBottom(m_loginWidget->getName(),uilib::Top);

        VerticalLayout *mainlay = new VerticalLayout;
        BasLabel *label1,*label2;
        label1 = new BasLabel;
        label1->setLabelInfo(lang->getStringById(StringEnum::Account).data(),"fonts/uifont35.fnt","default","",CCSizeMake(0,0),ccBLACK);
        label2 = new BasLabel;
        label2->setLabelInfo(lang->getStringById(StringEnum::Passwd).data(),"fonts/uifont35.fnt","default","",CCSizeMake(0,0),ccBLACK);

        m_accountBox = new InputBox;
        m_accountBox->setMaxLength(m_accountLimitLen);
        m_accountBox->setTheme("default","inputbg");
        m_accountBox->setText(m_account);
        m_accountBox->setMinHeightRefSize("parent",0.25);
        m_passwdBox = new InputBox;
        m_passwdBox->setMaxLength(m_passwdLimitLen);
        m_passwdBox->setTheme("default","inputbg");
        m_passwdBox->setText(m_passwd);
        m_passwdBox->setMinHeightRefSize("parent",0.25);
        m_passwdBox->setInputFlag(kEditBoxInputFlagPassword);

        mainlay->addWidget(label1);
        mainlay->addWidget(m_accountBox);
        mainlay->addWidget(label2);
        mainlay->addWidget(m_passwdBox);
        mainlay->setAlignChildsSize(false);
        mainlay->setAveraged(true);
        mainlay->setChildAlign(0,uilib::Left);
        mainlay->setChildAlign(2,uilib::Left);
        mainlay->setChildAlign(1,uilib::Left);
        mainlay->setChildAlign(1,uilib::Right);
        mainlay->setChildAlign(3,uilib::Left);
        mainlay->setChildAlign(3,uilib::Right);
        m_contentWidget->setLayout(mainlay);
    }
    this->addChild(m_contentWidget);
}
void LoginRegDialog::clear()
{
    m_accountLimitLen = 24;
    m_passwdLimitLen = 24;
    m_loginListener = 0;
    m_loginFunc = 0;
    m_cancelListener = 0;
    m_cancelFunc = 0;
    m_regListener = 0;
    m_regFunc = 0;
    m_accountBox = 0;
    m_passwdBox = 0;
    m_loginTitleWidget = 0;
    m_regTitleWidget = 0;
    m_contentWidget = 0;

    m_loginWidget = 0;
    m_regWidget = 0;
    m_loginButton = 0;
    m_loginCancelButton = 0;
    m_loginRegButton = 0;

    m_regButton = 0;
    m_regBackButton = 0;

    m_titleBg = "dialogtitle_a";
    m_loginImg = "buttonbg";
    m_cancelImg = "buttonbg_green";
    m_loginRegImg = "buttonbg_red";
    m_regImg = "buttonbg";
    m_regBackImg = "buttonbg_green";
}

}
