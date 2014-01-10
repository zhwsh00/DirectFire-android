#include "fsizespritedelegate.h"

namespace uilib {

FSizeSpriteDelegate::FSizeSpriteDelegate(CCSprite *sprite,const CCSize &size)
{
    m_sprite = sprite;
    m_size = size;
    bool scale = true;
    if(m_size.width == 0 && m_size.height == 0){
        scale = false;
        m_size = m_sprite->getContentSize();
    }
    this->CCNode::addChild(m_sprite);
    m_sprite->setAnchorPoint(ccp(0.5,0.5));
    m_sprite->setPosition(ccp(m_size.width / 2,m_size.height / 2));
    if(scale){
        CCSize csize = m_sprite->getContentSize();
        m_sprite->setScaleX(m_size.width / csize.width);
        m_sprite->setScaleY(m_size.height / csize.height);
    }
    setWidth(m_size.width);
    setHeight(m_size.height);
    setFixedSize(m_size);
}
FSizeSpriteDelegate::~FSizeSpriteDelegate()
{
    if(m_sprite){
        m_sprite->removeFromParentAndCleanup(true);
    }
}
void FSizeSpriteDelegate::getFixedSize(CCSize &size)
{
    size = m_size;
}

}

