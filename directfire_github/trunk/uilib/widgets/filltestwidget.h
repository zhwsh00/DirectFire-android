#ifndef _filltestwidget_h_
#define _filltestwidget_h_
#include "../base/widget.h"
#include "../base/touchnode.h"

namespace uilib
{
class FillTestWidget : public BasWidget
{
public:
    FillTestWidget(TouchNode *parent);
    virtual ~FillTestWidget();
    void layoutCompleted();
};
}
#endif
