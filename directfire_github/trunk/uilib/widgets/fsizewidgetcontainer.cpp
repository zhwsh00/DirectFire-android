#include "fsizewidgetcontainer.h"
#include "filltestwidget.h"

namespace uilib {

FSizeWidgetContainer::FSizeWidgetContainer()
{
    m_spacing = 5;
    m_fixedWidth = 0;
    m_fixedHeight = 0;
    m_type = uilib::CenterIn;
    m_moveListener = 0;
}
FSizeWidgetContainer::~FSizeWidgetContainer()
{

}
void FSizeWidgetContainer::setContainerFixedSize(const CCSize &size)
{
    m_fixedWidth = size.width;
    m_fixedHeight = size.height;
}
void FSizeWidgetContainer::getContainerFixedSize(CCSize &size)
{
    size.width = m_fixedWidth;
    size.height = m_fixedHeight;
}
void FSizeWidgetContainer::addFSizeWidget(BasFixedSizeWidget *widget)
{
    m_widgets.push_back(widget);
    this->addChild(widget);
    widget->setParentMoveListening(true);
}
void FSizeWidgetContainer::delFSizeWidget(BasFixedSizeWidget *widget)
{
    std::list<BasFixedSizeWidget*>::iterator iter;
    for(iter = m_widgets.begin();iter != m_widgets.end();iter++){
        if(widget == *iter){
            if(widget->parent())
                widget->parent()->delChild(widget);
            else
                delete widget;
            m_widgets.erase(iter);
            return;
        }
    }
}
void FSizeWidgetContainer::delAllChild()
{
    m_widgets.clear();
    BasWidget::delAllChild();
}
void FSizeWidgetContainer::setMoveListener(TouchNode *node)
{
    m_moveListener = node;
}
void FSizeWidgetContainer::listenerPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_moveListener)
        m_moveListener->listenerPressEvent(pTouch,pEvent);
}
void FSizeWidgetContainer::listenerMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_moveListener)
        m_moveListener->listenerMoveEvent(pTouch,pEvent);
}
bool FSizeWidgetContainer::listenerReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_moveListener)
        return m_moveListener->listenerReleaseEvent(pTouch,pEvent);
    else
        return false;
}

VFSizeWidgetContainer::VFSizeWidgetContainer()
{

}
VFSizeWidgetContainer::~VFSizeWidgetContainer()
{

}
void VFSizeWidgetContainer::exec()
{
    CCSize csize;
    std::string topname;
    m_fixedWidth = m_fixedHeight = 0;
    std::list<BasFixedSizeWidget*>::iterator iter;
    int index = 0;
    int size = m_widgets.size();
    for(iter = m_widgets.begin();iter != m_widgets.end();iter++,index++){
        BasFixedSizeWidget *w = *iter;
        w->getFixedSize(csize);
        if(m_fixedWidth < csize.width)
            m_fixedWidth = csize.width;
        m_fixedHeight += csize.height;
        if(topname.empty()){
            w->setTop("parent",uilib::Top);
            w->setTopMargin(2);
        }else{
            w->setTop(topname,uilib::Bottom);
        }
        topname = w->getName();
        if(m_spacing > 0 && index != (size - 1)){
            NullFrame *null = new NullFrame();
            this->addChild(null);
            null->setWidth(m_fixedWidth);
            null->setHeight(m_spacing);
            m_fixedHeight += m_spacing;
            null->setHorizontal("parent",0.5);
            null->setTop(topname,uilib::Bottom);
            topname = null->getName();
        }
        uilib::AnchorType type = w->getAnchorType();
        switch(type){
        case uilib::Left:{
            w->setLeft("parent",type);
            break;
        }
        case uilib::Right:{
            w->setRight("parent",type);
            break;
        }
        case uilib::CenterIn:{
            w->setHorizontal("parent",0.5);
        }
        default:{
            break;
        }
        }
    }
    if(m_fixedWidth == 0) m_fixedWidth = 1;
    if(m_fixedHeight == 0) m_fixedHeight = 1;
    setWidth(m_fixedWidth);
    setHeight(m_fixedHeight);
}
HFSizeWidgetContainer::HFSizeWidgetContainer()
{

}
HFSizeWidgetContainer::~HFSizeWidgetContainer()
{

}
void HFSizeWidgetContainer::exec()
{
    m_fixedWidth = 0;
    m_fixedHeight = 0;
    CCSize csize;
    std::string leftname;
    std::list<BasFixedSizeWidget*>::iterator iter;
    int index = 0;
    int size = m_widgets.size();
    for(iter = m_widgets.begin();iter != m_widgets.end();iter++,index++){
        BasFixedSizeWidget *w = *iter;
        w->getFixedSize(csize);
        if(m_fixedHeight < csize.height)
            m_fixedHeight = csize.height;
        m_fixedWidth += csize.width;
        if(leftname.empty()){
            w->setLeft("parent",uilib::Left);
            w->setLeftMargin(2);
        }else{
            w->setLeft(leftname,uilib::Right);
        }
        leftname = w->getName();
        if(m_spacing > 0 && index != (size - 1)){
            NullFrame *null = new NullFrame();
            this->addChild(null);
            null->setWidth(m_spacing);
            m_fixedWidth += m_spacing;
            null->setHeight(m_fixedHeight);
            null->setVertical("parent",0.5);
            null->setLeft(leftname,uilib::Right);
            leftname = null->getName();
        }
        uilib::AnchorType type = w->getAnchorType();
        switch(type){
        case uilib::Top:{
            w->setTop("parent",type);
            break;
        }
        case uilib::Bottom:{
            w->setBottom("parent",type);
            break;
        }
        case uilib::CenterIn:{
            w->setVertical("parent",0.5);
        }
        default:{
            break;
        }
        }
    }
    if(m_fixedWidth == 0) m_fixedWidth = 1;
    if(m_fixedHeight == 0) m_fixedHeight = 1;
    setWidth(m_fixedWidth);
    setHeight(m_fixedHeight);
}
}
