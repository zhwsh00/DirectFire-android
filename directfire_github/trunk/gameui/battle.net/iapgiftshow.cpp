#include "iapgiftshow.h"
#include "gamecore/resource/resourcemgr.h"

#include "utils/sysutils.h"
#include "prop/propdef.h"

#include "gamecore/serverinterface.h"

IAPGiftShow::IAPGiftShow(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_coinNum = 0;
}
IAPGiftShow::~IAPGiftShow()
{

}
void IAPGiftShow::exec()
{
    finished();
    BasShowDialog::exec();
}
void IAPGiftShow::finished()
{
    std::stringstream ss;
    // close button
    BasButton *closeBtn = new BasButton;
    closeBtn->setButtonInfo(ResourceMgr::getInstance()->getLangDef()->getStringById(StringEnum::Ok),m_theme,"buttonbg",CCSizeMake(0,0));
    closeBtn->setClickCB(this,callfuncND_selector(IAPGiftShow::onCloseClicked));
    closeBtn->setHorizontal("parent", 0.5);
    closeBtn->setBottom("parent",uilib::Bottom);
    closeBtn->setBottomMargin(15);
    this->addChild(closeBtn);
    setCloseCB(this,callfuncND_selector(IAPGiftShow::onCloseClicked));
    // title
    BasLabel *title = new BasLabel;
    title->setLabelInfo(m_titleText,"","",CCSizeMake(0,0),getSystemFont(),40,ccWHITE);
    this->addChild(title);
    title->setTop("parent", uilib::Top);
    title->setHorizontal("parent", 0.5);
    title->setTopMargin(8);

    BasWidget *top = title;
    if(m_coinNum != 0){
        std::string coinname;
        PropDef::getVirtualPropsName(PropDef::Props_Coin,coinname);
        coinname += ".png";
        CCSprite *coinSprite = CCSprite::createWithSpriteFrameName(coinname.data());
        BasNodeDelegateWidget *coinSpriteDele = new BasNodeDelegateWidget(coinSprite);
        this->addChild(coinSpriteDele);
        coinSpriteDele->setTop(title->getName(),uilib::Bottom);
        coinSpriteDele->setTopMargin(8);
        coinSpriteDele->setHorizontal(title->getName(),0.5);
        coinSpriteDele->setHorMargin(-coinSprite->getContentSize().width / 2);
        ss.str("");ss << "x" << m_coinNum;
        CCLabelBMFont *coinNumSprite = CCLabelBMFont::create(ss.str().data(),"fonts/font30.fnt");
        BasNodeDelegateWidget *coinNumDele = new BasNodeDelegateWidget(coinNumSprite);
        this->addChild(coinNumDele);
        coinNumDele->setLeft(coinSpriteDele->getName(),uilib::Right);
        coinNumDele->setLeftMargin(20);
        coinNumDele->setVertical(coinSpriteDele->getName(),0.5);

        top = coinSpriteDele;
    }

    BasWidget *center = new BasWidget;
    this->addChild(center);
    center->setLeft("parent",uilib::Left);
    center->setRight("parent",uilib::Right);
    center->setTop(top->getName(),uilib::Bottom);
    center->setBottom(closeBtn->getName(),uilib::Top);
    center->setMargins(10);
    // props
    VerticalLayout *vlay = new VerticalLayout;
    std::string propName;
    std::string reward;
    reward = ResourceMgr::getInstance()->getLangDef()->getStringById(StringEnum::Reward);
    for(unsigned int i = 0;i < m_gifts.size();i++){
        propName.clear();
        BasWidget *giftItem = new BasWidget;
        giftItem->setMaxWidthRefSize("parent", 0.6);
        giftItem->setMinWidthRefSize("parent", 0.6);
        giftItem->setMaxHeightRefSize("parent", 0.25);
        giftItem->setMinHeightRefSize("parent", 0.25);
        
        UiMsgEv::GiftPropEv &gift = m_gifts[i];
        PropDef::getVirtualPropsName(gift.m_id,propName);
        if(propName.empty())
            continue;
        propName += ".png";
        CCSprite *giftSprite = CCSprite::create();
        giftSprite->initWithSpriteFrameName(propName.data());
        ss.str("");ss << reward << " x" << gift.m_count;
        CCLabelBMFont *numSprite = CCLabelBMFont::create(ss.str().data(),"fonts/font30.fnt");
        
        BasWidget *giftItemLeft = new BasWidget;
        giftItemLeft->setMaxWidthRefSize("parent", 0.5);
        giftItemLeft->setMinWidthRefSize("parent", 0.5);
        giftItemLeft->setTop("parent", uilib::Top);
        giftItemLeft->setBottom("parent", uilib::Bottom);
        giftItemLeft->setLeft("parent", uilib::Left);
        BasWidget *giftItemRight = new BasWidget;
        giftItemRight->setMaxWidthRefSize("parent", 0.4);
        giftItemRight->setMinWidthRefSize("parent", 0.4);
        giftItemRight->setTop("parent", uilib::Top);
        giftItemRight->setBottom("parent", uilib::Bottom);
        giftItemRight->setLeft(giftItemLeft->getName(), uilib::Right);
        giftItemRight->setLeftMargin(m_edgeSize * 4);
        giftItem->addChild(giftItemLeft);
        giftItem->addChild(giftItemRight);
        
        BasNodeDelegateWidget *propImgWidget = new BasNodeDelegateWidget(giftSprite);
        propImgWidget->setVertical("parent", 0.5);
        propImgWidget->setRight("parent", uilib::Right);
        giftItemLeft->addChild(propImgWidget);
        BasNodeDelegateWidget *propCountWidget = new BasNodeDelegateWidget(numSprite);
        propCountWidget->setVertical("parent", 0.5);
        propCountWidget->setLeft("parent", uilib::Left);
        giftItemRight->addChild(propCountWidget);
        vlay->addWidget(giftItem);
    }
    vlay->setAveraged(true);
    center->setLayout(vlay);
}
void IAPGiftShow::onCloseClicked(CCNode *sender,void *data)
{
    if(m_coinNum != 0){
        ServerInterface::getInstance()->buySuccess(PropDef::Props_Coin,m_coinNum);
    }
    this->destroy();
}
