#ifndef _roomscene_h_
#define _roomscene_h_
#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"

using namespace uilib;

class RoomLayer;
class RoomScene : public CCScene
{
public:
    RoomScene();
    ~RoomScene();
    bool init();
    CREATE_FUNC(RoomScene)
protected:
    void switchToGamePage();
    void switchToRoomPage();
protected:
    void serverListener(CCNode *node,void *data);
protected:
    RoomLayer *m_roomLayer;
};
#endif
