#include "basscalewidget.h"


BasScaleWidget::BasScaleWidget()
{

}
BasScaleWidget::~BasScaleWidget()
{

}
void BasScaleWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    //setScale(CCDirector::sharedDirector()->getWinSize().height / 1280.0);
}
