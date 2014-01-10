#ifndef _socialshow_h_
#define _socialshow_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"
using namespace uilib;

#include "prop/propdef.h"
#include "propshow.h"
class SocialPropShow : public BasWidget
{
public:
    SocialPropShow();
    virtual ~SocialPropShow();
    void setProps(int id,int num);
    void finish();
protected:
    std::map<int,PropShow*> m_propShows;
};

#endif
