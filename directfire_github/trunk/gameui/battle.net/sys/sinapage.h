#ifndef _sinapage_h_
#define _sinapage_h_
#include "abssyspage.h"

class SinaPage : public BasSysPage
{
public:
    SinaPage();
    virtual ~SinaPage();
    virtual void moveInItem();
    virtual void moveOutItem();
    void layoutCompleted();
protected:
    virtual void initItem();
protected:
    bool m_itemInit;
};
#endif
