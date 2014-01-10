#ifndef _fsizewidgetdelegate_h_
#define _fsizewidgetdelegate_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "absfixedsizewidget.h"

#include <string>
using namespace std;

namespace uilib
{

class FSizeWidgetDelegate : public BasFixedSizeWidget
{
public:
    FSizeWidgetDelegate(BasWidget *widget,const CCSize &size = CCSizeMake(0,0));
    virtual ~FSizeWidgetDelegate();
    virtual void getFixedSize(CCSize &size);
    BasWidget *getWidget() { return m_widget;}
protected:
    BasWidget *m_widget;
    CCSize m_size;
};

}
#endif
