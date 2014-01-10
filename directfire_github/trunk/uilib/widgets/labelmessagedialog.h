#ifndef _labelmessagedialog_h_
#define _labelmessagedialog_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "absfixedsizewidget.h"
#include "absscrollwidget.h"
#include "../base/dialog.h"

#include <string>
using namespace std;

namespace uilib
{

class LabelMessageDialog : public BasDialog
{
public:
    LabelMessageDialog(CCNode *parent,const std::string &theme = "default",const std::string &bg = "dialog",const CCSize &size = CCSizeMake(0,0));
    virtual ~LabelMessageDialog();
    void setCloseName(const std::string &name);
    void setTitleName(const std::string &name);
    void addFixedSizeWidget(BasFixedSizeWidget *w);
    void setSpacing(float space) { m_scrollWidget->setSpacing(space);}
    float getSpacing() { return m_scrollWidget->getSpacing();}
    virtual void exec();    
    void close();
    virtual void setOnClosed(CCNode *listener, SEL_CallFuncN func);
protected:
    void onCloseClicked(CCNode *node,void *data);
    void onMoveOutActionFinished(CCNode *node);
protected:
    VerScrollWidget *m_scrollWidget;
    std::string m_closeName;
    std::string m_titleName;
protected:
    CCNode *m_closeListener;
    SEL_CallFuncN m_closeFunc;
protected:
    CCLayerColor *m_colorLayer;
};
}
#endif
