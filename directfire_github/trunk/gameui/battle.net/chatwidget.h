#ifndef _chatwidget_h_
#define _chatwidget_h_
#include "uilib/uilib.h"

using namespace uilib;

#include "cliententry/uimsgevent.h"

#include "gamecore/resource/resourcemgr.h"

#include <string>
#include <vector>
#include <sstream>
using namespace std;

class ChatWidget : public BorderWidget
{
public:
    ChatWidget();
    virtual ~ChatWidget();
    void layoutCompleted();
    void setChaterInfo(const std::string &id,const std::string &mail,const std::string &nick = "");
    void setChatType(UiMsgEv::MsgSendObjType type);
    void clearChatType();
    void setRecInfo(const std::string &id,const std::string &mail,const std::string &nick = "");
    void setRecHead(std::string *head);
    const std::string &getRecId() { return m_recId;}
    void clearRecInfo();
    void setMsgGroup(const std::vector<std::string> &groups);
    void setSendImg(const std::string &normal,const std::string &pressed);
    void addChatInfo(UiMsgEv::ChatInfo *info,int group = 0);
    void clearAllChatInfo();
    void setHeadCanClick(bool can);
    void setHeadClickCB(CCNode *listener,SEL_CallFuncND func);
    void getHeadInfo(std::string &id,std::string &mail,std::string &nick,CCPoint &pos);
    void setChatBoxVisible(bool visible);
protected:
    void initInputBar();
    void initGroupingBar();
    void initScrollArea();
protected:
    void onInputBoxReturned(CCNode *sender);
protected:
    void onSendButtonClicked(CCNode *node,void *data);
    void onFacingClicked(CCNode *node,void *data);
    void onPhraseClicked(CCNode *node,void *data);
    void onChatToClicked(CCNode *node,void *data);
    void onGroupingButtonsClicked(CCNode *node,void *data);
protected:
    void onFacingDialogFaceClicked(CCNode *node,void *data);
    void onPhraseDialogPhraseClicked(CCNode *node,void *data);
protected:
    void sendChatInfo(const std::string &chat);
protected:
    void onHeadClicked(CCNode *node,void *data);
protected:
    std::vector<std::string> m_msgGroups;
protected:
    std::string m_sendImg,m_sendPressedImg;
protected:
    InputBox *m_inputBox;
    BasButton *m_sendButton;
    BasButton *m_facingButton;
    BasButton *m_phraseButton;
    BasButton *m_toButton;
    CCLabelTTF *m_toLabel;
    CCSprite *m_toHead;
protected:
    BasWidget *m_groupingWidget;
    std::vector<VerScrollWidget*> m_scrollWidgets;
    int m_focusIndex;
    bool m_autoScroll;
protected:
    UiThemeDef *m_uiDef;
    bool m_init;
protected:
    std::string m_userId;
    std::string m_userMail;
    std::string m_userNickName;
    int m_chatType;
    std::string m_recId;
    std::string m_recMail;
    std::string m_recNickName;
protected:
    ChatFacingDialog *m_facingDialog;
    ChatPhraseDialog *m_phraseDialog;
protected:
    bool m_headCanClicked;
    CCNode *m_headListener;
    SEL_CallFuncND m_headFunc;
    typedef struct ChaterInfo{
        std::string m_id;
        std::string m_mail;
        std::string m_nick;
    }ChaterInfo;
    std::map<std::string,ChaterInfo*> m_chaterMap;
    std::string m_clickChater;
    CCPoint m_headWorldPos;
    std::string m_headName;
};

#endif
