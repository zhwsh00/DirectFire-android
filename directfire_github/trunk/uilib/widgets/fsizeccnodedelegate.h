#ifndef _fsizeccnodedelegate_h_
#define _fsizeccnodedelegate_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "absfixedsizewidget.h"

#include <string>
using namespace std;

namespace uilib
{

class FSizeCCNodeDelegate : public BasFixedSizeWidget
{
public:
    FSizeCCNodeDelegate(CCNode *node,const CCSize &size = CCSizeMake(0,0));
    virtual ~FSizeCCNodeDelegate();
    virtual void getFixedSize(CCSize &size);
    CCNode *getNode() { return m_node;}
protected:
    CCNode *m_node;
    CCSize m_size;
};

}
#endif
