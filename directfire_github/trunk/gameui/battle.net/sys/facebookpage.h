#ifndef _facebookpage_h_
#define _facebookpage_h_
#include "abssyspage.h"

class FaceBookPage : public BasSysPage
{
public:
    FaceBookPage();
    virtual ~FaceBookPage();
    virtual void moveInItem();
    virtual void moveOutItem();
    void layoutCompleted();
protected:
    virtual void initItem();
protected:
    bool m_itemInit;
};
#endif
