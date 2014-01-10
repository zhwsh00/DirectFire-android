#ifndef _hortriprogressbar_h_
#define _hortriprogressbar_h_

#include <string>
using namespace std;

#include "../base/widget.h"

#include "cocos2d.h"
using namespace std;

namespace uilib
{
class HorTriProgressBar : public BasWidget
{
public:
    HorTriProgressBar();
    virtual ~HorTriProgressBar();
    void setTheme(const std::string &theme,const std::string &bg,const std::string &fg);
    void setProgressTo(float time,float percent);
    void setProgressAdd(float time,float percent);
    void setBarChangeRate(const CCPoint &p);
    void setMidpoint(const CCPoint &p);
protected:
    void layoutCompleted();
protected:
    void onHeadProgTimerFinished(CCNode *sender,void *data);
    void onCenterProgTimerFinished(CCNode *sender,void *data);
protected:
    std::string m_theme;
    std::string m_bg;
    std::string m_fg;
protected:
    float m_actionTime;
protected:
    CCProgressTimer *m_progTimerHead;
    CCProgressTimer *m_progTimerTail;
    CCProgressTimer *m_progTimerCenter;
    CCSprite *m_spriteHead;
    CCSprite *m_spriteTail;
    CCSprite *m_spriteCenter;
    HTriWidget *m_bgSprite;
protected:
    float m_headRate;
    float m_centerRate;
    float m_tailRate;
    float m_destPercent;
};

}
#endif
