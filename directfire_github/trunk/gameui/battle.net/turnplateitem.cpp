#include "turnplateitem.h"

#include "gamecore/resource/resourcemgr.h"

#include "gamecore/sounds/soundmgr.h"

#include "prop/propdef.h"

TurnPlateItem::TurnPlateItem(SocialPage *owner)
    : BasSocialItem(owner)
{
    m_itemInit = false;
    m_itemlogo = 0;
    m_handSprite = 0;
    m_plateSprite = 0;
    m_frameSprite = 0;
    m_handDele = 0;
    m_plateDele = 0;
    m_frameDele = 0;
    m_turnDialog = 0;
//    m_busyAnim = 0;
//    m_isBusy = false;
}
TurnPlateItem::~TurnPlateItem()
{

}
void TurnPlateItem::moveInItem()
{
    if(!m_itemInit)
        init();
}
void TurnPlateItem::moveOutItem()
{

}
void TurnPlateItem::usePropReplyGot()
{
    //send gain prop
    if(m_turnDialog)
        m_turnDialog->usePropReplyGot();
}
void TurnPlateItem::onFrameClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_plateSprite->setRotation(0);
    m_frameSprite->setRotation(0);

    CCActionInterval *action1 = CCRotateTo::create(2,720);
    m_plateSprite->runAction(action1);
    CCActionInterval *action2 = CCRotateTo::create(3,-720);
    m_frameSprite->runAction(action2);

    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    m_turnDialog = new TurnPlateDialog(root,ccc4(0,0,0,128));
    m_turnDialog->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
    m_turnDialog->setCloseCB(this,callfuncND_selector(TurnPlateItem::onTurnDialogCloseClicked));

    std::vector<std::string> props;
    std::vector<int> payrate;
    if(1){
        //init turn plate
        int start = PropDef::Props_Gold;
        int end = PropDef::Props_Crystal2;
        std::string imgName;
        for(int i = 0;i < 15;i++){
            int randp = start + rand() % (end - start);
            int randpay = rand() % 99;
            PropDef::getVirtualPropsName(randp,imgName);
            imgName += ".png";
            props.push_back(imgName);
            payrate.push_back(randpay);
        }
        for(int i = 0;i < 8;i++){
            int index = rand() % 14;
            payrate[index] = 0;
        }
        m_turnDialog->setPropPayInfo(props,payrate);
        std::string goldName;
        PropDef::getVirtualPropsName(PropDef::Props_Gold,goldName);
        goldName += ".png";
        m_turnDialog->setGlodInfo(goldName,num);
    }
    m_turnDialog->exec();
}
void TurnPlateItem::onTurnDialogCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_turnDialog->destroy();
    m_turnDialog = 0;
}
void TurnPlateItem::init(int dummy)
{
    if(m_itemInit)
        return;
    m_serverIface = ServerInterface::getInstance();
    if(1){
        //item logo
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("turnplatelogo.png");
        m_itemlogo = new FSizeCCNodeDelegate(sprite,CCSizeMake(80,80));
        this->addChild(m_itemlogo);
        m_itemlogo->setLeft("parent",uilib::Left);
        m_itemlogo->setTop("parent",uilib::Top);
        m_itemlogo->setTopMargin(25);
        m_itemlogo->setLeftMargin(20);
    }
    if(1){
        //turn plate show
        float height = m_anchorHeight * 0.8;
        m_frameSprite = CCSprite::createWithSpriteFrameName("plateframe.png");
        m_plateSprite = CCSprite::createWithSpriteFrameName("platebg.png");
        m_handSprite = CCSprite::createWithSpriteFrameName("platehand.png");

        float rate = height / m_frameSprite->getContentSize().height;

        CCSize size;
        size = m_frameSprite->getContentSize();
        m_frameDele = new FSizeCCNodeDelegate(m_frameSprite,CCSizeMake(size.width * rate,size.height * rate));

        size = m_plateSprite->getContentSize();
        m_plateDele = new FSizeCCNodeDelegate(m_plateSprite,CCSizeMake(size.width * rate,size.height * rate));

        size = m_handSprite->getContentSize();
        m_handDele = new FSizeCCNodeDelegate(m_handSprite,CCSizeMake(size.width * rate,size.height * rate));

        this->addChild(m_frameDele);
        this->addChild(m_plateDele);
        this->addChild(m_handDele);

        m_frameDele->setCenterIn("parent");
        m_plateDele->setCenterIn("parent");
        m_handDele->setCenterIn("parent");

        m_frameDele->setCanTouch(true);
        m_frameDele->setClickCB(this,callfuncND_selector(TurnPlateItem::onFrameClicked));
    }
    m_itemInit = true;
    this->layout(true);
}
