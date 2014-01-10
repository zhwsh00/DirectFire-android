#ifndef _auotscrollwidget_h_
#define _auotscrollwidget_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
using namespace std;
#include "../base/scrollarea.h"
#include "fsizewidgetcontainer.h"
#include "absfixedsizewidget.h"

namespace uilib
{
/*
  Those widget not implemented completed
  we can some very complicated scroll effect
  in here
  */
class VerAutoScrollWidget : public BasScrollArea
{
public:
    VerAutoScrollWidget(const std::string &themeName = "",const std::string &themeBg = "",const CCSize &size = CCSizeMake(0,0));
    virtual ~VerAutoScrollWidget();
    void addFixedSizeWidget(BasFixedSizeWidget *widget);
    void delFixedSizeWidget(BasFixedSizeWidget *widget);
    void delAllFixedSizeWidget();
    void setSpacing(float space) { m_widgetContainer->setSpacing(space);}
    float getSpacing() { return m_widgetContainer->getSpacing();}
    virtual void delAllChild();
    int scrollItemCount() { return m_widgetContainer->fsizeChildCount();}
protected:
    void setTouchPriorityFinished();
protected:
    FSizeWidgetContainer *m_widgetContainer;
};

class HorAutoScrollWidget : public BasScrollArea
{
public:
    HorAutoScrollWidget(const std::string &themeName = "",const std::string &themeBg = "",const CCSize &size = CCSizeMake(0,0));
    virtual ~HorAutoScrollWidget();
    void addFixedSizeWidget(BasFixedSizeWidget *widget);
    void delFixedSizeWidget(BasFixedSizeWidget *widget);
    void delAllFixedSizeWidget();
    void setSpacing(float space) { m_widgetContainer->setSpacing(space);}
    float getSpacing() { return m_widgetContainer->getSpacing();}
    virtual void delAllChild();
    int scrollItemCount() { return m_widgetContainer->fsizeChildCount();}
protected:
    void setTouchPriorityFinished();
protected:
    FSizeWidgetContainer *m_widgetContainer;
};
}
#endif
