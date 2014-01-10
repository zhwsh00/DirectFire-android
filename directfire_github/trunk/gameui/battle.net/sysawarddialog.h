#ifndef _sysawarddialog_h_
#define _sysawarddialog_h_
#include "uilib/uilib.h"

using namespace uilib;
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "cocos2d.h"
using namespace std;

class SysAwardDialog : public BasShowDialog
{
public:
    SysAwardDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~SysAwardDialog();
    virtual void exec();
protected:
    void finished();
};

#endif
