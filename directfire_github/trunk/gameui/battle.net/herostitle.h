#ifndef _herostitle_h_
#define _herostitle_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "cliententry/uimsgevent.h"
#include "uilib/uilib.h"

using namespace uilib;

class HerosTitle : public BorderWidget
{
public:
    HerosTitle();
    virtual ~HerosTitle();
    void setTypeCB(CCNode *node,SEL_CallFuncND func);
    void setRefreshCB(CCNode *node,SEL_CallFuncND func);
    void setTitle(const std::string &title);
    void layoutCompleted();
    void setRefreshing(bool on);
    bool isRefreshing() { return m_refreshing;}
    void setSelectIndex(int index);
protected:
    void startRefresh();
protected:
    CCNode *m_typeListener;
    SEL_CallFuncND m_typeFunc;
    CCNode *m_refreshListener;
    SEL_CallFuncND m_refreshFunc;
protected:
    std::string m_title;
protected:
    BasWidget *m_refreshWidget;
    bool m_refreshing;
protected:
    std::vector<BasButton*> m_buttons;
    int m_currIndex;
};
#endif
