#ifndef _fsizecontainerlayer_h_
#define _fsizecontainerlayer_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "../base/widget.h"
#include "fsizewidgetcontainer.h"

#include <string>
#include <list>
using namespace std;

namespace uilib {
class FSizeContainerLayer : public BasWidget
{
public:
    FSizeContainerLayer();
    virtual ~FSizeContainerLayer();
    virtual void exec() = 0;
    void addContainer(FSizeWidgetContainer *);
    void setSpacing(float space) { m_spacing = space;}
    float getSpacing() { return m_spacing;}
    void getLayerFixedSize(CCSize &size);
protected:
    std::list<FSizeWidgetContainer*> m_containers;
protected:
    float m_spacing;
    float m_fixedWidth;
    float m_fixedHeight;
};
class VFSizeContainerLayer : public FSizeContainerLayer
{
public:
    VFSizeContainerLayer();
    virtual ~VFSizeContainerLayer();
    virtual void exec();
};
class HFSizeContainerLayer : public FSizeContainerLayer
{
public:
    HFSizeContainerLayer();
    virtual ~HFSizeContainerLayer();
    virtual void exec();
};
}
#endif
