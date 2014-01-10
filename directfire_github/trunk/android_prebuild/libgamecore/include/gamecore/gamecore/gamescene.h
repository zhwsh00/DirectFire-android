#ifndef _gamescene_h_
#define _gamescene_h_
#include "cocos2d.h"
using namespace cocos2d;
class GameScene : public cocos2d::CCScene
{
public:
	GameScene();
	~GameScene();
	bool init();
	CREATE_FUNC(GameScene);
};
#endif
