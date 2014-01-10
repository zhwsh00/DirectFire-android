#ifndef _syspage_h_
#define _syspage_h_

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "uilib/uilib.h"

using namespace std;

class SysTitle;
class BasSysPage;
class SysPage : public BasShowDialog
{
public:
    SysPage(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~SysPage();
    void headSettingClosed(int status);
    void exec();
protected:
    void onBackClicked(CCNode *node,void *data);
    void onItemClicked(CCNode *node,void *data);
    void onButtonPageMoveOutFinished(CCNode *node);
protected:
    void initItem();
protected:
    SysTitle *m_title;
    BasWidget *m_pageArea;
    BasWidget *m_buttonsPage;
    BasWidget *m_contentsPage;
    std::map<int,BasSysPage*> m_pages;
protected:
    BasSysPage *m_currPage;
protected:
    bool m_itemInit;
};
#endif
