#ifndef _abssyspage_h_
#define _abssyspage_h_
#include <string>
#include <vector>

using namespace std;

#include "cocos2d.h"
using namespace cocos2d;
#include "uilib/uilib.h"
using namespace uilib;

class BasSysPage : public BasWidget
{
public:
    BasSysPage();
    virtual ~BasSysPage();
    virtual void initItem(){}
    virtual void moveInItem();
    virtual void moveOutItem();
    virtual void setInputBoxVisible(bool){}
protected:
    void onMoveoutFinished(CCNode *node);
};

#endif
