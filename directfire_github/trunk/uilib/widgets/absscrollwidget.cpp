#include "absscrollwidget.h"
#include "filltestwidget.h"

namespace uilib {
VerScrollWidget::VerScrollWidget(const std::string &themeName,const std::string &themeBg,const CCSize &size)
    : BasScrollArea(themeName,themeBg,size)
{
    m_widgetContainer = new VFSizeWidgetContainer;
}
VerScrollWidget::~VerScrollWidget()
{

}
void VerScrollWidget::addFixedSizeWidget(BasFixedSizeWidget *widget)
{
    m_widgetContainer->addFSizeWidget(widget);
}
void VerScrollWidget::delFixedSizeWidget(BasFixedSizeWidget *widget)
{
    m_widgetContainer->delFSizeWidget(widget);
    m_widgetContainer->setTouchPriority(this->touchPriority());
    m_widgetContainer->exec();
    m_widgetContainer->layout(true);
    CCSize size;
    m_widgetContainer->getContainerFixedSize(size);
    setContainer(m_widgetContainer,size,true);
    setDirection(kCCScrollViewDirectionVertical);
}
void VerScrollWidget::delAllFixedSizeWidget()
{
    if(m_widgetContainer->fsizeChildCount() == 0)
        return;
    m_widgetContainer->delAllChild();
    m_widgetContainer->setTouchPriority(this->touchPriority());
    m_widgetContainer->exec();
    m_widgetContainer->layout(true);
    CCSize size;
    m_widgetContainer->getContainerFixedSize(size);
    setContainer(m_widgetContainer,size,true);
    setDirection(kCCScrollViewDirectionVertical);
}
void VerScrollWidget::delAllChild()
{
    m_widgetContainer->delAllChild();
}
void VerScrollWidget::listenerPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    m_viewDelegate->listenerPressEvent(pTouch,pEvent);
}
void VerScrollWidget::listenerMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    m_viewDelegate->listenerMoveEvent(pTouch,pEvent);
}
bool VerScrollWidget::listenerReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    return m_viewDelegate->listenerReleaseEvent(pTouch,pEvent);
}
void VerScrollWidget::setTouchPriorityFinished()
{
    m_widgetContainer->setTouchPriority(this->touchPriority());
    m_widgetContainer->exec();
    m_widgetContainer->layout(true);
    CCSize size;
    m_widgetContainer->getContainerFixedSize(size);
    setContainer(m_widgetContainer,size,true);
    setDirection(kCCScrollViewDirectionVertical);
}
HorScrollWidget::HorScrollWidget(const std::string &themeName,const std::string &themeBg,const CCSize &size)
 : BasScrollArea(themeName,themeBg,size)
{
    m_widgetContainer = new HFSizeWidgetContainer;
    m_widgetContainer->setMoveListener(this);
}
HorScrollWidget::~HorScrollWidget()
{

}
void HorScrollWidget::addFixedSizeWidget(BasFixedSizeWidget *widget)
{
    m_widgetContainer->addFSizeWidget(widget);
}
void HorScrollWidget::delFixedSizeWidget(BasFixedSizeWidget *widget)
{
    m_widgetContainer->delFSizeWidget(widget);
    m_widgetContainer->setTouchPriority(this->touchPriority());
    m_widgetContainer->exec();
    m_widgetContainer->layout(true);
    CCSize size;
    m_widgetContainer->getContainerFixedSize(size);
    setContainer(m_widgetContainer,size,false);
    setDirection(kCCScrollViewDirectionHorizontal);
}
void HorScrollWidget::delAllFixedSizeWidget()
{
    if(m_widgetContainer->fsizeChildCount() == 0)
        return;
    m_widgetContainer->delAllChild();
    m_widgetContainer->setTouchPriority(this->touchPriority());
    m_widgetContainer->exec();
    m_widgetContainer->layout(true);
    CCSize size;
    m_widgetContainer->getContainerFixedSize(size);
    setContainer(m_widgetContainer,size,false);
    setDirection(kCCScrollViewDirectionHorizontal);
}
void HorScrollWidget::delAllChild()
{
    m_widgetContainer->delAllChild();
}
void HorScrollWidget::listenerPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    m_viewDelegate->listenerPressEvent(pTouch,pEvent);
}
void HorScrollWidget::listenerMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    m_viewDelegate->listenerMoveEvent(pTouch,pEvent);
}
bool HorScrollWidget::listenerReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    return m_viewDelegate->listenerReleaseEvent(pTouch,pEvent);
}
void HorScrollWidget::setTouchPriorityFinished()
{
    m_widgetContainer->setTouchPriority(this->touchPriority());
    m_widgetContainer->exec();
    m_widgetContainer->layout(true);
    CCSize size;
    m_widgetContainer->getContainerFixedSize(size);
    setContainer(m_widgetContainer,size,false);
    setDirection(kCCScrollViewDirectionHorizontal);
}
}
