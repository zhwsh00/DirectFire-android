#ifndef _mailwidget_h_
#define _mailwidget_h_
#include "uilib/uilib.h"
#include "gamecore/serverinterface.h"

using namespace uilib;

class SendMsgDialog;
class MailWidget : public BasWidget
{
public:
    MailWidget(BasWidget *parent);
    virtual ~MailWidget();
    void mailUpdated();
    void setTheme(const std::string &theme,const std::string &mail,const std::string &nomail);
    void finish();
    void layoutCompleted();
protected:
    virtual bool getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size);
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    void onMailDialogCloseClicked(CCNode *node,void *data);
    void onMailDialogSendClicked(CCNode *node,void *data);
protected:
    bool m_inited;
    std::string m_theme;
    std::string m_mailImg;
protected:
    CCSprite *m_mailSprite;
protected:
    bool m_hasMail;
    ServerInterface *m_serverIface;
protected:
    SendMsgDialog *m_mailDialog;
    std::string m_senderId;
    std::string m_senderName;
};

#endif
