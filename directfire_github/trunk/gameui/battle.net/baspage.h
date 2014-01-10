#ifndef _baspage_h_
#define _baspage_h_
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "uilib/uilib.h"
using namespace uilib;

class BasPage : public BasWidget
{
public:
    BasPage(BasWidget *container = 0);
    void setContainer(BasWidget *container);
    virtual ~BasPage();
    virtual void onKeyPadBackClicked(){}
    virtual void moveinPage();
    virtual void moveoutPage();
protected:
};
#endif
