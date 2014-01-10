#ifndef _abanimsprite_h_
#define _abanimsprite_h_
#include <string>
#include <map>
#include <vector>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

namespace uilib {
class BasAnimSprite : public CCSprite
{
public:
    BasAnimSprite(const std::string &animName,const std::string &firstFrame);
    virtual ~BasAnimSprite();
    bool isLoaded() { return m_animation != 0;}
    void playInLoop(int loop);
    void start();
    void end();
    void setAnimFinishCB(CCNode *listener,SEL_CallFuncND func);
    void setAutoRelease(bool release) { m_autoRelease = release;}
    bool isRunning() { return m_isRunning;}
    const std::string &animName() { return m_animName;}
protected:
    void animFinish(CCNode *node);
protected:
    CCNode *m_finishListener;
    SEL_CallFuncND m_finishFunc;
protected:
    std::string m_animName;
    std::string m_firstFrame;
    CCAnimation *m_animation;
    CCAction *m_animAction;
protected:
    bool m_autoRelease;
    bool m_isRunning;
};
}
#endif
