#include "sendmsgdialog.h"

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"

SendMsgDialog::SendMsgDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_titleInput = 0;
    m_msgInput = 0;
    m_sendListener = 0;
    m_sendFunc = 0;
    m_initPage = true;
    m_canReply = false;
    m_sendPage = 0;
    m_showPage = 0;
    m_sendImg = "buttonbg";
    m_backImg = "buttonbg";
    m_replyImg = "buttonbg";

    m_needSendPage = true;
    m_needShowPage = false;
    m_edgeSize = 20;
}
SendMsgDialog::~SendMsgDialog()
{

}
void SendMsgDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void SendMsgDialog::setInitPage(bool send,bool show)
{
    m_needSendPage = send;
    m_needShowPage = show;
}
void SendMsgDialog::setInitShowPage(bool send)
{
    m_initPage = send;
}
void SendMsgDialog::finish()
{
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    if(m_needSendPage){
        //send page
        m_sendPage = new BasWidget;
        this->addChild(m_sendPage);
        m_sendPage->setFill("parent");
        BasWidget *sendBottom = new BasWidget;
        m_sendPage->addChild(sendBottom);
        sendBottom->setLeft("parent",uilib::Left);
        sendBottom->setRight("parent",uilib::Right);
        sendBottom->setBottom("parent",uilib::Bottom);
        sendBottom->setHeight(90);
        sendBottom->setLeftMargin(m_edgeSize);
        sendBottom->setRightMargin(m_edgeSize);
        sendBottom->setBottomMargin(m_edgeSize);

        BasButton *sendButton = new BasButton;
        sendButton->setButtonInfo(lang->getStringById(StringEnum::Send).data(),"fonts/uifont24.fnt",m_theme,m_sendImg,CCSizeMake(0,0));
        sendBottom->addChild(sendButton);
        sendButton->setBottom("parent",uilib::Bottom);
        sendButton->setRight("parent",uilib::Right);
        sendButton->setClickCB(m_sendListener,m_sendFunc);

        CCSize spsize;
        spsize.width = 120;
        spsize.height = 80;
        //head
        if(!m_recHead.empty()){
            CCImage *img = new CCImage;
            img->initWithImageData((void*)m_recHead.c_str(),m_recHead.size(),
                                   CCImage::kFmtUnKnown);
            CCTexture2D *texture = new CCTexture2D;
            texture->initWithImage(img);
            delete img;
            CCSprite *sprite = CCSprite::create();
            sprite->initWithTexture(texture);
            CCSize psize = sprite->getContentSize();
            if(psize.height > spsize.height){
                psize.height = spsize.height;
                psize.width = psize.height;
            }
            BasNodeDelegateWidget *headWidget = new BasNodeDelegateWidget(sprite,psize);

            sendBottom->addChild(headWidget);
            headWidget->setLeft("parent",uilib::Left);
            headWidget->setVertical(sendButton->getName(),0.5);
        }else{
            BasLabel *label = new BasLabel;
            label->setLabelInfo(m_recName,"","",CCSizeMake(0,0),getSystemFont(),30,ccWHITE);
            sendBottom->addChild(label);
            label->setVertical(sendButton->getName(),0.5);
            label->setLeft("parent",uilib::Left);
            label->setMaxHeightRefSize(sendButton->getName(),1.0);
            label->setMaxWidthRefSize(sendButton->getName(),1.0);
        }
        BasWidget *inputWidget = new BasWidget;
        m_sendPage->addChild(inputWidget);
        inputWidget->setTop("parent",uilib::Top);
        inputWidget->setLeft("parent",uilib::Left);
        inputWidget->setRight("parent",uilib::Right);
        inputWidget->setLeftMargin(m_edgeSize);
        inputWidget->setRightMargin(m_edgeSize);
        inputWidget->setTopMargin(m_edgeSize);
        inputWidget->setBottom(sendBottom->getName(),uilib::Top);

        VerticalLayout *vlay = new VerticalLayout;
        BasLabel *label1 = new BasLabel;
        label1->setLabelInfo(lang->getStringById(StringEnum::Title).data(),"fonts/uifont30.fnt","","",CCSizeMake(0,0));
        BasLabel *label2 =  new BasLabel;
        label2->setLabelInfo(lang->getStringById(StringEnum::MsgWord).data(),"fonts/uifont30.fnt","","",CCSizeMake(0,0));

        m_titleInput = new InputBox;
        m_titleInput->setHeight(80);
        m_titleInput->setTheme("default","inputbg");
        m_titleInput->setMaxLength(24);
        m_msgInput = new InputBox;
        m_msgInput->setHeight(80);
        m_msgInput->setTheme("default","inputbg");
        m_msgInput->setMaxLength(240);

        vlay->addWidget(label1);
        vlay->addWidget(m_titleInput);
        vlay->addWidget(label2);
        vlay->addWidget(m_msgInput);
        vlay->setAlignChildsSize(false);
        vlay->setAveraged(true);
        vlay->setChildAlign(0,uilib::Left);
        vlay->setChildAlign(2,uilib::Left);
        vlay->setChildAlign(1,uilib::Left);
        vlay->setChildAlign(1,uilib::Right);
        vlay->setChildAlign(3,uilib::Left);
        vlay->setChildAlign(3,uilib::Right);

        inputWidget->setLayout(vlay);
    }
    if(m_needShowPage){
        //show msg page
        m_showPage = new BasWidget;
        this->addChild(m_showPage);
        m_showPage->setFill("parent");

        BasWidget *replyBottom = new BasWidget;
        m_showPage->addChild(replyBottom);
        replyBottom->setLeft("parent",uilib::Left);
        replyBottom->setRight("parent",uilib::Right);
        replyBottom->setBottom("parent",uilib::Bottom);
        replyBottom->setLeftMargin(m_edgeSize);
        replyBottom->setBottomMargin(m_edgeSize);
        replyBottom->setRightMargin(m_edgeSize);
        replyBottom->setHeight(100);
        BasButton *replyButton = 0;
        CCSize spsize;
        if(m_canReply){
            replyButton = new BasButton;
            replyButton->setButtonInfo(lang->getStringById(StringEnum::Reply).data(),"fonts/uifont24.fnt",m_theme,m_sendImg,CCSizeMake(0,0));
            replyBottom->addChild(replyButton);
            replyButton->setBottom("parent",uilib::Bottom);
            replyButton->getPreferedSize(spsize);
            replyButton->setRight("parent",uilib::Right);
            replyButton->setClickCB(this,callfuncND_selector(SendMsgDialog::onReplyClicked));
        }else{
            spsize = CCSizeMake(76,76);
        }

        //head
        if(!m_senderHead.empty()){
            CCImage *img = new CCImage;
            img->initWithImageData((void*)m_senderHead.c_str(),m_senderHead.size(),
                                   CCImage::kFmtUnKnown);
            CCTexture2D *texture = new CCTexture2D;
            texture->initWithImage(img);
            delete img;
            CCSprite *sprite = CCSprite::create();
            sprite->initWithTexture(texture);
            CCSize psize = sprite->getContentSize();
            if(psize.height > spsize.height){
                psize.height = spsize.height;
                psize.width = psize.height;
            }
            BasNodeDelegateWidget *headWidget = new BasNodeDelegateWidget(sprite,psize);

            replyBottom->addChild(headWidget);
            headWidget->setLeft("parent",uilib::Left);
            headWidget->setVertical("parent",0.5);
        }else{
            BasLabel *label = new BasLabel;
            label->setLabelInfo(m_recName,"","",CCSizeMake(0,0),getSystemFont(),30,ccWHITE);
            replyBottom->addChild(label);
            label->setVertical("parent",0.5);
            label->setLeft("parent",uilib::Left);
            if(replyButton){
                label->setMaxHeightRefSize(replyButton->getName(),1.0);
                label->setMaxWidthRefSize(replyButton->getName(),1.0);
            }else{
                label->setMaximumSize(spsize);
            }
        }

        BasLabel *title = new BasLabel;
        title->setLabelInfo(m_msgTitle,"","",CCSizeMake(0,0),getSystemFont(),32,ccBLACK);

        TextScrollArea *msg = new TextScrollArea;
        msg->setTheme(m_theme,"");
        m_msgWord.insert(0," ");
        msg->setTextInfo(m_msgWord,getSystemFont(),30,ccWHITE);

        m_showPage->addChild(title);
        m_showPage->addChild(msg);

        title->setTop("parent",uilib::Top);
        title->setTopMargin(m_edgeSize);
        title->setHorizontal("parent",0.5);

        msg->setLeft("parent",uilib::Left);
        msg->setRight("parent",uilib::Right);
        msg->setTop(title->getName(),uilib::Bottom);
        msg->setBottom(replyBottom->getName(),uilib::Top);

        title->setTopMargin(m_edgeSize);
        msg->setMargins(m_edgeSize);
    }
    if(m_initPage){
        if(m_showPage)
            m_showPage->setVisible(false);
    }else{
        if(m_sendPage)
            m_sendPage->setVisible(false);
    }
}
void SendMsgDialog::onReplyClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    //switch to send page,can not change back
    if(m_showPage->getMoveinAction() == 0){
        BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
        BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
        moveIn->setEaseType(uilib::EaseSineInOut);
        moveIn->setMoveInType(uilib::HorizontalLeftIn);
        moveOut->setEaseType(uilib::EaseSineInOut);
        moveOut->setMoveOutType(uilib::HorizontalRightOut);
        moveOut->setActionTime(0.2);
        moveIn->setStartTime(0.2);
        if(m_sendPage){
            m_sendPage->setVisible(true);
            m_sendPage->setMoveinAction(moveIn);
            m_sendPage->setMoveoutAction(moveOut);
        }
        if(m_showPage){
            m_showPage->setMoveinAction(moveIn);
            m_showPage->setMoveoutAction(moveOut);
        }
    }
    if(m_showPage)
        m_showPage->moveOut();
    if(m_sendPage)
        m_sendPage->moveIn();
}
void SendMsgDialog::setSendImg(const std::string &normal,const std::string &pressed)
{
    m_sendImg = normal;
    m_sendPressedImg = pressed;
}
void SendMsgDialog::setReplyImg(const std::string &normal,const std::string &pressed)
{
    m_replyImg = normal;
    m_replyPressedImg = pressed;
}
void SendMsgDialog::setBackImg(const std::string &normal,const std::string &pressed)
{
    m_backImg = normal;
    m_backPressedImg = pressed;
}
void SendMsgDialog::setSendCB(CCNode *listener,SEL_CallFuncND func)
{
    m_sendListener = listener;
    m_sendFunc = func;
}
void SendMsgDialog::setRecInfo(const std::string &id,const std::string &name,const std::string &portrait)
{
    m_recId = id;
    m_recName = name;
    m_recHead = portrait;
}
void SendMsgDialog::setSenderInfo(const std::string &id,const std::string &name,const std::string &portrait)
{
    m_senderId = id;
    m_senderName = name;
    m_senderHead = portrait;
}
void SendMsgDialog::setMsgInfo(const std::string &title,const std::string &msg)
{
    m_msgTitle = title;
    m_msgWord = msg;
}
void SendMsgDialog::getSendMsg(std::string &title,std::string &word)
{
    if(m_titleInput)
        title = m_titleInput->getText();
    if(m_msgInput)
        word = m_msgInput->getText();
}
void SendMsgDialog::setCanReply(bool reply)
{
    m_canReply = reply;
}
