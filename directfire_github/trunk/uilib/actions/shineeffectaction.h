#ifndef _shineeffectaction_h_
#define _shineeffectaction_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include "absnodeaction.h"

namespace uilib
{
class TouchNode;
class ShineEffectAction : public BasNodeEffectAction
{
public:
    ShineEffectAction();
    virtual ~ShineEffectAction();
    virtual void doAction(TouchNode *node,bool enable);
protected:
    std::vector<CCSprite*> m_sprites;
    std::vector<CCSprite*> m_createSprites;
};

}
#endif
