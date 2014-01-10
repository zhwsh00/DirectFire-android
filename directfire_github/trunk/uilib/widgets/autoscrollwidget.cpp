#include "autoscrollwidget.h"

namespace uilib
{

VerAutoScrollWidget::VerAutoScrollWidget(const std::string &themeName,const std::string &themeBg,const CCSize &size)
    : BasScrollArea(themeName,themeBg,size)
{
    m_widgetContainer = new VFSizeWidgetContainer;
}
VerAutoScrollWidget::~VerAutoScrollWidget()
{

}
void VerAutoScrollWidget::addFixedSizeWidget(BasFixedSizeWidget *widget)
{
    m_widgetContainer->addFSizeWidget(widget);
}
void VerAutoScrollWidget::delFixedSizeWidget(BasFixedSizeWidget *widget)
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
void VerAutoScrollWidget::delAllFixedSizeWidget()
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
void VerAutoScrollWidget::delAllChild()
{
    m_widgetContainer->delAllChild();
}
void VerAutoScrollWidget::setTouchPriorityFinished()
{
    m_widgetContainer->setTouchPriority(this->touchPriority());
    m_widgetContainer->exec();
    m_widgetContainer->layout(true);
    CCSize size;
    m_widgetContainer->getContainerFixedSize(size);
    setContainer(m_widgetContainer,size,true);
    setDirection(kCCScrollViewDirectionVertical);
    m_widgetContainer->getAnchorSize(size.width,size.height);
}
HorAutoScrollWidget::HorAutoScrollWidget(const std::string &themeName,const std::string &themeBg,const CCSize &size)
    : BasScrollArea(themeName,themeBg,size)
{
    m_widgetContainer = new HFSizeWidgetContainer;
}
HorAutoScrollWidget::~HorAutoScrollWidget()
{

}
void HorAutoScrollWidget::addFixedSizeWidget(BasFixedSizeWidget *widget)
{
    m_widgetContainer->addFSizeWidget(widget);
}
void HorAutoScrollWidget::delFixedSizeWidget(BasFixedSizeWidget *widget)
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
void HorAutoScrollWidget::delAllFixedSizeWidget()
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
void HorAutoScrollWidget::delAllChild()
{
    m_widgetContainer->delAllChild();
}
void HorAutoScrollWidget::setTouchPriorityFinished()
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

