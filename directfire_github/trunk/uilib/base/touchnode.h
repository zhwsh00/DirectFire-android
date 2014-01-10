#ifndef _touchnode_h_
#define _touchnode_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <map>
using namespace std;
#include "absanchor.h"
#include "sizepolicy.h"
namespace uilib
{
enum PriorityLevel{
    TopPriority = -10000,
    HighestPriority = -1000,
    HighPriority = -900,
    NormalPriority = -500,
    LowPriority = -200,
    MenuPriority = -128,
    SafePriorityGap = 100
};

class TouchNode : public CCNode,public CCTouchDelegate,public BasAnchor,public SizePolicy
{
public:
    TouchNode(TouchNode *parent = 0);
    virtual ~TouchNode();
    bool canTouch();
    void setCanTouch(bool touch);
    bool blockEvent();
    void setBlockEvent(bool block);
    inline void setTouchPriority(int priority) { m_touchPriority = priority;}
    inline int touchPriority() { return m_touchPriority;}
    bool isAncestorOf(TouchNode *node);
    bool isParentOf(TouchNode *node);
    bool isChildOf(TouchNode *node);
    TouchNode *parent();
    TouchNode *rootParent();
    void setParent(TouchNode *parent);
    bool setName(const std::string &name);
    const std::string &getName() { return m_name;}
    virtual bool getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size);
    virtual void layout(bool force = false);
public:
    virtual void getPreferedSize(CCSize &size);
    virtual void adjustSize(CCSize &size);
    virtual void getRefSize(const std::string &name,CCSize &size);
    TouchNode *getChildByName(const std::string &name);
public:
    void setClickCB(CCNode *listener,SEL_CallFuncND func);
    void resetClickCB();
    bool containClickPosition(float x,float y);
    bool containClickPosition(const CCPoint &pos);
    bool containClickPosition(CCTouch *pTouch);
    bool addChild(TouchNode *child);
    virtual void delChild(TouchNode *child,bool clean = true);
    virtual void delAllChild();
    TouchNode *childAt(float x,float y);
    TouchNode *childAt(const CCPoint &pos);
    bool hasFocus();
    void setSizeLimitedToParent();
    inline bool isTop() { return m_parent == 0;}
    int getHighestAncestorPriority();    
    void resetTouchPriority();
    virtual void setEnabled(bool enabled);
    bool isEnabled() { return m_enabled;}
public:
    void setParentMoveListening(bool on){ m_parentMoveListening = on;}
    virtual void listenerPressEvent(CCTouch *pTouch, CCEvent *pEvent){}
    virtual void listenerMoveEvent(CCTouch *pTouch, CCEvent *pEvent){}
    //return the event if handled
    virtual bool listenerReleaseEvent(CCTouch *pTouch, CCEvent *pEvent){return false;}
    inline bool underMouse() { return m_mouseIn;}
protected:
    bool ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float fDelta);
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveInEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveOutEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
    inline void setUnderMouse(bool in) { m_mouseIn = in;}
    virtual void moveInStart();
    virtual void moveOutStart();
protected:
    bool checkChildLocationValid();
    virtual void reLayout();
    virtual void invalidAllChild();
    virtual void doLayout();
    virtual bool doAbsoluateLayout();
    virtual bool doRelativeLayout();
    virtual void layoutCompleted();
    virtual void childLayoutStarted();
    virtual void childLayoutCompleted();
    virtual bool setChildName(TouchNode *child,const std::string &name);
    bool hasChildByName(const std::string &name);
protected:
    virtual void setAnchoredSize(float width,float height);
    virtual void getChildMaxPreferedSize(CCSize & size);
    virtual void getSilbingMaxPreferedSize(CCSize &size);
public:
    const CCPoint &getDestPoint() { return m_destPoint;}
protected:
    virtual bool handleCenterIn(const CCSize &preferedSize);
    virtual bool handleFill(const CCSize &preferedSize);
    virtual bool handleHorizontal(const CCSize &preferedSize);
    virtual bool handleVertical(const CCSize &preferedSize);
    virtual bool handleLeft(const CCSize &preferedSize);
    virtual bool handleTop(const CCSize &preferedSize);
    virtual bool handleRight(const CCSize &preferedSize);
    virtual bool handleBottom(const CCSize &preferedSize);
protected:
    TouchNode *getAnchorNode(const std::string &name);
    virtual void setTouchPriorityFinished();
protected:
    std::string m_name;
    TouchNode *m_parent;
protected:
    bool m_canTouch;
    bool m_blockEvent;
    bool m_childDirty;
    int m_touchPriority;
    bool m_selected;
    bool m_enabled;
private:
    std::map<std::string,TouchNode*> m_childsNameMap;
    std::map<TouchNode*,std::string> m_childsMap;
private:
    std::map<std::string,TouchNode*> m_finishedPool;
    std::map<std::string,TouchNode*> m_unfinishedPool;
protected:
    SEL_CallFuncND m_clickFunc;
    CCNode *m_clickListener;
protected:
    CCPoint m_destPoint;
protected:
    bool m_mouseIn;
    bool m_addedIntoTouch;
    bool m_parentMoveListening;
};

}
#endif
