#include "scrollbar.h"
#include "../skin/absskin.h"
#include "frame.h"
#include "touchnode.h"

namespace uilib
{

ScrollBar::ScrollBar(ScrollBarEnum bar,UiThemeDef *theme,TouchNode *parent)
    : BasFrame(0,parent)
{
    if(bar == VScrollBar){
        m_skin = VScrollImageSkin::create(CCSizeMake(0,0),theme);
        this->CCNode::addChild(m_skin);
    }else if(bar == HScrollBar){
        m_skin = HScrollImageSkin::create(CCSizeMake(0,0),theme);
        this->CCNode::addChild(m_skin);
    }else{
        m_skin = 0;
    }
}
ScrollBar::~ScrollBar()
{

}
void ScrollBar::setScrollPercent(float percent)
{
    if(percent < 0.0) percent = 0.0;
    if(percent > 1.0) percent = 1.0;
    if(percent >= 0.0 && percent <= 1.0 && m_skin)
        ((ScrollImageSkin*)m_skin)->setIndicatorPercent(percent);
    else
        cout << "ScrollBar::setScrollPercent,invalid set,please check!" << endl;
}

}
