#include "shoppage.h"

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"

#include "propexdialog.h"
#include "propsyndialog.h"
#include "coin2golddialog.h"
#include "prop2golddialog.h"
#include "iapgiftshow.h"
#include "iap/IAPHelper.h"

ShopPage::ShopPage(CCNode *parent,const ccColor4B &color) : BasShowDialog(parent,color)
{
    m_itemInit = false;

    m_shopWidget = 0;
    m_iapLoadingDialog = 0;
    m_exDialog = 0;
    m_synDialog = 0;
    m_coin2Gold = 0;
    m_prop2Gold = 0;
    m_iapIndex = 0;
    ServerInterface::getInstance()->setSellBuyEvCB(this,callfuncND_selector(ShopPage::serverListener));
    // dialog size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    setHeight(size.height * 0.9);
}
ShopPage::~ShopPage()
{
    ServerInterface::getInstance()->setSellBuyEvCB(0,0);
}
void ShopPage::exec()
{
    initItem();
    BasShowDialog::exec();
}

void ShopPage::serverListener(CCNode *sender,void *type)
{
    NetEventPackage *netEvent = (NetEventPackage*)type;
    switch(netEvent->eventId()){
    case UiMsgHandler::UiEv_salePropRely:{
        if(m_coin2Gold)
            m_coin2Gold->exchangeReply(true);
        if(m_prop2Gold)
            m_prop2Gold->exchangeReply(true);
        break;
    }
    case UiMsgHandler::UiEv_salePropFailedRely:{
        if(m_coin2Gold)
            m_coin2Gold->exchangeReply(false);
        if(m_prop2Gold)
            m_prop2Gold->exchangeReply(false);
        break;
    }
    case UiMsgHandler::UiEv_buyPropRely:{
        if(m_exDialog)
            m_exDialog->exchangeReply(true);
        break;
    }
    case UiMsgHandler::UiEv_buyPropFailedRely:{
        if(m_exDialog)
            m_exDialog->exchangeReply(false);
        break;
    }
    case UiMsgHandler::UiEv_buyActionGot:{
        std::string word;
        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        IAPGiftShow *iapGiftShow = new IAPGiftShow(root);
        iapGiftShow->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
        iapGiftShow->setTitleText(ResourceMgr::getInstance()->getLangDef()->getStringById(StringEnum::IAPSuccess));
        int buynum = IAPHelper::getInstance()->getCoinNumByProductId(m_iapIndex);

        iapGiftShow->setCoinNum(buynum);
        std::vector<UiMsgEv::GiftPropEv>& gifts = iapGiftShow->gifts();
        if (ServerInterface::getInstance()->getReceivedBuyInfo(gifts, word)) {
            iapGiftShow->exec();
        }
        if (m_iapLoadingDialog) {
            m_iapLoadingDialog->destory();
            m_iapLoadingDialog = 0;
        }
        break;
    }
    case UiMsgHandler::UiEv_iapFailed:{
        if (m_iapLoadingDialog) {
            m_iapLoadingDialog->destory();
            m_iapLoadingDialog = 0;
        }
        break;	
    }
    default:
        break;
    }
}
void ShopPage::initItem()
{
    if(m_itemInit)
        return;
    UiThemeMgr *mgr = ResourceMgr::getInstance()->getUiThemeMgr();
    const std::vector<ShopDef> &shops = mgr->getShopDef();

    m_shopWidget = new BasWidget;
    this->addChild(m_shopWidget);
    m_shopWidget->setLeft("parent",uilib::Left);
    m_shopWidget->setRight("parent",uilib::Right);
    m_shopWidget->setTop("parent",uilib::Top);
    m_shopWidget->setTopMargin(20);
    m_shopWidget->setBottom("parent",uilib::Bottom);

    if(1){
        //init shopping
        int row = 5;
        int col = 2;
        GridLayout *grid = new GridLayout(row,col);
        grid->setSpacing(0);
        BasButton *button;
        ccLanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
        std::string pricename;
        if(!ResourceMgr::getInstance()->isLanguageSupport(currentLanguageType)){
            currentLanguageType = kLanguageEnglish;
        }
        switch (currentLanguageType)
        {
        case kLanguageEnglish:
            pricename = "eng";
            break;
        case kLanguageChinese:
            pricename = "china";
            break;
        case kLanguageFrench:
            pricename = "french";
            break;
        case kLanguageGerman:
            pricename = "german";
            break;
        case kLanguageItalian:
            pricename = "italian";
            break;
        case kLanguageRussian:
            pricename = "russian";
            break;
        case kLanguageSpanish:
            pricename = "spanish";
            break;
        case kLanguageKorean:
            pricename = "korean";
            break;
        }
        std::stringstream ss;
        for(int i = 0;i < shops.size();i++){
            const ShopDef &def = shops[i];
            button = new BasButton;
            button->setButtonInfo("","default",def.m_name,CCSizeMake(0,0));
            button->setButtonIndex(i);
            button->setClickCB(this,callfuncND_selector(ShopPage::onShopButtonClicked));
            button->setWidthHeightRate(0.528);
            grid->addWidget(button);
            ss.str("");ss << pricename << "price" << (i+1) << ".png";
            CCSprite *priceSprite = CCSprite::createWithSpriteFrameName(ss.str().data());
            BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(priceSprite);
            button->addChild(dele);
            dele->setRight("parent",uilib::Right);
            dele->setRightMargin(10);
            dele->setVertical("parent",0.5);
        }
        button = new BasButton();
        button->setButtonInfo("","default","coin2gold",CCSizeMake(0,0));
        button->setClickCB(this,callfuncND_selector(ShopPage::onCoin2GoldClicked));
        button->setWidthHeightRate(0.528);
        grid->addWidget(button);

        button = new BasButton();
        button->setButtonInfo("","default","propex",CCSizeMake(0,0));
        button->setClickCB(this,callfuncND_selector(ShopPage::onPropExClicked));
        button->setWidthHeightRate(0.528);
        grid->addWidget(button);

        button = new BasButton();
        button->setButtonInfo("","default","prop2gold",CCSizeMake(0,0));
        button->setClickCB(this,callfuncND_selector(ShopPage::onProp2GoldClicked));
        button->setWidthHeightRate(0.528);
        grid->addWidget(button);
        m_shopWidget->setLayout(grid);
    }
    this->layout(true);
    m_itemInit = true;
}
void ShopPage::onShopButtonClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY){
        std::string text = "IAP no supported in bb10 now,you can get gold from your friend gift!";
        new SplashMessageWidget(this,text);
        return;
    }else if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
        std::string text = "IAP no supported in Android now,you can get gold from your friend gift!";
        new SplashMessageWidget(this,text);
        return;
    }
    if(m_iapLoadingDialog == 0){
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        m_iapLoadingDialog = new BusyDialog();
        m_iapLoadingDialog->setTouchPriority(uilib::TopPriority - uilib::SafePriorityGap);
        CCNode *root = this->getParent();
        while (root->getParent()) {
            root = root->getParent();
        }
        root->addChild(m_iapLoadingDialog, 11000);
        m_iapLoadingDialog->setBusyText(lang->getStringById(StringEnum::Loading));
        m_iapLoadingDialog->setAnimationName("uiloadinga");
    }
    m_iapLoadingDialog->setLoadFinishedCB(this,callfuncN_selector(ShopPage::onShopStart));
    m_iapLoadingDialog->exec();
    BasButton *button = (BasButton *)node;
    m_iapIndex = button->getButtonIndex();
}
void ShopPage::onShopStart(CCNode *sender)
{
    ServerInterface::getInstance()->buyProduct(m_iapIndex);
}
void ShopPage::onPropExClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_exDialog == 0){
        m_exDialog = new PropExDialog(root,ccc4(0,0,0,128));
        m_exDialog->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
        m_exDialog->setCloseCB(this,callfuncND_selector(ShopPage::onPropExCloseClicked));
    }
    m_exDialog->exec();
}
void ShopPage::onPropSynClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_synDialog == 0){
        m_synDialog = new PropSynDialog(root,ccc4(0,0,0,128));
        m_synDialog->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
        m_synDialog->setCloseCB(this,callfuncND_selector(ShopPage::onPropSynCloseClicked));
    }
    m_synDialog->exec();
}
void ShopPage::onCoin2GoldClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_coin2Gold == 0){
        m_coin2Gold = new Coin2GoldDialog(root,ccc4(0,0,0,128));
        m_coin2Gold->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
        m_coin2Gold->setCloseCB(this,callfuncND_selector(ShopPage::onCoin2GoldCloseClicked));
    }
    m_coin2Gold->exec();
}
void ShopPage::onProp2GoldClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_prop2Gold == 0){
        m_prop2Gold = new Prop2GoldDialog(root,ccc4(0,0,0,128));
        m_prop2Gold->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
        m_prop2Gold->setCloseCB(this,callfuncND_selector(ShopPage::onProp2GoldCloseClicked));
    }
    m_prop2Gold->exec();
}
void ShopPage::onPropExCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_exDialog->destroy();
    m_exDialog = 0;
}
void ShopPage::onPropSynCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_synDialog->destroy();
    m_synDialog = 0;
}
void ShopPage::onCoin2GoldCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_coin2Gold->destroy();
    m_coin2Gold = 0;
}
void ShopPage::onProp2GoldCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_prop2Gold->destroy();
    m_prop2Gold = 0;
}
