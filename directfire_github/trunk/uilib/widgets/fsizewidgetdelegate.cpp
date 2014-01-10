#include "fsizewidgetdelegate.h"

namespace uilib {

FSizeWidgetDelegate::FSizeWidgetDelegate(BasWidget *widget,const CCSize &size)
{
    m_widget = widget;
    m_size = size;
    if(m_size.width == 0 && m_size.height == 0){
        m_size.width = m_widget->getWidth();
        m_size.height = m_widget->getHeight();
    }
    this->addChild(m_widget);
    m_widget->setCenterIn("parent");
    setWidth(m_size.width);
    setHeight(m_size.height);
    setFixedSize(m_size);
}
FSizeWidgetDelegate::~FSizeWidgetDelegate()
{
    if(m_widget)
        this->delChild(m_widget);
}
void FSizeWidgetDelegate::getFixedSize(CCSize &size)
{
    size = m_size;
}

}
