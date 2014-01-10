#ifndef _popbuttonsdialog_h_
#define _popbuttonsdialog_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
using namespace std;

#include "fsizewidgetcontainer.h"
#include "../actions/absnodeaction.h"

namespace uilib
{
class PopButtonsDialog : public BasWidget
{
public:
    PopButtonsDialog(TouchNode *parent,const CCPoint &pos);
    virtual ~PopButtonsDialog();
    void setTheme(const std::string &theme,const std::string &bg);
    void addButton(const std::string &text,const CCSize &size = CCSizeMake(0,0));
    void addButton(BasButton *button,const CCSize &size = CCSizeMake(0,0));
    void setButtonCB(CCNode *sender,SEL_CallFuncND func);
    void setMoveInTime(float time);
    void setMoveOutTime(float time);
    inline void setEdgeSize(float size) { m_edgeSize = size;}
    inline float getEdgeSize() { return m_edgeSize;}
    void setSpacing(float space);
    virtual void exec();
protected:
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    void onButtonClicked(CCNode *sender,void *data);
    void layoutCompleted();
    void onMoveInFinished(CCNode *node);
    void onMoveOutFinised(CCNode *node);
protected:
    std::string m_theme;
    std::string m_bg;
    float m_moveInTime;
    float m_moveOutTime;
    CCPoint m_pos;
protected:
    CCNode *m_buttonListener;
    SEL_CallFuncND m_buttonFunc;
    int m_buttonIndex;
    float m_edgeSize;
protected:
    VFSizeWidgetContainer *m_verContainer;
};
}

#endif
