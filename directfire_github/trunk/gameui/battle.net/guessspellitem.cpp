#include "guessspellitem.h"
#include "waitingmoreitem.h"
#include "gamecore/resource/resourcemgr.h"

#include "prop/propdef.h"

#include "cliententry/uimsgevent.h"

#include "gamecore/serverinterface.h"
#include "gamecore/sounds/soundmgr.h"

GuessSpellItem::GuessSpellItem(SocialPage *owner)
    : BasSocialItem(owner)
{
    m_itemInited = false;
    m_anim = 0;
    m_selIcon = 0;
    m_selDele = 0;
    m_posDele = 0;
    m_isGuessing = false;
    m_won = false;
    m_timePool = 0;
    m_interval = 50;
    m_countDowner = 0;

    m_giftType = PropDef::Props_Gold;
    m_giftCount = 200;
    m_showNode = 0;
}
GuessSpellItem::~GuessSpellItem()
{

}
void GuessSpellItem::moveInItem()
{

}
void GuessSpellItem::moveOutItem()
{

}
void GuessSpellItem::onCardClicked(CCNode *node,void *data)
{
    if(!m_isGuessing)
        return;
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    FSizeCCNodeDelegate *click = dynamic_cast<FSizeCCNodeDelegate*>(node);
    if(click == 0)
        return;
    CardSprite *card = (CardSprite*)click->getNode();
    card->setVertexZ(m_anchorWidth / 10);
    card->openCard();
    int num = click->getTag();
    if(num == m_selectNum){
        //success
        m_won = true;
        sendGift();
    }else{
        //failed
        m_won = false;
        startTimePool();
    }
    m_isGuessing = false;
}
void GuessSpellItem::onSpellClicked(CCNode *node,void *data)
{
    if(!m_isGuessing)
        timePool(1.0);
}
void GuessSpellItem::onFlipFinished(CCNode *node,void *data)
{
    CardSprite *card = (CardSprite*)node;
    card->setVertexZ(0);
    if(m_won){
        const std::vector<std::string> &props = ResourceMgr::getInstance()->propsNames();
        std::string anim,first;
        anim = props[m_selectNum];
        anim += "exec";
        first = anim;
        ResourceMgr::getInstance()->getFrameSpriteFirstFrame(first);
        m_anim = new BasAnimSprite(anim,first);
        if(m_anim->isLoaded()){
            m_anim->setAnimFinishCB(this,callfuncND_selector(GuessSpellItem::onAnimFinished));
            CCSprite *front = card->frontSprite();
            CCSize size = front->getContentSize();
            front->addChild(m_anim);
            m_anim->setAnchorPoint(ccp(0.5,0.5));
            m_anim->setPosition(ccp(size.width/2,size.height/2));
            m_anim->playInLoop(1);
            CCSize animSize = m_anim->getContentSize();
            m_anim->setScale(size.width / animSize.width);
            m_won = false;
        }else{
            delete m_anim;
            m_anim = 0;
        }
    }
}
void GuessSpellItem::onAnimFinished(CCNode *node,void *data)
{
    if(m_anim){
        m_anim->removeFromParentAndCleanup(true);
        m_anim = 0;
        startTimePool();
    }
}
void GuessSpellItem::closeAllCard()
{
    for(unsigned int i = 0;i < m_cards.size();i++){
        CardSprite *card = (CardSprite*)m_cards[i]->getNode();
        if(!card->isClosed()){
            card->setVertexZ(m_anchorWidth / 10);
            card->closeCard();
        }
    }
}
void GuessSpellItem::layoutCompleted()
{
    BasSocialItem::layoutCompleted();
    if(!m_itemInited){
        init();
    }
}
void GuessSpellItem::timePool(float dt)
{
    m_timePool -= 1;
    if(m_timePool <= 0){
        endTimePool();
        m_timePool = 0;
        resetGuess();
    }else{
        std::stringstream ss;
        ss << "Time:" << m_timePool;
        m_countDowner->setString(ss.str().data());
    }
}
void GuessSpellItem::startTimePool()
{
    m_timePool = m_interval + 1;
    timePool(1.0);
    m_countDowner->setVisible(true);
    this->schedule(schedule_selector(GuessSpellItem::timePool),1.0);
}
void GuessSpellItem::endTimePool()
{
    m_countDowner->setVisible(false);
    this->unschedule(schedule_selector(GuessSpellItem::timePool));
}
void GuessSpellItem::resetGuess()
{
    closeAllCard();

    const std::vector<std::string> props = ResourceMgr::getInstance()->propsNames();
    m_selectNum = rand() % props.size();
    std::vector<int> runNums;
    runNums.push_back(rand() % props.size());
    runNums.push_back(rand() % props.size());
    runNums.push_back(rand() % props.size());
    runNums[rand() % runNums.size()] = m_selectNum;
    if(1){
        std::string icon = props[m_selectNum];
        icon += ".png";
        m_selIcon->initWithSpriteFrameName(icon.data());
    }
    for(unsigned int i = 0;i < runNums.size();i++){
        m_cards[i]->setTag(runNums[i]);
    }
    m_isGuessing = true;
}
void GuessSpellItem::sendGift()
{
    ServerInterface *server = ServerInterface::getInstance();
    std::string uid = server->getLoginAccountInfo()->m_id;
    std::vector<UiMsgEv::PropDef> props;
    props.push_back(UiMsgEv::PropDef(m_giftType,m_giftCount));
    // 3: social guess.
    server->gainPropAction(uid,3,props);
    showGift();
}
void GuessSpellItem::showGift()
{
    m_showNode = CCNode::create();
    std::string imgName;
    PropDef::getVirtualPropsName(m_giftType,imgName);
    imgName += ".png";
    CCSprite *giftSprite = CCSprite::createWithSpriteFrameName(imgName.data());
    std::stringstream ss;
    ss << "x" << m_giftCount;
    CCLabelBMFont *giftNum = CCLabelBMFont::create(ss.str().data(),"fonts/font20.fnt");
    CCSize giftSize = giftSprite->getContentSize();
    CCSize numSize = giftNum->getContentSize();
    CCSize size = CCSizeMake(MAX(giftSize.width,numSize.width),giftSize.height + numSize.height);
    m_showNode->setContentSize(size);
    m_showNode->addChild(giftSprite);
    m_showNode->addChild(giftNum);
    giftSprite->setAnchorPoint(ccp(0,1.0));
    giftSprite->setPosition(ccp(0,size.height));
    giftNum->setAnchorPoint(ccp(0.5,0));
    giftNum->setPosition(ccp(size.width/2,0));
    this->CCNode::addChild(m_showNode,100);
    m_showNode->setAnchorPoint(ccp(0.5,0.5));
    m_showNode->setPosition(ccp(m_anchorWidth/2,m_anchorHeight/2));
    m_showNode->setVisible(true);
    m_showNode->runAction(CCSequence::create(CCScaleTo::create(0.5,10),
                                             CCCallFuncN::create(this,callfuncN_selector(GuessSpellItem::onShowGiftFinished)),0));
}
void GuessSpellItem::onShowGiftFinished(CCNode *node)
{
    m_showNode->removeFromParentAndCleanup(true);
    m_showNode = 0;
}
void GuessSpellItem::setSendGift(int type,int count)
{
    m_giftType = type;
    m_giftCount = count;
}
void GuessSpellItem::init(int dummy)
{
    if(m_itemInited)
        return;
    float srate = CCDirector::sharedDirector()->getWinSize().height / 1280.0;
    if(1){
        float height = m_anchorHeight * 0.75;
        float width = m_anchorWidth / 5;

        const std::vector<std::string> props = ResourceMgr::getInstance()->propsNames();
        m_selectNum = rand() % props.size();
        std::vector<int> runNums;
        runNums.push_back(rand() % props.size());
        runNums.push_back(rand() % props.size());
        runNums.push_back(rand() % props.size());
        runNums[rand() % runNums.size()] = m_selectNum;

        if(1){
            //selected spell position
            CCSprite *posSprite = CCSprite::createWithSpriteFrameName("guessspellpos.png");
            CCSize posSize = posSprite->getContentSize();
            m_posDele = new BasNodeDelegateWidget(posSprite,CCSizeMake(posSize.width * srate,posSize.height * srate));
            this->addChild(m_posDele);
            m_posDele->setTop("parent",uilib::Top);
            m_posDele->setLeft("parent",uilib::Left);
            m_posDele->setTopMargin(25);
            m_posDele->setLeftMargin(25);

            std::string icon = props[m_selectNum];
            icon += ".png";
            m_selIcon = CCSprite::createWithSpriteFrameName(icon.data());
            m_selDele = new FSizeCCNodeDelegate(m_selIcon,CCSizeMake(60,60));
            m_selDele->setCanTouch(true);
            m_selDele->setClickCB(this,callfuncND_selector(GuessSpellItem::onSpellClicked));
            m_posDele->addChild(m_selDele);
            m_selDele->setCenterIn("parent");
        }
        for(unsigned int i = 0;i < runNums.size();i++){
            CardSprite *card = new CardSprite(CCSizeMake(width,height),0.5);
            card->setFlipListener(this,callfuncND_selector(GuessSpellItem::onFlipFinished));
            card->setCards("cardfg.png","cardbg.png");
            FSizeCCNodeDelegate *dele = new FSizeCCNodeDelegate(card,CCSizeMake(width,height));
            dele->setCanTouch(true);
            dele->setTag(runNums[i]);
            dele->setClickCB(this,callfuncND_selector(GuessSpellItem::onCardClicked));
            m_cards.push_back(dele);
            this->addChild(dele);
        }
        FSizeCCNodeDelegate *mid = m_cards[1];
        FSizeCCNodeDelegate *left = m_cards[0];
        FSizeCCNodeDelegate *right = m_cards[2];
        mid->setCenterIn("parent");
        left->setRight(mid->getName(),uilib::Left);
        left->setRightMargin(10);
        left->setVertical("parent",0.5);

        right->setLeft(mid->getName(),uilib::Right);
        right->setLeftMargin(10);
        right->setVertical("parent",0.5);

        m_isGuessing = true;
    }
    if(1){
        //count downer
        std::stringstream ss;
        ss << "Time:" << m_interval;
        m_countDowner = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
        m_countDowner->setVisible(false);
        FSizeCCNodeDelegate *dele = new FSizeCCNodeDelegate(m_countDowner);
        this->addChild(dele);
        dele->setTop(m_posDele->getName(),uilib::Bottom);
        dele->setTopMargin(10);
        dele->setHorizontal(m_posDele->getName(),0.5);
    }
    m_itemInited = true;
}
