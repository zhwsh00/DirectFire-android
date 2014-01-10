#ifndef _propsyndialog_h_
#define _propsyndialog_h_
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"
using namespace uilib;

#include "prop/propdef.h"

class PropSynDialog : public BasShowDialog
{
public:
    PropSynDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~PropSynDialog();
    virtual void exec();
protected:
    void finish();
};
#endif
