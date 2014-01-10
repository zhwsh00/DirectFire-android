#ifndef _fsizenulldelegate_h_
#define _fsizenulldelegate_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "absfixedsizewidget.h"

#include <string>
using namespace std;

namespace uilib
{

class FSizeNullDelegate : public BasFixedSizeWidget
{
public:
    FSizeNullDelegate(const CCSize &size);
    virtual ~FSizeNullDelegate();
    virtual void getFixedSize(CCSize &size);
protected:
    CCSize m_size;
};

}
#endif
