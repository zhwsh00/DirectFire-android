#include "gamepageitem.h"
#include "gamepage.h"

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/serverinterface.h"

#include "gamecore/sounds/soundmgr.h"
#include "gamedata/gametype.h"

GamePageItem::GamePageItem(GamePage *owner)
{
    m_theme = "default";
    m_themeBg = "propbg";
    m_roomInfo = 0;
    m_owner = owner;
    m_quickGameImg = "buttonbg";
    m_createRoomImg = "buttonbg_red";
}
GamePageItem::~GamePageItem()
{

}
void GamePageItem::setRoomInfo(UiMsgEv::RoomMapInfoEv *info)
{
    m_roomInfo = info;
}
void GamePageItem::setCreateRoomImg(const std::string &normal,const std::string &pressed)
{
    m_createRoomImg = normal;
    m_createRoomPressedImg = pressed;
}
void GamePageItem::setQuickGameImg(const std::string &normal,const std::string &pressed)
{
    m_quickGameImg = normal;
    m_quickGamePressedImg = pressed;
}
void GamePageItem::finish()
{
    if(m_roomInfo == 0)
        return;
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    BasButton *quickButton,*createRoom;
    quickButton = new BasButton;
    quickButton->setButtonInfo("",m_theme,m_quickGameImg,CCSizeMake(110,60),m_quickGamePressedImg);
    if(1){
        //text
        CCLabelBMFont *font = CCLabelBMFont::create(lang->getStringById(StringEnum::JoinGame).data(),"fonts/uifont35.fnt");
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(font);
        quickButton->addChild(dele);
        dele->setCenterIn("parent");
    }
    createRoom = new BasButton;
    createRoom->setButtonInfo("",m_theme,m_createRoomImg,CCSizeMake(110,60),m_createRoomPressedImg);
    if(1){
        //text
        CCLabelBMFont *font = CCLabelBMFont::create(lang->getStringById(StringEnum::CreateGame).data(),"fonts/uifont35.fnt");
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(font);
        createRoom->addChild(dele);
        dele->setCenterIn("parent");
    }
    this->addChild(quickButton);
    this->addChild(createRoom);

    quickButton->setRight("parent",uilib::Right);
    quickButton->setRightMargin(8);
    quickButton->setVertical("parent",0.5);

    createRoom->setVertical("parent",0.5);
    createRoom->setRight(quickButton->getName(),uilib::Left);
    createRoom->setRightMargin(8);

    quickButton->setClickCB(this,callfuncND_selector(GamePageItem::onQuickGameClicked));
    createRoom->setClickCB(this,callfuncND_selector(GamePageItem::onCreateRoomClicked));

    BasWidget *mapWidget;
    if(1){
        //map abbrev
        CCSprite *mapab = ResourceMgr::getInstance()->loadSpriteByTexture(m_roomInfo->m_mapAbbrevName);

        mapWidget = new BasNodeDelegateWidget(mapab,CCSizeMake(108,72));
        this->addChild(mapWidget);
        mapWidget->setVertical("parent",0.5);
        mapWidget->setLeft("parent",uilib::Left);
        mapWidget->setLeftMargin(20);
    }
    BasWidget *infoWidget = new BasWidget;
    this->addChild(infoWidget);
    infoWidget->setLeft(mapWidget->getName(),uilib::Right);
    infoWidget->setTop("parent",uilib::Top);
    infoWidget->setBottom("parent",uilib::Bottom);
    infoWidget->setRight(createRoom->getName(),uilib::Left);
    infoWidget->setMargins(4);

    if(1){
        std::stringstream ss;
        std::string mapName = m_roomInfo->m_mapName;
        CCLabelBMFont *nameFont = CCLabelBMFont::create(mapName.data(),"fonts/uifont24.fnt");
        BasNodeDelegateWidget *nameDele = new BasNodeDelegateWidget(nameFont);
        infoWidget->addChild(nameDele);
        nameDele->setLeft("parent",uilib::Left);
        nameDele->setLeftMargin(5);
        nameDele->setTop("parent",uilib::Top);

        //cost golden
        BasButton *costGolden = new BasButton;
        costGolden->setButtonInfo("","default","costgolden",CCSizeMake(0,0));
        infoWidget->addChild(costGolden);
        costGolden->setLeft("parent",uilib::Left);
        costGolden->setLeftMargin(5);
        costGolden->setVertical("parent",0.5);
        ss.str("");ss << "x" << m_roomInfo->m_coinCost;
        CCLabelBMFont *costNum = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
        BasNodeDelegateWidget *costDele = new BasNodeDelegateWidget(costNum);
        infoWidget->addChild(costDele);
        costDele->setVertical("parent",0.5);
        costDele->setLeft(costGolden->getName(),uilib::Right);
        costDele->setLeftMargin(5);
        //room num,playernum
        ss.str("");ss << "R: x" << m_roomInfo->m_roomsCount;
        CCLabelBMFont *roomNum = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
        BasNodeDelegateWidget *roomDele = new BasNodeDelegateWidget(roomNum);
        infoWidget->addChild(roomDele);
        roomDele->setLeft("parent",uilib::Left);
        roomDele->setLeftMargin(5);
        roomDele->setBottom("parent",uilib::Bottom);

        ss.str("");ss << "P: x" << m_roomInfo->m_inMapUserCount;
        CCLabelBMFont *playerNum = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
        BasNodeDelegateWidget *playerDele = new BasNodeDelegateWidget(playerNum);
        infoWidget->addChild(playerDele);
        playerDele->setVertical(roomDele->getName(),0.5);
        playerDele->setLeft(roomDele->getName(),uilib::Right);
        playerDele->setLeftMargin(30);
    }
}
void GamePageItem::onCreateRoomClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);

    ServerInterface::getInstance()->setGameModel(m_owner->m_gameType);
    ServerInterface::getInstance()->createRoomPrepare(m_roomInfo);
}
void GamePageItem::onQuickGameClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);

    ServerInterface::getInstance()->setGameModel(m_owner->m_gameType);
    ServerInterface::getInstance()->quickGamePrepare(m_roomInfo);
}
