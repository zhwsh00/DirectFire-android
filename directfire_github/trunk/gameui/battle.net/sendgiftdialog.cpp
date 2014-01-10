#include "sendgiftdialog.h"
#include "prop/propdef.h"

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"

SendGiftDialog::SendGiftDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_input = 0;
    m_sendListener = 0;
    m_sendFunc = 0;
    m_bottomWidget = 0;
    m_propScrollWidget = 0;
    m_headWidget = 0;
    m_sendImg = "buttonbg";
    m_edgeSize = 20;
}
SendGiftDialog::~SendGiftDialog()
{

}
void SendGiftDialog::setSendCB(CCNode *node,SEL_CallFuncND func)
{
    m_sendListener = node;
    m_sendFunc = func;
}
void SendGiftDialog::setSendImg(const std::string &normal,const std::string &pressed)
{
    m_sendImg = normal;
    m_sendPressedImg = pressed;
}
void SendGiftDialog::setSendtoInfo(const std::string &name,const std::string &portrait)
{
    m_sendtoName = name;
    m_sendtoPortrait = portrait;
}
void SendGiftDialog::addProp(int propId,int propNum)
{
    m_hasProps.push_back(GiftPropDef(propId,propNum));
}
void SendGiftDialog::getSendProp(std::vector<UiMsgEv::GiftPropEv> &props,std::string &word)
{
    word = m_input->getText();
    //get gift
    for(unsigned i = 0;i < m_hasProps.size();i++){
        GiftPropDef &def = m_hasProps[i];
        if(def.m_sendCount == 0)
            continue;
        props.push_back(UiMsgEv::GiftPropEv(def.m_id,def.m_sendCount));
    }
}
void SendGiftDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void SendGiftDialog::finish()
{
    if(m_bottomWidget != 0)
        return;
    m_bottomWidget = new BasWidget;
    this->addChild(m_bottomWidget);
    m_bottomWidget->setLeft("parent",uilib::Left);
    m_bottomWidget->setRight("parent",uilib::Right);
    m_bottomWidget->setBottom("parent",uilib::Bottom);
    m_bottomWidget->setHeight(70);
    m_bottomWidget->setLeftMargin(m_edgeSize);
    m_bottomWidget->setBottomMargin(m_edgeSize);
    m_bottomWidget->setRightMargin(m_edgeSize);

    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    if(1){
        //bottom content
        BasButton *send = new BasButton;
        send->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
        send->setButtonInfo(lang->getStringById(StringEnum::Send).data(),"fonts/uifont24.fnt",m_theme,m_sendImg,CCSizeMake(0,0));
        m_bottomWidget->addChild(send);
        send->setRight("parent",uilib::Right);
        send->setBottom("parent",uilib::Bottom);
        send->setClickCB(m_sendListener,m_sendFunc);

        CCSize spsize;
        spsize.width = 120;
        spsize.height = 80;
        if(!m_sendtoPortrait.empty()){
            CCImage *img = new CCImage;
            img->initWithImageData((void*)m_sendtoPortrait.c_str(),m_sendtoPortrait.size(),
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

            m_bottomWidget->addChild(headWidget);
            headWidget->setLeft("parent",uilib::Left);
            headWidget->setVertical(send->getName(),0.5);
            m_headWidget = headWidget;
        }else{
            BasLabel *label = new BasLabel;
            label->setLabelInfo(m_sendtoName,"","",CCSizeMake(0,0),getSystemFont(),30,ccWHITE);
            m_bottomWidget->addChild(label);
            label->setVertical(send->getName(),0.5);
            label->setLeft("parent",uilib::Left);
            label->setMaxHeightRefSize(send->getName(),1.0);
            label->setMaxWidthRefSize(send->getName(),1.0);
            m_headWidget = label;
        }
        m_input = new InputBox;
        m_input->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
        m_input->setMaxLength(120);
        m_input->setTheme("default","inputbg");
        m_input->setPlaceHolder(lang->getStringById(StringEnum::CommonReplyWord));
        m_bottomWidget->addChild(m_input);
        m_input->setLeft(m_headWidget->getName(),uilib::Right);
        m_input->setRight(send->getName(),uilib::Left);
        m_input->setVertical(send->getName(),0.5);
        m_input->setMaxHeightRefSize(send->getName(),1);
        m_input->setMinHeightRefSize(send->getName(),1);
    }
    if(1){
        //init prop
        m_propScrollWidget = new VerScrollWidget("","");
        this->addChild(m_propScrollWidget);
        m_propScrollWidget->setLeft("parent",uilib::Left);
        m_propScrollWidget->setRight("parent",uilib::Right);
        m_propScrollWidget->setTop("parent",uilib::Top);
        m_propScrollWidget->setBottom(m_bottomWidget->getName(),uilib::Top);
        m_propScrollWidget->setLeftMargin(m_edgeSize);
        m_propScrollWidget->setRightMargin(m_edgeSize);
        m_propScrollWidget->setTopMargin(m_edgeSize);

        float w = m_anchorWidth - m_edgeSize * 4;
        float h = 100;
        CCSize bsize = CCSizeMake(w,h);
        for(unsigned int i = 0;i < m_hasProps.size();i++){
            GiftPropDef &gift = m_hasProps[i];
            if (!PropDef::propCanPresentAble(gift.m_id)) {
                continue;
            }
            gift.m_sendCount = 0;
            gift.m_index = i;
            gift.m_sendNum = 0;
            std::string name;
            PropDef::getVirtualPropsName(gift.m_id,name);
            if(name.empty())
                continue;
            name += ".png";

            BorderWidget *border = new BorderWidget();
            border->setTheme(m_theme,"propbg");
            border->setWidth(w);
            border->setHeight(h);
            FSizeWidgetDelegate *fdele = new FSizeWidgetDelegate(border,bsize);
            m_propScrollWidget->addFixedSizeWidget(fdele);

            CCSprite *propSprite = CCSprite::create();
            propSprite->initWithSpriteFrameName(name.c_str());
            std::stringstream ss;
            ss << "x" << gift.m_count;
            CCLabelBMFont *numSprite = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
            propSprite->addChild(numSprite);
            CCSize giftSize = propSprite->getContentSize();
            CCSize numSize = numSprite->getContentSize();
            numSprite->setAnchorPoint(ccp(0,0));
            numSprite->setPosition(ccp(giftSize.width - numSize.width / 2,0));

            BasNodeDelegateWidget *pdele = new BasNodeDelegateWidget(propSprite);
            border->addChild(pdele);
            pdele->setVertical("parent",0.5);
            pdele->setLeft("parent",uilib::Left);
            pdele->setLeftMargin(m_edgeSize);

            gift.m_incButton = new BasButton;
            gift.m_incButton->setButtonInfo("",m_theme,"uiincrease",CCSizeMake(0,0));
            gift.m_incButton->setClickCB(this,callfuncND_selector(SendGiftDialog::onIncButtonClicked));
            gift.m_decButton = new BasButton;
            gift.m_decButton->setButtonInfo("",m_theme,"uidecrease",CCSizeMake(0,0));
            gift.m_decButton->setClickCB(this,callfuncND_selector(SendGiftDialog::onDecButtonClicked));

            border->addChild(gift.m_incButton);
            gift.m_incButton->setVertical("parent",0.5);
            gift.m_incButton->setRight("parent",uilib::Right);
            gift.m_incButton->setRightMargin(m_edgeSize);
            gift.m_incButton->setButtonIndex(i);

            border->addChild(gift.m_decButton);
            gift.m_decButton->setVertical("parent",0.5);
            gift.m_decButton->setRight(gift.m_incButton->getName(),uilib::Left);
            gift.m_decButton->setRightMargin(m_edgeSize);
            gift.m_decButton->setButtonIndex(i);


            gift.m_sendNum = CCLabelBMFont::create("0","fonts/font30.fnt");
            BasNodeDelegateWidget *sendDele = new BasNodeDelegateWidget(gift.m_sendNum);
            border->addChild(sendDele);
            sendDele->setCenterIn("parent");
        }
        m_propScrollWidget->setSpacing(20);
    }
}
void SendGiftDialog::onIncButtonClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data;
    if(index < 0 || index >= m_hasProps.size())
        return;
    GiftPropDef &def = m_hasProps[index];
    if(def.m_sendNum == 0)
        return;
    def.m_sendCount++;
    if(def.m_sendCount >= def.m_count)
        def.m_sendCount = def.m_count;
    std::stringstream ss;
    ss << def.m_sendCount;
    def.m_sendNum->setString(ss.str().data());
}
void SendGiftDialog::onDecButtonClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data;
    if(index < 0 || index >= m_hasProps.size())
        return;
    GiftPropDef &def = m_hasProps[index];
    if(def.m_sendNum == 0)
        return;
    def.m_sendCount--;
    if(def.m_sendCount < 0)
        def.m_sendCount = 0;
    std::stringstream ss;
    ss << def.m_sendCount;
    def.m_sendNum->setString(ss.str().data());
}
