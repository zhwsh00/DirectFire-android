#ifndef _gamepagetitle_h_
#define _gamepagetitle_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

//#include "baspage.h"
#include "uilib/uilib.h"

using namespace uilib;

class GamePageTitle : public BorderWidget
{
public:
    GamePageTitle();
    virtual ~GamePageTitle();
    void setRefreshCB(CCNode *node,SEL_CallFuncND func);
    void setDfModelCB(CCNode *node,SEL_CallFuncND func);
    void setTowerModelCB(CCNode *node,SEL_CallFuncND func);
    void setSortByMapNameCB(CCNode *node,SEL_CallFuncND func);
    void setSortByPlayerNumCB(CCNode *node,SEL_CallFuncND func);
    void setTitle(const std::string &title);
    void setRefreshImg(const std::string &normal,const std::string &pressed);
    void layoutCompleted();
    void setRefreshing(bool on);
    bool isRefreshing() { return m_refreshing;}
protected:
    void startRefresh();
protected:
    CCNode *m_refreshListener;
    SEL_CallFuncND m_refreshFunc;
protected:
    CCNode *m_nameSortListener;
    SEL_CallFuncND m_nameSortFunc;
    CCNode *m_numSortListener;
    SEL_CallFuncND m_numSortFunc;
    CCNode *m_dfListener;
    SEL_CallFuncND m_dfFunc;
    CCNode *m_towerListener;
    SEL_CallFuncND m_towerFunc;
protected:
    std::string m_refreshImg,m_refreshPressedImg;
    std::string m_title;
protected:
    BasWidget *m_refreshWidget;
    bool m_refreshing;
};

#endif
