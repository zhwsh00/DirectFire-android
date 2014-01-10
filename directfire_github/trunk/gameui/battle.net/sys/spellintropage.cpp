#include "spellintropage.h"

#include "gamecore/resource/resourcemgr.h"

SpellIntroPage::SpellIntroPage()
{
    m_scroll = 0;
}
SpellIntroPage::~SpellIntroPage()
{

}
void SpellIntroPage::moveInItem()
{
    BasSysPage::moveInItem();
}
void SpellIntroPage::moveOutItem()
{
    BasSysPage::moveOutItem();
}
void SpellIntroPage::layoutCompleted()
{
    BasSysPage::layoutCompleted();
    if(m_scroll == 0)
        initItem();
}
void SpellIntroPage::initItem()
{
    ResourceMgr *mgr = ResourceMgr::getInstance();
    LangDef *lang = mgr->getLangDef();
    m_scroll = new VerScrollWidget();
    this->addChild(m_scroll);
    m_scroll->setFill("parent");
    const std::vector<std::string> &props = mgr->propsNames();
    int introstart = StringEnum::StormIntro;
    float width = m_anchorWidth * 0.9;
    std::string animName,first;
    for(unsigned int i = 0;i < props.size();i++){
        const std::string &prop = props[i];
        animName = prop + "exec";
        first = animName;
        mgr->getFrameSpriteFirstFrame(first);
        if(first.empty())
            continue;
        BasAnimSprite *anim = new BasAnimSprite(animName,first);
        anim->setAnimFinishCB(this,callfuncND_selector(SpellIntroPage::onSpellFinished));
        m_animMap.insert(std::make_pair(prop,anim));
        std::string logoName = prop + ".png";
        CCSprite *spellLogo = CCSprite::createWithSpriteFrameName(logoName.data());
        CCSize animSize = spellLogo->getContentSize();
        spellLogo->addChild(anim);
        anim->setAnchorPoint(ccp(0.5,0.5));
        anim->setPosition(ccp(animSize.width/2,animSize.height/2));
        anim->setVisible(false);

        const std::string introContent = lang->getStringById(introstart + i);
        CCLabelBMFont *introSprite = CCLabelBMFont::create(introContent.data(),"fonts/font20.fnt",width*0.6,kCCTextAlignmentLeft);
        CCSize fontSize = introSprite->getContentSize();
        CCSize size = CCSizeMake(width,MAX(animSize.height,fontSize.height));

        FSizeNullDelegate *dele = new FSizeNullDelegate(size);
        FSizeCCNodeDelegate *animDele = new FSizeCCNodeDelegate(spellLogo);
        animDele->setCanTouch(true);
        animDele->setClickCB(this,callfuncND_selector(SpellIntroPage::onSpellClicked));
        animDele->setName(prop);
        dele->addChild(animDele);
        animDele->setVertical("parent",0.5);
        animDele->setHorizontal("parent",0.2);

        FSizeCCNodeDelegate *fontDele = new FSizeCCNodeDelegate(introSprite);
        dele->addChild(fontDele);
        fontDele->setVertical("parent",0.5);
        fontDele->setHorizontal("parent",0.7);
        m_scroll->addFixedSizeWidget(dele);
    }
    m_scroll->setSpacing(10);
}
void SpellIntroPage::onSpellClicked(CCNode *node,void *data)
{
    TouchNode *touch = dynamic_cast<TouchNode*>(node);
    if(touch){
        const std::string &name = touch->getName();
        std::map<std::string,BasAnimSprite*>::iterator iter;
        iter = m_animMap.find(name);
        if(iter != m_animMap.end()){
            BasAnimSprite *anim = iter->second;
            anim->setVisible(true);
            anim->playInLoop(1);
        }
    }
}
void SpellIntroPage::onSpellFinished(CCNode *node,void *data)
{
    BasAnimSprite *anim = dynamic_cast<BasAnimSprite*>(node);
    if(anim){
        anim->setVisible(false);
    }
}
