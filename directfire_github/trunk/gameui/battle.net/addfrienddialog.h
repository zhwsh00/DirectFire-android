#ifndef _addfrienddialog_h_
#define _addfrienddialog_h_
#include "cliententry/uimsgevent.h"

#include "uilib/uilib.h"
using namespace uilib;
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "cocos2d.h"
using namespace std;
class AddFriendDialog : public BasShowDialog
{
public:
    AddFriendDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~AddFriendDialog();
    void setAddImg(const std::string &normal,const std::string &pressed);
    void setAddCB(CCNode *listener,SEL_CallFuncND func);
    void getAskInfo(std::string &id,std::string &word);
    void setAddId(const std::string &id);
    virtual void exec();
protected:
    void finish();
protected:
    std::string m_addImg,m_addPressedImg;
protected:
    CCNode *m_addListener;
    SEL_CallFuncND m_addFunc;
protected:
    InputBox *m_idInput;
    InputBox *m_wordInput;
protected:
    std::string m_setId;
};

#endif
