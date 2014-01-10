#ifndef _fsizespritedelegate_h_
#define _fsizespritedelegate_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "absfixedsizewidget.h"

#include <string>
using namespace std;

namespace uilib
{

class FSizeSpriteDelegate : public BasFixedSizeWidget
{
public:
    FSizeSpriteDelegate(CCSprite *sprite,const CCSize &size = CCSizeMake(0,0));
    virtual ~FSizeSpriteDelegate();
    virtual void getFixedSize(CCSize &size);
    CCSprite *getSprite() { return m_sprite;}
protected:
    CCSprite *m_sprite;
    CCSize m_size;
};

}
#endif
