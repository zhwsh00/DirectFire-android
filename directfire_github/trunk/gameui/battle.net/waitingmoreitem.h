#ifndef _waitingmoreitem_h_
#define _waitingmoreitem_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "uilib/uilib.h"
using namespace uilib;

#include "abssocialitem.h"
class SocialPage;
class WaitingMoreItem : public BasSocialItem
{
public:
    WaitingMoreItem(SocialPage *owner);
    virtual ~WaitingMoreItem();
    void moveInItem();
    void moveOutItem();
protected:
    void init(int dummy=0);
protected:
    bool m_itemInited;
protected:
    VerAutoScrollWidget *m_autoScroll;
};

#endif
