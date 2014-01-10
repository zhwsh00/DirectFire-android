#ifndef _autofitwidget_h_
#define _autofitwidget_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
using namespace std;

#include "../base/widget.h"

namespace uilib
{
class AutoFitWidget : public BasWidget
{
public:
    AutoFitWidget(CCNode *node);
    virtual ~AutoFitWidget();
    void layoutCompleted();
    CCNode *getNode() { return m_node;}
protected:
    CCNode *m_node;
};
}
#endif
