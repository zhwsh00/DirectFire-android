#ifndef _usershow_h_
#define _usershow_h_
#include <string>
#include <map>
#include <vector>

using namespace std;
#include "uilib/uilib.h"
using namespace uilib;

class AddFriendDialog;
class SendGiftDialog;
class SendMsgDialog;
class ServerInterface;

class HeadPortraitWidget;
class WonGameShow;
class SocialPropShow;
class LevelExpShow;
class UserShow : public BasWidget
{
public:
    UserShow(BasWidget *parent);
    virtual ~UserShow();
    bool onKeyPadBackClicked();
    void clear();
    void setMale(bool male) { m_male = male;}
    void setTheme(const std::string &val);
    void setHeadPortrait(const std::string &val);
    void setNickName(const std::string &val);
    void setAccountId(const std::string &val);
    void setIntelligence(int val);
    void setEnergy(int val);
    void setLucky(int val);
    void setLeadership(int val);
    void setSocialLevel(int val);
    void setOwnsProps();
    void setUserPropNum(int id,int num);
    void setLevelExp(int level,int currexp,int levelexp,int nextlexp);
    void portraitUpdated(std::string *data);
    void upThumbFoot(int thumb,int foot);
    void notifyResetUserInfo();
public:
    void finish();
protected:
    bool m_male;
    std::string m_theme;
    std::string m_headPortrait;
    std::string m_nickName;
    std::string m_accountId;
protected:
    int m_intelligence;
    int m_energy;
    int m_lucky;
    int m_leadership;
    int m_socialLevel;
protected:
    HeadPortraitWidget *m_headWidget;
    SocialPropShow *m_propShow;
    LevelExpShow *m_levelShow;
protected:
    int m_footNum;
    int m_thumbNum;
    CCLabelBMFont *m_thumbFont;
    CCLabelBMFont *m_footFont;
    BasNodeDelegateWidget *m_thumbContainer;
    CCLabelBMFont *m_nickFont;
protected:
    CCLabelBMFont *m_coinFont;
    CCLabelBMFont *m_goldFont;
protected:
    ServerInterface *m_serverIface;
};


#endif
