#ifndef _systitle_h_
#define _systitle_h_
#include <string>
#include <vector>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"
using namespace uilib;

class SysTitle : public BorderWidget
{
public:
    SysTitle();
    virtual ~SysTitle();
    void setBackClickCB(CCNode *listener,SEL_CallFuncND func);
    void setTitle(const std::string &title);
    void setBackEnabled(bool can);
    void layoutCompleted();
protected:
    BasButton *m_backButton;
protected:
    std::string m_title;
    CCNode *m_backListener;
    SEL_CallFuncND m_backFunc;
    bool m_backEnabled;
protected:
    bool m_inited;
};

#endif
