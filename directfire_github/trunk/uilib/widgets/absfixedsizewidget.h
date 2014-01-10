#ifndef _absfixedsizewidget_h_
#define _absfixedsizewidget_h_
#include "../base/widget.h"

namespace uilib
{

class BasFixedSizeWidget : public BasWidget
{
public:
    BasFixedSizeWidget();
    virtual ~BasFixedSizeWidget();
    virtual void getFixedSize(CCSize &size) = 0;
    void setAnchorType(uilib::AnchorType type) { m_type = type;}
    uilib::AnchorType getAnchorType() { return m_type;}
protected:
    uilib::AnchorType m_type;
};
}
#endif
