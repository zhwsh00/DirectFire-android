#ifndef _taskwidget_h_
#define _taskwidget_h_
#include "uilib/uilib.h"
#include "gamecore/serverinterface.h"

using namespace uilib;

class TaskShowDialog;
class TaskWidget : public BasWidget
{
public:
    TaskWidget(BasWidget *parent);
    virtual ~TaskWidget();
    void taskUpdated();
    void setTheme(const std::string &theme,const std::string &has,const std::string &no);
    void finish();
    void layoutCompleted();
protected:
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    void onTaskDialogCloseClicked(CCNode *node,void *data);
    void onTaskDialogDrawClicked(CCNode *node,void *data);
protected:
    bool m_inited;
    std::string m_theme;
    std::string m_hasImg;
protected:
    CCSprite *m_hasSprite;
protected:
    bool m_has;
    ServerInterface *m_serverIface;
protected:
    TaskShowDialog *m_showDialog;
};


#endif
