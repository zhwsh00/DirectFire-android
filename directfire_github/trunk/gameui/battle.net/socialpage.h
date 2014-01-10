#ifndef _socialpage_h_
#define _socialpage_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "baspage.h"
#include "uilib/uilib.h"
using namespace uilib;

class BasSocialItem;
class SocialPage : public BasShowDialog
{
public:
    SocialPage(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~SocialPage();
    void initSocialPage();
    void thumbPortraitUpdate();
    void usePropReplyGot();
    void leftHandClicked(int index);
    void rightHandClicked(int index);
    void exec();
    void childLayoutStarted();
protected:
    void childLayoutCompleted();
protected:
    void onMoveoutFinished(CCNode *node);
protected:
    std::vector<BasSocialItem*> m_items;
};
#endif
