#ifndef _absareaskin_h_
#define _absareaskin_h_
#include <string>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

namespace uilib
{
class GraySuppSprite : public CCSprite
{
public:
    GraySuppSprite();
    virtual ~GraySuppSprite();
    static GraySuppSprite* create(const char* pszFileName);
    bool initWithTexture(CCTexture2D* pTexture, const CCRect& tRect);
    virtual void draw();
};

class BasAreaSkin : public CCSprite
{
public:
    BasAreaSkin();
    virtual ~BasAreaSkin();
    void setSkin(const std::string &skin,bool anti = true);
    const std::string &getSkin() { return m_skin;}
    void setSize(const CCSize &size);
    void setEnabled(bool enabled);
    inline bool isEnabled() { return m_enabled;}
    CCSprite *clone();
protected:
    std::string m_skin;
    bool m_enabled;
private:
    GraySuppSprite *m_graySkin;
};

}
#endif
