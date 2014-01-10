#ifndef _herospage_h_
#define _herospage_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "baspage.h"
#include "uilib/uilib.h"

using namespace uilib;
#include "gamecore/serverinterface.h"

#include "cliententry/uimsgevent.h"

class HerosTitle;
class HerosPage : public BasPage
{
public:
    HerosPage(uilib::BasWidget *container = 0);
    virtual ~HerosPage();
    virtual void moveinPage();
    virtual void moveoutPage();
    void startGetHerosInfo();
    void endGetHerosInfo();
    void updateHeroInfo();
    void updateUserInfo();
protected:
    void init(int dummy = 0);
    void startHerosInfo(float dt);
protected:
    void onRefreshClicked(CCNode *node,void *data);
    void onSortTypeClicked(CCNode *node,void *data);
protected:
    void fillItem(BasWidget *parent,int type,int sortnum,const UiMsgEv::HeroInfo &hero);
    void fillLevelItem(BasWidget *parent,int sortnum,const UiMsgEv::HeroInfo &hero);
    void fillGoldItem(BasWidget *parent,int sortnum,const UiMsgEv::HeroInfo &hero);
    void fillPlayedItem(BasWidget *parent,int sortnum,const UiMsgEv::HeroInfo &hero);
    void fillWonItem(BasWidget *parent,int sortnum,const UiMsgEv::HeroInfo &hero);
    void fillLoseItem(BasWidget *parent,int sortnum,const UiMsgEv::HeroInfo &hero);
protected:
    void fillItemSortNum(BasWidget *parent,int sortnum,bool isSelf);
    void fillItemPlayerName(BasWidget *parent,const std::string &name,bool isSelf);
    void fillItemWonRate(BasWidget *parent,int wonrate);
protected:
    HerosTitle *m_title;
protected:
    std::vector<VerScrollWidget*> m_cates;
protected:
    bool m_itemInit;
    ServerInterface *m_serverIface;
    std::string m_id;
protected:
    int m_currIndex;
    std::stringstream ss;
};

#endif
