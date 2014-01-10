#include "shineeffectaction.h"
#include "../base/touchnode.h"
#include "../skin/absareaskin.h"

namespace uilib
{

ShineEffectAction::ShineEffectAction()
{

}
ShineEffectAction::~ShineEffectAction()
{

}
void ShineEffectAction::doAction(TouchNode *node,bool enable)
{
    CCSize spriteSize;
    if(m_sprites.size() == 0){
        node->getShowSprite(m_sprites,spriteSize);
        for(unsigned int i = 0;i < m_sprites.size();i++){
            BasAreaSkin *skin = dynamic_cast<BasAreaSkin*>(m_sprites[i]);
            if(skin){
                CCSprite *sprite = skin->clone();
                if(sprite){
                    skin->addChild(sprite,-1);
                    sprite->autorelease();
                    sprite->setAnchorPoint(ccp(0.5,0.5));
                    CCSize csize = sprite->getContentSize();
                    sprite->setPosition(ccp(csize.width/2,csize.height/2));
                    m_createSprites.push_back(sprite);
                }
            }
        }
    }
    if(m_sprites.size() == 0){
        return;
    }
    if(m_running == enable)
        return;

    m_running = enable;
    if(m_running){
        float runtime = 0.5;
        for(unsigned int i = 0;i < m_createSprites.size();i++){
            CCSprite *sprite = m_createSprites[i];
            sprite->setScale(1.05);
            CCScaleTo *scaleTo = CCScaleTo::create(runtime,1.2);
            CCFadeOut *fadeOut = CCFadeOut::create(runtime);
            CCScaleTo *scaleBack = CCScaleTo::create(runtime,1.05);
            CCFadeIn *fadeIn = CCFadeIn::create(runtime);
            CCFiniteTimeAction *spawn1 = CCSpawn::create(scaleTo,fadeOut,0);
            CCFiniteTimeAction *spawn2 = CCSpawn::create(scaleBack,fadeIn,0);
            CCAction *action = CCRepeatForever::create((CCActionInterval*)CCSequence::create(spawn1,spawn2,0));
            sprite->runAction(action);
        }
    }else{
        for(unsigned int i = 0;i < m_createSprites.size();i++){
            m_createSprites[i]->stopAllActions();
        }
    }
}
}
