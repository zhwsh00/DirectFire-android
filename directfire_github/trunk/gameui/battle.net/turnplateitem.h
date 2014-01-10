#ifndef _turnplateitem_h_
#define _turnplateitem_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "uilib/uilib.h"
using namespace uilib;

#include "gamecore/serverinterface.h"
#include "abssocialitem.h"
class SocialPage;
class TurnPlateItem : public BasSocialItem
{
public:
    TurnPlateItem(SocialPage *owner);
    virtual ~TurnPlateItem();
    void moveInItem();
    void moveOutItem();
    void usePropReplyGot();
protected:
    void onFrameClicked(CCNode *node,void *data);
    void onTurnDialogCloseClicked(CCNode *node,void *data);
protected:
    void init(int dummy=0);
    bool m_itemInit;
protected:
    FSizeCCNodeDelegate *m_itemlogo;
protected:
    CCSprite *m_handSprite;
    CCSprite *m_plateSprite;
    CCSprite *m_frameSprite;
    FSizeCCNodeDelegate *m_handDele;
    FSizeCCNodeDelegate *m_plateDele;
    FSizeCCNodeDelegate *m_frameDele;
protected:
    TurnPlateDialog *m_turnDialog;
protected:
    ServerInterface *m_serverIface;
};

#endif
