#ifndef _gamerulepage_h_
#define _gamerulepage_h_
#include "abssyspage.h"

class GameRulePage : public BasSysPage
{
public:
    GameRulePage();
    virtual ~GameRulePage();
    virtual void moveInItem();
    virtual void moveOutItem();
    void layoutCompleted();
    virtual void initItem();
protected:
    VerScrollWidget *m_scroll;
};

#endif
