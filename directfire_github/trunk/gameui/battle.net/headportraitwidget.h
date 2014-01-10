#ifndef _headportraitwidget_h_
#define _headportraitwidget_h_
#include <string>
#include <vector>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "uilib/uilib.h"
#include "headsettingdialog.h"

#include "basscalewidget.h"

using namespace uilib;

class HeadPortraitWidget : public BasScaleWidget
{
public:
    typedef struct CircleBarDef{
        CircleBarDef(){
            m_percent = 0;
        }
        std::string m_barBg;
        std::string m_barFg;
        int m_percent;
    }CircleBarDef;

    HeadPortraitWidget();
    virtual ~HeadPortraitWidget();
    bool onKeyPadBackClicked();
    void setPortrait(const std::string &theme,
                     const std::string &bg,
                     const std::string &head);
    void setHeadFile(const std::string &headfile);
    void updateHeadFile(const std::string &headfile);
    void setActionTime(float time);
    void addPercentTo(int index,float percent);
    void addPercentBy(int index,float percent);
    void addCircleBar(CircleBarDef *def);
    void setIndentRate(float rate);
    void portraitUpdated(std::string *data);
    void openHeadSettingDialog(bool editAble=false);
protected:
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    void onHeadSettingDialogCloseClicked(CCNode *node,void *data);
    void onHeadSettingDialogPortraitSubmitted(CCNode *node,void *data);
protected:
    void layoutCompleted();
    void finish();
protected:
    std::string m_theme;
    std::string m_headBg;
    std::string m_headPortrait;
    std::string m_headFile;
    float m_actionTime;
    float m_indentRate;
    CCSize m_headSize;
protected:
    std::vector<CircleBarDef*> m_barDefs;
protected:
    CircleProgressBar *m_intellBar;
    CircleProgressBar *m_energyBar;
    CircleProgressBar *m_luckyBar;
    CircleProgressBar *m_leaderBar;
    CCSprite *m_headSprite;
protected:
    std::vector<CircleProgressBar*> m_circleBars;
protected:
    HeadSettingDialog* m_headSettingDialog;
};

#endif
