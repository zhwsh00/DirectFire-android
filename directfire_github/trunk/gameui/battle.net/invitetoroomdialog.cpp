#include "invitetoroomdialog.h"

#include "utils/sysutils.h"

#include "gamecore/resource/resourcemgr.h"

InviteToRoomDialog::InviteToRoomDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_serverIFace = ServerInterface::getInstance();
}
InviteToRoomDialog::~InviteToRoomDialog()
{

}
void InviteToRoomDialog::exec()
{
    finish();
    this->schedule(schedule_selector(InviteToRoomDialog::counterDownFinish),5.0);
    BasShowDialog::exec();
}
void InviteToRoomDialog::setInviter(const std::string &id,const std::string &mail,const std::string &nick)
{
    m_inviterId = id;
    m_inviterMail = mail;
    m_inviterNick = nick;
}
void InviteToRoomDialog::onAcceptClickd(CCNode *node,void *data)
{
    m_serverIFace->acceptInvitedToGame(m_inviterId);
    destroy();
}
void InviteToRoomDialog::onRejectClicked(CCNode *node,void *data)
{
    destroy();
}
void InviteToRoomDialog::onClosedClicked(CCNode *node,void *data)
{
    destroy();
}
void InviteToRoomDialog::counterDownFinish(float dt)
{
    this->unschedule(schedule_selector(InviteToRoomDialog::counterDownFinish));
    destroy();
}
void InviteToRoomDialog::finish()
{
    std::string name = m_inviterNick;
    if(name.empty())
        mailToNickName(m_inviterMail,name);
    if(name.empty())
        name = m_inviterId;
    std::string *head;
    BasWidget *inviter;
    if(m_serverIFace->getHeadPortrait(m_inviterId,&head)){
        CCImage *img = new CCImage;
        img->initWithImageData((void*)head->c_str(),head->size(),
                               CCImage::kFmtUnKnown);
        CCTexture2D *texture = new CCTexture2D;
        texture->initWithImage(img);
        delete img;
        CCSprite *sprite = CCSprite::createWithTexture(texture);
        FSizeCCNodeDelegate *dele = new FSizeCCNodeDelegate(sprite);
        this->addChild(dele);
        dele->setHorizontal("parent",0.5);
        dele->setVertical("parent",0.3);
        inviter = dele;
    }else{
        BasLabel *label = new BasLabel;
        label->setLabelInfo(name,"","",CCSizeMake(0,0));
        this->addChild(label);
        label->setHorizontal("parent",0.5);
        label->setVertical("parent",0.3);
        inviter = label;
    }
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    BasLabel *content = new BasLabel;
    content->setLabelInfo(lang->getStringById(StringEnum::RoomInviteToRoomContent),"","",CCSizeMake(0,0),getSystemFont(),25,ccWHITE);
    this->addChild(content);
    content->setTop(inviter->getName(),uilib::Bottom);
    content->setTopMargin(10);
    content->setHorizontal("parent",0.5);

    BasButton *accept = new BasButton;
    accept->setButtonInfo(lang->getStringById(StringEnum::AcceptInvite).data(),"fonts/uifont24.fnt","default","buttonbg",CCSizeMake(0,0));
    accept->setClickCB(this,callfuncND_selector(InviteToRoomDialog::onAcceptClickd));
    this->addChild(accept);
    accept->setBottom("parent",uilib::Bottom);
    accept->setBottomMargin(10);
    accept->setHorizontal("parent",0.25);

    BasButton *reject = new BasButton;
    reject->setButtonInfo(lang->getStringById(StringEnum::RejectInvite).data(),"fonts/uifont24.fnt","default","buttonbg",CCSizeMake(0,0));
    reject->setClickCB(this,callfuncND_selector(InviteToRoomDialog::onRejectClicked));
    this->addChild(reject);
    reject->setBottom("parent",uilib::Bottom);
    reject->setBottomMargin(10);
    reject->setHorizontal("parent",0.75);

    setCloseCB(this,callfuncND_selector(InviteToRoomDialog::onClosedClicked));
}
