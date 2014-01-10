#ifndef _thumbfootitem_h_
#define _thumbfootitem_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "uilib/uilib.h"
using namespace uilib;

#include "abssocialitem.h"
class SocialPage;
class ThumbFootItem : public BasSocialItem
{
public:
    ThumbFootItem(SocialPage *owner);
    virtual ~ThumbFootItem();
    void thumbPortraitUpdate();
    void moveInItem();
    void moveOutItem();
    void setSendGift(int type,int count);
protected:
    void onStartClicked(CCNode *node,void *data);
    void onSubmitClicked(CCNode *node,void *data);
    void onThumbClicked(CCNode *node,void *data);
    void onFootClicked(CCNode *node,void *data);
    void onHeadClicked(CCNode *node,void *data);
protected:
    void onHDCloseChicked(CCNode *node,void *data);
    void onGitShowFinished(CCNode *node);
protected:
    void loadData();
    void showPortraits();
    void showSubmitButton();
protected:
    void sendGift();
    void showGift();
protected:
    void init(int dummy=0);
    bool m_itemInit;
protected:
    std::vector<BorderWidget *> m_frameBgs;
    std::vector<CCSprite *> m_portratis;
    std::vector<BasButton *> m_thumbButtons;
    std::vector<BasButton *> m_footButtons;
protected:
    FSizeCCNodeDelegate *m_itemlogo;
    BasButton *m_startButton;
    BasButton *m_submitButton;
    BasAnimSprite *m_busyAnim;
    FSizeCCNodeDelegate *m_busyNode;
protected:
    BasShowDialog *m_hdDialog;
protected:
    bool m_isWorking;
    int m_thumbIndex;
    int m_footIndex;
protected:
    int m_giftType;
    int m_giftCount;
    CCNode *m_showNode;
};

#endif
