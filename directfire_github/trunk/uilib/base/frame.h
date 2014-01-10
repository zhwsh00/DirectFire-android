#ifndef _frame_h_
#define _frame_h_
#include "touchnode.h"

/* The main purpose of this class is
  include Skin related thing
  */
namespace uilib{
class BasSkin;

class NullFrame : public TouchNode
{
public:
    NullFrame(TouchNode *parent = 0);
    virtual ~NullFrame();
    virtual void finishLayout();
    virtual void setAnchoredSize(float width,float height);
    virtual void getPreferedSize(CCSize &size);
};

class BasFrame : public TouchNode
{
public:
    BasFrame(BasSkin *skin = 0,TouchNode *parent = 0);
    virtual ~BasFrame();
    void setSkinFillHor(bool fill);
    void setSkinFillVer(bool fill);
    void setSkin(BasSkin *skin);
    void replaceSkin(BasSkin *skin);
    BasSkin *getSkin();
    virtual void getPreferedSize(CCSize &size);
    virtual void getSkinSize(CCSize &size);
    virtual void setPreferedSize(const CCSize &size);
    virtual void setAnchoredSize(float width,float height);
    virtual void finishLayout();
    inline bool disabled() { return m_disabled;}
    virtual void setDisabled(bool disable);
    virtual bool getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size);
protected:
    BasSkin *m_skin;
    bool m_disabled;
    bool m_skinFillHor;
    bool m_skinFillVer;
};

}

#endif
