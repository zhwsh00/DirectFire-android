#ifndef _ccimagecliper_h_
#define _ccimagecliper_h_
#include "cocos2d.h"
using namespace cocos2d;
#include <string>
#include <list>
using namespace std;
#include "uilib/uilib.h"
using namespace uilib;

class HeadSettingDialog;

class CCImageCliper;
class ClipDrawer : public CCNode
{
public:
    ClipDrawer();
    virtual ~ClipDrawer();
    void setClipSize(int w,int h);
    void draw();
protected:
    int m_width;
    int m_height;
};

class ImageDelete : public BasNodeDelegateWidget
{
public:
    ImageDelete(CCImageCliper *owner,CCNode *node,const CCSize &_size = CCSizeMake(0,0));
    virtual ~ImageDelete();
    void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    CCImageCliper *m_owner;
    int m_width;
    int m_height;
};

class CCImageCliper : public BasShowDialog
{
public:
    CCImageCliper(const std::string &imagepath,HeadSettingDialog *owner,CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~CCImageCliper();
    void setImageSize(int w,int h);
    virtual void exec();
    void moveDraw(const CCPoint &pos);
protected:
    void layoutCompleted();
protected:
    void onCloseClicked(CCNode *node,void *data);
    void onOkClicked(CCNode *node,void *data);
    void finish();
protected:
    HeadSettingDialog *m_owner;
    std::string m_imagePath;
    int m_needWidth;
    int m_needHeight;
protected:
    ClipDrawer *m_drawer;
    bool m_visit;
};

#endif
