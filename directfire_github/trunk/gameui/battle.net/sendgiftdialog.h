#ifndef _sendgiftdialog_h_
#define _sendgiftdialog_h_
#include "uilib/uilib.h"
#include "cliententry/uimsgevent.h"

using namespace uilib;
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "cocos2d.h"
using namespace std;

class SendGiftDialog : public BasShowDialog
{
public:
    SendGiftDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~SendGiftDialog();
    void setSendCB(CCNode *node,SEL_CallFuncND func);
    void setSendImg(const std::string &normal,const std::string &pressed);
    void setSendtoInfo(const std::string &name,const std::string &portrait);
    void addProp(int propId,int propNum);
    void getSendProp(std::vector<UiMsgEv::GiftPropEv> &props,std::string &word);
    virtual void exec();
protected:
    void finish();
protected:
    void onIncButtonClicked(CCNode *node,void *data);
    void onDecButtonClicked(CCNode *node,void *data);
protected:
    std::string m_sendImg,m_sendPressedImg;
protected:
    InputBox *m_input;
protected:
    std::string m_sendtoName;
    std::string m_sendtoPortrait;
protected:
    CCNode *m_sendListener;
    SEL_CallFuncND m_sendFunc;
protected:
    BasWidget *m_bottomWidget;
    VerScrollWidget *m_propScrollWidget;
    BasWidget *m_headWidget;
protected:
    typedef struct GiftPropDef
    {
        GiftPropDef(int id,int count){
            m_id = id;
            m_count = count;
            m_sendCount = 0;
            m_incButton = m_decButton = 0;
            m_sendNum = 0;
        }

        int m_index;
        int m_id;
        int m_count;
        BasButton *m_incButton;
        BasButton *m_decButton;
        CCLabelBMFont *m_sendNum;
        int m_sendCount;
    }GiftPropDef;

    std::vector<GiftPropDef> m_hasProps;
};
#endif
