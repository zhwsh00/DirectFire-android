#ifndef _scrollarea_h_
#define _scrollarea_h_
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
#include <string>
using namespace std;
#include "widget.h"
#include "scrollbar.h"

class UiThemeDef;
namespace uilib
{
enum ScrollAreaShowPolicy
{
    ScrollShow_Always,
    ScrollShow_Need,
    ScrollShow_Never
};

class ScrollBar;

class BasScrollArea;
class ScrollViewDelegate : public NullFrame
{
public:
    ScrollViewDelegate(BasScrollArea *owner,TouchNode *parent = 0);
    virtual ~ScrollViewDelegate();
    virtual void setContainer(CCNode *node,const CCSize &contentSize,bool ver = true);
    virtual void updateContainer(CCNode *node,const CCSize &contentSize,bool ver = true);
    void setDirection (CCScrollViewDirection direction);
    CCScrollView *getScrollView() { return m_scrollView;}    
    void scrollToEnd(bool ver = true);
    void scrollToEnd(float dt = 5.0,bool ver = true);
    void scrollToBegin(bool ver = true);
    void scrollToBegin(float dt = 5.0,bool ver = true);
    void setUserCanScroll(bool can);
    void resetScrollOffset(bool ver);
public:
    virtual void listenerPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void listenerMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual bool listenerReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    CCScrollView *m_scrollView;
    BasScrollArea *m_owner;
protected:
    bool m_canUserScroll;
protected:
    CCPoint m_listenerPressPos;
    bool m_eatListener;
};

class BasScrollArea : public BasWidget , public CCScrollViewDelegate
{
public:
    friend class ScrollViewDelegate;
    BasScrollArea(const std::string &themeName = "",const std::string &themeBg = "",const CCSize &size = CCSizeMake(0,0));
    BasScrollArea(UiThemeDef *theme = 0,const std::string &bgname = "",const CCSize &size = CCSizeMake(0,0));
    virtual ~BasScrollArea();
    void setUserCanScroll(bool can);
    virtual void setContainer(CCNode *node,const CCSize &contentSize,bool ver = true);
    virtual CCNode *getContainer();
    void getPreferedScrollAreaSize(float &w,float &h);
    void setDirection (CCScrollViewDirection direction);
    void setVerticalScrollPolicy(ScrollAreaShowPolicy policy);
    void setHorizontalScrollPolicy(ScrollAreaShowPolicy policy);
    void scrollToEnd(bool ver = true);
    void scrollToEnd(float dt = 5.0,bool ver = true);
    void scrollToBegin(bool ver = true);
    void scrollToBegin(float dt = 5.0,bool ver = true);
    bool hasUserScrolled();
    void clearUserScrolled();
    void resetScrollOffset(bool ver = true);
protected:
    virtual void init(const std::string &para = "");
    virtual void layoutCompleted();
    virtual void childLayoutCompleted();
    virtual void finishLayout();
    void scrollViewDidScroll(CCScrollView* view);
    void scrollViewDidZoom(CCScrollView* view);
protected:
    void setScrollBar();
protected:
    CCNode *m_containerNode;
    ScrollViewDelegate *m_viewDelegate;
protected:
    ScrollBar *m_vscrollBar;
    ScrollBar *m_hscrollBar;
    ScrollAreaShowPolicy m_vscrollPolicy;
    ScrollAreaShowPolicy m_hscrollPolicy;
    CCSize m_containerCSize;
protected:
    std::string m_themeName;
    std::string m_themeBg;
    CCSize m_themeSize;
protected:
    bool m_userScrolling;
};

class TextScrollArea : public BasScrollArea
{
public:
    TextScrollArea();
    virtual ~TextScrollArea();
    void setTheme(const std::string &themeName,const std::string &bgName);
    void setTextInfo(const std::string &text,const std::string &fontfamily = "",int fontSize = 60,ccColor3B color = ccBLACK);
protected:
    virtual void childLayoutCompleted();
protected:
    std::string m_text;
    std::string m_fontFamily;
    int m_fontSize;
    ccColor3B m_fontColor;
};
}
#endif
