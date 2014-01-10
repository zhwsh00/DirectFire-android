#include "autofitwidget.h"

namespace uilib
{
AutoFitWidget::AutoFitWidget(CCNode *node)
{
    m_node = node;
    this->CCNode::addChild(node);
}
AutoFitWidget::~AutoFitWidget()
{
    if(m_node)
        m_node->removeFromParentAndCleanup(true);
}
void AutoFitWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    CCSize size = m_node->getContentSize();
    m_node->setScaleX(m_anchorWidth / size.width);
    m_node->setScaleY(m_anchorHeight / size.height);
    m_node->setAnchorPoint(ccp(0.5,0.5));
    m_node->setPosition(ccp(m_anchorWidth / 2,m_anchorHeight / 2));
}
}
