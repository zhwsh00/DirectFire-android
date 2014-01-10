#include "fsizeccnodedelegate.h"

namespace uilib {

FSizeCCNodeDelegate::FSizeCCNodeDelegate(CCNode *node,const CCSize &size)
{
    m_node = node;
    m_size = size;
    bool scale = true;
    if(m_size.width == 0 && m_size.height == 0){
        scale = false;
        m_size = m_node->getContentSize();
    }
    this->CCNode::addChild(m_node);
    m_node->setAnchorPoint(ccp(0.5,0.5));
    m_node->setPosition(ccp(m_size.width / 2,m_size.height / 2));
    if(scale){
        CCSize csize = m_node->getContentSize();
        m_node->setScaleX(m_size.width / csize.width);
        m_node->setScaleY(m_size.height / csize.height);
    }
    setWidth(m_size.width);
    setHeight(m_size.height);
    setFixedSize(m_size);
}
FSizeCCNodeDelegate::~FSizeCCNodeDelegate()
{
    if(m_node){
        m_node->removeFromParentAndCleanup(true);
    }
}
void FSizeCCNodeDelegate::getFixedSize(CCSize &size)
{
    size = m_size;
}

}
