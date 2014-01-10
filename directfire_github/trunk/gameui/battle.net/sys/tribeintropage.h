#ifndef _tribeintropage_h_
#define _tribeintropage_h_
#include "abssyspage.h"

class TribeIntroPage : public BasSysPage
{
public:
    TribeIntroPage();
    virtual ~TribeIntroPage();
    virtual void moveInItem();
    virtual void moveOutItem();
    void layoutCompleted();
    virtual void initItem();
protected:
    VerScrollWidget *m_scroll;
};
#endif
