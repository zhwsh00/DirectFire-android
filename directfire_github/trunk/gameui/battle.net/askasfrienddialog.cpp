#include "askasfrienddialog.h"
#include "gamecore/resource/resourcemgr.h"

AskAsFriendDialog::AskAsFriendDialog(CCNode *parent,const ccColor4B &color)
    :   BasShowDialog(parent,color)
{
    m_okImg = "buttonbg";
    m_rejectImg = "buttonbg";
    m_okListener = 0;
    m_okFunc = 0;
    m_rejectListener = 0;
    m_rejectFunc = 0;
    m_edgeSize = 20;
}
AskAsFriendDialog::~AskAsFriendDialog()
{

}
void AskAsFriendDialog::setOkCB(CCNode *listener,SEL_CallFuncND func)
{
    m_okListener = listener;
    m_okFunc = func;
}
void AskAsFriendDialog::setRejectCB(CCNode *listener, SEL_CallFuncND func)
{
    m_rejectListener = listener;
    m_rejectFunc = func;
}
void AskAsFriendDialog::setOkImg(const std::string &normal,const std::string &pressed)
{
    m_okImg = normal;
    m_okPressedImg = pressed;
}
void AskAsFriendDialog::setRejectImg(const string &normal, const string &pressed)
{
    m_rejectImg = normal;
    m_rejectPressedImg = pressed;
}
void AskAsFriendDialog::setAskInfo(const std::string &id,const std::string &name,const std::string &word,const std::string &head)
{
    m_askId = id;
    m_askName = name;
    m_askHead = head;
    m_askWord = word;
}
void AskAsFriendDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void AskAsFriendDialog::finish()
{
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();

    BasButton *okButton = new BasButton;
    okButton->setButtonInfo(lang->getStringById(StringEnum::Ok).data(),"fonts/uifont24.fnt","default","buttonbg",
                            CCSizeMake(0,0));
    okButton->setClickCB(m_okListener,m_okFunc);

    this->addChild(okButton);
    okButton->setBottomMargin(m_edgeSize);
    okButton->setBottom("parent",uilib::Bottom);
    okButton->setHorizontal("parent",0.75);

    BasButton *rejectButton = new BasButton;
    rejectButton->setButtonInfo(lang->getStringById(StringEnum::Reject).data(),"fonts/uifont24.fnt","default","buttonbg",
                                CCSizeMake(0,0));
    rejectButton->setClickCB(m_rejectListener,m_rejectFunc);

    this->addChild(rejectButton);
    rejectButton->setBottomMargin(m_edgeSize);
    rejectButton->setBottom("parent",uilib::Bottom);
    rejectButton->setHorizontal("parent",0.25);
    BasWidget *headWidget;
    if(!m_askHead.empty()){
        CCImage *img = new CCImage;
        img->initWithImageData((void*)m_askHead.c_str(),m_askHead.size(),
                               CCImage::kFmtUnKnown);
        CCTexture2D *texture = new CCTexture2D;
        texture->initWithImage(img);
        delete img;
        CCSprite *sprite = CCSprite::create();
        sprite->initWithTexture(texture);
        headWidget = new BasNodeDelegateWidget(sprite);

        this->addChild(headWidget);
        headWidget->setHorizontal("parent",0.5);
        headWidget->setVertical("parent",0.3);
    }else{
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("headdefault.png");
        headWidget = new BasNodeDelegateWidget(sprite);

        this->addChild(headWidget);
        headWidget->setHorizontal("parent",0.5);
        headWidget->setVertical("parent",0.3);
    }
    m_askWord.insert(0,"    ");
    TextScrollArea *area = new TextScrollArea;
    area->setTheme("","");
    area->setTextInfo(m_askWord,getSystemFont(),40,ccWHITE);
    this->addChild(area);
    area->setLeft("parent",uilib::Left);
    area->setRight("parent",uilib::Right);
    area->setLeftMargin(10);
    area->setRightMargin(10);
    area->setTop(headWidget->getName(),uilib::Bottom);
    area->setBottom(rejectButton->getName(),uilib::Top);
}
