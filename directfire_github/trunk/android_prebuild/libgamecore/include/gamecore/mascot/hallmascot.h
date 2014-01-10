#ifndef _hallmascot_h_
#define _hallmascot_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
using namespace std;

#include "uilib/uilib.h"
using namespace uilib;

#include "gamecore/resource/resourcemgr.h"

class HallMascot : public BasWidget
{
public:
    HallMascot();
    virtual ~HallMascot();
    void finish();
    void moveIn();
    void moveOut();
    void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchMoveInEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchMoveOutEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
    void addButton(const std::string &text);
    void setButtonCB(CCNode *listener,SEL_CallFuncND func);

    void onChangeHallMascotFace(CCNode *sender);
    void onMascotFaceFinished(CCNode *sender,void *data);

    void layoutCompleted();
protected:
    PopButtonsDialog *m_popDialog;
    BasAnimSprite *m_sheepFace1;
    BasAnimSprite *m_sheepFace2;
    CCSprite *m_sheepBasic;

    BasNodeDelegateWidget *m_basicDele;
    BasNodeDelegateWidget *m_face1Dele;
    BasNodeDelegateWidget *m_face2Dele;
protected:
    CCNode *m_buttonListener;
    SEL_CallFuncND m_buttonFunc;
    std::vector<std::string> m_buttons;
private:
    CCPoint m_origPos;
    CCPoint m_pressStartPos;
    CCPoint m_pressEndPos;
};

#endif
