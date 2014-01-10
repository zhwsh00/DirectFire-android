#include "filltestwidget.h"
#include "../skin/absskin.h"
#include "../actions/absnodeaction.h"

namespace uilib
{

FillTestWidget::FillTestWidget(TouchNode *parent)
{
    parent->addChild(this);
    this->setFill("parent");
    this->setMargins(0);
}
FillTestWidget::~FillTestWidget()
{

}
void FillTestWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(m_skin == 0){
        BasSkin *skin = BorderImageSkin::create(CCSizeMake(m_anchorWidth,m_anchorHeight),"default","inputbg");
        setSkin(skin);
    }
}

}
