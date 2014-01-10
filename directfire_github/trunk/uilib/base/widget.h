#ifndef _widget_h_
#define _widget_h_
#include "frame.h"
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
namespace uilib
{
/* The main purpose of this class
   is add basic layout into touch node,
   the layout response for the location of
   sub-touchnode and the location's animation
*/
class BasWidget;
class BasSkin;
class BasNodeAction;
class BasNodeEffectAction;
class BasLayout : public NullFrame
{
    friend class BasWidget;
public:
    BasLayout();
    virtual ~BasLayout();
    void addWidget(BasWidget *widget);
    void addLayout(BasLayout *layout);
    inline void setSpacing(float space) { m_spacing = space;}
    inline float getSpacing() { return m_spacing;}
    virtual void execLayout() = 0;
    inline void setAveraged(bool set) { m_averageSet = set;}
    inline bool getAveraged() { return m_averageSet;}
    inline void setChildsAction(BasNodeAction *action) { m_childsAction = action;}
    inline BasNodeAction *getChildAction() { return m_childsAction;}
    inline int childsCount() { return m_childs.size();}
    inline void setAlignChildsSize(bool set) { m_alignChildSize = set;}
    inline bool alignChildsSize() { return m_alignChildSize;}
    virtual void childLayoutStarted();
    virtual void setChildAlign(int index,uilib::AnchorType type);
protected:
    BasWidget *getOwner() { return m_owner;}
    void setOwner(BasWidget *owner);
protected:
    BasWidget *m_owner;
    std::vector<TouchNode*> m_childs;
    float m_spacing;
    bool m_averageSet;
    bool m_alignChildSize;
protected:
    BasNodeAction *m_childsAction;
protected:
    typedef struct ChildAlign{
        int index;
        uilib::AnchorType type;
    }ChildAlign;
    std::vector<ChildAlign> m_childAligns;
};
class VerticalLayout : public BasLayout
{
public:
    VerticalLayout();
    virtual ~VerticalLayout();
    void setChildAlign(int index,uilib::AnchorType type);
    /*
    void getPreferedSize(CCSize &size);
    void getRefSize(const string &name, CCSize &size);
    */
    void childLayoutCompleted();
protected:
    void execLayout();
};
class HorizontalLayout : public BasLayout
{
public:
    HorizontalLayout();
    virtual ~HorizontalLayout();
    void setChildAlign(int index,uilib::AnchorType type);
    /*
    void getPreferedSize(CCSize &size);
    void getRefSize(const string &name, CCSize &size);
    */
    void childLayoutCompleted();
protected:
    void execLayout();
};
class GridLayout : public BasLayout
{
public:
    GridLayout(int row,int col);
    virtual ~GridLayout();
protected:
    void execLayout();
protected:
    int m_row;
    int m_col;
};

class BasWidget : public BasFrame
{
public:
    BasWidget();
    virtual ~BasWidget();
    void setLayout(BasLayout *layout);
    BasLayout *getLayout();
    void removeLayout();
    BasLayout *takeLayout();
    /*
    virtual void getPreferedSize(CCSize &size);
    */
    virtual void layoutCompleted();
    virtual void childLayoutCompleted();
    void moveIn();
    void moveOut();
    inline void setMoveinAction(BasNodeAction *action) { m_moveinAction = action;}
    inline BasNodeAction *getMoveinAction() { return m_moveinAction;}
    inline void setMoveoutAction(BasNodeAction *action) { m_moveoutAction = action;}
    inline BasNodeAction *getMoveoutAction() { return m_moveoutAction;}
    inline void setLayoutInAction(BasNodeAction *action) { m_layoutInAction = action;}
    inline BasNodeAction *getLayoutInAction() { return m_layoutInAction;}
    inline void setLayoutOutAction(BasNodeAction *action) { m_layoutOutAction = action;}
    inline BasNodeAction *getLayoutOutAction() { return m_layoutOutAction;}
    inline void setEffectAction(BasNodeEffectAction *action) { m_effectAction = action;}
    inline BasNodeEffectAction *getEffectAction() { return m_effectAction;}
    virtual void setEffectActionEnabled(bool enable);
    void setEffectActionRunningLayoutCompleted();
protected:
    BasLayout *m_layout;
    BasNodeAction *m_moveinAction;
    BasNodeAction *m_moveoutAction;
    BasNodeAction *m_layoutInAction;
    BasNodeAction *m_layoutOutAction;
    BasNodeEffectAction *m_effectAction;
    bool m_eActionEnabledACompleted;
};
class BasButton : public BasWidget
{
public:
    BasButton();
    virtual ~BasButton();
    void setButtonInfo(const std::string &text,
                       const std::string &theme = "default",
                       const std::string &buttonbg = "buttonbg",
                       const CCSize &size = CCSizeMake(160,60),
                       const std::string &pressedButtonBg = "",
                       const std::string &fontFaimily = "",
                       int fontSize = 30,
                       ccColor3B color = ccBLACK);
    void setButtonInfo(const char *text,const char *fontFile,
                       const std::string &theme = "default",
                       const std::string &buttonbg = "buttonbg",
                       const CCSize &size = CCSizeMake(160,60),
                       ccColor3B color = ccWHITE);
    void setButtonInfoWithBorder(const char *text,const char *fontFile,
                       const std::string &theme = "default",
                       const std::string &buttonbg = "buttonbg",
                       const CCSize &size = CCSizeMake(160,60),
                       ccColor3B color = ccWHITE);
    const std::string &getTheme();
    const std::string &getText();
    inline void setButtonIndex(int index) { m_buttonIndex = index;}
    inline int getButtonIndex() { return m_buttonIndex;}
    inline void setScaleRate(float rate) { m_scaleRate = rate;}
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveInEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveOutEvent(CCTouch *pTouch, CCEvent *pEvent);
    void setTouchInCB(CCNode *listener,SEL_CallFuncND func);
    void setTouchOutCB(CCNode *listener,SEL_CallFuncND func);
    void setEnabled(bool enabled);
    bool isEnabled();
protected:
    std::string m_text;
    std::string m_theme;
    int m_buttonIndex;
protected:
    BasSkin *m_normalSkin;
    BasSkin *m_pressedSkin;
protected:
    CCNode *m_touchInListener;
    CCNode *m_touchOutListener;
    SEL_CallFuncND m_touchInFunc;
    SEL_CallFuncND m_touchOutFunc;
protected:
    bool m_enabled;
    float m_scaleRate;
};
class BasLabel : public BasWidget
{
public:
    BasLabel();
    virtual ~BasLabel();
    void setLabelInfo(const std::string &text,
                      const std::string &theme = "default",
                      const std::string &labelbg = "labelbg",
                      const CCSize &size = CCSizeMake(160,80),
                      const std::string &fontFaimily = "",
                      int fontSize = 30,
                      ccColor3B color = ccBLACK);
    void setLabelInfo(const char *text,const char *fontFile,
                      const std::string &theme = "default",
                      const std::string &labelbg = "labelbg",
                      const CCSize &size = CCSizeMake(160,80),
                      ccColor3B color = ccWHITE);
    void setLabelText(const std::string &text);
    const std::string &getTheme();
    const std::string &getText();
    inline void setLabelIndex(int index) { m_labelIndex = index;}
    inline int getLabelIndex() { return m_labelIndex;}
protected:
    std::string m_text;
    std::string m_theme;
    int m_labelIndex;
};
class CheckBox : public BasWidget
{
public:
    CheckBox();
    virtual ~CheckBox();
    void setCheckInfo(const std::string &text,
                      const std::string &theme = "default",
                      const std::string &bg = "buttonbg",
                      const std::string &labelbg = "",
                      const CCSize &size = CCSizeMake(200,80),
                      const std::string &fontFaimily = "",
                      int fontSize = 30,
                      ccColor3B color = ccBLACK);
    void setCheckInfo(const char *text,const char *fontFile,
                      const std::string &theme = "default",
                      const std::string &bg = "buttonbg",
                      const CCSize &size = CCSizeMake(200,80),
                      ccColor3B color = ccWHITE);
    void layoutCompleted();
    const std::string &getTheme();
    const std::string &getText();
    void setCheck(bool check);
    inline bool isCheck() { return m_checked;}
    inline void setCheckIndex(int index) { m_checkIndex = index;}
    inline int getCheckIndex() { return m_checkIndex;}
    virtual void getPreferedSize(CCSize &size);
    BasWidget *getLabelWidget();
    BasWidget *getIconWidget();
public:
    virtual void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveInEvent(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchMoveOutEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    std::string m_text;
    std::string m_theme;
    std::string m_bg;
    CCSize m_setSize;
    bool m_checked;
    int m_checkIndex;
    BasSkin *m_checkedSkin;
    BasSkin *m_uncheckedSkin;
protected:
    BasLabel *m_labelWidget;
    BasWidget *m_iconWidget;
protected:
    int m_contextMargin;
};
class BorderWidget : public BasWidget
{
public:
    BorderWidget();
    virtual ~BorderWidget();
    void layoutCompleted();
    void setTheme(const std::string &theme,const std::string &bg);
    const std::string &getTheme();
    const std::string &getThemeBg();
protected:
    std::string m_theme;
    std::string m_themeBg;
};
class HTriWidget : public BasWidget
{
public:
    HTriWidget();
    virtual ~HTriWidget();
    void layoutCompleted();
    void setTheme(const std::string &theme,const std::string &bg);
    const std::string &getTheme();
    const std::string &getThemeBg();
protected:
    std::string m_theme;
    std::string m_themeBg;
protected:
    BasSkin *m_themeSkin;
};
class VTriWidget : public BasWidget
{
public:
    VTriWidget();
    virtual ~VTriWidget();
    void layoutCompleted();
    void setTheme(const std::string &theme,const std::string &bg);
    const std::string &getTheme();
    const std::string &getThemeBg();
protected:
    std::string m_theme;
    std::string m_themeBg;
protected:
    BasSkin *m_themeSkin;
};
class BasNodeDelegateWidget : public BasWidget
{
public:
    BasNodeDelegateWidget(CCNode *client,const CCSize &_size = CCSizeMake(0,0));
    virtual ~BasNodeDelegateWidget();
    CCNode *getClient() { return m_node;}
protected:
    CCNode *m_node;
    CCSize m_size;
};
class BasNodeLimitWidget : public BasWidget
{
public:
    BasNodeLimitWidget(CCNode *client,const CCSize &_size = CCSizeMake(0,0));
    virtual ~BasNodeLimitWidget();
    void layoutCompleted();
    CCNode *getClient() { return m_node;}
protected:
    CCNode *m_node;
    CCSize m_nodeSize;
    bool m_added;
};
class SplashMessageWidget : public BasWidget
{
public:
    SplashMessageWidget(TouchNode *parent,const std::string &text,const std::string &theme = "default",const std::string &bg = "inputbg",const std::string &fontFamily = "",float fontSize = 32,const ccColor3B &color = ccBLACK);
    virtual ~SplashMessageWidget();
    void setDelayTime(float time);
    void setMoveInTime(float time);
    void setMoveOutTime(float time);
    void setFinishedCB(CCNode *listener,SEL_CallFuncN func);
protected:
    void onDelayFinished(CCNode *sender);
    void onMoveInActionFinished(CCNode *sender);
    void onMoveOutActionFinished(CCNode *sender);
protected:
    float m_delayTime;
protected:
    CCNode *m_finishedListener;
    SEL_CallFuncN m_finishedFunc;
};

}
#endif
