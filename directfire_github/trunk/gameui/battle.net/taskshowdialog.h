#ifndef _taskshowdialog_h_
#define _taskshowdialog_h_
#include "uilib/uilib.h"

using namespace uilib;
#include <string>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

#include "cocos2d.h"
using namespace std;

#include "cliententry/uimsgevent.h"
#include "cliententry/uimsghandler.h"

class TaskShowDialog : public BasShowDialog
{
public:
    TaskShowDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~TaskShowDialog();
    void setDrawCB(CCNode *listener,SEL_CallFuncND func);
    void setDrawImg(const std::string &normal,const std::string &pressed);
    void setAwardTaskInfo(UiMsgEv::AwardTaskInfo *info);
    void getTaskRuleKey(std::string &key);
    virtual void exec();
protected:
    int getTaskDescIdFromTaskKey(const std::string &key);
    void finish();
protected:
    void onShowAnimFinished(CCNode *node);
protected:
    std::string m_drawImg,m_drawPressedImg;
protected:
    CCNode *m_drawListener;
    SEL_CallFuncND m_drawFunc;
protected:
    UiMsgEv::AwardTaskInfo *m_taskInfo;
};
#endif
