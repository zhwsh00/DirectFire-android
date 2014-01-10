#ifndef _friendpage_h_
#define _friendpage_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "baspage.h"
#include "uilib/uilib.h"

#include "cliententry/uimsgevent.h"
#include "gamecore/serverinterface.h"
using namespace uilib;

class FriendTitle;
class FriendItem;
class AddFriendDialog;
class FriendsPage : public BasPage
{
public:
    FriendsPage(uilib::BasWidget *container = 0);
    virtual ~FriendsPage();
    virtual void moveinPage();
    virtual void moveoutPage();
    bool hasInit();
    void initFriends(const std::vector<UiMsgEv::PlayerInfoEv*> &fs);
public:
    void addFriend(const std::string &fid);
    void delFriend(const std::string &fid);
    void updateFriendProp(const std::string &uid);
    void updateFriendPortrait(const std::string &uid,const std::string &head);
    void updateFriendWonNum(const std::string &uid);
    void updateOnlineFriend();
    void startRefreshing();
    void endRefreshing();
    void deleteItem(FriendItem *item);
    void relayScroll();
protected:
    void addFriendItem(UiMsgEv::PlayerInfoEv *ev);
protected:
    void onTitleAddClick(CCNode *node,void *data);
    void onTitleRefreshClick(CCNode *node,void *data);
protected:
    void onAddFriendDialogCloseClicked(CCNode *node,void *data);
    void onAddFriendDlalogAddClicked(CCNode *node,void *data);
protected:
    FriendTitle *m_title;
protected:
    VerScrollWidget *m_scrollList;
protected:
    std::map<std::string,FSizeWidgetDelegate *> m_friendMap;
protected:
    bool m_init;
    ServerInterface *m_serverIface;
protected:
    AddFriendDialog *m_addFriendDialog;
};
#endif
