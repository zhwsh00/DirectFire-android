#include "delfrienddialog.h"

#include "resource/resourcemgr.h"

DelFriendDialog::DelFriendDialog(CCNode *parent,const ccColor4B &color)
    :   BasShowDialog(parent,color)
{
    m_okImg = "buttonbg";
    m_okListener = 0;
    m_okFunc = 0;
    m_edgeSize = 20;
}
DelFriendDialog::~DelFriendDialog()
{

}
void DelFriendDialog::setOkCB(CCNode *listener,SEL_CallFuncND func)
{
    m_okListener = listener;
    m_okFunc = func;
}
void DelFriendDialog::setOkImg(const std::string &normal,const std::string &pressed)
{
    m_okImg = normal;
    m_okPressedImg = pressed;
}
void DelFriendDialog::setDelInfo(const std::string &id,const std::string &name,const std::string &head)
{
    m_delId = id;
    m_delName = name;
    m_delHead = head;
}
void DelFriendDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void DelFriendDialog::finish()
{
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    BasButton *delButton = new BasButton;
    delButton->setButtonInfo(lang->getStringById(StringEnum::Delete).data(),"fonts/uifont24.fnt",m_theme,m_okImg,CCSizeMake(0,0));
    delButton->setClickCB(m_okListener,m_okFunc);
    this->addChild(delButton);
    delButton->setRight("parent",uilib::Right);
    delButton->setBottom("parent",uilib::Bottom);
    delButton->setRightMargin(m_edgeSize);
    delButton->setBottomMargin(m_edgeSize);

    BasWidget *headWidget;
    if(!m_delHead.empty()){
        CCImage *img = new CCImage;
        img->initWithImageData((void*)m_delHead.c_str(),m_delHead.size(),
                               CCImage::kFmtUnKnown);
        CCTexture2D *texture = new CCTexture2D;
        texture->initWithImage(img);
        delete img;
        CCSprite *sprite = CCSprite::create();
        sprite->initWithTexture(texture);
        headWidget = new BasNodeDelegateWidget(sprite);

        this->addChild(headWidget);
        headWidget->setHorizontal("parent",0.5);
        headWidget->setVertical("parent",0.4);
    }else{
        UiThemeDef *def = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
        std::string img;
        def->getNormalData()->getImg("portraitdefault",img);
        CCSprite *sprite = CCSprite::create();
        sprite->initWithSpriteFrameName(img.data());
        headWidget = new BasNodeDelegateWidget(sprite);

        this->addChild(headWidget);
        headWidget->setHorizontal("parent",0.5);
        headWidget->setVertical("parent",0.4);
    }
    BasLabel *label = new BasLabel;
    label->setLabelInfo(lang->getStringById(StringEnum::QueryDelFriend),"","",CCSizeMake(0,0),"",30,ccWHITE);
    label->setMaxWidthRefSize("parent",1.0);
    this->addChild(label);
    label->setHorizontal("parent",0.5);
    label->setTop(headWidget->getName(),uilib::Bottom);
}
