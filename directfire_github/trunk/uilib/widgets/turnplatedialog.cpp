#include "turnplatedialog.h"
#include "cliententry/cliententry.h"
#include "prop/propdef.h"

namespace uilib
{
TurnPlateNodeDelegate::TurnPlateNodeDelegate(TurnPlateDialog *owner,CCNode *node,const CCSize &size)
    : FSizeCCNodeDelegate(node,size)
{
    m_owner = owner;
}
TurnPlateNodeDelegate::~TurnPlateNodeDelegate()
{

}
void TurnPlateNodeDelegate::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    m_pressEvent = pTouch->getLocationInView();
    FSizeCCNodeDelegate::touchPressEvent(pTouch,pEvent);
}
void TurnPlateNodeDelegate::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    m_releaseEvent = pTouch->getLocationInView();
    m_owner->setForce(ccpDistance(m_pressEvent,m_releaseEvent));
    FSizeCCNodeDelegate::touchReleaseEvent(pTouch,pEvent);
}

TurnPlateDialog::TurnPlateDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_plateGridNum = 15;
    m_plateSpeed = 0;
    m_frameSpeed = 0;
    m_handString = "platehand.png";
    m_plateString = "platebg.png";
    m_frameString = "plateframe.png";
    m_inString = "turnindicator.png";
    m_force = 50;
    m_goldNum = 0;
    m_betNumSprite = 0;
    m_incButton = 0;
    m_decButton = 0;
    m_betMinNum = 100;
    m_betMaxNum = 1000;
    m_betOnNum = 0;
    m_wonShowSprite = 0;
    m_usePropGot = false;
}
TurnPlateDialog::~TurnPlateDialog()
{

}
void TurnPlateDialog::exec()
{
    finish();
    initPlateProps();
    initGoldInfo();
    initBetInfo();
    BasShowDialog::exec();
}
void TurnPlateDialog::setPlateInfo(const std::string &hand,const std::string &plate,const std::string &frame,const std::string &ind)
{
    m_handString = hand;
    m_plateString = plate;
    m_frameString = frame;
    m_inString = ind;
}
void TurnPlateDialog::setPropPayInfo(const std::vector<std::string> &props,const std::vector<int> &payrate)
{
    m_props = props;
    m_payRate = payrate;
}
void TurnPlateDialog::setForce(float force)
{
    m_force = force;
}
void TurnPlateDialog::setGlodInfo(const std::string &img,int num)
{
    m_goldImg = img;
    m_goldNum = num;
}
void TurnPlateDialog::setBetMinMax(int min,int max)
{
    m_betMinNum = min;
    m_betMaxNum = max;
}    
void TurnPlateDialog::usePropReplyGot()
{
    m_usePropGot = true;
    if(m_frameFinished && m_plateFinished)
        calculateResult();
}
void TurnPlateDialog::finish()
{
    float srate = CCDirector::sharedDirector()->getWinSize().height / 1280.0 - 0.1;
    //turn plate show
    m_frameSprite = CCSprite::createWithSpriteFrameName(m_frameString.data());
    m_plateSprite = CCSprite::createWithSpriteFrameName(m_plateString.data());
    m_handSprite = CCSprite::createWithSpriteFrameName(m_handString.data());
    m_inSprite = CCSprite::createWithSpriteFrameName(m_inString.data());
    m_inSprite->setVisible(false);

    CCSize size = m_frameSprite->getContentSize();
    m_frameDele = new TurnPlateNodeDelegate(this,m_frameSprite,CCSizeMake(srate * size.width,srate * size.height));
    size = m_plateSprite->getContentSize();
    m_plateDele = new FSizeCCNodeDelegate(m_plateSprite,CCSizeMake(srate * size.width,srate * size.height));
    size = m_handSprite->getContentSize();
    m_handDele = new FSizeCCNodeDelegate(m_handSprite,CCSizeMake(srate * size.width,srate * size.height));
    m_inDele = new FSizeCCNodeDelegate(m_inSprite);

    this->addChild(m_frameDele);
    this->addChild(m_plateDele);
    this->addChild(m_handDele);
    this->addChild(m_inDele);

    m_frameDele->setCenterIn("parent");
    m_plateDele->setCenterIn("parent");
    m_handDele->setCenterIn("parent");
    m_inDele->setCenterIn("parent");

    m_frameDele->setClickCB(this,callfuncND_selector(TurnPlateDialog::onFrameClicked));
}
void TurnPlateDialog::initPlateProps()
{
    if(m_plateGridNum != m_props.size())
        return;
    CCSize psize = m_plateSprite->getContentSize();
    float pradius = psize.width / 2;
    float propradius = pradius * 7 / 8;
    float payradius = pradius * 5 / 8;
    float width = pradius * 0.25;
    float height = width;
    std::stringstream ss;
    for(int i = 0;i < m_plateGridNum;i++){
        CCSprite *prop = CCSprite::createWithSpriteFrameName(m_props.at(i).data());
        CCSize size = prop->getContentSize();
        prop->setScaleX(width / size.width);
        prop->setScaleY(height / size.height);
        m_plateSprite->addChild(prop);

        float degree = 360 * (2 * i + 1) / (m_plateGridNum * 2);
        float radius = CC_DEGREES_TO_RADIANS(degree);
        prop->setRotation(degree + 90);
        prop->setAnchorPoint(ccp(0.5,0.5));
        prop->setPosition(ccp(pradius + propradius * cos(radius),
                              pradius + propradius * -sin(radius)));

        ss << m_payRate.at(i);
        CCLabelBMFont *num = CCLabelBMFont::create(ss.str().data(),"fonts/uifont35.fnt");
        m_plateSprite->addChild(num);
        num->setRotation(degree + 90);
        num->setAnchorPoint(ccp(0.5,0.5));
        num->setPosition(ccp(pradius + payradius * cos(radius),
                              pradius + payradius * -sin(radius)));
        ss.str("");
    }
}
void TurnPlateDialog::initGoldInfo()
{
    if(m_goldImg.empty())
        return;
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(m_goldImg.data());
    FSizeCCNodeDelegate *goldDele = new FSizeCCNodeDelegate(sprite);
    this->addChild(goldDele);
    goldDele->setLeft("parent",uilib::Left);
    goldDele->setTop("parent",uilib::Top);
    goldDele->setLeftMargin(5);
    goldDele->setTopMargin(5);

    std::stringstream ss;
    ss << "x" << m_goldNum;
    m_goldSprite = CCLabelBMFont::create(ss.str().data(),"fonts/font30.fnt");
    FSizeCCNodeDelegate *numDele = new FSizeCCNodeDelegate(m_goldSprite);
    this->addChild(numDele);
    numDele->setLeft(goldDele->getName(),uilib::Right);
    numDele->setLeftMargin(5);
    numDele->setVertical(goldDele->getName(),0.5);
}
void TurnPlateDialog::initBetInfo()
{
    std::stringstream ss;
    ss << "x" << m_betMaxNum;
    m_betNumSprite = CCLabelBMFont::create(ss.str().data(),"fonts/font30.fnt");
    CCSize betNumSize = m_betNumSprite->getContentSize();

    BasNodeLimitWidget *coinBgDele = new BasNodeLimitWidget(m_betNumSprite,betNumSize);
    this->addChild(coinBgDele);
    coinBgDele->setHorizontal("parent",0.5);
    coinBgDele->setTop(m_frameDele->getName(),uilib::Bottom);
    coinBgDele->setBottom("parent",uilib::Bottom);
    coinBgDele->setWidth(betNumSize.width);
    m_betNumSprite->setString("x0");

    m_incButton = new BasButton;
    m_incButton->setButtonInfo("","default","turnplate_inc",CCSizeMake(0,0));
    m_incButton->setClickCB(this,callfuncND_selector(TurnPlateDialog::onIncClicked));
    this->addChild(m_incButton);
    m_incButton->setVertical(coinBgDele->getName(),0.5);
    m_incButton->setLeft(coinBgDele->getName(),uilib::Right);
    m_incButton->setLeftMargin(2);

    m_decButton = new BasButton;
    m_decButton->setButtonInfo("","default","turnplate_dec",CCSizeMake(0,0));
    m_decButton->setClickCB(this,callfuncND_selector(TurnPlateDialog::onDecClicked));
    this->addChild(m_decButton);
    m_decButton->setVertical(coinBgDele->getName(),0.5);
    m_decButton->setRight(coinBgDele->getName(),uilib::Left);
    m_decButton->setRightMargin(2);
}
void TurnPlateDialog::startIndicator()
{
    m_inSprite->stopAllActions();
    m_inSprite->setRotation(0);
    m_inSprite->setVisible(true);
    CCActionInterval *rot = CCRotateTo::create(1,360 * 2);
    CCActionInterval *fade = CCFadeOut::create(1.0);
    m_inSprite->runAction(CCSequence::create(CCSpawn::create(rot,fade,0),
                                             CCCallFuncND::create(this,callfuncND_selector(TurnPlateDialog::onFrameIndicatorFinished),0),0));
}
void TurnPlateDialog::onFrameClicked()
{
    float timemin = 4;
    float timemax = 7;
    float loopmin = 4;
    float loopmax = 7;
    float time,loop;
    if(m_betOnNum < m_betMinNum)
        return;
    // send used gold action
    std::vector<UiMsgEv::PropDef> useProps;
    UiMsgEv::PropDef usedGold;
    usedGold.m_type = PropDef::Props_Gold;
    usedGold.m_count = m_betOnNum;
    useProps.push_back(usedGold);
    const std::string &id = ClientEntryProxy::getInstance()->getClientEntry()->getLoginAccountInfo()->m_id;
    // 5: social turnplate.
    ClientEntryProxy::getInstance()->getClientEntry()->usePropAction(id,5,useProps);
    
    m_decButton->setCanTouch(false);
    m_incButton->setCanTouch(false);
    if(m_force < 100) m_force = 100;
    if(m_force > 400) m_force = 400;
    time = timemin + (timemax - timemin) * (m_force - 10) / (400 - 10);
    loop = loopmin + (loopmax - loopmin) * (m_force - 10) / (400 - 10);
    m_plateSprite->setRotation(rand() % 360);
    m_frameSprite->setRotation(rand() % 360);

    CCActionInterval *action1 = CCRotateBy::create(time,720*loop);
    CCActionInterval *plateAction =
            (CCActionInterval*)CCSequence::create(action1,
            CCCallFuncND::create(this,callfuncND_selector(TurnPlateDialog::onPlateActionFinished),0),0);

    m_plateSpeed = CCEaseExponentialOut::create(plateAction);
    m_plateSprite->runAction(m_plateSpeed);
    
    CCActionInterval *action2 = CCRotateBy::create(time,-720*loop);
    CCActionInterval *frameAction =
            (CCActionInterval*)CCSequence::create(action2,
            CCCallFuncND::create(this,callfuncND_selector(TurnPlateDialog::onFrameActionFinished),0),0);

    m_frameSpeed = CCEaseExponentialOut::create(frameAction);
    m_frameSprite->runAction(m_frameSpeed);

    m_handSprite->setRotation(0);
    m_handSprite->runAction(CCRotateTo::create(1,720));
    m_frameDele->setCanTouch(false);
    m_plateFinished = false;
    m_frameFinished = false;
    m_usePropGot = false;
}
void TurnPlateDialog::onPlateActionFinished(CCNode *node,void *data)
{
    m_plateFinished = true;
    if(m_frameFinished && m_usePropGot)
        calculateResult();
}
void TurnPlateDialog::onFrameActionFinished(CCNode *node,void *data)
{
    m_frameFinished = true;
    if(m_plateFinished && m_usePropGot)
        calculateResult();
}
void TurnPlateDialog::onFrameIndicatorFinished(CCNode *node,void *data)
{
    m_frameDele->setCanTouch(true);
}
void TurnPlateDialog::calculateResult()
{
    float rotation = m_plateSprite->getRotation();
    rotation = (int)rotation % 360;
    while(rotation > 360.0)
        rotation -= 360.0;
    while(rotation < 0)
        rotation += 360.0;
    float angle = 360.0 / m_plateGridNum;
    int index = floor((270.0 - rotation) / angle);
    if(index < 0)
        index += m_plateGridNum;
    if(index > m_plateGridNum)
        index -= m_plateGridNum;
    int num = m_payRate[index];
    if(num != 0){
        std::string wonname = m_props[index];
        float rate = m_betOnNum * 1.0 / m_betMinNum;
        showBetResult(wonname,num,round(rate));
        // send gain prop action
        UiMsgEv::PropDef got;
        got.m_type = PropDef::getVirtualPropsId(wonname.substr(0,wonname.size() - 4));
        got.m_count = num * rate;
        std::vector<UiMsgEv::PropDef> gotProps;
        gotProps.push_back(got);
        const std::string &id = ClientEntryProxy::getInstance()->getClientEntry()->getLoginAccountInfo()->m_id;
        // 5: social turnplate.
        ClientEntryProxy::getInstance()->getClientEntry()->gainPropAction(id,5,gotProps);
    }
    m_betOnNum = 0;
    m_betNumSprite->setString("x0");
    m_decButton->setCanTouch(true);
    m_incButton->setCanTouch(true);
}
void TurnPlateDialog::sendBetResult()
{

}
void TurnPlateDialog::showBetResult(const std::string &img,int num,int rate)
{
    std::stringstream ss;
    m_wonShowSprite = new CCNode;
    CCSprite *imgSprite = CCSprite::createWithSpriteFrameName(img.data());
    CCSize imgSize = imgSprite->getContentSize();
    ss << "x" << num << " x" << rate;
    CCLabelBMFont *numSprite = CCLabelBMFont::create(ss.str().data(),"fonts/font20.fnt");
    CCSize numSize = numSprite->getContentSize();

    CCSize size;
    size.height = MAX(imgSize.height,numSize.height);
    size.width = imgSize.width + numSize.width;
    m_wonShowSprite->setContentSize(size);

    m_wonShowSprite->addChild(imgSprite);
    m_wonShowSprite->addChild(numSprite);

    imgSprite->setAnchorPoint(ccp(0,1.0));
    imgSprite->setPosition(ccp(0,size.height));
    numSprite->setAnchorPoint(ccp(1.0,0.5));
    numSprite->setPosition(ccp(size.width,size.height / 2));

    this->CCNode::addChild(m_wonShowSprite,10);
    m_wonShowSprite->setAnchorPoint(ccp(0.5,0.5));
    m_wonShowSprite->setPosition(ccp(m_anchorWidth / 2,m_anchorHeight / 2));

    m_wonShowSprite->runAction(CCSequence::create(CCScaleTo::create(0.5,4),CCDelayTime::create(0.2),
                                             CCCallFuncND::create(this,callfuncND_selector(TurnPlateDialog::onShowResultFinished),0),0));
}
void TurnPlateDialog::onShowResultFinished(CCNode *node,void *data)
{
    m_wonShowSprite->removeFromParentAndCleanup(true);
    m_wonShowSprite = 0;
}
void TurnPlateDialog::onIncClicked(CCNode *node,void *data)
{
    std::stringstream ss;
    if(m_betOnNum >= m_betMaxNum)
        return;
    if(m_goldNum >= m_betMinNum){
        m_betOnNum += m_betMinNum;
        ss << "x" << m_betOnNum;
        m_betNumSprite->setString(ss.str().data());
        m_goldNum -= m_betMinNum;
        ss.str("");
        ss << "x" << m_goldNum;
        m_goldSprite->setString(ss.str().data());
    }else{
        m_betOnNum += m_goldNum;
        ss << "x" << m_betOnNum;
        m_betNumSprite->setString(ss.str().data());
        m_goldNum = 0;
        ss.str("");
        ss << "x" << m_goldNum;
        m_goldSprite->setString(ss.str().data());
    }
    m_frameDele->setCanTouch(false);
    if(m_betOnNum >= m_betMinNum)
        startIndicator();
}
void TurnPlateDialog::onDecClicked(CCNode *node,void *data)
{
    std::stringstream ss;
    if(m_betOnNum == 0)
        return;
    if(m_betOnNum >= m_betMinNum){
        m_betOnNum -= m_betMinNum;
        ss << "x" << m_betOnNum;
        m_betNumSprite->setString(ss.str().data());
        m_goldNum += m_betMinNum;
        ss.str("");
        ss << "x" << m_goldNum;
        m_goldSprite->setString(ss.str().data());
    }else{
        m_goldNum += m_betOnNum;
        m_betOnNum = 0;
        ss << "x" << m_betOnNum;
        m_betNumSprite->setString(ss.str().data());
        ss.str("");
        ss << "x" << m_goldNum;
        m_goldSprite->setString(ss.str().data());
    }
    m_frameDele->setCanTouch(false);
    if(m_betOnNum >= m_betMinNum)
        startIndicator();
}
}
