#include "recgiftshow.h"
#include "gamecore/resource/resourcemgr.h"

#include "utils/sysutils.h"
#include "prop/propdef.h"

#include "gamecore/serverinterface.h"

RecGiftShow::RecGiftShow(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    clear();
    m_theme = "default";
    m_bg = "dialog";
    m_edgeSize = 20;
}
RecGiftShow::~RecGiftShow()
{

}
void RecGiftShow::clear()
{
    m_isFriend = false;
    m_isForMe = true;
    m_theme = "default";
    m_bg = "inputbg";
    m_closeListener = 0;
    m_closeFunc = 0;
    m_sendMsgListener = 0;
    m_sendMsgFunc = 0;
    m_sendGiftListener = 0;
    m_sendGiftFunc = 0;    
    m_addFriendListener = 0;
    m_addFriendFunc = 0;
    m_closeImg = "uiexit";
    m_sendMsgImg = "buttonbg";
    m_sendGiftImg = "buttonbg";
    m_input = 0;
    m_widgetBottom = 0;
    m_widgetLeft = 0;
    m_widgetRight = 0;
    m_widgetWord = 0;
}
void RecGiftShow::setSenderInfo(bool isFriend,const std::string &name,const std::string &word,const std::string &headPortrait)
{
    m_isFriend = isFriend;
    m_senderName = name;
    m_giftWord = word;
    m_senderHead = headPortrait;
}
void RecGiftShow::setSenderContent(const std::vector<UiMsgEv::GiftPropEv> &gifts)
{
    m_gifts = gifts;
}
void RecGiftShow::setSendMsgImg(const std::string &normal,const std::string &pressed)
{
    m_sendMsgImg = normal;
    m_sendMsgPressedImg = pressed;
}
void RecGiftShow::setSendGiftImg(const std::string &normal,const std::string &pressed)
{
    m_sendGiftImg = normal;
    m_sendGiftPressedImg = pressed;
}
void RecGiftShow::setSendMsgCB(CCNode *node,SEL_CallFuncND func)
{
    m_sendMsgListener = node;
    m_sendMsgFunc = func;
}
void RecGiftShow::setSendGiftCB(CCNode *node,SEL_CallFuncND func)
{
    m_sendGiftListener = node;
    m_sendGiftFunc = func;
}
void RecGiftShow::setAddFriendCB(CCNode *node,SEL_CallFuncND func)
{
    m_addFriendListener = node;
    m_addFriendFunc = func;
}
void RecGiftShow::getReplyWord(std::string &title,std::string &word)
{
    if(m_input){
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        title = lang->getStringById(StringEnum::CommonReplyTitle);
        word = m_input->getText();
        if(word.empty()){
            word = lang->getStringById(StringEnum::CommonReplyWord);
        }
    }
}
void RecGiftShow::exec()
{
    finished();
    BasShowDialog::exec();
}
void RecGiftShow::finished()
{
    if(m_widgetLeft){
        //finished
        return;
    }

    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    if(m_isForMe){
        //if this is for me,will create reply buttons...
        m_widgetBottom = new BasWidget;
        this->addChild(m_widgetBottom);
        m_widgetBottom->setLeft("parent",uilib::Left);
        m_widgetBottom->setRight("parent",uilib::Right);
        m_widgetBottom->setBottom("parent",uilib::Bottom);
        m_widgetBottom->setMaxHeightRefSize("parent",0.2);
        m_widgetBottom->setMinHeightRefSize("parent",0.2);

        BasButton *button;
        button = new BasButton;
        button->setButtonInfo(lang->getStringById(StringEnum::Send).data(),"fonts/uifont24.fnt",m_theme,"buttonbg",CCSizeMake(0,0));
        m_input = new InputBox;
        m_input->setMaxLength(120);
        m_input->setTheme("default","inputbg");
        m_input->setPlaceHolder(lang->getStringById(StringEnum::CommonReplyWord));

        m_widgetBottom->addChild(button);
        m_widgetBottom->addChild(m_input);
        button->setClickCB(m_sendMsgListener,m_sendMsgFunc);

        button->setRight("parent",uilib::Right);
        button->setBottom("parent",uilib::Bottom);
        button->setRightMargin(m_edgeSize);
        button->setBottomMargin(m_edgeSize);
        m_input->setRight(button->getName(),uilib::Left);
        m_input->setLeft("parent",uilib::Left);
        m_input->setVertical(button->getName(),0.5);
        m_input->setMaxHeightRefSize(button->getName(),1.0);
        m_input->setMinHeightRefSize(button->getName(),1.0);
        m_input->setLeftMargin(m_edgeSize);
    }
    if(!m_giftWord.empty()){
        m_giftWord.insert(0,"    ");
        m_widgetWord = new TextScrollArea;
        m_widgetWord->setMargins(m_edgeSize);
        m_widgetWord->setTheme("","");
        m_widgetWord->setTextInfo(m_giftWord,getSystemFont(),30,ccWHITE);
        this->addChild(m_widgetWord);

        m_widgetWord->setLeft("parent",uilib::Left);
        m_widgetWord->setRight("parent",uilib::Right);
        m_widgetWord->setMaxHeightRefSize("parent",0.3);
        m_widgetWord->setMinHeightRefSize("parent",0.3);
        m_widgetWord->setVerticalScrollPolicy(ScrollShow_Never);
        m_widgetWord->setHorizontalScrollPolicy(ScrollShow_Never);
        if(m_widgetBottom)
            m_widgetWord->setBottom(m_widgetBottom->getName(),uilib::Top);
        else
            m_widgetWord->setBottom("parent",uilib::Bottom);
    }
    if(1){
        //init senderinfo
        m_widgetLeft = new BasWidget;
        this->addChild(m_widgetLeft);
        m_widgetLeft->setLeft("parent",uilib::Left);
        m_widgetLeft->setTop("parent",uilib::Top);
        if(m_widgetWord){
            m_widgetLeft->setBottom(m_widgetWord->getName(),uilib::Top);
        }else if(m_widgetBottom){
            m_widgetLeft->setBottom(m_widgetBottom->getName(),uilib::Top);
        }else{
            m_widgetLeft->setBottom("parent",uilib::Bottom);
        }
        m_widgetLeft->setMaxWidthRefSize("parent",0.4);
        m_widgetLeft->setMinWidthRefSize("parent",0.4);
        m_widgetLeft->setMargins(m_edgeSize);

        BasNodeDelegateWidget *headWidget = 0;
        if(!m_senderHead.empty()){
            CCImage *img = new CCImage;
            img->initWithImageData((void*)m_senderHead.c_str(),m_senderHead.size(),
                                   CCImage::kFmtUnKnown);
            CCTexture2D *texture = new CCTexture2D;
            texture->initWithImage(img);
            CCSprite *sprite = CCSprite::create();
            sprite->initWithTexture(texture);
            headWidget = new BasNodeDelegateWidget(sprite);
            m_widgetLeft->addChild(headWidget);
            headWidget->setHorizontal("parent",0.5);
            headWidget->setVertical("parent",0.45);
            delete img;
            headWidget->setCanTouch(true);
            headWidget->setClickCB(this,callfuncND_selector(RecGiftShow::onHeadPortraitClicked));
        }
        if(!m_senderName.empty()){
            BasLabel *label = new BasLabel();
            label->setLabelInfo(m_senderName,"","",CCSizeMake(0,0),getSystemFont(),30,ccWHITE);
            m_widgetLeft->addChild(label);
            if(headWidget == 0){
                label->setCenterIn("parent");
                label->setSizeLimitedToParent();
            }else{
                label->setHorizontal("parent",0.5);
                label->setTop(headWidget->getName(),uilib::Bottom);
                label->setTopMargin(m_edgeSize);
            }
            label->setCanTouch(true);
            label->setClickCB(this,callfuncND_selector(RecGiftShow::onHeadPortraitClicked));
        }
    }
    if(1){
        //init gift info
        m_widgetRight = new BasWidget;
        this->addChild(m_widgetRight);
        m_widgetRight->setRight("parent",uilib::Right);
        m_widgetRight->setLeft(m_widgetLeft->getName(),uilib::Right);
        m_widgetRight->setTop("parent",uilib::Top);
        if(m_widgetWord){
            m_widgetRight->setBottom(m_widgetWord->getName(),uilib::Top);
        }else if(m_widgetBottom){
            m_widgetRight->setBottom(m_widgetBottom->getName(),uilib::Top);
        }else{
            m_widgetRight->setBottom("parent",uilib::Bottom);
        }
        m_widgetRight->setMargins(m_edgeSize);

        HorizontalLayout *hlay = new HorizontalLayout;
        std::string propName;
        for(unsigned int i = 0;i < m_gifts.size();i++){
            propName.clear();
            UiMsgEv::GiftPropEv &gift = m_gifts[i];
            PropDef::getVirtualPropsName(gift.m_id,propName);
            if(propName.empty())
                continue;
            propName += ".png";
            CCSprite *giftSprite = CCSprite::create();
            giftSprite->initWithSpriteFrameName(propName.data());

            std::stringstream ss;
            ss << "x" << gift.m_count;
            CCLabelBMFont *numSprite = CCLabelBMFont::create(ss.str().data(),"fonts/font20.fnt");
            giftSprite->addChild(numSprite);
            CCSize giftSize = giftSprite->getContentSize();
            CCSize numSize = numSprite->getContentSize();
            numSprite->setAnchorPoint(ccp(0,0));
            numSprite->setPosition(ccp(giftSize.width - numSize.width / 2,0));
            BasNodeDelegateWidget *delegate = new BasNodeDelegateWidget(giftSprite);
            hlay->addWidget(delegate);
        }
        hlay->setAveraged(true);
        m_widgetRight->setLayout(hlay);
        if(1){
            //gift action
            BasNodeAction *giftinaction = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
            giftinaction->setEaseType(uilib::EaseBackInOut);
            giftinaction->setMoveInType(uilib::DropScaleIn);
            giftinaction->setActionTime(1.0);
            m_widgetRight->setMoveinAction(giftinaction);
            m_widgetRight->moveIn();
        }
        if(1){
            CCSprite *anim = CCSprite::create();
            anim->initWithSpriteFrameName("whiteshining.png");
            CCScaleTo *scale = CCScaleTo::create(1,40);
            CCFadeOut *fade = CCFadeOut::create(1);
            anim->runAction(CCSequence::create(scale,fade,0));
            BasNodeDelegateWidget *delegate = new BasNodeDelegateWidget(anim);
            m_widgetRight->addChild(delegate);
            delegate->setCenterIn("parent");
        }
    }
}
void RecGiftShow::onHeadPortraitClicked(CCNode *node,void *data)
{
    CCPoint pos = this->convertToNodeSpace(*(CCPoint*)data);
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    PopButtonsDialog *pop = new PopButtonsDialog(this,pos);
    pop->setButtonCB(this,callfuncND_selector(RecGiftShow::onPopButtonsClicked));
    if(!m_isFriend){
        pop->addButton(lang->getStringById(StringEnum::AddFriend));
    }
    pop->addButton(lang->getStringById(StringEnum::SendGift));
    pop->setSpacing(10);
    pop->setEdgeSize(20);
    pop->exec();
}
void RecGiftShow::onPopButtonsClicked(CCNode *node,void *data)
{
    int index = *(int*)data;
    if(m_isFriend){
        if(m_sendGiftListener && m_sendGiftFunc){
            (m_sendGiftListener->*m_sendGiftFunc)(node,data);
        }
    }else{
        if(index == 0){
            if(m_addFriendListener && m_addFriendFunc){
                (m_addFriendListener->*m_addFriendFunc)(node,data);
            }
        }else if(index == 1){
            if(m_sendGiftListener && m_sendGiftFunc){
                (m_sendGiftListener->*m_sendGiftFunc)(node,data);
            }
        }
    }
}
