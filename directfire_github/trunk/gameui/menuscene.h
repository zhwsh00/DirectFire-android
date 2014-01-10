#ifndef _menuscene_h_
#define _menuscene_h_
#include "cocos2d.h"
using namespace cocos2d;

class MenuScene : public cocos2d::CCScene
{
public:
	MenuScene();
	~MenuScene();
	bool init();
    CREATE_FUNC(MenuScene)
};
#endif
