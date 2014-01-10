#ifndef _gamepageitem_h_
#define _gamepageitem_h_
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

#include "baspage.h"
#include "uilib/uilib.h"

using namespace uilib;

#include "cliententry/uimsgevent.h"

class GamePage;
class GamePageItem : public BorderWidget
{
public:
    GamePageItem(GamePage *owner);
    virtual ~GamePageItem();
    void setRoomInfo(UiMsgEv::RoomMapInfoEv *info);
    int mapId() { return m_roomInfo->m_mapId;}
    void setCreateRoomImg(const std::string &normal,const std::string &pressed);
    void setQuickGameImg(const std::string &normal,const std::string &pressed);
    void finish();
protected:
    void onCreateRoomClicked(CCNode *node,void *data);
    void onQuickGameClicked(CCNode *node,void *data);
protected:
    UiMsgEv::RoomMapInfoEv *m_roomInfo;
protected:
    std::string m_createRoomImg,m_createRoomPressedImg;
    std::string m_quickGameImg,m_quickGamePressedImg;
protected:
    GamePage *m_owner;
};
#endif
