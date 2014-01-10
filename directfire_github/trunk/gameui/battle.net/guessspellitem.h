#ifndef _guessspellitem_h_
#define _guessspellitem_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "uilib/uilib.h"
using namespace uilib;

#include "abssocialitem.h"
class SocialPage;
class GuessSpellItem : public BasSocialItem
{
public:
    GuessSpellItem(SocialPage *owner);
    virtual ~GuessSpellItem();
    void moveInItem();
    void moveOutItem();
    void layoutCompleted();
    void setInterval(int t) { m_interval = t;}
    void timePool(float dt);
    void setSendGift(int type,int count);
protected:
    void startTimePool();
    void endTimePool();
protected:
    void init(int dummy=0);
    void resetGuess();
    void sendGift();
    void showGift();
protected:
    void onShowGiftFinished(CCNode *node);
protected:
    void onCardClicked(CCNode *node,void *data);
    void onSpellClicked(CCNode *node,void *data);
    void onFlipFinished(CCNode *node,void *data);
    void onAnimFinished(CCNode *node,void *data);
protected:
    void closeAllCard();
protected:
    bool m_itemInited;
protected:
    std::vector<FSizeCCNodeDelegate *> m_cards;
    FSizeCCNodeDelegate *m_selDele;
    BasNodeDelegateWidget *m_posDele;
    CCSprite *m_selIcon;
protected:
    BasAnimSprite *m_anim;
    int m_selectNum;
    bool m_isGuessing;
    bool m_won;
protected:
    int m_timePool;
    int m_interval;
protected:
    CCLabelBMFont *m_countDowner;
protected:
    int m_giftType;
    int m_giftCount;
    CCNode *m_showNode;
protected:
    std::string m_uid;
};

#endif
