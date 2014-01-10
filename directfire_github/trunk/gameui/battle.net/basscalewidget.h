#ifndef _basscalewidget_h_
#define _basscalewidget_h_
#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"
using namespace uilib;

class BasScaleWidget : public BasWidget
{
public:
    BasScaleWidget();
    virtual ~BasScaleWidget();
    virtual void layoutCompleted();
protected:
};

#endif
