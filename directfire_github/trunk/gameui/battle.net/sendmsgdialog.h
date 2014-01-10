#ifndef _sendmsgdialog_h_
#define _sendmsgdialog_h_
#include "uilib/uilib.h"
#include "cliententry/uimsgevent.h"

using namespace uilib;
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "cocos2d.h"
using namespace std;

class SendMsgDialog : public BasShowDialog
{
public:
    SendMsgDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~SendMsgDialog();
    virtual void exec();
    void setInitPage(bool send,bool show);
    void setInitShowPage(bool send);
    void setSendImg(const std::string &normal,const std::string &pressed);
    void setReplyImg(const std::string &normal,const std::string &pressed);
    void setBackImg(const std::string &normal,const std::string &pressed);
    void setSendCB(CCNode *listener,SEL_CallFuncND func);
    void setRecInfo(const std::string &id,const std::string &name,const std::string &portrait);
    void setSenderInfo(const std::string &id,const std::string &name,const std::string &portrait);
    void setMsgInfo(const std::string &title,const std::string &msg);
    void getSendMsg(std::string &title,std::string &word);
    void setCanReply(bool reply);
protected:
    void finish();
    void onReplyClicked(CCNode *node,void *data);
protected:
    std::string m_sendImg,m_sendPressedImg;
    std::string m_replyImg,m_replyPressedImg;
    std::string m_backImg,m_backPressedImg;
protected:
    InputBox *m_titleInput;
    InputBox *m_msgInput;
protected:
    CCNode *m_sendListener;
    SEL_CallFuncND m_sendFunc;
protected:
    std::string m_senderId,m_senderName,m_senderHead;
    std::string m_recId,m_recName,m_recHead;
    std::string m_msgTitle,m_msgWord;
protected:
    bool m_initPage;
    bool m_canReply;
    bool m_needSendPage;
    bool m_needShowPage;
protected:
    BasWidget *m_sendPage;
    BasWidget *m_showPage;
};
#endif
