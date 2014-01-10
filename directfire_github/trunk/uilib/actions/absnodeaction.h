#ifndef _absnodeaction_h_
#define _absnodeaction_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <iostream>
#include <vector>
using namespace std;

namespace uilib
{
class TouchNode;
enum EaseType
{
    EaseNone,
    EaseIn,
    EaseOut,
    EaseInOut,
    EaseExponentialIn,
    EaseExponentialOut,
    EaseExponentialInOut,
    EaseSineIn,
    EaseSineOut,
    EaseSineInOut,
    EaseElastic,
    EaseElasticIn,
    EaseElasticOut,
    EaseElasticInOut,
    EaseBounce,
    EaseBounceIn,
    EaseBounceOut,
    EaseBounceInOut,
    EaseBackIn,
    EaseBackOut,
    EaseBackInOut
};
enum MoveInType{
    HorizontalRightIn,
    HorizontalLeftIn,
    HorizontalBothIn,
    VerticalTopIn,
    VerticalBottomIn,
    VerticalBothin,
    ScaleIn,
    ScaleXIn,
    ScaleYIn,
    SwayIn,
    RotateIn,
    BlinkIn,
    ReelIn,
    FireIn,
    DropScaleIn
};
enum MoveOutType{
    HorizontalRightOut,
    HorizontalLeftOut,
    HorizontalBothOut,
    VerticalTopOut,
    VerticalBottomOut,
    VerticalBothOut,
    ScaleOut,
    ScaleXOut,
    ScaleYOut,
    SwayOut,
    RotateOut,
    BlinkOut,
    ReelOut,
    FireOut
};
enum RunningEffectType
{
    ShineEffect,
    SwayEffect,
    ScaleEffect,
    AnimEffect
};

class BasNodeEffectAction : public CCNode
{
public:
    BasNodeEffectAction();
    virtual ~BasNodeEffectAction();
    virtual void finished();
    virtual void doAction(TouchNode *node,bool enable) = 0;
    inline void setEaseType(EaseType type) { m_easeType = type;}
    inline EaseType getEaseType() { return m_easeType;}
    inline void setActionTime(float time) { m_actionTime = time;}
    inline float getActionTime() { return m_actionTime;}
    inline void setStartTime(float time) { m_startTime = time;}
    inline float getStartTime() { return m_startTime;}
    void setFinishCB(CCNode *listener,SEL_CallFuncN func);
    inline bool isRunning() { return m_running;}
protected:
    EaseType m_easeType;
    float m_actionTime;
    float m_startTime;
protected:
    bool m_running;
protected:
    SEL_CallFuncN m_finishFunc;
    CCNode *m_listener;
};

class BasNodeAction : public CCNode
{
public:
    BasNodeAction();
    virtual ~BasNodeAction();
    virtual void finished();
    virtual void doAction(const std::vector<TouchNode*> &nodes) = 0;
    void setDelayTime(float delay) { m_delayTime = delay;}
    float getDelayTime() { return m_delayTime;}
    inline void setEaseType(EaseType type) { m_easeType = type;}
    inline EaseType getEaseType() { return m_easeType;}
    inline void setMoveInType(MoveInType type) { m_inType = type;}
    inline MoveInType getMoveInType() { return m_inType;}
    inline void setMoveOutType(MoveOutType type) { m_outType = type;}
    inline MoveOutType getMoveOutType() { return m_outType;}
    inline void setActionTime(float time) { m_actionTime = time;}
    inline float getActionTime() { return m_actionTime;}
    inline void setStartTime(float time) { m_startTime = time;}
    inline float getStartTime() { return m_startTime;}
    inline void setRate(float rate) { m_rate = rate;}
    inline float getRate() { return m_rate;}
    void setFinishCB(CCNode *listener,SEL_CallFuncN func,CCNode *actionNode = 0);
protected:
    CCActionEase  *createEaseAction();
protected:
    int m_actionRunNum;
    float m_delayTime;
    EaseType m_easeType;
    MoveInType m_inType;
    MoveOutType m_outType;
    float m_actionTime;
    float m_rate;
    float m_startTime;
protected:
    SEL_CallFuncN m_finishFunc;
    CCNode *m_listener;
    CCNode *m_actionNode;
};

class UiNodeActionFactory
{
    UiNodeActionFactory();
    ~UiNodeActionFactory();
    static UiNodeActionFactory *m_instance;
public:
    static UiNodeActionFactory *getInstance();
    BasNodeAction *getMoveActionByName(const std::string &name);
    BasNodeEffectAction *getEffectActionByName(const std::string &name);
protected:
};

}
#endif
