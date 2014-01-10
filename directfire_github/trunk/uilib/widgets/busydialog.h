#ifndef _busydialog_h_
#define _busydialog_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
using namespace std;

#include "../base/dialog.h"
/*
added by water: 2012/12/20 remove others dependence for build alone
class BasFrameSprite;
*/
namespace uilib
{
class BasNodeDelegateWidget;
class SimpleBusyDialog : public BasDialog
{
public:
    SimpleBusyDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~SimpleBusyDialog();
    void setAnimationName(const std::string &name);
    void setBusyText(const std::string &text,
                 const std::string &fontFamily = "",
                 int fontSize = 28,
                 const ccColor3B &color = ccBLACK);
    virtual void exec();
    virtual void setLoadFinishedCB(CCNode *listener,SEL_CallFuncN func);
    virtual void deleteLater();
    void destory();
protected:
    void onMoveInActionFinished(CCNode *node);
    void onMoveOutActionFinished(CCNode *node);
protected:
    CCNode *m_loadFinishedListener;
    SEL_CallFuncN m_loadFinishedFunc;
    std::string m_animName;
protected:
    BasNodeDelegateWidget *m_animDelegate;
    BasNodeDelegateWidget *m_labelDelegate;
protected:
    bool m_moveInFinished;
    bool m_deleteLater;
};

class BusyDialog : public SimpleBusyDialog
{
public:
    BusyDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~BusyDialog();
    void setCancelButton(const std::string &text,
                         const std::string &fontfamily = "",
                         int fontSize = 30,
                         const std::string &bgimg = "buttonbg");
    void setCancelVisible(bool visible);
    virtual void exec();
};

}
#endif
