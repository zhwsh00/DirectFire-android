#include "frame.h"
#include "../skin/absskin.h"

namespace uilib
{

NullFrame::NullFrame(TouchNode *parent) : TouchNode(parent)
{

}
NullFrame::~NullFrame()
{

}
void NullFrame::finishLayout()
{
    //dothing
}
void NullFrame::setAnchoredSize(float width,float height)
{
    setContentSize(CCSizeMake(width,height));
    BasAnchor::setAnchoredSize(width,height);
    finishLayout();
}
void NullFrame::getPreferedSize(CCSize &size)
{
    TouchNode::getPreferedSize(size);
    TouchNode::adjustSize(size);
}

BasFrame::BasFrame(BasSkin *skin,TouchNode *parent) : TouchNode(parent)
{
    m_skinFillHor = true;
    m_skinFillVer = true;
    m_disabled = false;
    m_skin = skin;
    if(m_skin)
        this->CCNode::addChild(m_skin,0);
}
BasFrame::~BasFrame()
{

}
void BasFrame::setSkinFillHor(bool fill)
{
    m_skinFillHor = fill;
    if(m_skin)
        m_skin->setSkinFillHor(fill);
}
void BasFrame::setSkinFillVer(bool fill)
{
    m_skinFillVer = fill;
    if(m_skin)
        m_skin->setSkinFillVer(fill);
}
void BasFrame::setSkin(BasSkin *skin)
{
    if(m_skin){
        m_skin->removeFromParentAndCleanup(true);
    }
    m_skin = skin;
    this->CCNode::addChild(m_skin);
    if(m_skin->skinFillHor() != m_skinFillHor ||
            m_skin->skinFillVer() != m_skinFillVer){
        m_skin->setSkinFillHor(m_skinFillHor);
        m_skin->setSkinFillVer(m_skinFillVer);
    }
}
void BasFrame::replaceSkin(BasSkin *skin)
{
    if(m_skin == skin)
        return;
    if(m_skin){
        this->CCNode::removeChild(m_skin);
    }
    m_skin = skin;
    if(m_skin){
        this->CCNode::addChild(m_skin);
        if(m_skin->skinFillHor() != m_skinFillHor ||
                m_skin->skinFillVer() != m_skinFillVer){
            m_skin->setSkinFillHor(m_skinFillHor);
            m_skin->setSkinFillVer(m_skinFillVer);
        }
        finishLayout();
    }
}
BasSkin *BasFrame::getSkin()
{
    return m_skin;
}
void BasFrame::getPreferedSize(CCSize &size)
{
    if(m_skin){
        m_skin->getPreferedSize(size);
        TouchNode::adjustSize(size);
    }else{
        TouchNode::getPreferedSize(size);
        TouchNode::adjustSize(size);
    }
}
void BasFrame::getSkinSize(CCSize &size)
{
    if(m_skin){
        m_skin->getPreferedSize(size);
    }else{
        size.width = 0;
        size.height = 0;
    }
}
void BasFrame::setPreferedSize(const CCSize &size)
{
    if(m_skin){
        //set to framesize
        m_skin->setFrameSize(size);
    }
    TouchNode::setPreferedSize(size);
}
void BasFrame::setAnchoredSize(float width,float height)
{
    setContentSize(CCSizeMake(width,height));
    TouchNode::setAnchoredSize(width,height);
    finishLayout();
}
void BasFrame::finishLayout()
{
    if(m_skin){
        m_skin->setFrameSize(CCSizeMake(m_anchorWidth,m_anchorHeight));
    }
}
void BasFrame::setDisabled(bool disable)
{
    m_disabled = disable;
    if(m_skin){
        m_skin->setEnabled(!m_disabled);
    }
}
bool BasFrame::getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size)
{
    if(m_skin){
        return m_skin->getShowSprite(sprites,size);
    }else{
        return false;
    }
}
}
