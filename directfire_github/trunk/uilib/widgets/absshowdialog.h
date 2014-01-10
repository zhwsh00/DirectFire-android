#ifndef _absshowdialog_h_
#define _absshowdialog_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "../base/widget.h"

namespace uilib
{
class BasShowDialog : public BasWidget
{
public:
    BasShowDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~BasShowDialog();
    void setTheme(const std::string &theme,const std::string &bg);
    void setEdgeSize(float h,float v);
    void setFillPattern(const std::string &pattern);
    void setCloseImg(const std::string &normal,const std::string &pressed);
    void setCloseCB(CCNode *node,SEL_CallFuncND func);
    inline void setEdgeSize(float size) { m_edgeSize = size;}
    inline float getEdgeSize() { return m_edgeSize ;}
    inline void setMoveInTime(float time) { m_moveInTime = time;}
    inline void setMoveOutTime(float time) { m_moveOutTime = time;}
    virtual void exec();
    virtual void destroy();
    virtual void layoutCompleted();
protected:
    void finish();
protected:
    void onMoveInActionFinished(CCNode *node);
    void onMoveOutActionFinished(CCNode *node);
protected:
    float m_moveInTime;
    float m_moveOutTime;
protected:
    float m_edgeSize;
    std::string m_theme;
    std::string m_bg;
    std::string m_fillPattern;
    float m_fillHEdge;
    float m_fillVEdge;
protected:
    std::string m_closeImg,m_closePressedImg;
    BasButton *m_closeButton;
protected:
    CCNode *m_closeListener;
    SEL_CallFuncND m_closeFunc;
};
}
#endif
