#ifndef _gamepage_h_
#define _gamepage_h_
#include <vector>
#include <map>
using namespace std;

#include "baspage.h"
#include "uilib/uilib.h"
using namespace uilib;

#include "cliententry/uimsgevent.h"
#include "gamecore/serverinterface.h"

class GamePageTitle;
class GamePageItem;
class GamePage : public BasPage
{
public:
    friend class GamePageItem;
    GamePage(uilib::BasWidget *container = 0);
    virtual ~GamePage();
    void resetHallInfo(int sortType = 2);
    virtual void moveinPage();
    virtual void moveoutPage();
    void startRefreshing();
    void endRefreshing();
    void setGameType(GameType::RunType type);
    GameType::RunType getGameType();
protected:
    void onTitleRefreshClick(CCNode *node,void *data);
    void onTitleNameSortClick(CCNode *node,void *data);
    void onTitleNumSortClick(CCNode *node,void *data);
    void onTitleTdModeClick(CCNode *node,void *data);
    void onTitleDfModeClick(CCNode *node,void *data);
protected:
    GamePageTitle *m_title;
protected:
    VerScrollWidget *m_scrollList;
protected:
    bool m_init;
    ServerInterface *m_serverIface;
    std::vector<UiMsgEv::RoomMapInfoEv> m_rooms;
    std::vector<UiMsgEv::RoomMapInfoEv> m_runRooms;
protected:
    GameType::RunType m_gameType;
};
#endif
