#ifndef _feedbackpage_h_
#define _feedbackpage_h_
#include "abssyspage.h"

class FeedBackPage : public BasSysPage
{
public:
    FeedBackPage();
    virtual ~FeedBackPage();
    virtual void moveInItem();
    virtual void moveOutItem();
    virtual void setInputBoxVisible(bool);
    void layoutCompleted();
protected:
    void onSendClicked(CCNode *node,void *data);
protected:
    virtual void initItem();
protected:
    bool m_itemInit;
protected:
    BasButton *m_sendButton;
    InputBox *m_titleInput;
    InputBox *m_contentInput;
};
#endif
