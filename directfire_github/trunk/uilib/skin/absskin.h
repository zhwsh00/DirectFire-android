#ifndef _absskin_h_
#define _absskin_h_
#include <string>
#include <iostream>
using namespace std;

#include "cocos2d.h"
using namespace std;
#include "absareaskin.h"

class UiThemeDef;
namespace uilib
{

class BasSkin : public CCNode
{
public:
    BasSkin();
    virtual ~BasSkin();
    void setSkinFillHor(bool fill);
    void setSkinFillVer(bool fill);
    inline bool skinFillHor(){ return m_skinFillHor;}
    inline bool skinFillVer() { return m_skinFillVer;}
    virtual void setFrameSize(const CCSize &size);
    virtual void getPreferedSize(CCSize &size);
    inline const CCSize &getFrameSize() { return m_frameSize;}
    void setUiTheme(UiThemeDef *theme,const std::string &name);
    inline UiThemeDef *getUiTheme() { return m_uiTheme;}
    inline std::string &getUiName() { return m_uiName;}
    inline void setName(const std::string &name) { m_name = name;}
    inline std::string &name() { return m_name;}
    virtual void setEnabled(bool enabled);
    bool isEnabled() { return m_enabled;}
    virtual bool getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size);
    virtual void reLayout() = 0;
protected:
    virtual bool init(){ return false;}
protected:
    CCSize m_frameSize;
    UiThemeDef *m_uiTheme;
    std::string m_uiName;
protected:
    std::string m_name;
    bool m_inited;
    bool m_enabled;
protected:
    bool m_skinFillHor;
    bool m_skinFillVer;
};

class ButtonImageSkin : public BasSkin
{
public:
    ButtonImageSkin();
    ~ButtonImageSkin();
    static BasSkin *create(const CCSize &size,UiThemeDef *theme,const std::string &themename);
    void getPreferedSize(CCSize &psize);
    bool init();
    virtual void setEnabled(bool enabled);
    virtual void reLayout();
    virtual bool getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size);
protected:
    BasAreaSkin m_bg;
};

class ButtonTextImageSkin : public BasSkin
{
public:
    ButtonTextImageSkin();
    virtual ~ButtonTextImageSkin();
    virtual void setFrameSize(const CCSize &size);
    static BasSkin *create(const std::string &text,const CCSize &framesize,UiThemeDef *theme,const std::string &themename,
                           const std::string &family = std::string(),
                           int size = 16,
                           ccColor3B color = ccBLACK);
    void getPreferedSize(CCSize &psize);
    void setText(const std::string &text,
                 const std::string &family = std::string(),
                 int size = 16,
                 ccColor3B color = ccBLACK);
    bool init();
    virtual void updateText(const std::string &text);
    virtual void setEnabled(bool enabled);
    virtual void reLayout();
    virtual bool getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size);
protected:
    BasAreaSkin m_bg;
    std::string m_text;
    std::string m_fontFamily;
    int m_fontSize;
    ccColor3B m_fontColor;
    CCLabelTTF *m_label;
};

class BorderImageSkin : public BasSkin
{
public:
    BorderImageSkin();
    virtual ~BorderImageSkin();
    static BasSkin *create(const CCSize &size,UiThemeDef *theme,const std::string &themename);
    static BasSkin *create(const CCSize &size,const std::string &theme,const std::string &bg);
    void getPreferedSize(CCSize &psize);
    bool init();
    virtual void setEnabled(bool enabled);
    virtual void reLayout();
protected:
    std::string m_bgName;
protected:
    BasAreaSkin m_lt;
    BasAreaSkin m_top;
    BasAreaSkin m_rt;
    BasAreaSkin m_left;
    BasAreaSkin m_center;
    BasAreaSkin m_right;
    BasAreaSkin m_lb;
    BasAreaSkin m_bottom;
    BasAreaSkin m_rb;
};
class TrisectionImageSkin : public BasSkin
{
public:
    TrisectionImageSkin();
    virtual ~TrisectionImageSkin();
    virtual void setEnabled(bool enabled);
protected:
    BasAreaSkin m_headSkin;
    BasAreaSkin m_tailSkin;
    BasAreaSkin m_bgSkin;
protected:
    std::string m_headImg;
    std::string m_tailImg;
    std::string m_img;
};
class HTrisectionImageSkin : public TrisectionImageSkin
{
public:
    HTrisectionImageSkin();
    virtual ~HTrisectionImageSkin();
    static BasSkin *create(const CCSize &size,UiThemeDef *theme,const std::string &img);
    static BasSkin *create(const CCSize &size,const std::string &theme,const std::string &img);
    virtual void getPreferedSize(CCSize &size);
    bool init();
    virtual void reLayout();
};
class VTrisectionImageSkin : public TrisectionImageSkin
{
public:
    VTrisectionImageSkin();
    virtual ~VTrisectionImageSkin();
    static BasSkin *create(const CCSize &size,UiThemeDef *theme,const std::string &img);
    static BasSkin *create(const CCSize &size,const std::string &theme,const std::string &img);
    virtual void getPreferedSize(CCSize &size);
    bool init();
    virtual void reLayout();
};
class ScrollImageSkin : public BasSkin
{
public:
    ScrollImageSkin();
    virtual ~ScrollImageSkin();
    virtual void setIndicatorPercent(float percent);
    float getIndicatorPercent();
    virtual void setEnabled(bool enabled);
protected:
    BasAreaSkin m_scrollHead;
    BasAreaSkin m_scrollTail;
    BasAreaSkin m_scrollBg;
    BasAreaSkin m_scrollIndicator;
protected:
    float m_indicatorPercent;
};

class VScrollImageSkin : public ScrollImageSkin
{
public:
    VScrollImageSkin();
    virtual ~VScrollImageSkin();
    static BasSkin *create(const CCSize &size,UiThemeDef *theme);
    void setIndicatorPercent(float percent);
    virtual void getPreferedSize(CCSize &size);
    bool init();
    virtual void reLayout();
protected:
};

class HScrollImageSkin : public ScrollImageSkin
{
public:
    HScrollImageSkin();
    virtual ~HScrollImageSkin();
    static BasSkin *create(const CCSize &size,UiThemeDef *theme);
    void setIndicatorPercent(float percent);
    virtual void getPreferedSize(CCSize &size);
    bool init();
    virtual void reLayout();
protected:
};
}
#endif
