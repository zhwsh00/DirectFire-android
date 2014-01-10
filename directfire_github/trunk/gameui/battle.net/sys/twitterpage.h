#ifndef _twitterpage_h_
#define _twitterpage_h_
#include "abssyspage.h"

class TwitterPage : public BasSysPage
{
public:
    TwitterPage();
    virtual ~TwitterPage();
    virtual void moveInItem();
    virtual void moveOutItem();
    void layoutCompleted();
protected:
    virtual void initItem();
protected:
    bool m_itemInit;
};
#endif
