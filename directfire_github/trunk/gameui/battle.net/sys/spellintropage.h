#ifndef _spellintropage_h_
#define _spellintropage_h_
#include "abssyspage.h"

#include "uilib/uilib.h"
using namespace uilib;

class SpellIntroPage : public BasSysPage
{
public:
    SpellIntroPage();
    virtual ~SpellIntroPage();
    virtual void moveInItem();
    virtual void moveOutItem();
    void layoutCompleted();
    virtual void initItem();
protected:
    void onSpellClicked(CCNode *node,void *data);
    void onSpellFinished(CCNode *node,void *data);
protected:
    VerScrollWidget *m_scroll;
protected:
    std::map<std::string,BasAnimSprite*> m_animMap;
};
#endif
