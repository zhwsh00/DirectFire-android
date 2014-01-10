#ifndef _hallmainwidget_h_
#define _hallmainwidget_h_
#include <string>
#include <map>
#include <vector>
using namespace std;

#include "uilib/uilib.h"
#include "gamecore/resource/resourcemgr.h"

using namespace uilib;

class BasPage;
class HallMainWidget : public BasWidget
{
public:
    typedef struct HallPageDef{
        std::string m_img;
        std::string m_pressedImg;
        BasPage *m_page;
    }HallPageDef;

    HallMainWidget();
    virtual ~HallMainWidget();
    bool onKeyPadBackClicked();
    void finish();
    void addPage(HallPageDef *page);
    int pageCount();
    BasPage *getPageByIndex(int index);
protected:
    void layoutCompleted();
    void childLayoutCompleted();
    void onPageButtonClicked(CCNode *node,void *data);
protected:
    void disablePage(int index);
    void enablePage(int index);
protected:
    std::string m_buttonTheme;
protected:
    std::vector<HallPageDef*> m_pages;
    int m_currPage;
};

#endif
