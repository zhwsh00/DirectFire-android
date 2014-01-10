#ifndef _levelexpshow_h_
#define _levelexpshow_h_
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"
using namespace uilib;

#include "prop/propdef.h"

class LevelExpShow : public BasWidget
{
public:
    LevelExpShow();
    virtual ~LevelExpShow();
    void setBarTheme(const std::string &theme,
                     const std::string &bg,const std::string &fg);
    void setLevelExp(int level,int exp,int levelexp,int nextexp);
protected:
    void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    std::string m_theme;
    std::string m_bg;
    std::string m_fg;
protected:
    int m_level;
    int m_exp;
    int m_levelExp;
    int m_nextLevelNeedExp;
protected:
    HorTriProgressBar *m_progressBar;
    BasNodeDelegateWidget *m_medalWidget;
    BasNodeDelegateWidget *m_lightWidget;
};

#endif
