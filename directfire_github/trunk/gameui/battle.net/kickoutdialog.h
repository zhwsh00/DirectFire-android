#ifndef _kickoutdialog_h_
#define _kickoutdialog_h_
#include <string>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"
using namespace uilib;

class KickOutDialog : public BasShowDialog
{
public:
    KickOutDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~KickOutDialog();
    void setKickerInfo(const std::string &nick,std::string *head);
    void setOkCB(CCNode *node,SEL_CallFuncND func);
    virtual void exec();
protected:
    void finish();
protected:
    std::string m_kickId;
    std::string *m_headPortrait;
protected:
    CCNode *m_okListener;
    SEL_CallFuncND m_okFunc;
};
#endif
