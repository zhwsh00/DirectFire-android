#ifndef _fsizelabeldelegate_h_
#define _fsizelabeldelegate_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "absfixedsizewidget.h"

#include <string>
using namespace std;

namespace uilib
{

class FSizeLabelDelegate : public BasFixedSizeWidget
{
public:
    FSizeLabelDelegate(CCLabelTTF *label,const CCSize &size = CCSizeMake(0,0));
    virtual ~FSizeLabelDelegate();
    virtual void getFixedSize(CCSize &size);
    CCLabelTTF *getLabel() { return m_label;}
protected:
    CCLabelTTF *m_label;
    CCSize m_size;
};

}
#endif
