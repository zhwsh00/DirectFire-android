#ifndef _querydialog_h_
#define _querydialog_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
using namespace std;

#include "../base/dialog.h"
#include "../widgets/absshowdialog.h"
namespace uilib
{

class QueryDialog : public BasDialog
{
public:
    QueryDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~QueryDialog();
    void setTextInfo(const std::string &text,const std::string &fontfamily = "",int fontSize = 28,ccColor3B color = ccBLACK);
    virtual void exec();
    void enableButtons(bool ok = true,bool retry = false,bool cancel = true);
    inline void setOkId(int id) { m_okId = id;}
    inline void setRetryId(int id) { m_retryId = id;}
    inline void setCancelId(int id) { m_cancelId = id;}
    void close();

    BasButton *getOkButton();
    BasButton *getRetryButton();
    BasButton *getCancelButton();
    void setOkClickCB(CCNode *node,SEL_CallFuncND func);
    void setRetryClickCB(CCNode *node,SEL_CallFuncND func);
    void setCancelClickCB(CCNode *node,SEL_CallFuncND func);
protected:
    virtual void onButtonClicked(CCNode *pSender,void *index);
protected:
    void onClosed(CCNode *pSender);
protected:
    int m_okId;
    int m_retryId;
    int m_cancelId;
    std::string m_msg;
    CCNode *m_okListener;
    SEL_CallFuncND m_okFunc;
    CCNode *m_retryListener;
    SEL_CallFuncND m_retryFunc;
    CCNode *m_cancelListener;
    SEL_CallFuncND m_cancelFunc;
};
}
#endif
