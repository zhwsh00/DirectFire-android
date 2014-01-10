#ifndef _chatwidgetlayer_h_
#define _chatwidgetlayer_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "absfixedsizewidget.h"

#include <string>
using namespace std;

namespace uilib
{

class ChatWidgetLayer : public BasFixedSizeWidget
{
public:
    ChatWidgetLayer(float width);
    virtual ~ChatWidgetLayer();
    virtual void getFixedSize(CCSize &size);
    void setHeadWidget(BasFixedSizeWidget *head);
    void setHeadWidth(float width);
    void addContentWidget(BasFixedSizeWidget *content);
    void exec();
protected:
    void doLayout();
protected:
    BasFixedSizeWidget *m_headWidget;
    std::vector<BasFixedSizeWidget *> m_widgets;
protected:
    float m_widgetWidth;
    float m_fixedWidth;
    float m_fixedHeight;
    float m_headWidth;
protected:
    bool m_layed;
};

}
#endif
