#include "headsettingdialog.h"

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"
#include "utils/sysutils.h"
#include "utils/fileutils.h"
#include "ccimagecliper.h"

HeadSettingDialog::HeadSettingDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_serverInf = ServerInterface::getInstance();
    m_accountInf = m_serverInf->getLoginAccountInfo();
    m_headSprite = CCSprite::create();
    m_headPortrait = "portraitdefault";
    m_resetImg = "buttonbg";
    m_resetButton = 0;
    m_loadingDialog = 0;
    m_submitPortraitListener = 0;
    m_submitPortraitFunc = 0;
    PhotoHelper::getInstance()->registerListener(this);
    m_serverInf->setHeadSettingCB(this,callfuncND_selector(HeadSettingDialog::onSubmitSuc),callfuncND_selector(HeadSettingDialog::onSubmitFailed));
    m_editAble = false;
}
HeadSettingDialog::~HeadSettingDialog()
{
    PhotoHelper::getInstance()->unRegisterListener(this);
}
void HeadSettingDialog::takePhotoFinished(const char* imageData, int len, const char* imageDataHq, int lenHq)
{
    m_headPortrait.assign(imageDataHq, lenHq);
    portraitUpdated(m_headPortrait);
    if(m_submitPortraitListener && m_submitPortraitFunc) {
        (m_submitPortraitListener->*m_submitPortraitFunc)(this,&m_headPortrait);
    }
}
void HeadSettingDialog::takePhotoFinished(const char* imageFile)
{
    if(imageFile == 0)
        return;
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    CCImageCliper *cliper = new CCImageCliper(imageFile,this,root,ccc4(0,0,0,128));
    cliper->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
    cliper->exec();
}
void HeadSettingDialog::takePhotoFailed()
{
}
void HeadSettingDialog::takePhotoCanceled()
{

}
void HeadSettingDialog::setHeadSprite(CCSprite *headSprite)
{
    m_headSprite->initWithTexture(headSprite->getTexture());
}
void HeadSettingDialog::setEditAble(bool editAble)
{
    m_editAble = editAble;
}
void HeadSettingDialog::setSubmitPortraitCB(CCNode *listener,SEL_CallFuncND func)
{
    m_submitPortraitListener = listener;
    m_submitPortraitFunc = func;
}
void HeadSettingDialog::portraitUpdated(const std::string& imgData)
{
    float width = 220;
    float height = 220;
    CCImage *img = new CCImage;
    img->initWithImageData((void*)imgData.data(),imgData.size(),
                           CCImage::kFmtUnKnown);
    CCTexture2D *texture = new CCTexture2D;
    texture->initWithImage(img);
    m_headSprite->initWithTexture(texture);
    CCSize csize = m_headSprite->getContentSize();
    m_headSprite->setScaleX(width / csize.width);
    m_headSprite->setScaleY(height / csize.height);
    delete img;
    
    CCFadeIn *fade = CCFadeIn::create(0.5);
    m_headSprite->runAction(fade);
}
void HeadSettingDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void HeadSettingDialog::finish()
{
    // dialog
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    setHeight(size.height * 0.9);
    
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    // base area
    m_baseArea = new BasWidget;
    this->addChild(m_baseArea);
    m_baseArea->setFill("parent");
    BasWidget *portraitArea = new BasWidget;
    m_baseArea->addChild(portraitArea);
    portraitArea->setHeight(getHeight() / 4.0);
    portraitArea->setWidth(getWidth() - (m_edgeSize * 2));
    BasWidget *accountArea = new BasWidget;
    m_baseArea->addChild(accountArea);
    accountArea->setHeight(getHeight() / 2.0);
    accountArea->setWidth(getWidth() - (m_edgeSize * 2));
    BasWidget *accountAreaLeft = new BasWidget;
    BasWidget *accountAreaRight = new BasWidget;
    accountAreaLeft->setTop("parent", uilib::Top);
    accountAreaLeft->setBottom("parent", uilib::Bottom);
    accountAreaLeft->setLeft("parent", uilib::Left);
    accountAreaLeft->setMaxWidthRefSize("parent", 0.3);
    accountAreaLeft->setMinWidthRefSize("parent", 0.3);
    accountAreaRight->setTop("parent", uilib::Top);
    accountAreaRight->setBottom("parent", uilib::Bottom);
    accountAreaRight->setLeft(accountAreaLeft->getName(), uilib::Right);
    accountAreaRight->setLeftMargin(m_edgeSize);
    accountAreaRight->setRight("parent", uilib::Right);
    accountAreaRight->setRightMargin(m_edgeSize * 2);
    accountArea->addChild(accountAreaLeft);
    accountArea->addChild(accountAreaRight);
    
    BasWidget *bottomArea = new BasWidget;
    m_baseArea->addChild(bottomArea);
    bottomArea->setHeight(getHeight() / 6.0);
    bottomArea->setWidth(getWidth() - (m_edgeSize * 2));
    
    // portrait area
    portraitArea->setTop("parent",uilib::Top);
    portraitArea->setTopMargin(m_edgeSize * 10.0);
    portraitArea->setHorizontal("parent",0.5);
    BasWidget *portraitLeftArea = new BasWidget;
    BasWidget *portraitRightArea = new BasWidget;
    portraitLeftArea->setLeft("parent", uilib::Left);
    portraitLeftArea->setTop("parent", uilib::Top);
    portraitLeftArea->setBottom("parent", uilib::Bottom);
    portraitLeftArea->setMaxWidthRefSize("parent", 0.6);
    portraitLeftArea->setMinWidthRefSize("parent", 0.6);
    portraitRightArea->setLeft(portraitLeftArea->getName(), uilib::Right);
    portraitRightArea->setLeftMargin(m_edgeSize);
    portraitRightArea->setTop("parent", uilib::Top);
    portraitRightArea->setBottom("parent", uilib::Bottom);
    portraitRightArea->setRight("parent", uilib::Right);
    portraitArea->addChild(portraitLeftArea);
    portraitArea->addChild(portraitRightArea);
    
    // portrait sub area
    m_headDelegate = new BasNodeDelegateWidget(m_headSprite);
    portraitLeftArea->addChild(m_headDelegate);
    m_headDelegate->setVertical("parent",0.5);
    m_headDelegate->setHorizontal("parent",0.5);
    // upload button layout
    BasButton* uploadButton = new BasButton;
    uploadButton->setWidth(150.0f);
    // logout button layout
    BasButton* logoutButton = new BasButton;
    logoutButton->setWidth(150.0f);
    //exit button
    BasButton *exitButton = new BasButton;
    exitButton->setWidth(150.0f);

    VerticalLayout *vlayPortrait = new VerticalLayout;
    vlayPortrait->addWidget(exitButton);
    vlayPortrait->addWidget(logoutButton);
    vlayPortrait->addWidget(uploadButton);
    vlayPortrait->setAveraged(true);
    vlayPortrait->setChildAlign(0,uilib::Left);
    vlayPortrait->setChildAlign(1,uilib::Left);
    vlayPortrait->setChildAlign(2,uilib::Left);
    portraitRightArea->setLayout(vlayPortrait);
    // portrait
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    if(!m_headSprite->getTexture()) {
        std::string headimg;
        uiDef->getNormalData()->getImg(m_headPortrait,headimg);
        m_headSprite->initWithSpriteFrameName(headimg.data());
    }
    // upload button
    uploadButton->setButtonInfo(lang->getStringById(StringEnum::Upload),m_theme,m_resetImg,CCSizeMake(0,0),m_resetPressedImg,getSystemFont(),24,ccWHITE);
    uploadButton->setClickCB(this,callfuncND_selector(HeadSettingDialog::onUploadClicked));
    // logout button
    logoutButton->setButtonInfo(lang->getStringById(StringEnum::Logout),m_theme,m_resetImg,CCSizeMake(0,0),m_resetPressedImg,getSystemFont(),24,ccWHITE);
    logoutButton->setClickCB(this,callfuncND_selector(HeadSettingDialog::onLogOutClicked));
    //exit button
    exitButton->setButtonInfo(lang->getStringById(StringEnum::QuitGame),m_theme,m_resetImg,CCSizeMake(0,0),m_resetPressedImg,getSystemFont(),24,ccWHITE);
    exitButton->setClickCB(this,callfuncND_selector(HeadSettingDialog::onExitGameClicked));

    // account info area
    accountArea->setBottom(bottomArea->getName(),uilib::Top);
    accountArea->setBottomMargin(m_edgeSize * 2.0);
    accountArea->setHorizontal("parent",0.5);

    // id
    BasLabel *idLbl = new BasLabel;
    idLbl->setLabelInfo(lang->getStringById(StringEnum::ID),"","",CCSizeMake(0,0),getSystemFont(),24);
    BasLabel *idLbl2 = new BasLabel;
    idLbl2->setLabelInfo(m_accountInf->m_id,"","",CCSizeMake(0,0),getSystemFont(),24);
    // account
    BasLabel *accountLbl = new BasLabel;
    accountLbl->setLabelInfo(lang->getStringById(StringEnum::Mail),"","",CCSizeMake(0,0),getSystemFont(),24);
    m_accountInput = new InputBox;
    m_accountInput->setMaxLength(24);
    m_accountInput->setTheme("default","inputbg");
    m_accountInput->setText(m_accountInf->m_mail);
    m_accountInput->setHeight(60);
    // password 
    BasLabel *pwdLbl = new BasLabel;
    pwdLbl->setLabelInfo(lang->getStringById(StringEnum::Password),"","",CCSizeMake(0,0),getSystemFont(),24);
    m_pwdInput = new InputBox;
    m_pwdInput->setMaxLength(24);
    m_pwdInput->setTheme("default","inputbg");
    m_pwdInput->setText(m_accountInf->m_password);
    m_pwdInput->setInputFlag(kEditBoxInputFlagPassword);
    m_pwdInput->setHeight(60);
    // password confirm
    BasLabel *pwdConfirmLbl = new BasLabel;
    pwdConfirmLbl->setLabelInfo(lang->getStringById(StringEnum::PasswordConfirm),"","",CCSizeMake(0,0),getSystemFont(),24);
    m_pwdConfirmInput = new InputBox;
    m_pwdConfirmInput->setMaxLength(24);
    m_pwdConfirmInput->setTheme("default","inputbg");
    m_pwdConfirmInput->setText(m_accountInf->m_password);
    m_pwdConfirmInput->setInputFlag(kEditBoxInputFlagPassword);
    m_pwdConfirmInput->setHeight(60);
    // nick name
    BasLabel *nickNameLbl = new BasLabel;
    nickNameLbl->setLabelInfo(lang->getStringById(StringEnum::NickName),"","",CCSizeMake(0,0),getSystemFont(),24);
    m_nickNameInput = new InputBox;
    m_nickNameInput->setMaxLength(14);
    m_nickNameInput->setTheme("default","inputbg");
    m_nickNameInput->setText(m_accountInf->m_name);
    m_nickNameInput->setHeight(60);
    if(m_accountInf->m_name.empty()){
        //show the nick name no exist warnning
        BasLabel *nickNameSet = new BasLabel;
        nickNameSet->setLabelInfo(lang->getStringById(StringEnum::SetYourNickName),"","",CCSizeMake(0,0),getSystemFont(),24,ccWHITE);
        this->addChild(nickNameSet);
        nickNameSet->setHorizontal("parent",0.5);
        nickNameSet->setTop("parent",uilib::Top);
        nickNameSet->setTopMargin(10);
    }
    // sex
    BasLabel *sexLbl = new BasLabel;
    sexLbl->setLabelInfo(lang->getStringById(StringEnum::Sex),"","",CCSizeMake(0,0),getSystemFont(),24);
    BasWidget *sexRadioArea = new BasWidget;
    sexRadioArea->setWidth(accountAreaRight->getWidth());
    // female radio button
    m_femaleButton = new CheckBox;
    m_maleButton = new CheckBox;
    sexRadioArea->addChild(m_maleButton);
    sexRadioArea->addChild(m_femaleButton);
    m_maleButton->setTop("parent", uilib::Top);
    m_maleButton->setBottom("parent", uilib::Bottom);
    m_maleButton->setLeft("parent", uilib::Left);
    m_maleButton->setMaxWidthRefSize("parent", 0.5);
    m_maleButton->setMinWidthRefSize("parent", 0.5);
    m_maleButton->setClickCB(this,callfuncND_selector(HeadSettingDialog::onMaleClicked));
    m_maleButton->setCheckInfo(lang->getStringById(StringEnum::Male).data(),"fonts/uifont24.fnt","default","",CCSizeMake(60,60));
    m_femaleButton->setTop("parent", uilib::Top);
    m_femaleButton->setBottom("parent", uilib::Bottom);
    m_femaleButton->setLeft(m_maleButton->getName(), uilib::Right);
    m_femaleButton->setLeftMargin(m_edgeSize);
    m_femaleButton->setRight("parent", uilib::Right);
    m_femaleButton->setRightMargin(m_edgeSize * 2);
    m_femaleButton->setClickCB(this,callfuncND_selector(HeadSettingDialog::onFemaleClicked));
    m_femaleButton->setCheckInfo(lang->getStringById(StringEnum::Female).data(),"fonts/uifont24.fnt","default","",CCSizeMake(60,60));

    if (m_accountInf->m_sex == 0) {
        m_femaleButton->setCheck(true);
        m_maleButton->setCheck(false);
    } else {
        m_femaleButton->setCheck(false);
        m_maleButton->setCheck(true);
    }

    // account area layout
    VerticalLayout *vlayAccountLeft = new VerticalLayout;
    vlayAccountLeft->addWidget(idLbl);
    vlayAccountLeft->addWidget(accountLbl);
    vlayAccountLeft->addWidget(pwdLbl);
    vlayAccountLeft->addWidget(pwdConfirmLbl);
    vlayAccountLeft->addWidget(nickNameLbl);
    vlayAccountLeft->addWidget(sexLbl);
    vlayAccountLeft->setAveraged(true);
    vlayAccountLeft->setChildAlign(0,uilib::Left);
    vlayAccountLeft->setChildAlign(1,uilib::Left);
    vlayAccountLeft->setChildAlign(2,uilib::Left);
    vlayAccountLeft->setChildAlign(3,uilib::Left);
    vlayAccountLeft->setChildAlign(4,uilib::Left);
    vlayAccountLeft->setChildAlign(5,uilib::Left);
    vlayAccountLeft->setLeftMargin(40);
    accountAreaLeft->setLayout(vlayAccountLeft);
    
    VerticalLayout *vlayAccountRight = new VerticalLayout;
    vlayAccountRight->addWidget(idLbl2);
    vlayAccountRight->addWidget(m_accountInput);
    vlayAccountRight->addWidget(m_pwdInput);
    vlayAccountRight->addWidget(m_pwdConfirmInput);
    vlayAccountRight->addWidget(m_nickNameInput);
    vlayAccountRight->addWidget(sexRadioArea);
    vlayAccountRight->setAveraged(true);
    vlayAccountRight->setChildAlign(0,uilib::Left);
    vlayAccountRight->setChildAlign(1,uilib::Left);
    vlayAccountRight->setChildAlign(2,uilib::Left);
    vlayAccountRight->setChildAlign(3,uilib::Left);
    vlayAccountRight->setChildAlign(4,uilib::Left);
    vlayAccountRight->setChildAlign(5,uilib::Left);
    vlayAccountRight->setChildAlign(1,uilib::Right);
    vlayAccountRight->setChildAlign(2,uilib::Right);
    vlayAccountRight->setChildAlign(3,uilib::Right);
    vlayAccountRight->setChildAlign(4,uilib::Right);
    vlayAccountRight->setChildAlign(5,uilib::Right);
    accountAreaRight->setLayout(vlayAccountRight);
    
    // button area
    bottomArea->setBottom("parent",uilib::Bottom);
    bottomArea->setBottomMargin(m_edgeSize * 2.0);
    bottomArea->setHorizontal("parent",0.5);
    // reset button
    m_resetButton = new BasButton;
    m_resetButton->setButtonInfo(lang->getStringById(StringEnum::Reset),m_theme,m_resetImg,CCSizeMake(0,0),m_resetPressedImg,getSystemFont(),24,ccWHITE);
    bottomArea->addChild(m_resetButton);
    m_resetButton->setVertical("parent",0.5);
    m_resetButton->setHorizontal("parent",0.5);
    m_resetButton->setClickCB(this,callfuncND_selector(HeadSettingDialog::onResetClicked));
    // submit button
    m_submitButton = new BasButton;
    m_submitButton->setButtonInfo(lang->getStringById(StringEnum::Submit),m_theme,m_resetImg,CCSizeMake(0,0),m_resetPressedImg,getSystemFont(),24,ccWHITE);
    bottomArea->addChild(m_submitButton);
    m_submitButton->setVertical("parent",0.5);
    m_submitButton->setHorizontal("parent",0.5);
    m_submitButton->setClickCB(this,callfuncND_selector(HeadSettingDialog::onSubmitClicked));
    editEnabled(m_editAble);
}
void HeadSettingDialog::setResetImg(const std::string &normal,const std::string &pressed)
{
    m_resetImg = normal;
    m_resetPressedImg = pressed;
}
void HeadSettingDialog::onUploadClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY){
        std::string text;
        text.append("Upload portrait no supported in bb10 now!");
        new SplashMessageWidget(this,text);
        return;
    }else if(CC_TARGET_PLATFORM == CC_PLATFORM_LINUX){
        takePhotoFinished("/home/water/work/cocos2d-2.1beta3-x-2.1.0/directfire/trunk/Resources/ss0.jpg");
        return;
    }
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    PhotoHelper::getInstance()->setLangCancel(lang->getStringById(StringEnum::Cancel));
    PhotoHelper::getInstance()->setLangChooseImage(lang->getStringById(StringEnum::ChooseImage));
    PhotoHelper::getInstance()->setLangTakePhoto(lang->getStringById(StringEnum::TakePhoto));
    PhotoHelper::getInstance()->takePhoto();
}
void HeadSettingDialog::onLogOutClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_serverInf->disconnectGameServer();
}
void HeadSettingDialog::onExitGameClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_serverInf->disconnectGameServer();
    ResourceMgr::getInstance()->getUserDataMgr()->getInstance()->flush();
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void HeadSettingDialog::onResetClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    editEnabled(true);
}
void HeadSettingDialog::editEnabled(bool enable)
{
    if (enable) {
        m_resetButton->setVisible(false);
        m_submitButton->setVisible(true);
        showEditAbleInputBox();
        m_femaleButton->setEnabled(true);
        m_maleButton->setEnabled(true);
    } else {
        m_resetButton->setVisible(true);
        m_submitButton->setVisible(false);
        showDisableInputBox();
        m_femaleButton->setEnabled(false);
        m_maleButton->setEnabled(false);
    }
}
void HeadSettingDialog::onSubmitClicked(CCNode *sender,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(!sendFormData())
        return;
}
bool HeadSettingDialog::sendFormData()
{
    m_resetButton->setVisible(true);
    m_submitButton->setVisible(false);
    // hidden the inputbox prevent on top of loading dialog
    hiddenInputBox();
    m_femaleButton->setEnabled(false);
    m_maleButton->setEnabled(false);
    
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    string mail = m_accountInput->getText();
    string password = m_pwdInput->getText();
    string passwordConfirm = m_pwdConfirmInput->getText();
    string nickName = m_nickNameInput->getText();
    short sex = 0;
    if(m_femaleButton->isCheck())
        sex = 0;
    else
        sex = 1;
    
    // nothing changed
    if ((mail.compare(m_accountInf->m_mail) == 0 && !mail.empty())
        && (password.compare(m_accountInf->m_password) == 0 && !password.empty())
        && (passwordConfirm.compare(m_accountInf->m_password) == 0 && !passwordConfirm.empty())
        && (nickName.compare(m_accountInf->m_name) == 0 && !nickName.empty())
        && (sex == m_accountInf->m_sex)) {
        showDisableInputBox();
        return true;
    }
    
    // verify account
    if (mail.empty()) {
        SplashMessageWidget *splash = new SplashMessageWidget(this,lang->getStringById(StringEnum::AccountEmptyError));
        splash->setFinishedCB(this,callfuncN_selector(HeadSettingDialog::onFailedSplashFinished));
        return false;
    }
    if (!isMailAddress(mail)) {
        SplashMessageWidget *splash = new SplashMessageWidget(this,lang->getStringById(StringEnum::AccountNotMailError));
        splash->setFinishedCB(this,callfuncN_selector(HeadSettingDialog::onFailedSplashFinished));
        return false;
    }
    // verify password
    if (password.empty() || passwordConfirm.empty()) {
        SplashMessageWidget *splash = new SplashMessageWidget(this,lang->getStringById(StringEnum::PasswordEmptyError));
        splash->setFinishedCB(this,callfuncN_selector(HeadSettingDialog::onFailedSplashFinished));
        return false;
    }
    if (password.size() < 4) {
        SplashMessageWidget *splash = new SplashMessageWidget(this,lang->getStringById(StringEnum::PasswordLenError));
        splash->setFinishedCB(this,callfuncN_selector(HeadSettingDialog::onFailedSplashFinished));
        return false;
    }
    if (password.compare(passwordConfirm) != 0) {
        SplashMessageWidget *splash = new SplashMessageWidget(this,lang->getStringById(StringEnum::PasswordConfirmError));
        splash->setFinishedCB(this,callfuncN_selector(HeadSettingDialog::onFailedSplashFinished));
        return false;
    }
    if (nickName.empty()) {
        SplashMessageWidget *splash = new SplashMessageWidget(this,lang->getStringById(StringEnum::NickNameEmptyError));
        splash->setFinishedCB(this,callfuncN_selector(HeadSettingDialog::onFailedSplashFinished));
        return false;
    }
    if (hasSpecialChar(mail) || hasSpecialChar(password) || hasSpecialChar(nickName)) {
        SplashMessageWidget *splash = new SplashMessageWidget(this,lang->getStringById(StringEnum::SpecialCharactersError));
        splash->setFinishedCB(this,callfuncN_selector(HeadSettingDialog::onFailedSplashFinished));
        return false;
    }
    if(m_loadingDialog == 0){
        m_loadingDialog = new BusyDialog();
        m_loadingDialog->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
        CCNode *root = this->getParent();
        while (root->getParent()) {
            root = root->getParent();
        }
        root->addChild(m_loadingDialog, 11000);
        m_loadingDialog->setBusyText(lang->getStringById(StringEnum::Loading));
        m_loadingDialog->setAnimationName("uiloadinga");
    }
    m_loadingDialog->setLoadFinishedCB(this,callfuncN_selector(HeadSettingDialog::onSubmitStart));
    m_loadingDialog->exec();
    return true;
}
void HeadSettingDialog::onSubmitStart()
{
    string mail = m_accountInput->getText();
    string password = m_pwdInput->getText();
    string passwordConfirm = m_pwdConfirmInput->getText();
    string nickName = m_nickNameInput->getText();
    short sex = 0;
    if(m_femaleButton->isCheck())
        sex = 0;
    else
        sex = 1;
    // send change
    m_serverInf->resetUserInfo(mail, password, nickName, sex);
}
void HeadSettingDialog::onSubmitSuc(CCNode *sender,void *data)
{
    if(m_loadingDialog != 0){
        m_loadingDialog->destory();
        m_loadingDialog = 0;
    }
    showDisableInputBox();
}
void HeadSettingDialog::onSubmitFailed(CCNode *sender,void *data)
{
    int no = *(int*)data;
    if(m_loadingDialog != 0){
        m_loadingDialog->destory();
        m_loadingDialog = 0;
    }
    LangDef *lang = ResourceMgr::getInstance()->getNetLangDef();
    SplashMessageWidget *splash = new SplashMessageWidget(this,lang->getStringById(no));
    splash->setFinishedCB(this,callfuncN_selector(HeadSettingDialog::onFailedSplashFinished));
}
void HeadSettingDialog::onFailedSplashFinished(CCNode *sender)
{
    m_resetButton->setVisible(false);
    m_submitButton->setVisible(true);
    showEditAbleInputBox();
    m_femaleButton->setEnabled((true));
    m_maleButton->setEnabled((true));
}
void HeadSettingDialog::onFemaleClicked(CCNode *sender,void *data)
{
    if(!m_femaleButton->isEnabled())
        return;
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_femaleButton->setCheck(true);
    m_maleButton->setCheck(false);
}
void HeadSettingDialog::onMaleClicked(CCNode *sender,void *data)
{
    if(!m_maleButton->isEnabled())
        return;
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_femaleButton->setCheck(false);
    m_maleButton->setCheck(true);
}
void HeadSettingDialog::hiddenInputBox()
{
    m_accountInput->setVisible(false);
    m_pwdInput->setVisible(false);
    m_pwdConfirmInput->setVisible(false);
    m_nickNameInput->setVisible(false);
}
void HeadSettingDialog::showEditAbleInputBox()
{
    // show inputbox and enable edit
    m_accountInput->setVisible(true);
    m_pwdInput->setVisible(true);
    m_pwdConfirmInput->setVisible(true);
    m_nickNameInput->setVisible(true);
    
    if (m_accountInf->m_mail.empty()) {
        m_accountInput->setEnabled(true);
    } else {
        m_accountInput->setEnabled(false);
    }
    m_pwdInput->setEnabled(true);
    m_pwdConfirmInput->setEnabled(true);
    m_nickNameInput->setEnabled(true);
}
void HeadSettingDialog::showDisableInputBox()
{
    // show inputbox and disable edit
    m_accountInput->setVisible(true);
    m_pwdInput->setVisible(true);
    m_pwdConfirmInput->setVisible(true);
    m_nickNameInput->setVisible(true);
    
    m_accountInput->setEnabled(false);
    m_pwdInput->setEnabled(false);
    m_pwdConfirmInput->setEnabled(false);
    m_nickNameInput->setEnabled(false);
}
