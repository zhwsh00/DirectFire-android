#ifndef _scaleeffectaction_h_
#define _scaleeffectaction_h_
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
class ScaleEffectAction : public BasNodeEffectAction
{
public:
    ScaleEffectAction();
    virtual ~ScaleEffectAction();
    virtual void doAction(TouchNode *node,bool enable);
};
}

#endif
