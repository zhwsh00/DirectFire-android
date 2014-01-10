#ifndef _animeffectaction_h_
#define _animeffectaction_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include "absnodeaction.h"
namespace uilib
{

class BasAnimSprite;
class TouchNode;
class AnimEffectAction : public BasNodeEffectAction
{
public:
    AnimEffectAction();
    virtual ~AnimEffectAction();
    virtual void doAction(TouchNode *node,bool enable);
    inline void setAnimName(const std::string &name) { m_animName = name;}
    const std::string &getAnimName() { return m_animName;}
protected:
    std::string m_animName;
    BasAnimSprite *m_animSprite;
};
}
#endif
