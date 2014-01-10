#ifndef _swayeffectaction
#define _swayeffectaction
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
class SwayEffectAction : public BasNodeEffectAction
{
public:
    SwayEffectAction();
    virtual ~SwayEffectAction();
    virtual void doAction(TouchNode *node,bool enable);
};
}
#endif
