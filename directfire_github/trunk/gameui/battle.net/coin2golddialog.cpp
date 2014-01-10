#include "coin2golddialog.h"
#include "gamecore/serverinterface.h"

#include "prop/propdef.h"
#include "resource/resourcemgr.h"
#include "sounds/soundmgr.h"

Coin2GoldDialog::Coin2GoldDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_serverIface = ServerInterface::getInstance();
    m_coinHad = 0;
    m_goldHad = 0;
    m_coinSprite = 0;
    m_goldSprite = 0;
    m_coinOnEx = 0;
    m_coinExSprite = 0;

    m_submitButton = 0;
    m_incButton = 0;
    m_decButton = 0;
    m_busyAnim = 0;

    m_edgeSize = 10;
}
Coin2GoldDialog::~Coin2GoldDialog()
{

}
void Coin2GoldDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void Coin2GoldDialog::exchangeReply(bool succ)
{
    m_incButton->setCanTouch(true);
    m_decButton->setCanTouch(true);
    m_submitButton->setCanTouch(true);
    m_busyAnim->end();
    m_busyAnim->setVisible(false);
    if(succ){
        m_coinOnEx = 0;
        m_coinExSprite->setString("x0");
    }else{
        new SplashMessageWidget(this,ResourceMgr::getInstance()->getLangDef()->getStringById(StringEnum::CommWithServerFailed));
    }
}
void Coin2GoldDialog::finish()
{
    std::stringstream ss;
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    if(1){
        //submit button
        m_submitButton = new BasButton;
        m_submitButton->setButtonInfo(lang->getStringById(StringEnum::ExChange).data(),"fonts/uifont24.fnt",
                                      m_theme,"buttonbg",CCSizeMake(0,0));
        m_submitButton->setClickCB(this,callfuncND_selector(Coin2GoldDialog::onSubmitButtonClicked));
        this->addChild(m_submitButton);
        m_submitButton->setHorizontal("parent",0.5);
        m_submitButton->setBottom("parent",uilib::Bottom);
        m_submitButton->setBottomMargin(m_edgeSize);
    }
    if(1){
        //init coin gold info
        m_id = m_serverIface->getLoginAccountInfo()->m_id;
        m_coinHad = m_serverIface->getPropNumByUid(m_id,PropDef::Props_Coin);
        m_goldHad = m_serverIface->getPropNumByUid(m_id,PropDef::Props_Gold);
        UiMsgEv::PropExchangeRule outRule;
        if(!m_serverIface->getPropExchangeRuleByPropType(PropDef::Props_Coin, outRule)){
            cout << "Coin2GoldDialog: cannot find coin exchange rate!" << endl;
            m_exRate = 100;
        }else{
            m_exRate = outRule.m_salePriceCount;
        }
        std::string coinImg,goldImg;
        PropDef::getVirtualPropsName(PropDef::Props_Coin,coinImg);
        PropDef::getVirtualPropsName(PropDef::Props_Gold,goldImg);
        coinImg += ".png";
        goldImg += ".png";

        CCSprite *coinSprite = CCSprite::createWithSpriteFrameName(coinImg.data());
        FSizeCCNodeDelegate *coinDele = new FSizeCCNodeDelegate(coinSprite);
        this->addChild(coinDele);
        coinDele->setLeft("parent",uilib::Left);
        coinDele->setTop("parent",uilib::Top);
        coinDele->setLeftMargin(m_edgeSize);
        coinDele->setTopMargin(m_edgeSize);

        ss.str("");ss << "x" << m_coinHad;
        m_coinSprite = CCLabelBMFont::create(ss.str().data(),"fonts/font30.fnt");
        FSizeCCNodeDelegate *coinNumDele = new FSizeCCNodeDelegate(m_coinSprite);
        this->addChild(coinNumDele);
        coinNumDele->setLeft(coinDele->getName(),uilib::Right);
        coinNumDele->setLeftMargin(2);
        coinNumDele->setVertical(coinDele->getName(),0.5);

        CCSprite *goldSprite = CCSprite::createWithSpriteFrameName(goldImg.data());
        FSizeCCNodeDelegate *goldDele = new FSizeCCNodeDelegate(goldSprite);
        this->addChild(goldDele);
        goldDele->setLeft("parent",uilib::Left);
        goldDele->setTop(coinDele->getName(),uilib::Bottom);
        goldDele->setLeftMargin(m_edgeSize);
        goldDele->setTopMargin(m_edgeSize);

        ss.str("");ss << "x" << m_goldHad;
        m_goldSprite = CCLabelBMFont::create(ss.str().data(),"fonts/font30.fnt");
        FSizeCCNodeDelegate *goldNumDele = new FSizeCCNodeDelegate(m_goldSprite);
        this->addChild(goldNumDele);
        goldNumDele->setLeft(goldDele->getName(),uilib::Right);
        goldNumDele->setLeftMargin(2);
        goldNumDele->setVertical(goldDele->getName(),0.5);
    }
    if(1){
        //init oper area
        ss.str("");ss << "x" << m_coinHad;
        m_coinExSprite = CCLabelBMFont::create(ss.str().data(),"fonts/font30.fnt");
        FSizeCCNodeDelegate *coinExDele = new FSizeCCNodeDelegate(m_coinExSprite);
        this->addChild(coinExDele);
        coinExDele->setCenterIn("parent");
        m_coinExSprite->setString("x0");

        m_incButton = new BasButton();
        m_incButton->setButtonInfo("",m_theme,"uiincrease",CCSizeMake(0,0));
        m_incButton->setClickCB(this,callfuncND_selector(Coin2GoldDialog::onIncButtonClicked));
        this->addChild(m_incButton);
        m_incButton->setLeft(coinExDele->getName(),uilib::Right);
        m_incButton->setLeftMargin(2);
        m_incButton->setVertical(coinExDele->getName(),0.5);
        m_incButton->setTouchInCB(this,callfuncND_selector(Coin2GoldDialog::onIncTouchBegin));
        m_incButton->setTouchOutCB(this,callfuncND_selector(Coin2GoldDialog::onIncTouchEnd));

        m_decButton = new BasButton();
        m_decButton->setButtonInfo("",m_theme,"uidecrease",CCSizeMake(0,0));
        m_decButton->setClickCB(this,callfuncND_selector(Coin2GoldDialog::onDecButtonClicked));
        this->addChild(m_decButton);
        m_decButton->setRight(coinExDele->getName(),uilib::Left);
        m_decButton->setRightMargin(2);
        m_decButton->setVertical(coinExDele->getName(),0.5);
        m_decButton->setTouchInCB(this,callfuncND_selector(Coin2GoldDialog::onDecTouchBegin));
        m_decButton->setTouchOutCB(this,callfuncND_selector(Coin2GoldDialog::onDecTouchEnd));
    }
    if(1){
        //loading busy
        std::string anim,first;
        anim = "uiloadinga";
        first = anim;
        ResourceMgr::getInstance()->getFrameSpriteFirstFrame(first);
        m_busyAnim = new BasAnimSprite(anim,first);
        FSizeCCNodeDelegate *busyNode = new FSizeCCNodeDelegate(m_busyAnim);
        this->addChild(busyNode);
        busyNode->setCenterIn("parent");
        m_busyAnim->setVisible(false);
    }
}
void Coin2GoldDialog::onIncButtonClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    std::stringstream ss;
    if(m_coinHad == 0)
        return;
    m_coinHad--;
    ss << "x" << m_coinHad;
    m_coinSprite->setString(ss.str().data());
    m_goldHad += m_exRate;
    ss.str("");ss << "x" << m_goldHad;
    m_goldSprite->setString(ss.str().data());

    m_coinOnEx++;
    ss.str("");ss << "x" << m_coinOnEx;
    m_coinExSprite->setString(ss.str().data());
}
void Coin2GoldDialog::onDecButtonClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    std::stringstream ss;
    if(m_coinOnEx == 0)
        return;
    m_coinHad++;
    ss << "x" << m_coinHad;
    m_coinSprite->setString(ss.str().data());
    m_goldHad -= m_exRate;
    ss.str("");ss << "x" << m_goldHad;
    m_goldSprite->setString(ss.str().data());

    m_coinOnEx--;
    ss.str("");ss << "x" << m_coinOnEx;
    m_coinExSprite->setString(ss.str().data());
}
void Coin2GoldDialog::onSubmitButtonClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_coinOnEx == 0)
        return;
    m_busyAnim->setVisible(true);
    m_busyAnim->playInLoop(-1);
    std::vector<UiMsgEv::PropDef> props;
    UiMsgEv::PropDef prop;
    prop.m_type = PropDef::Props_Coin;
    prop.m_count = m_coinOnEx;
    props.push_back(prop);
    m_serverIface->salePropAction(m_id,props);
    m_incButton->setCanTouch(false);
    m_decButton->setCanTouch(false);
    m_submitButton->setCanTouch(false);
}
void Coin2GoldDialog::autoIncStep(float dt)
{
    onIncButtonClicked(0,0);
}
void Coin2GoldDialog::autoDecStep(float dt)
{
    onDecButtonClicked(0,0);
}
void Coin2GoldDialog::onIncTouchBegin(CCNode *node,void *data)
{
    this->schedule(schedule_selector(Coin2GoldDialog::autoIncStep),0.2);
}
void Coin2GoldDialog::onIncTouchEnd(CCNode *node,void *data)
{
    this->unschedule(schedule_selector(Coin2GoldDialog::autoIncStep));
}
void Coin2GoldDialog::onDecTouchBegin(CCNode *node,void *data)
{
    this->schedule(schedule_selector(Coin2GoldDialog::autoDecStep),0.2);
}
void Coin2GoldDialog::onDecTouchEnd(CCNode *node,void *data)
{
    this->unschedule(schedule_selector(Coin2GoldDialog::autoDecStep));
}
