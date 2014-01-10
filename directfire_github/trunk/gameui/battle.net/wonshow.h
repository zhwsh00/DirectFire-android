#ifndef _wonshow_h_
#define _wonshow_h_
#include <string>
#include <vector>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"
using namespace uilib;

class WonGameShow : public BasWidget
{
public:
    typedef struct WonBarDef{
        WonBarDef(){
            m_percent = 0;
        }
        std::string m_barBg;
        std::string m_barFg;
        float m_percent;
    }WonBarDef;
    WonGameShow();
    virtual ~WonGameShow();
    void setTheme(const std::string &theme);
    void addWonBarDef(WonBarDef *def);
    void resetWonBarLen(const std::vector<float> &len);
    void setActionTime(float time);
    void addPercentTo(int index,float percent);
    void addPercentBy(int index,float percent);
protected:
    void layoutCompleted();
    void finish();
protected:
    std::string m_theme;
    float m_actionTime;
    std::vector<WonBarDef*> m_barDefs;
protected:
    std::vector<HorTriProgressBar*> m_wonBars;
};

#endif
