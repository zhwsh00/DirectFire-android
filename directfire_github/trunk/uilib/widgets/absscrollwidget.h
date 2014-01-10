#ifndef _absscrollwidget_h_
#define _absscrollwidget_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
using namespace std;
#include "../base/scrollarea.h"
#include "fsizewidgetcontainer.h"
#include "absfixedsizewidget.h"

namespace uilib
{
class VerScrollWidget : public BasScrollArea
{
public:
    VerScrollWidget(const std::string &themeName = "",const std::string &themeBg = "",const CCSize &size = CCSizeMake(0,0));
    virtual ~VerScrollWidget();
    void addFixedSizeWidget(BasFixedSizeWidget *widget);
    void delFixedSizeWidget(BasFixedSizeWidget *widget);
    void delAllFixedSizeWidget();
    void setSpacing(float space) { m_widgetContainer->setSpacing(space);}
    float getSpacing() { return m_widgetContainer->getSpacing();}
    virtual void delAllChild();
    int scrollItemCount() { return m_widgetContainer->fsizeChildCount();}
    virtual void listenerPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void listenerMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual bool listenerReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    void setTouchPriorityFinished();
protected:
    FSizeWidgetContainer *m_widgetContainer;
};
class HorScrollWidget : public BasScrollArea
{
public:
    HorScrollWidget(const std::string &themeName = "",const std::string &themeBg = "",const CCSize &size = CCSizeMake(0,0));
    virtual ~HorScrollWidget();
    void addFixedSizeWidget(BasFixedSizeWidget *widget);
    void delFixedSizeWidget(BasFixedSizeWidget *widget);
    void delAllFixedSizeWidget();
    void setSpacing(float space) { m_widgetContainer->setSpacing(space);}
    float getSpacing() { return m_widgetContainer->getSpacing();}
    virtual void delAllChild();
    int scrollItemCount() { return m_widgetContainer->fsizeChildCount();}
    virtual void listenerPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void listenerMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual bool listenerReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    void setTouchPriorityFinished();
protected:
    FSizeWidgetContainer *m_widgetContainer;
};
}
#endif
