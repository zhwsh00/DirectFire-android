#include "cardsprite.h"

namespace uilib
{

#define kInAngleZ        270
#define kInDeltaZ        90

#define kOutAngleZ       0
#define kOutDeltaZ       90

enum {
    tag_inCard = 1,
    tag_outCard
};

CardSprite::CardSprite(const CCSize &size,float time)
{
    m_cSize = size;
    m_inSprite = 0;
    m_outSprite = 0;
    m_isOpened = 0;
    m_openAnimIn = 0;
    m_openAnimOut = 0;
    setContentSize(m_cSize);
    m_time = time;
    m_listener = 0;
    m_func = 0;
}

CardSprite::~CardSprite()
{
    m_openAnimIn->release();
    m_openAnimOut->release();
}
void CardSprite::setCards(const std::string &in,const std::string &out)
{
    m_inImg = in;
    m_outImg = out;
    if(m_inSprite == 0){
        m_inSprite = CCSprite::createWithSpriteFrameName(m_inImg.data());
        this->addChild(m_inSprite);
    }else{
        m_inSprite->initWithSpriteFrameName(m_inImg.data());
    }
    if(m_outSprite == 0){
        m_outSprite = CCSprite::createWithSpriteFrameName(m_outImg.data());
        this->addChild(m_outSprite);
    }else{
        m_outSprite->initWithSpriteFrameName(m_outImg.data());
    }
    m_inSprite->setAnchorPoint(ccp(0.5,0.5));
    m_inSprite->setPosition(ccp(m_cSize.width / 2,m_cSize.height / 2));
    m_inSprite->setVisible(false);

    m_outSprite->setAnchorPoint(ccp(0.5,0.5));
    m_outSprite->setPosition(ccp(m_cSize.width / 2,m_cSize.height / 2));

    CCSize inSize = m_inSprite->getContentSize();
    m_inSprite->setScaleX(m_cSize.width / inSize.width);
    m_inSprite->setScaleY(m_cSize.height / inSize.height);

    CCSize outSize = m_outSprite->getContentSize();
    m_outSprite->setScaleX(m_cSize.width / outSize.width);
    m_outSprite->setScaleY(m_cSize.height / outSize.height);

    m_openAnimIn = (CCActionInterval*)CCSequence::create(CCDelayTime::create(m_time * .5),
                                                         CCShow::create(),
                                                         CCOrbitCamera::create(m_time * .5, 1, 0, kInAngleZ, kInDeltaZ, 0, 0),
                                                         0);
    m_openAnimIn->retain();

    m_openAnimOut = (CCActionInterval *)CCSequence::create(CCOrbitCamera::create(m_time * .5, 1, 0, kOutAngleZ, kOutDeltaZ, 0, 0),
                                                           CCHide::create(),
                                                           CCDelayTime::create(m_time * .5),
                                                           CCCallFuncND::create(this,callfuncND_selector(CardSprite::onFlipFinished),0),
                                                           0);
    m_openAnimOut->retain();
}

void CardSprite::openCard()
{
    m_inSprite->stopAllActions();
    m_outSprite->stopAllActions();
    m_inSprite->runAction(m_openAnimIn);
    m_outSprite->runAction(m_openAnimOut);
}
void CardSprite::closeCard()
{
    m_inSprite->stopAllActions();
    m_outSprite->stopAllActions();
    m_inSprite->runAction(m_openAnimOut);
    m_outSprite->runAction(m_openAnimIn);
}
bool CardSprite::isClosed()
{
    return m_outSprite->isVisible();
}
void CardSprite::setFlipListener(CCNode *node,SEL_CallFuncND func)
{
    m_listener = node;
    m_func = func;
}
void CardSprite::onFlipFinished(CCNode *node,void *data)
{
    if(m_listener && m_func){
        (m_listener->*m_func)(this,0);
    }
}

}
