#ifndef _friendtitle_
#define _friendtitle_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "uilib/uilib.h"

using namespace uilib;

class FriendTitle : public BasWidget
{
public:
    FriendTitle();
    virtual ~FriendTitle();
    void setAddCB(CCNode *node,SEL_CallFuncND func);
    void setRefreshCB(CCNode *node,SEL_CallFuncND func);
    void setTitle(const std::string &title);
    void setAddImg(const std::string &normal,const std::string &pressed);
    void setRefreshImg(const std::string &normal,const std::string &pressed);
    void layoutCompleted();
    void setRefreshing(bool on);
    void startRefresh();
    bool isRefreshing() { return m_refreshing;}
protected:
    CCNode *m_addListener;
    SEL_CallFuncND m_addFunc;
    CCNode *m_refreshListener;
    SEL_CallFuncND m_refreshFunc;
protected:
    std::string m_refreshImg,m_refreshPressedImg;
    std::string m_addImg,m_addPressedImg;
    std::string m_title;
protected:
    BasWidget *m_refreshWidget;
    bool m_refreshing;
};

#endif
