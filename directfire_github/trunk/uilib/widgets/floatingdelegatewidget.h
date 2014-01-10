#ifndef _floatingdelegatewidget_h_
#define _floatingdelegatewidget_h_
#include "../base/widget.h"

namespace uilib
{

class FloatingDelegateWidget : public BasWidget
{
public:
    FloatingDelegateWidget(TouchNode *parent,BasWidget *widget,const CCSize &size = CCSizeMake(0,0),const CCPoint &pos = ccp(-1,-1),const std::string &theme = "default",const std::string &bg = "inputbg");
    virtual ~FloatingDelegateWidget();
    void setMoveInTime(float time);
    void setMoveOutTime(float time);
protected:
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    void onMoveOutActionFinished(CCNode *sender);
    void onMoveInActionFinished(CCNode *sender);
protected:
    BasWidget *m_widget;
    std::string m_theme;
    std::string m_bg;
};

}
#endif
