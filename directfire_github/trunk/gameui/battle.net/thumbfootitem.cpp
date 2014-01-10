#include "thumbfootitem.h"
#include "cliententry/uimsgevent.h"

#include "gamecore/serverinterface.h"
#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"

ThumbFootItem::ThumbFootItem(SocialPage *owner)
    : BasSocialItem(owner)
{
    m_itemInit = false;
    m_startButton = 0;
    m_submitButton = 0;
    m_busyNode = 0;
    m_busyAnim = 0;
    m_isWorking = false;
    m_thumbIndex = -1;
    m_footIndex = -1;

    m_giftType = PropDef::Props_Gold;
    m_giftCount = 10;
    m_showNode = 0;
    m_hdDialog = 0;
}
ThumbFootItem::~ThumbFootItem()
{

}
void ThumbFootItem::thumbPortraitUpdate()
{
    if(m_busyNode){
        m_busyNode->setVisible(false);
        m_busyAnim->end();
    }
    showPortraits();
    m_isWorking = true;
    m_thumbIndex = -1;
    m_footIndex = -1;
}
void ThumbFootItem::moveInItem()
{
    if(!m_itemInit)
        init();
}
void ThumbFootItem::moveOutItem()
{

}
void ThumbFootItem::setSendGift(int type,int count)
{
    m_giftType = type;
    m_giftCount = count;
}
void ThumbFootItem::onStartClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_startButton->setVisible(false);
    if(m_busyNode){
        m_busyNode->setVisible(true);
        m_busyAnim->playInLoop(-1);
    }
    //ask data
    loadData();
}
void ThumbFootItem::onSubmitClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    UiMsgEv::ThumbPortrait *ports = ServerInterface::getInstance()->getThumbPortrait();
    if(m_thumbIndex != -1){
        ServerInterface::getInstance()->thumbPlayer(ports->m_ids[m_thumbIndex]);
        m_thumbIndex = -1;
    }
    if(m_footIndex != -1){
        ServerInterface::getInstance()->footPlayer(ports->m_ids[m_footIndex]);
        m_footIndex = -1;
    }
    for(unsigned int i = 0;i < m_portratis.size();i++){
        m_portratis[i]->removeFromParentAndCleanup(true);
    }
    m_portratis.clear();
    m_submitButton->setVisible(false);
    m_startButton->setVisible(true);

    for(unsigned int i = 0;i < m_thumbButtons.size();i++){
        m_thumbButtons[i]->setVisible(false);
        m_footButtons[i]->setVisible(false);
        m_frameBgs[i]->setCanTouch(false);
    }
    m_isWorking = false;
    sendGift();
}
void ThumbFootItem::onThumbClicked(CCNode *node,void *data)
{
    if(m_hdDialog){
        m_hdDialog->destroy();
        m_hdDialog = 0;
    }
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data;
    BasButton *button = m_thumbButtons[index];
    if(m_thumbIndex == index){
        m_thumbIndex = -1;
        showSubmitButton();
        button->setVisible(false);
        return;
    }else if(m_thumbIndex != -1){
        BasButton *orig = m_thumbButtons[m_thumbIndex];
        orig->setVisible(false);
    }
    button->setVisible(true);
    m_thumbIndex = index;
    showSubmitButton();
}
void ThumbFootItem::onFootClicked(CCNode *node,void *data)
{
    if(m_hdDialog){
        m_hdDialog->destroy();
        m_hdDialog = 0;
    }
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data;
    BasButton *button = m_footButtons[index];
    if(m_footIndex == index){
        m_footIndex = -1;
        showSubmitButton();
        button->setVisible(false);
        return;
    }else if(m_footIndex != -1){
        BasButton *orig = m_footButtons[m_footIndex];
        orig->setVisible(false);
    }
    button->setVisible(true);
    m_footIndex = index;
    showSubmitButton();
}
void ThumbFootItem::onHeadClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    TouchNode *touch = (TouchNode*)node;
    const std::string &name = touch->getName();
    int index = -1;
    if(name == "left")
        index = 0;
    else if(name == "mid")
        index = 1;
    else if(name == "right")
        index = 2;
    else
        return;
    UiMsgEv::ThumbPortrait *ports = ServerInterface::getInstance()->getThumbPortrait();
    if(index >= ports->m_ids.size())
        return;
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    m_hdDialog = new BasShowDialog(root,ccc4(0,0,0,128));
    m_hdDialog->setCloseCB(this,callfuncND_selector(ThumbFootItem::onHDCloseChicked));
    m_hdDialog->setTheme("default","dialog");
    if(1){
        CCImage *img = new CCImage;
        img->initWithImageData((void*)ports->m_heads[index].c_str(),ports->m_heads[index].size(),
                               CCImage::kFmtUnKnown);
        CCTexture2D *texture = new CCTexture2D;
        texture->initWithImage(img);
        delete img;
        CCSprite *headSprite = CCSprite::create();
        headSprite->initWithTexture(texture);
        CCSize dialogSize;
        dialogSize.width = m_hdDialog->getWidth();
        dialogSize.height = m_hdDialog->getHeight();
        float width = MIN(dialogSize.width,dialogSize.height) * 2 / 3;
        BorderWidget *puton = new BorderWidget;
        puton->setTheme("default","putonbg");
        puton->setWidth(width);
        puton->setHeight(width);
        m_hdDialog->addChild(puton);
        puton->setHorizontal("parent",0.5);
        puton->setTop("parent",uilib::Top);
        puton->setTopMargin(25);

        FSizeSpriteDelegate *dele = new FSizeSpriteDelegate(headSprite,CCSizeMake(width - 20,width - 20));
        puton->addChild(dele);
        dele->setCenterIn("parent");

        BasButton *thumb = new BasButton;
        thumb->setButtonInfo("","default","thumbbutton",CCSizeMake(0,0));
        m_hdDialog->addChild(thumb);
        thumb->setBottom("parent",uilib::Bottom);
        thumb->setBottomMargin(25);
        thumb->setHorizontal("parent",0.35);
        thumb->setClickCB(this,callfuncND_selector(ThumbFootItem::onThumbClicked));
        thumb->setButtonIndex(index);

        BasButton *foot = new BasButton;
        foot->setButtonInfo("","default","footbutton",CCSizeMake(0,0));
        m_hdDialog->addChild(foot);
        foot->setBottom("parent",uilib::Bottom);
        foot->setBottomMargin(25);
        foot->setHorizontal("parent",0.65);
        foot->setClickCB(this,callfuncND_selector(ThumbFootItem::onFootClicked));
        foot->setButtonIndex(index);
    }
    m_hdDialog->exec();
}
void ThumbFootItem::onHDCloseChicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_hdDialog){
        m_hdDialog->destroy();
        m_hdDialog = 0;
    }
}
void ThumbFootItem::loadData()
{
    ServerInterface::getInstance()->getRandHQPortraits(3);
}
void ThumbFootItem::showPortraits()
{
    float width;
    float height;
    UiMsgEv::ThumbPortrait *ports = ServerInterface::getInstance()->getThumbPortrait();

    for(unsigned int i = 0;i < m_portratis.size();i++){
        m_portratis[i]->removeFromParentAndCleanup(true);
    }
    m_portratis.clear();
    for(unsigned int i = 0;i < ports->m_ids.size();i++){
        BorderWidget *del = m_frameBgs[i];
        del->getAnchorSize(width,height);
        CCImage *img = new CCImage;
        img->initWithImageData((void*)ports->m_heads[i].c_str(),ports->m_heads[i].size(),
                               CCImage::kFmtUnKnown);
        CCTexture2D *texture = new CCTexture2D;
        texture->initWithImage(img);
        delete img;
        CCSprite *headSprite = CCSprite::create();
        headSprite->initWithTexture(texture);
        CCSize size = headSprite->getContentSize();
        headSprite->setScaleX((width - 30) / size.width);
        headSprite->setScaleY((height -30) / size.height);
        m_portratis.push_back(headSprite);

        del->setCanTouch(true);
        del->CCNode::addChild(headSprite,0);
        headSprite->setAnchorPoint(ccp(0.5,0.5));
        headSprite->setPosition(ccp(width/2,height/2));
    }
}
void ThumbFootItem::showSubmitButton()
{
    if(m_thumbIndex != -1 || m_footIndex != -1)
        m_submitButton->setVisible(true);
    else
        m_submitButton->setVisible(false);
}
void ThumbFootItem::sendGift()
{
    ServerInterface *server = ServerInterface::getInstance();
    std::string uid = server->getLoginAccountInfo()->m_id;
    std::vector<UiMsgEv::PropDef> props;
    props.push_back(UiMsgEv::PropDef(m_giftType,m_giftCount));
    // 4: social rate portrait.
    server->gainPropAction(uid,4,props);
    showGift();
}
void ThumbFootItem::showGift()
{
    m_showNode = new CCNode;
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
    m_showNode->setScale(1.0);
    m_showNode->setVisible(true);
    m_showNode->runAction(CCSequence::create(CCScaleTo::create(0.5,10),
                                             CCCallFuncN::create(this,callfuncN_selector(ThumbFootItem::onGitShowFinished)),0));
}
void ThumbFootItem::onGitShowFinished(CCNode *node)
{
    m_showNode->removeFromParentAndCleanup(true);
    m_showNode = 0;
}
void ThumbFootItem::init(int dummy)
{
    if(m_itemInit)
        return;
    float width = m_anchorWidth / 5;
    float height = width;
    if(1){
        //head frame bg
        for(int i = 0;i < 3;i++){
            BorderWidget *border = new BorderWidget;
            border->setTheme("default","putonbg");
            border->setWidth(width);
            border->setHeight(height);
            this->addChild(border);
            m_frameBgs.push_back(border);
            border->setClickCB(this,callfuncND_selector(ThumbFootItem::onHeadClicked));
        }
        BorderWidget *mid = m_frameBgs[1];
        BorderWidget *left = m_frameBgs[0];
        BorderWidget *right = m_frameBgs[2];
        mid->setName("mid");
        left->setName("left");
        right->setName("right");
        mid->setVertical("parent",0.5);
        mid->setHorizontal("parent",0.5);
        left->setVertical("parent",0.5);
        left->setRight(mid->getName(),uilib::Left);
        left->setRightMargin(10);
        right->setVertical("parent",0.5);
        right->setLeft(mid->getName(),uilib::Right);
        right->setLeftMargin(10);
    }
    if(1){
        //start button
        m_startButton = new BasButton;
        m_startButton->setButtonInfo("","default","thumbstart",CCSizeMake(0,0));
        m_startButton->setClickCB(this,callfuncND_selector(ThumbFootItem::onStartClicked));
        this->addChild(m_startButton);
        m_startButton->setTop("parent",uilib::Top);
        m_startButton->setLeft("parent",uilib::Left);
        m_startButton->setTopMargin(25);
        m_startButton->setLeftMargin(20);
    }
    if(1){
        //submit button
        m_submitButton = new BasButton;
        m_submitButton->setButtonInfo("","default","thumbsubmit",CCSizeMake(0,0));
        m_submitButton->setClickCB(this,callfuncND_selector(ThumbFootItem::onSubmitClicked));
        this->addChild(m_submitButton);
        m_submitButton->setTop("parent",uilib::Top);
        m_submitButton->setLeft("parent",uilib::Left);
        m_submitButton->setTopMargin(25);
        m_submitButton->setLeftMargin(20);
        m_submitButton->setVisible(false);
    }
    if(1){
        //loading busy
        std::string anim,first;
        anim = "uiloadinga";
        first = anim;
        ResourceMgr::getInstance()->getFrameSpriteFirstFrame(first);
        m_busyAnim = new BasAnimSprite(anim,first);
        m_busyNode = new FSizeCCNodeDelegate(m_busyAnim);
        this->addChild(m_busyNode);
        m_busyNode->setCenterIn("parent");
        m_busyNode->setVisible(false);
    }
    if(1){
        //thumb foot sign
        BasButton *button;
        for(unsigned int i = 0;i < 3;i++){
            BorderWidget *node = m_frameBgs[i];
            button = new BasButton;
            button->setCanTouch(false);
            button->setButtonInfo("","default","thumb",CCSizeMake(30,30));
            node->addChild(button);
            button->setLeft("parent",uilib::Left);
            button->setBottom("parent",uilib::Bottom);
            button->setVisible(false);
            m_thumbButtons.push_back(button);

            button = new BasButton;
            button->setButtonInfo("","default","foot",CCSizeMake(30,30));
            node->addChild(button);
            button->setCanTouch(false);
            button->setVisible(false);
            button->setRight("parent",uilib::Right);
            button->setBottom("parent",uilib::Bottom);
            m_footButtons.push_back(button);
        }
    }
    m_itemInit = true;
    this->layout(true);
}
