#ifndef _sendmsganim_h_
#define _sendmsganim_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
using namespace std;

#include "uilib/uilib.h"
using namespace uilib;

class SendMsgAnim : public CCSprite
{
public:
    SendMsgAnim(CCNode *parent,const CCPoint &pos,const std::string &theme = "default",const std::string &name = "uimailsending");
    virtual ~SendMsgAnim();
    void setTheme(const std::string &theme = "default",const std::string &anim = "uimailsending");
    void exec();
protected:
    void onActionFinished(CCNode *);
protected:
    std::string m_theme;
    std::string m_animName;
    CCPoint m_pos;
};

#endif
