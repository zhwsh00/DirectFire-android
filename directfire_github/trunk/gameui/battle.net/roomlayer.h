#ifndef _roomlayer_h_
#define _roomlayer_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "uilib/uilib.h"
#include "gamecore/serverinterface.h"

using namespace uilib;

class RoomMainWidget;
class RoomLayer : public CCLayer
{
public:
    RoomLayer();
    virtual ~RoomLayer();
    bool init();
    void setEnable(bool enable);
    CREATE_FUNC(RoomLayer)
protected:
    RoomMainWidget *m_mainWidget;
};
#endif
