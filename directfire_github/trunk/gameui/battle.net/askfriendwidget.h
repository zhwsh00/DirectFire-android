#ifndef _askfriendwidget_h_
#define _askfriendwidget_h_
#include "uilib/uilib.h"
using namespace uilib;
#include "gamecore/serverinterface.h"

using namespace uilib;

class AskAsFriendDialog;
class AddFriendDialog;
class AskFriendWidget : public BasWidget
{
public:
    AskFriendWidget(BasWidget *parent);
    virtual ~AskFriendWidget();
    void askFriendUpdated();
    void setTheme(const std::string &theme,const std::string &has,const std::string &no);
    void finish();
    void layoutCompleted();
protected:
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    void onAskDialogCloseClicked(CCNode *node,void *data);
    void onAskDialogOkClicked(CCNode *node,void *data);
    void onAskDialogRejectClicked(CCNode *node,void *data);
protected:
    void onAddFriendCloseClicked(CCNode *node,void *data);
    void onAddFriendAddClicked(CCNode *node,void *data);
protected:
    bool m_inited;
    std::string m_theme;
    std::string m_hasImg;
protected:
    CCSprite *m_hasSprite;
    BasWidget *m_hasWidget;
protected:
    bool m_has;
    ServerInterface *m_serverIface;
protected:
    AskAsFriendDialog *m_askDialog;
    AddFriendDialog *m_addDialog;
};

#endif
