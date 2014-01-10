#ifndef _scrollbar_h_
#define _scrollbar_h_
#include <string>
using namespace std;
#include "frame.h"
#include "cocos2d.h"
using namespace std;

class UiThemeDef;
namespace uilib
{
class TouchNode;
enum ScrollBarEnum{
    VScrollBar,
    HScrollBar
};

class ScrollBar : public BasFrame
{
public:
    ScrollBar(ScrollBarEnum bar = VScrollBar,UiThemeDef *theme = 0,TouchNode *parent = 0);
    virtual ~ScrollBar();
    void setScrollPercent(float percent);
protected:
};
}
#endif
