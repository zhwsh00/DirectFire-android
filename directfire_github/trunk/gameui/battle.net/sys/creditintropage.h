#ifndef _creditintropage_h_
#define _creditintropage_h_
#include "abssyspage.h"

class CreditInfoPage : public BasSysPage
{
public:
    CreditInfoPage();
    virtual ~CreditInfoPage();
    virtual void moveInItem();
    virtual void moveOutItem();
    void layoutCompleted();
protected:
    virtual void initItem();
protected:
    bool m_itemInit;
    VerScrollWidget *m_scroll;
};
#endif
