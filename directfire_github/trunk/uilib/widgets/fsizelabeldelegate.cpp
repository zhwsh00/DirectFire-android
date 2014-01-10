#include "fsizelabeldelegate.h"

namespace uilib {

FSizeLabelDelegate::FSizeLabelDelegate(CCLabelTTF *label,const CCSize &size)
{
    m_label = label;
    m_size = size;
    if(m_size.width == 0 && m_size.height == 0)
        m_size = m_label->getTexture()->getContentSize();
    this->CCNode::addChild(m_label);
    setWidth(m_size.width);
    setHeight(m_size.height);
    setFixedSize(m_size);
    m_label->setAnchorPoint(ccp(0.5,0.5));
    m_label->setPosition(ccp(m_size.width / 2,m_size.height / 2));
}
FSizeLabelDelegate::~FSizeLabelDelegate()
{

}
void FSizeLabelDelegate::getFixedSize(CCSize &size)
{
    size = m_size;
}

}
