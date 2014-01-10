#include "gamepage.h"
#include "gamepageitem.h"
#include "gamepagetitle.h"

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"
#include "gamecore/utils/ccutils.h"
#include <algorithm>
using namespace std;

GamePage::GamePage(uilib::BasWidget *container) : BasPage(container)
{
    m_title = new GamePageTitle;
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    m_title->setTitle(lang->getStringById(StringEnum::GameList));
    m_title->setRefreshCB(this,callfuncND_selector(GamePage::onTitleRefreshClick));
    m_title->setSortByMapNameCB(this,callfuncND_selector(GamePage::onTitleNameSortClick));
    m_title->setSortByPlayerNumCB(this,callfuncND_selector(GamePage::onTitleNumSortClick));
    m_title->setTowerModelCB(this,callfuncND_selector(GamePage::onTitleTdModeClick));
    m_title->setDfModelCB(this,callfuncND_selector(GamePage::onTitleDfModeClick));
    this->addChild(m_title);
    float srate = getAdaptResourceScale();
    m_title->setLeft("parent",uilib::Left);
    m_title->setBottom("parent",uilib::Top);
    m_title->setLeftMargin(20);
    m_title->setRightMargin(20);
    m_title->setWidth(610 * srate);
    m_title->setHeight(92 * srate);

    this->setTopMargin(30);

    m_scrollList = new VerScrollWidget("","");
    m_scrollList->setMargins(5);
    this->addChild(m_scrollList);
    m_scrollList->setLeft("parent",uilib::Left);
    m_scrollList->setRight("parent",uilib::Right);
    m_scrollList->setTop("parent",uilib::Top);
    m_scrollList->setTopMargin(10);
    m_scrollList->setBottom("parent",uilib::Bottom);
    m_scrollList->setSpacing(20);
    m_scrollList->setVerticalScrollPolicy(uilib::ScrollShow_Never);
    m_scrollList->setHorizontalScrollPolicy(uilib::ScrollShow_Never);
    m_init = false;
    m_serverIface = ServerInterface::getInstance();

    m_gameType = GameType::RunType_Battle;
}
GamePage::~GamePage()
{

}
void GamePage::resetHallInfo(int sortType)
{
    m_scrollList->delAllFixedSizeWidget();
    m_rooms.clear();
    m_runRooms.clear();
    m_serverIface->getHallRoomInfo(m_rooms);
    const std::vector<UiMsgEv::MapInfo> *mapsInfo = m_serverIface->getMapsInfo();
    std::vector<int> noadds;
    int mapType;
    if(m_gameType == GameType::RunType_Battle){
        mapType = 0;
    }else if(m_gameType == GameType::RunType_Td){
        mapType = 1;
    }else{
        mapType = 0;//toll is no supported,just set to battle mode
    }
    for(unsigned int i = 0;i < mapsInfo->size();i++){
        bool add = false;
        const UiMsgEv::MapInfo &map = mapsInfo->at(i);
        for(unsigned int k = 0;k < m_rooms.size();k++){
            UiMsgEv::RoomMapInfoEv &ev = m_rooms[k];
            if(ev.m_mapType == mapType && ev.m_mapId == map.m_mapId){
                ev.m_alignNum = map.m_maxAlign;
                ev.m_suppNum = map.m_maxPlayer;
                ev.m_mapAbbrevName = map.m_mapAbbvName;
                ev.m_mapHeight = map.m_height;
                ev.m_mapWidth = map.m_width;
                ev.m_mapName = map.m_mapName;
                ev.m_mapFile = map.m_gateId;
                ev.m_coinCost = map.m_costGolds;
                add = true;
                m_runRooms.push_back(ev);
                break;
            }
        }
        if(!add && map.m_mapType == mapType){
            noadds.push_back(i);
        }
    }
    for(unsigned int i = 0;i < noadds.size();i++){
        const UiMsgEv::MapInfo &map = mapsInfo->at(noadds[i]);
        m_runRooms.push_back(UiMsgEv::RoomMapInfoEv());
        UiMsgEv::RoomMapInfoEv &ev = m_runRooms[m_runRooms.size() - 1];
        ev.m_mapId = map.m_mapId;
        ev.m_alignNum = map.m_maxAlign;
        ev.m_suppNum = map.m_maxPlayer;
        ev.m_mapAbbrevName = map.m_mapAbbvName;
        ev.m_mapHeight = map.m_height;
        ev.m_mapWidth = map.m_width;
        ev.m_mapName = map.m_mapName;
        ev.m_mapFile = map.m_gateId;
        ev.m_coinCost = map.m_costGolds;
        ev.m_roomsCount = 0;
        ev.m_inMapUserCount = 0;
    }
    if(sortType == 1)
        std::sort(m_runRooms.begin(),m_runRooms.end(),game_sortByOnlineNum);
    else if(sortType == 2)
        std::sort(m_runRooms.begin(),m_runRooms.end(),game_sortByMapName);
    float w = m_anchorWidth - m_scrollList->leftMargin() * 8;
    float h = 100;
    CCSize size = CCSizeMake(w,h);
    for(unsigned int i = 0;i < m_runRooms.size();i++){
        GamePageItem *item = new GamePageItem(this);
        item->setWidth(w);
        item->setHeight(h);
        item->setRoomInfo(&m_runRooms[i]);

        FSizeWidgetDelegate *dele = new FSizeWidgetDelegate(item,size);
        m_scrollList->addFixedSizeWidget(dele);

        item->finish();
    }
    m_init = true;
    m_scrollList->layout(true);
    m_scrollList->scrollToBegin(true);
}
void GamePage::moveinPage()
{
    if(m_init){
        if(m_scrollList->scrollItemCount() == 0
                && !m_title->isRefreshing())
            m_serverIface->refreshHallInfo(m_gameType);
    }else{
        m_serverIface->refreshHallInfo(m_gameType);
    }
}
void GamePage::moveoutPage()
{

}
void GamePage::startRefreshing()
{
    if(m_title)
        m_title->setRefreshing(true);
}
void GamePage::endRefreshing()
{
    if(m_title)
        m_title->setRefreshing(false);
}
void GamePage::setGameType(GameType::RunType type)
{
    m_gameType = type;
}
GameType::RunType GamePage::getGameType()
{
    return m_gameType;
}
void GamePage::onTitleRefreshClick(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(!m_title->isRefreshing())
        m_serverIface->refreshHallInfo();
}
void GamePage::onTitleNameSortClick(CCNode *node,void *data)
{
    resetHallInfo(2);
}
void GamePage::onTitleNumSortClick(CCNode *node,void *data)
{
    resetHallInfo(1);
}
void GamePage::onTitleTdModeClick(CCNode *node,void *data)
{
    m_gameType = GameType::RunType_Td;
    resetHallInfo(2);
}
void GamePage::onTitleDfModeClick(CCNode *node,void *data)
{
    m_gameType = GameType::RunType_Battle;
    resetHallInfo(2);
}
