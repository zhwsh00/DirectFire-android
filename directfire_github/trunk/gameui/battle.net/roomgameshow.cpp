#include "roomgameshow.h"
#include "roommainwidget.h"

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"
#include "gamecore/utils/ccutils.h"

RoomGameShow::RoomGameShow(RoomMainWidget *owner)
{
    m_owner = owner;
    m_theme = "default";
    m_themeBg = "roomb2";
    m_quitListener = 0;
    m_quitFunc = 0;
    m_startListener = 0;
    m_startFunc = 0;
    m_bonusListener = 0;
    m_bonusFunc = 0;
    m_spellListener = 0;
    m_spellFunc = 0;
    m_spellNumSprite = 0;
    m_quitImg = "buttonbg";
    m_startImg = "buttonbg";
    m_bonusImg = "buttonbg";
    m_spellImg = "buttonbg";
    m_spellWidget = 0;
    m_spellNumButton = 0;
    m_quitButton = 0;
    m_startButton = 0;
    if(m_owner->m_serverIFace->isBattleModel()){
        m_spellMaxNum = 10;
    }else{
        m_spellMaxNum = 8;
    }
    m_roomHost = false;
    m_spellNum = 5;
    m_selNum = 0;
}
RoomGameShow::~RoomGameShow()
{

}
void RoomGameShow::reset()
{
    /*
    updateSpellNum(5);
    */
}
void RoomGameShow::setMapInfo(int id,const std::string &name,const std::string &abbrev)
{
    float wscale = getWholeScaleRate();
    m_mapId = id;
    m_mapName = name;
    m_mapAbbrev = abbrev;
    CCSprite *map = ResourceMgr::getInstance()->loadSpriteByTexture(m_mapAbbrev);
    if(map != 0){
        BasNodeDelegateWidget *mapWidget = new BasNodeDelegateWidget(map,CCSizeMake(120 * wscale,80 * wscale));
        m_containerWidget->addChild(mapWidget);
        mapWidget->setLeft("parent",uilib::Left);
        mapWidget->setBottom("parent",uilib::Bottom);
        mapWidget->setLeftMargin(10);
        mapWidget->setBottomMargin(4);
        BasLabel *mapName = new BasLabel;
        mapName->setLabelInfo(m_mapName.data(),"fonts/uifont30.fnt","default","",CCSizeMake(0,0));
        m_containerWidget->addChild(mapName);
        mapName->setBottom("parent",uilib::Bottom);
        mapName->setLeft(mapWidget->getName(),uilib::Right);
        mapName->setLeftMargin(4);
        mapName->setBottomMargin(4);
        m_containerWidget->layout(true);
    }
}
void RoomGameShow::setIsHost(bool host)
{
    m_roomHost = host;
    if(m_spellNumButton != 0){
        //inited
        setStartQuitButtons();
    }
}
void RoomGameShow::setQuitImg(const std::string &normal,const std::string &pressed)
{
    m_quitImg = normal;
    m_quitPressedImg = pressed;
}
void RoomGameShow::setStartImg(const std::string &normal,const std::string &pressed)
{
    m_startImg = normal;
    m_startPressedImg = pressed;
}
void RoomGameShow::setBonusImg(const std::string &normal,const std::string &pressed)
{
    m_bonusImg = normal;
    m_bonusPressedImg = pressed;
}
void RoomGameShow::setSpellImg(const std::string &normal,const std::string &pressed)
{
    m_spellImg = normal;
    m_spellPressedImg = pressed;
}
void RoomGameShow::setQuitCB(CCNode *listener,SEL_CallFuncND func)
{
    m_quitListener = listener;
    m_quitFunc = func;
}
void RoomGameShow::setStartCB(CCNode *listener,SEL_CallFuncND func)
{
    m_startListener = listener;
    m_startFunc = func;
}
void RoomGameShow::setBonusCB(CCNode *listener,SEL_CallFuncND func)
{
    m_bonusListener = listener;
    m_bonusFunc = func;
}
void RoomGameShow::setSpellMaxNum(int num)
{
    m_spellMaxNum = num;
}
void RoomGameShow::setSpellCB(CCNode *listener,SEL_CallFuncND func)
{
    m_spellListener = listener;
    m_spellFunc = func;
}
void RoomGameShow::layoutCompleted()
{
    float wscale = getWholeScaleRate();
    BorderWidget::layoutCompleted();
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    float margin = 4;
    if(m_spellWidget != 0)
        return;
    m_containerWidget = new BasWidget;
    this->addChild(m_containerWidget);
    m_containerWidget->setLeft("parent",uilib::Left);
    m_containerWidget->setRight("parent",uilib::Right);
    m_containerWidget->setBottom("parent",uilib::Bottom);
    m_containerWidget->setMaxHeightRefSize("parent",0.8);
    m_containerWidget->setMinHeightRefSize("parent",0.8);
    if(1){
        float bw = 70 * wscale;
        float bh = 70 * wscale;
        CCSize size = CCSizeMake(bw,bh);

        std::stringstream ss; ss << "X" << m_spellNum;
        m_spellNumButton = new BasButton;

        m_spellNumButton->setTouchPriority(this->touchPriority() - uilib::SafePriorityGap);
        m_spellNumButton->setButtonInfo("",m_theme,"spellnum",size);
        m_spellNumSprite = CCLabelBMFont::create(ss.str().data(),"fonts/uifont30.fnt",60);
        m_spellNumButton->CCNode::addChild(m_spellNumSprite);
        m_spellNumSprite->setAnchorPoint(ccp(0.5,0.5));
        m_spellNumSprite->setPosition(ccp(size.width/2,size.height / 2));
        m_containerWidget->addChild(m_spellNumButton);
        m_spellNumButton->setTop("parent",uilib::Top);
        m_spellNumButton->setRight("parent",uilib::Right);
        m_spellNumButton->setMargins(margin);
        m_spellNumButton->setClickCB(this,callfuncND_selector(RoomGameShow::onSpellNumButtonClicked));

        size = CCSizeMake(120 * wscale,60 * wscale);
        m_startButton = new BasButton;
        m_startButton->setButtonInfo(lang->getStringById(StringEnum::StartGame).data(),"fonts/uifont24.fnt",m_theme,
                                     m_startImg,size);
        m_containerWidget->addChild(m_startButton);
        m_startButton->setMargins(margin);

        m_quitButton = new BasButton;
        m_quitButton->setButtonInfo(lang->getStringById(StringEnum::QuitRoom).data(),"fonts/uifont24.fnt",m_theme,
                                    m_quitImg,size);
        m_containerWidget->addChild(m_quitButton);
        m_quitButton->setMargins(margin);

        m_quitButton->setRight("parent",uilib::Right);
        m_quitButton->setBottom("parent",uilib::Bottom);
        m_startButton->setRight(m_quitButton->getName(),uilib::Left);
        m_startButton->setBottom("parent",uilib::Bottom);

        m_quitButton->setClickCB(m_quitListener,m_quitFunc);
        m_startButton->setClickCB(m_startListener,m_startFunc);
        setStartQuitButtons();
    }
    if(1){
        m_spellWidget = new HorScrollWidget;
        m_containerWidget->addChild(m_spellWidget);
        m_spellWidget->setLeft("parent",uilib::Left);
        m_spellWidget->setRight(m_spellNumButton->getName(),uilib::Left);

        m_spellWidget->setTop("parent",uilib::Top);
        m_spellWidget->setMargins(margin);
        m_spellWidget->setRightMargin(20);
        m_spellWidget->setHeight(70 * wscale);
        m_spellWidget->setSpacing(20);
        m_spellWidget->setVerticalScrollPolicy(ScrollShow_Never);
        m_spellWidget->setHorizontalScrollPolicy(ScrollShow_Never);

        std::vector<std::string> spells;
        if(m_owner->m_serverIFace->isBattleModel()){
            spells = ResourceMgr::getInstance()->battlePropsNames();
        }else{
            spells = ResourceMgr::getInstance()->tdPropsNames();
        }

        for(unsigned int i = 0;i < spells.size();i++){
            std::string img = spells[i];
            img += ".png";
            CCSprite *spellSprite = CCSprite::createWithSpriteFrameName(img.data());
            FSizeSpriteDelegate *dele = new FSizeSpriteDelegate(spellSprite,CCSizeMake(70 * wscale,70 * wscale));
            dele->setCanTouch(true);
            dele->setTag(i);
            dele->setClickCB(this,callfuncND_selector(RoomGameShow::onSpellClicked));
            m_spellWidget->addFixedSizeWidget(dele);
            CCSprite *sprite = CCSprite::createWithSpriteFrameName("spellselected.png");
            FSizeSpriteDelegate *seldele = new FSizeSpriteDelegate(sprite);
            dele->addChild(seldele);
            seldele->setName(img);
            seldele->setVisible(false);
            seldele->setTop("parent",uilib::Top);
            seldele->setRight("parent",uilib::Right);
            m_selected.push_back(seldele);
        }
    }
}
void RoomGameShow::updateSpellNum(int num)
{
    if(num < m_selNum){
        for(unsigned int i = 0;i < m_selected.size();i++){
            FSizeSpriteDelegate *dele = m_selected[i];
            if(dele->isVisible()){
                dele->setVisible(false);
                m_selNum--;
                if(num == m_selNum)
                    break;
            }
        }
    }
    m_spellNum = num;
    std::stringstream ss;
    ss << "X" << m_spellNum;
    m_spellNumSprite->setString(ss.str().data());
}
int RoomGameShow::getSpellNum()
{
    return m_spellNum;
}
void RoomGameShow::getSpellSelected(int &num,std::vector<std::string> &spells)
{
    num = m_spellNum;
    for(unsigned int i = 0;i < m_selected.size();i++){
        FSizeSpriteDelegate *dele = m_selected[i];
        if(dele->isVisible()){
            spells.push_back(dele->getName());
        }
    }
    int index = 0;
    for(unsigned int i = spells.size();i < num;i++){
        for(;index < m_selected.size();){
            FSizeSpriteDelegate *dele = m_selected[index++];
            if(!dele->isVisible()){
                dele->setVisible(true);
                spells.push_back(dele->getName());
                break;
            }
        }
    }
    m_selNum = m_spellNum;
}
void RoomGameShow::enableStartAfterSec(int sec)
{
    if(m_roomHost){
        m_startButton->setVisible(false);
        this->scheduleOnce(schedule_selector(RoomGameShow::enableStartStep),sec);
    }
}
void RoomGameShow::enableStartStep(float dt)
{
    if(m_roomHost){
        m_startButton->setVisible(true);
        CCScaleTo *scaleTo = CCScaleTo::create(0.5,1.1);
        CCScaleTo *scaleBack = CCScaleTo::create(0.5,1.0);
        m_startButton->runAction(CCSequence::create(scaleTo,scaleBack,0));
    }
}
void RoomGameShow::setStartQuitButtons()
{
    if(m_roomHost){
        m_startButton->setVisible(true);
        m_quitButton->setVisible(true);
    }else{
        m_startButton->setVisible(false);
        m_quitButton->setVisible(true);
    }
}
void RoomGameShow::onSpellNumButtonClicked(CCNode *node,void *data)
{
    if(!m_roomHost)
        return;
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int num = m_spellNum;
    if((num+1) > m_spellMaxNum)
        num = -1;
    m_owner->m_serverIFace->requestChangeSpellNum(m_owner->m_accountInfo->m_id,num+1);
}
void RoomGameShow::onSpellClicked(CCNode *node,void *data)
{
    TouchNode *touch  = (TouchNode*)node;
    if(!touch->underMouse())
        return;
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = node->getTag();
    FSizeSpriteDelegate *dele = m_selected[index];
    if(dele->isVisible()){
        dele->setVisible(false);
        m_selNum--;
    }else{
        if(m_selNum >= m_spellNum){
            dele->setVisible(true);
            for(unsigned int i = 0;i < m_selected.size();i++){
                if(i == index)
                    continue;
                if(m_selected[i]->isVisible()){
                    m_selected[i]->setVisible(false);
                    break;
                }
            }
        }else{
            dele->setVisible(true);
            m_selNum++;
        }
    }
}
