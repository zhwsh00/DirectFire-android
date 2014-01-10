#ifndef _chatfacingdialog_h_
#define _chatfacingdialog_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "absfixedsizewidget.h"

#include <string>
#include <vector>
using namespace std;

namespace uilib
{
class ChatFacingDialog : public BorderWidget
{
public:
    ChatFacingDialog(TouchNode *parent,const CCPoint &pos);
    virtual ~ChatFacingDialog();
    void show();
    void hide();
    void getUserClickedFacing(std::string &face);
    void setFacingClickCB(CCNode *node,SEL_CallFuncND func);
protected:
    void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    void init(int dummy=0);
    void onFaceClicked(CCNode *node,void *data);
protected:
    std::string m_facingBg;
protected:
    CCNode *m_faceListener;
    SEL_CallFuncND m_faceFunc;
protected:
    CCPoint m_pos;
    CCSize m_size;
    std::string m_clickedFace;
};
}
#endif
