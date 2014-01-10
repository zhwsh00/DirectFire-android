#ifndef _fsizewidgetcontainer_h_
#define _fsizewidgetcontainer_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "absfixedsizewidget.h"
#include "../base/widget.h"

#include <string>
#include <vector>
#include <list>

using namespace std;

namespace uilib
{
class FSizeWidgetContainer : public BasWidget
{
public:
    FSizeWidgetContainer();
    virtual ~FSizeWidgetContainer();
    virtual void exec() = 0;
    void setContainerFixedSize(const CCSize &size);
    void getContainerFixedSize(CCSize &size);
    void addFSizeWidget(BasFixedSizeWidget *widget);
    void delFSizeWidget(BasFixedSizeWidget *widget);
    int fsizeChildCount() { return m_widgets.size();}
    void setSpacing(float space) { m_spacing = space;}
    float getSpacing() { return m_spacing;}
    virtual void delAllChild();
    void setAnchorType(uilib::AnchorType type) { m_type = type;}
    uilib::AnchorType getAnchorType() { return m_type;}
    void setMoveListener(TouchNode *node);
    virtual void listenerPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void listenerMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual bool listenerReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    std::list<BasFixedSizeWidget*> m_widgets;
    float m_spacing;
    float m_fixedWidth;
    float m_fixedHeight;
    AnchorType m_type;
protected:
    TouchNode *m_moveListener;
};

class VFSizeWidgetContainer : public FSizeWidgetContainer
{
public:
    VFSizeWidgetContainer();
    virtual ~VFSizeWidgetContainer();
    virtual void exec();
protected:
};
class HFSizeWidgetContainer : public FSizeWidgetContainer
{
public:
    HFSizeWidgetContainer();
    virtual ~HFSizeWidgetContainer();
    virtual void exec();
};
}
#endif
