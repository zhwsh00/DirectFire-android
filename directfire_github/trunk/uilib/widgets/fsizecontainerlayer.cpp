#include "fsizecontainerlayer.h"

namespace uilib {

FSizeContainerLayer::FSizeContainerLayer()
{
    m_spacing = 5;
    m_fixedWidth = 0;
    m_fixedHeight = 0;
}
FSizeContainerLayer::~FSizeContainerLayer()
{

}
void FSizeContainerLayer::addContainer(FSizeWidgetContainer *container)
{
    m_containers.push_back(container);
    this->addChild(container);
}
void FSizeContainerLayer::getLayerFixedSize(CCSize &size)
{
    size.width = m_fixedWidth;
    size.height = m_fixedHeight;
}

VFSizeContainerLayer::VFSizeContainerLayer()
{

}
VFSizeContainerLayer::~VFSizeContainerLayer()
{

}
void VFSizeContainerLayer::exec()
{
    FSizeWidgetContainer *w;
    std::list<FSizeWidgetContainer*>::iterator iter;
    m_fixedWidth = 0;
    m_fixedHeight = 0;
    std::string topname;
    CCSize csize;
    int index = 0;
    int size = m_containers.size();
    for(iter = m_containers.begin();iter != m_containers.end();iter++,index++){
        w = *iter;
        w->getContainerFixedSize(csize);
        if(m_fixedWidth < csize.width)
            m_fixedWidth = csize.width;
        m_fixedHeight += csize.height;
        if(topname.empty()){
            w->setTop("parent",uilib::Top);
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
    setWidth(m_fixedWidth);
    setHeight(m_fixedHeight);
}

HFSizeContainerLayer::HFSizeContainerLayer()
{

}
HFSizeContainerLayer::~HFSizeContainerLayer()
{

}
void HFSizeContainerLayer::exec()
{
    FSizeWidgetContainer *w;
    std::list<FSizeWidgetContainer*>::iterator iter;
    m_fixedWidth = 0;
    m_fixedHeight = 0;
    std::string leftname;
    CCSize csize;
    int index = 0;
    int size = m_containers.size();
    for(iter = m_containers.begin();iter != m_containers.end();iter++,index++){
        w = *iter;
        w->getContainerFixedSize(csize);
        if(m_fixedHeight < csize.height)
            m_fixedHeight = csize.height;
        m_fixedWidth += csize.width;
        if(leftname.empty()){
            w->setLeft("parent",uilib::Left);
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
    setWidth(m_fixedWidth);
    setHeight(m_fixedHeight);
}

}
