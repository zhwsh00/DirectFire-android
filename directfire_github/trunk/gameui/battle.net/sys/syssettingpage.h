#ifndef _syssettingpage_h_
#define _syssettingpage_h_
#include "abssyspage.h"
class SoundMgr;
class SysSettingPage : public BasSysPage
{
public:
    SysSettingPage();
    virtual ~SysSettingPage();
    virtual void moveInItem();
    virtual void moveOutItem();
    void layoutCompleted();
    virtual void initItem();
protected:
    void onGameMusicClicked(CCNode *node,void *data);
    void onBgMusicFinished(CCNode *node,void *data);
protected:
    bool m_itemInit;
    SoundMgr *m_soundMgr;
};
#endif
