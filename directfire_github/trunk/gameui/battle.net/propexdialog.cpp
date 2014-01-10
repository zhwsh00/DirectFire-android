#include "propexdialog.h"

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"

PropExDialog::PropExDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_serverIface = ServerInterface::getInstance();
    m_propRules = m_serverIface->getPropExchangeRule();
    m_scrollWidget = 0;
    m_confirmButton = 0;
    m_goldImgDele = 0;
    m_autoStepIndex = -1;
    m_isBusy = false;
    m_busyAnim = 0;
    m_edgeSize = 10;
}
PropExDialog::~PropExDialog()
{

}
void PropExDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void PropExDialog::exchangeReply(bool succ)
{
    m_isBusy = false;
    m_busyAnim->setVisible(false);
    m_busyAnim->end();
    if(succ){
        for(unsigned int i = 0;i < m_goldExOn.size();i++){
            m_goldExOn[i] = 0;
        }
        for(unsigned int i = 0;i < m_propExLabel.size();i++){
            if(m_propExLabel[i])
                m_propExLabel[i]->setString("0x");
        }
    }else{
        new SplashMessageWidget(this,ResourceMgr::getInstance()->getLangDef()->getStringById(StringEnum::CommWithServerFailed));
    }
}
void PropExDialog::finish()
{
    m_id = m_serverIface->getLoginAccountInfo()->m_id;
    std::stringstream ss;
    if(1){
        //init gold has info
        m_goldHad = m_serverIface->getPropNumByUid(m_id,PropDef::Props_Gold);
        std::string goldImg;
        PropDef::getVirtualPropsName(PropDef::Props_Gold,goldImg);
        goldImg += ".png";
        CCSprite *goldSprite = CCSprite::createWithSpriteFrameName(goldImg.data());
        m_goldImgDele = new FSizeCCNodeDelegate(goldSprite);
        this->addChild(m_goldImgDele);
        m_goldImgDele->setLeft("parent",uilib::Left);
        m_goldImgDele->setTop("parent",uilib::Top);
        m_goldImgDele->setLeftMargin(m_edgeSize);
        m_goldImgDele->setTopMargin(m_edgeSize);

        ss.str("");ss << "x" << m_goldHad;
        m_goldSprite = CCLabelBMFont::create(ss.str().data(),"fonts/font30.fnt");
        FSizeCCNodeDelegate *numDele = new FSizeCCNodeDelegate(m_goldSprite);
        this->addChild(numDele);
        numDele->setLeft(m_goldImgDele->getName(),uilib::Right);
        numDele->setLeftMargin(2);
        numDele->setVertical(m_goldImgDele->getName(),0.5);
    }
    if(1){
        //init confirmbutton
        LangDef *lang = ResourceMgr::getInstance()->getLangDef();
        m_confirmButton = new BasButton();
        m_confirmButton->setButtonInfo(lang->getStringById(StringEnum::BuyInto),"default","buttonbg",CCSizeMake(0,0),"",getSystemFont(),24,ccWHITE);
        m_confirmButton->setClickCB(this,callfuncND_selector(PropExDialog::onSubmitButtonClicked));
        m_confirmButton->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
        this->addChild(m_confirmButton);
        m_confirmButton->setHorizontal("parent",0.5);
        m_confirmButton->setBottom("parent",uilib::Bottom);
        m_confirmButton->setBottomMargin(m_edgeSize);
    }
    if(1){
        //init scroll widget
        m_scrollWidget = new VerScrollWidget;
        m_scrollWidget->setVerticalScrollPolicy(uilib::ScrollShow_Need);
        m_scrollWidget->setHorizontalScrollPolicy(uilib::ScrollShow_Never);

        this->addChild(m_scrollWidget);
        m_scrollWidget->setLeft("parent",uilib::Left);
        m_scrollWidget->setRight("parent",uilib::Right);
        m_scrollWidget->setTop(m_goldImgDele->getName(),uilib::Bottom);
        m_scrollWidget->setBottom(m_confirmButton->getName(),uilib::Top);
        m_scrollWidget->setBottomMargin(8);
        m_scrollWidget->setLeftMargin(m_edgeSize);
        m_scrollWidget->setRightMargin(m_edgeSize);
        int ruleCount = m_propRules->size();
        float width = m_anchorWidth - m_edgeSize * 4;
        std::stringstream ss;
        std::string imgName;
        for(int i = 0;i < ruleCount;i++){
            const UiMsgEv::PropExchangeRule &rule = m_propRules->at(i);
            if(rule.m_propType == PropDef::Props_Coin){
                m_goldExOn.push_back(0);
                m_propExLabel.push_back(0);
                continue;
            }
            BorderWidget *border = new BorderWidget;
            border->setTheme("default","propbg");
            border->setWidth(width);
            border->setHeight(100);
            FSizeWidgetDelegate *dele = new FSizeWidgetDelegate(border,CCSizeMake(width,100));
            m_scrollWidget->addFixedSizeWidget(dele);

            imgName = rule.m_priceName + ".png";
            CCSprite *priceSprite = CCSprite::createWithSpriteFrameName(imgName.data());
            ss.str("");ss << "x" << rule.m_buyPriceCount;
            CCLabelBMFont *priceNum = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
            CCSize priceSpriteSize = priceSprite->getContentSize();
            CCSize priceNumSize = priceNum->getContentSize();
            CCSize size = CCSizeMake(priceSpriteSize.width + priceNumSize.width,MAX(priceSpriteSize.height,priceNumSize.height));
            CCNode *priceNode = CCNode::create();
            priceNode->addChild(priceSprite);
            priceNode->addChild(priceNum);
            priceNode->setContentSize(size);
            priceSprite->setAnchorPoint(ccp(0,0));
            priceSprite->setPosition(ccp(0,0));
            priceNum->setAnchorPoint(ccp(1.0,0.0));
            priceNum->setPosition(ccp(size.width,0));

            imgName = rule.m_propName + ".png";
            CCSprite *propSprite = CCSprite::createWithSpriteFrameName(imgName.data());

            FSizeCCNodeDelegate *propDele = new FSizeCCNodeDelegate(propSprite);
            border->addChild(propDele);
            propDele->setLeft("parent",uilib::Left);
            propDele->setVertical("parent",0.5);
            propDele->setRightMargin(10);

            FSizeCCNodeDelegate *priceDele = new FSizeCCNodeDelegate(priceNode,CCSizeMake(size.width*0.7,size.height*0.7));
            border->addChild(priceDele);
            priceDele->setLeft(propDele->getName(),uilib::Right);
            priceDele->setTop("parent",uilib::Top);

            BasButton *incButton = new BasButton;
            incButton->setButtonIndex(i);
            incButton->setButtonInfo("","default","uiincrease",CCSizeMake(0,0));
            incButton->setClickCB(this,callfuncND_selector(PropExDialog::onIncButtonClicked));
            border->addChild(incButton);
            incButton->setRight("parent",uilib::Right);
            incButton->setRightMargin(2);
            incButton->setVertical("parent",0.5);
            incButton->setTouchInCB(this,callfuncND_selector(PropExDialog::onIncTouchBegin));
            incButton->setTouchOutCB(this,callfuncND_selector(PropExDialog::onIncTouchEnd));

            ss.str("");ss << "x" << 100;
            CCLabelBMFont *propNumLabel = CCLabelBMFont::create(ss.str().data(),"fonts/font30.fnt");
            FSizeCCNodeDelegate *propNumDele = new FSizeCCNodeDelegate(propNumLabel);
            propNumLabel->setString("x0");
            border->addChild(propNumDele);
            propNumDele->setRight(incButton->getName(),uilib::Left);
            propNumDele->setVertical("parent",0.5);
            m_goldExOn.push_back(0);
            m_propExLabel.push_back(propNumLabel);

            BasButton *decButton = new BasButton;
            decButton->setButtonIndex(i);
            decButton->setButtonInfo("","default","uidecrease",CCSizeMake(0,0));
            decButton->setClickCB(this,callfuncND_selector(PropExDialog::onDecButtonClicked));
            border->addChild(decButton);
            decButton->setRight(propNumDele->getName(),uilib::Left);
            decButton->setVertical("parent",0.5);
            decButton->setTouchInCB(this,callfuncND_selector(PropExDialog::onDecTouchBegin));
            decButton->setTouchOutCB(this,callfuncND_selector(PropExDialog::onDecTouchEnd));
        }
        m_scrollWidget->setSpacing(20);
    }
    if(1){
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
void PropExDialog::onIncButtonClicked(CCNode *node,void *data)
{
    if(m_isBusy)
        return;
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data;
    if(index < 0 || index >= m_propRules->size())
        return;
    const UiMsgEv::PropExchangeRule &rule = m_propRules->at(index);
    int price = rule.m_buyPriceCount;
    if(m_goldHad >= price){
        std::stringstream ss;
        m_goldHad -= price;
        ss << "x" << m_goldHad;
        m_goldSprite->setString(ss.str().data());

        m_goldExOn[index] = m_goldExOn[index] + 1;
        ss.str("");ss << "x" << m_goldExOn[index];
        m_propExLabel[index]->setString(ss.str().data());
    }
}
void PropExDialog::onDecButtonClicked(CCNode *node,void *data)
{
    if(m_isBusy)
        return;
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data;
    if(index < 0 || index >= m_propRules->size())
        return;
    const UiMsgEv::PropExchangeRule &rule = m_propRules->at(index);
    int price = rule.m_buyPriceCount;
    if(m_goldExOn[index] > 0){
        std::stringstream ss;
        m_goldHad += price;
        ss << "x" << m_goldHad;
        m_goldSprite->setString(ss.str().data());

        m_goldExOn[index] = m_goldExOn[index] - 1;
        ss.str("");ss << "x" << m_goldExOn[index];
        m_propExLabel[index]->setString(ss.str().data());
    }
}
void PropExDialog::onSubmitButtonClicked(CCNode *node,void *data)
{
    if(m_isBusy)
        return;
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int gold = m_serverIface->getPropNumByUid(m_id,PropDef::Props_Gold);
    if(gold == m_goldHad)
        return;
    std::vector<UiMsgEv::PropDef> props;
    for(unsigned int i = 0;i < m_goldExOn.size();i++){
        int num = m_goldExOn[i];
        if(num <= 0)
            continue;
        UiMsgEv::PropDef prop;
        prop.m_count = num;
        prop.m_type = m_propRules->at(i).m_propType;
        props.push_back(prop);
    }
    m_serverIface->buyPropAction(m_id,props);
    m_busyAnim->setVisible(true);
    m_busyAnim->playInLoop(-1);
    m_isBusy = true;
}
void PropExDialog::autoIncStep(float dt)
{
    onIncButtonClicked(this,&m_autoStepIndex);
}
void PropExDialog::autoDecStep(float dt)
{
    onDecButtonClicked(this,&m_autoStepIndex);
}
void PropExDialog::onIncTouchBegin(CCNode *node,void *data)
{
    m_autoStepIndex = *(int*)data;
    this->schedule(schedule_selector(PropExDialog::autoIncStep),0.2);
}
void PropExDialog::onIncTouchEnd(CCNode *node,void *data)
{
    this->unschedule(schedule_selector(PropExDialog::autoIncStep));
    m_autoStepIndex = -1;
}
void PropExDialog::onDecTouchBegin(CCNode *node,void *data)
{
    m_autoStepIndex = *(int*)data;
    this->schedule(schedule_selector(PropExDialog::autoDecStep),0.2);
}
void PropExDialog::onDecTouchEnd(CCNode *node,void *data)
{
    this->unschedule(schedule_selector(PropExDialog::autoDecStep));
    m_autoStepIndex = -1;
}