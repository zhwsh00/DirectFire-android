#ifndef _invitetoroomdialog_h_
#define _invitetoroomdialog_h_
#include "uilib/uilib.h"
#include "cliententry/uimsgevent.h"

using namespace uilib;
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "gamecore/serverinterface.h"

class InviteToRoomDialog : public BasShowDialog
{
public:
    InviteToRoomDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~InviteToRoomDialog();
    virtual void exec();
    void setInviter(const std::string &id,const std::string &mail = "",const std::string &nick="");
protected:
    void onAcceptClickd(CCNode *node,void *data);
    void onRejectClicked(CCNode *node,void *data);
    void onClosedClicked(CCNode *node,void *data);
    void counterDownFinish(float dt);
protected:
    void finish();
protected:
    std::string m_inviterId,m_inviterMail,m_inviterNick;
    ServerInterface *m_serverIFace;
};

#endif
