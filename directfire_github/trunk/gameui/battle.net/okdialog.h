#ifndef _okdialog_h_
#define _okdialog_h_
#include <string>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"
using namespace uilib;

class OkDialog : public BasShowDialog
{
public:
    OkDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~OkDialog();
    virtual void exec();
    
    void setDialogContent(const std::string &content);
    void setOnOkClickedCB(CCNode *listener, SEL_CallFuncND func);
    
protected:
    void onOkClicked(CCNode *node,void *data);
    void onClosedClicked(CCNode *node,void *data);
    
protected:
    void finish();
    
protected:
    SEL_CallFuncND m_okClickedFunc;
    CCNode *m_okClickedListener;
    
private:
    std::string m_content;
};

#endif
