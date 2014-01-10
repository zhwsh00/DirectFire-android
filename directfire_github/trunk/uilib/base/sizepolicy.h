#ifndef _sizepolicy_h_
#define _sizepolicy_h_
#include <string>
#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;

namespace uilib
{
class SizePolicy
{
public:
    SizePolicy();
    ~SizePolicy();

public:
    virtual void adjustSize(CCSize &size);
    virtual void getPreferedSize(CCSize &size);
    virtual void getMinimumSize(CCSize &size);
    virtual void getMaximumSize(CCSize &size);
    virtual void setPreferedSize(const CCSize &size);
    virtual void setPreferedSizeToChildMax(bool set);
    inline bool preferedSizeToChildMax() { return m_preferedSizeToChildMax;}
    virtual void getChildMaxPreferedSize(CCSize & size);
    void setFixedSize(const CCSize &size);
    void setMinimumSize(const CCSize &size);
    void setMaximumSize(const CCSize &size);
    void setMaxWidthRefSize(const std::string &name,float rate);
    void setMaxHeightRefSize(const std::string &name,float rate);
    void setMinWidthRefSize(const std::string &name,float rate);
    void setMinHeightRefSize(const std::string &name,float rate);
    virtual void getRefSize(const std::string &name,CCSize &size);
    void setWidthHeightRate(float rate){ m_whRate = rate;}
protected:
    CCSize m_preferedSize;
    CCSize m_minSize;
    CCSize m_maxSize;
    std::string m_maxWidthRef;
    float m_maxWidthRate;
    std::string m_maxHeihgtRef;
    float m_maxHeightRate;
    std::string m_minWidthRef;
    float m_minWidthRate;
    std::string m_minHeightRef;
    float m_minHeightRate;
    float m_whRate;
protected:
    bool m_preferedSizeToChildMax;
};

}
#endif
