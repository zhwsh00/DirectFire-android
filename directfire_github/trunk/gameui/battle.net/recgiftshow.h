#ifndef _recgiftshow_h_
#define _recgiftshow_h_
#include "uilib/uilib.h"
#include "cliententry/uimsgevent.h"

using namespace uilib;
#include <string>
#include <vector>
using namespace std;

#include "cocos2d.h"
using namespace std;

class RecGiftShow : public BasShowDialog
{
public:
    RecGiftShow(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~RecGiftShow();
    void setSendToMe(bool is) { m_isForMe = is;}
    void setSenderInfo(bool isFriend,const std::string &name,const std::string &word,const std::string &headPortrait = "");
    void setSenderContent(const std::vector<UiMsgEv::GiftPropEv> &gift);
    void setSendMsgImg(const std::string &normal,const std::string &pressed);
    void setSendGiftImg(const std::string &normal,const std::string &pressed);
    void setSendMsgCB(CCNode *node,SEL_CallFuncND func);
    void setSendGiftCB(CCNode *node,SEL_CallFuncND func);
    void setAddFriendCB(CCNode *node,SEL_CallFuncND func);
    void getReplyWord(std::string &title,std::string &word);
    std::vector<UiMsgEv::GiftPropEv> &getGiftsContainer() { return m_gifts;}
    void exec();
protected:
    void clear();
    void finished();
protected:
    void onHeadPortraitClicked(CCNode *node,void *data);
    void onPopButtonsClicked(CCNode *node,void *data);
protected:
    float m_edgeSize;
    bool m_isForMe;
protected:
    bool m_isFriend;
    CCNode *m_sendMsgListener;
    SEL_CallFuncND m_sendMsgFunc;
    CCNode *m_sendGiftListener;
    SEL_CallFuncND m_sendGiftFunc;
    CCNode *m_addFriendListener;
    SEL_CallFuncND m_addFriendFunc;
protected:
    std::string m_sendMsgImg,m_sendMsgPressedImg;
    std::string m_sendGiftImg,m_sendGiftPressedImg;
protected:
    InputBox *m_input;
protected:
    BasWidget *m_widgetBottom;
    BasWidget *m_widgetLeft;
    BasWidget *m_widgetRight;
    TextScrollArea *m_widgetWord;
protected:
    std::string m_senderName;
    std::string m_senderHead;
    std::string m_giftWord;
    std::vector<UiMsgEv::GiftPropEv> m_gifts;
};

#endif
