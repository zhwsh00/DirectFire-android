#ifndef _endlessscene_h_
#define _endlessscene_h_
#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"
#include "gamecore/gamecore/gameboard.h"

using namespace uilib;

class EndlessScene : public CCScene
{
public:
    EndlessScene();
    ~EndlessScene();
    bool init();
    CREATE_FUNC(EndlessScene)
protected:
    void switchToGamePage();
protected:
    void serverListener(CCNode *node,void *data);
protected:
    GameBoard *m_gameBoard;
};
#endif
