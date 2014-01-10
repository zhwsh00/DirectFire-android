#ifndef _askasfrienddialog_h_
#define _askasfrienddialog_h_
#include "uilib/uilib.h"

using namespace uilib;
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "cocos2d.h"
using namespace std;

class AskAsFriendDialog : public BasShowDialog
{
public:
    AskAsFriendDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~AskAsFriendDialog();
    void setOkCB(CCNode *listener,SEL_CallFuncND func);
    void setRejectCB(CCNode *listener,SEL_CallFuncND func);
    void setOkImg(const std::string &normal,const std::string &pressed);
    void setRejectImg(const std::string &normal,const std::string &pressed);
    void setAskInfo(const std::string &id,const std::string &name,const std::string &word,const std::string &head);
    const std::string &getAskId() { return m_askId;}
    virtual void exec();
protected:
    void finish();
protected:
    std::string m_okImg,m_okPressedImg;
    std::string m_rejectImg,m_rejectPressedImg;
protected:
    CCNode *m_okListener;
    SEL_CallFuncND m_okFunc;
    CCNode *m_rejectListener;
    SEL_CallFuncND m_rejectFunc;
protected:
    std::string m_askId,m_askName,m_askHead,m_askWord;
};
#endif
