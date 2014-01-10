#include "kickoutdialog.h"
#include "gamecore/resource/resourcemgr.h"

KickOutDialog::KickOutDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_headPortrait = 0;
    m_okListener = 0;
    m_okFunc = 0;
    m_edgeSize = 10;
}
KickOutDialog::~KickOutDialog()
{

}
void KickOutDialog::setKickerInfo(const std::string &nick,std::string *head)
{
    m_kickId = nick;
    m_headPortrait = head;
}
void KickOutDialog::setOkCB(CCNode *node,SEL_CallFuncND func)
{
    m_okListener = node;
    m_okFunc = func;
}
void KickOutDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void KickOutDialog::finish()
{
    if(m_headPortrait != 0){
        CCImage *img = new CCImage;
        img->initWithImageData((void*)m_headPortrait->c_str(),m_headPortrait->size(),
                               CCImage::kFmtUnKnown);
        CCTexture2D *texture = new CCTexture2D;
        texture->initWithImage(img);
        delete img;
        CCSprite *sprite = CCSprite::create();
        sprite->initWithTexture(texture);
        FSizeCCNodeDelegate *headDele = new FSizeCCNodeDelegate(sprite);
        this->addChild(headDele);
        headDele->setHorizontal("parent",0.5);
        headDele->setVertical("parent",0.3);
    }else{
        BasLabel *name = new BasLabel;
        name->setLabelInfo(m_kickId,"","",CCSizeMake(0,0));
        this->addChild(name);
        name->setHorizontal("parent",0.5);
        name->setVertical("parent",0.3);
    }
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    BasLabel *content = new BasLabel;
    content->setLabelInfo(lang->getStringById(StringEnum::BeenKickOut),"","",CCSizeMake(0,0),getSystemFont(),25,ccWHITE);
    this->addChild(content);
    content->setCenterIn("parent");

    BasButton *button = new BasButton;
    button->setButtonInfo(lang->getStringById(StringEnum::Ok),"default","buttonbg",CCSizeMake(0,0),"",getSystemFont(),24,ccWHITE);
    button->setClickCB(m_okListener,m_okFunc);
    this->addChild(button);
    button->setHorizontal("parent",0.5);
    button->setBottomMargin(m_edgeSize);
    button->setBottom("parent",uilib::Bottom);
}
