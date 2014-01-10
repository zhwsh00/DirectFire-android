#ifndef _delfrienddialog_h_
#define _delfrienddialog_h_
#include "uilib/uilib.h"
#include "cliententry/uimsgevent.h"

using namespace uilib;
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "cocos2d.h"
using namespace std;

class DelFriendDialog : public BasShowDialog
{
public:
    DelFriendDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~DelFriendDialog();
    void setOkCB(CCNode *listener,SEL_CallFuncND func);
    void setOkImg(const std::string &normal,const std::string &pressed);
    void setDelInfo(const std::string &id,const std::string &name,const std::string &head);
    virtual void exec();
protected:
    void finish();
protected:
    std::string m_okImg,m_okPressedImg;
protected:
    CCNode *m_okListener;
    SEL_CallFuncND m_okFunc;
protected:
    std::string m_delId,m_delName,m_delHead;
};

#endif
