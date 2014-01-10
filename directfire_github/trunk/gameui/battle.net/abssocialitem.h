#ifndef _abssocialitem_h_
#define _abssocialitem_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "uilib/uilib.h"
using namespace uilib;

class SocialPage;
class BasSocialItem : public BasWidget
{
public:
    BasSocialItem(SocialPage *owner);
    virtual ~BasSocialItem();
    void setIndex(int index) { m_index = index;}
    int getIndex() { return m_index;}
    void setFirstLast(bool first,bool last);
    void layoutCompleted();
    virtual void moveInItem();
    virtual void moveOutItem();
protected:
    void initMe();
protected:
    void onLeftClicked(CCNode *node,void *data);
    void onRightClicked(CCNode *node,void *data);
protected:
    SocialPage *m_owner;
protected:
    BasButton *m_leftButton;
    BasButton *m_rightButton;
    bool m_isFirst;
    bool m_isLast;
    int m_index;
private:
    bool m_inited;
};

#endif
