#ifndef _circleprogressbar_h_
#define _circleprogressbar_h_
#include <string>
using namespace std;

#include "../base/widget.h"

#include "cocos2d.h"
using namespace std;

namespace uilib
{
class CircleProgressBar : public BasWidget
{
public:
    CircleProgressBar();
    virtual ~CircleProgressBar();
    void setTheme(const std::string &theme,const std::string &bg,const std::string &fg);
    void setProgressTo(float time,float percent);
    void setProgressAdd(float time,float percent);
    void setBarChangeRate(const CCPoint &p);
    void setMidpoint(const CCPoint &p);
protected:
    void layoutCompleted();
protected:
    std::string m_theme;
    std::string m_bg;
    std::string m_fg;
protected:
    CCProgressTimer *m_progTimer;
    CCSprite *m_bgSprite;
};

}
#endif
