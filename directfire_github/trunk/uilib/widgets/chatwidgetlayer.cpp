#include "chatwidgetlayer.h"
#include "filltestwidget.h"

namespace uilib
{
ChatWidgetLayer::ChatWidgetLayer(float width)
{
    m_widgetWidth = width;
    m_fixedWidth = 0;
    m_fixedHeight = 0;
    m_headWidth = 0;
    m_layed = false;
}
ChatWidgetLayer::~ChatWidgetLayer()
{

}
void ChatWidgetLayer::getFixedSize(CCSize &size)
{
    size.width = m_fixedWidth;
    size.height = m_fixedHeight;
}
void ChatWidgetLayer::setHeadWidget(BasFixedSizeWidget *head)
{
    m_headWidget = head;
    this->addChild(head);
}
void ChatWidgetLayer::setHeadWidth(float width)
{
    m_headWidth = width;
}
void ChatWidgetLayer::addContentWidget(BasFixedSizeWidget *content)
{
    m_widgets.push_back(content);
    this->addChild(content);
}
void ChatWidgetLayer::exec()
{
    CCSize headSize;
    m_headWidget->getFixedSize(headSize);
    float maxRowHeight = headSize.height;
    if(m_widgets.size() == 0){
        m_fixedWidth = m_widgetWidth;
        m_fixedHeight = headSize.height;
        m_headWidget->setLeft("parent",uilib::Left);
        m_headWidget->setVertical("parent",0.5);
        setWidth(m_fixedWidth);
        setHeight(m_fixedHeight);
        return;
    }
    std::vector<int> rowsCount;
    std::vector<CCSize> widgetSizes;
    if(1){
        //get the maxRowHeight
        CCSize fsize;
        for(unsigned int i = 0;i < m_widgets.size();i++){
            m_widgets[i]->getFixedSize(fsize);
            if(fsize.height > maxRowHeight)
                maxRowHeight = fsize.height;
        }
    }
    int itemCount = 0;
    float rowLeft = m_widgetWidth - headSize.width;//first ,begin with head
    for(unsigned int i = 0;i < m_widgets.size();i++){
        //distribute widget to multi-rows
        CCSize fsize;
        m_widgets[i]->getFixedSize(fsize);
        widgetSizes.push_back(fsize);
        if(fsize.width <= rowLeft){
            itemCount++;
            rowLeft -= fsize.width;
        }else{
            rowsCount.push_back(itemCount);
            itemCount = 1;
            rowLeft = m_widgetWidth - m_headWidth;
        }
    }
    if(rowsCount.size() == 0){
        rowsCount.push_back(m_widgets.size());
    }else if(itemCount != 0){
        rowsCount.push_back(itemCount);
    }
    //real anchor
    m_fixedWidth = m_widgetWidth;
    m_fixedHeight = rowsCount.size() * maxRowHeight;
    setWidth(m_fixedWidth);
    setHeight(m_fixedHeight);
    int index = 0;
    for(unsigned int i = 0;i < rowsCount.size();i++){
        int itemCount = rowsCount[i];
        float hor = i == 0 ? headSize.width : m_headWidth;
        float ver = m_fixedHeight * (i + 1) / rowsCount.size();
        if(i == 0){
            //handle headwidget
            m_headWidget->setLeft("parent",uilib::Left);
            m_headWidget->setVertical("parent",(ver - headSize.height/2) / m_fixedHeight);
        }
        for(int k = 0;k < itemCount;k++,index++){
            BasFixedSizeWidget *widget = m_widgets[index];
            CCSize &wsize = widgetSizes[index];
            if(1){
                //hor
                widget->setHorizontal("parent",(hor + wsize.width/2) / m_fixedWidth);
                hor += wsize.width;
            }
            if(1){
                //ver
                widget->setVertical("parent",(ver - wsize.height/2) / m_fixedHeight);
            }
        }
    }
}
void ChatWidgetLayer::doLayout()
{
    if(m_layed)
        return;
    BasFixedSizeWidget::doLayout();
    m_layed = true;
}

}
