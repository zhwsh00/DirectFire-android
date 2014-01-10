#ifndef _splashscene_h_
#define _splashscene_h_
#include "cocos2d.h"
using namespace cocos2d;

class SplashScene : public cocos2d::CCScene
{
public:
    SplashScene();
    ~SplashScene();
    bool init();
    CREATE_FUNC(SplashScene)
protected:
    void onSplashFinished(CCNode *sender);
    void onBgClicked(CCNode *node,void *data);
    void onNoShowClicked(CCNode *node,void *data);
};
#endif
