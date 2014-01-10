#include "sizepolicy.h"

namespace uilib
{
SizePolicy::SizePolicy()
{
    m_minSize.setSize(0,0);
    m_maxSize.setSize(1000000,1000000);
    m_preferedSize.setSize(640,480);
    m_maxWidthRate = 0;
    m_preferedSizeToChildMax = false;
    m_whRate = 0;
}
SizePolicy::~SizePolicy()
{

}
void SizePolicy::getPreferedSize(CCSize &size)
{
    if(m_preferedSizeToChildMax){
        getChildMaxPreferedSize(size);
        return;
    }
    size = m_preferedSize;
    if(size.width < m_minSize.width)
        size.width = m_minSize.width;
    if(size.height < m_minSize.height)
        size.height = m_minSize.height;
    if(size.width > m_maxSize.width)
        size.width = m_maxSize.width;
    if(size.height > m_maxSize.height)
        size.height = m_maxSize.height;
}
void SizePolicy::adjustSize(CCSize &size)
{
    if(size.width < m_minSize.width)
        size.width = m_minSize.width;
    if(size.height < m_minSize.height)
        size.height = m_minSize.height;
    if(size.width > m_maxSize.width)
        size.width = m_maxSize.width;
    if(size.height > m_maxSize.height)
        size.height = m_maxSize.height;
    CCSize refsize;
    if(m_maxWidthRef.size() != 0){
        getRefSize(m_maxWidthRef,refsize);
        refsize.width *= m_maxWidthRate;
        if(refsize.width < size.width)
            size.width = refsize.width;
    }
    refsize.width = 0;
    refsize.height = 0;
    if(m_maxHeihgtRef.size() != 0){
        getRefSize(m_maxHeihgtRef,refsize);
        refsize.height *= m_maxHeightRate;
        if(refsize.height < size.height)
            size.height = refsize.height;
    }    
    refsize.width = 0;
    refsize.height = 0;
    if(m_minWidthRef.size() != 0){
        getRefSize(m_minWidthRef,refsize);
        refsize.width *= m_minWidthRate;
        if(refsize.width > size.width)
            size.width = refsize.width;
    }
    refsize.width = 0;
    refsize.height = 0;
    if(m_minHeightRef.size() != 0){
        getRefSize(m_minHeightRef,refsize);
        refsize.height *= m_minHeightRate;
        if(refsize.height > size.height)
            size.height = refsize.height;
    }
    if(fabs(m_whRate) > 0.001){
        float h = size.width * m_whRate;
        if(size.height > h){
            size.height = h;
        }else{
            float w = size.height / m_whRate;
            if(size.width > w)
                size.width = w;
        }
    }
}
void SizePolicy::getMinimumSize(CCSize &size)
{
    size = m_minSize;
}
void SizePolicy::getMaximumSize(CCSize &size)
{
    size = m_maxSize;
}
void SizePolicy::setPreferedSize(const CCSize &size)
{
    m_preferedSize = size;
}
void SizePolicy::setPreferedSizeToChildMax(bool set)
{
    m_preferedSizeToChildMax = set;
}
void SizePolicy::getChildMaxPreferedSize(CCSize & size)
{
    size.width = 0;
    size.height = 0;
}
void SizePolicy::setFixedSize(const CCSize &size)
{
    m_minSize = size;
    m_maxSize = size;
}
void SizePolicy::setMinimumSize(const CCSize &size)
{
    m_minSize = size;
}
void SizePolicy::setMaximumSize(const CCSize &size)
{
    m_maxSize = size;
}
void SizePolicy::setMaxWidthRefSize(const std::string &name,float rate)
{
    m_maxWidthRef = name;
    m_maxWidthRate = rate;
}
void SizePolicy::setMaxHeightRefSize(const std::string &name,float rate)
{
    m_maxHeihgtRef = name;
    m_maxHeightRate = rate;
}
void SizePolicy::setMinWidthRefSize(const std::string &name,float rate)
{
    m_minWidthRef = name;
    m_minWidthRate = rate;
}
void SizePolicy::setMinHeightRefSize(const std::string &name,float rate)
{
    m_minHeightRef = name;
    m_minHeightRate = rate;
}
void SizePolicy::getRefSize(const std::string &name,CCSize &size)
{
    size.width = 0;
    size.height = 0;
}
}
