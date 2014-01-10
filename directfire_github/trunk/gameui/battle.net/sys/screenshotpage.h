#ifndef _screenshot_h_
#define _screenshot_h_
#include "abssyspage.h"

class ScreenShotPage : public BasSysPage
{
public:
    ScreenShotPage();
    virtual ~ScreenShotPage();
    virtual void moveInItem();
    virtual void moveOutItem();
    void layoutCompleted();
    void setDir(const std::string &dir);
protected:
    virtual void initItem();
protected:
    bool m_itemInit;
    HorScrollWidget *m_scroll;
protected:
    std::string m_dir;
};
#endif
