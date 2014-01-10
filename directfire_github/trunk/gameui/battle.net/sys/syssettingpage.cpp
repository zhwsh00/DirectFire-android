#include "syssettingpage.h"
#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"
#include "gamecore/userdata/userdata.h"

SysSettingPage::SysSettingPage()
{
    m_itemInit = false;
    m_soundMgr = SoundMgr::getInstance();
}
SysSettingPage::~SysSettingPage()
{

}
void SysSettingPage::moveInItem()
{
    BasSysPage::moveInItem();
}
void SysSettingPage::moveOutItem()
{
    BasSysPage::moveOutItem();
}
void SysSettingPage::layoutCompleted()
{
    BasSysPage::layoutCompleted();
    if(!m_itemInit)
        initItem();
}
void SysSettingPage::initItem()
{
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();

    CheckBox *checkbox1 = new CheckBox();
    checkbox1->setCheckInfo(lang->getStringById(StringEnum::CloseBgMusic).data(),"fonts/uifont35.fnt","default","",CCSizeMake(300,80),ccWHITE);
    checkbox1->setClickCB(this,callfuncND_selector(SysSettingPage::onBgMusicFinished));
    checkbox1->setCheck(m_soundMgr->isBgSoundOn());

    CheckBox *checkbox2 = new CheckBox();
    checkbox2->setCheckInfo(lang->getStringById(StringEnum::CloseGameMusic).data(),"fonts/uifont35.fnt","default","",CCSizeMake(300,80),ccWHITE);
    checkbox2->setClickCB(this,callfuncND_selector(SysSettingPage::onGameMusicClicked));
    checkbox2->setCheck(m_soundMgr->isGameSoundOn());

    this->addChild(checkbox1);
    this->addChild(checkbox2);

    checkbox1->setTop("parent",uilib::Top);
    checkbox1->setLeft("parent",uilib::Left);
    checkbox1->setMargins(40);
    checkbox2->setTop(checkbox1->getName(),uilib::Bottom);
    checkbox2->setLeft("parent",uilib::Left);
    checkbox2->setMargins(40);
}
void SysSettingPage::onGameMusicClicked(CCNode *node,void *data)
{
    m_soundMgr->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_soundMgr->switchGameSoundOn(!m_soundMgr->isGameSoundOn());
}
void SysSettingPage::onBgMusicFinished(CCNode *node,void *data)
{
    m_soundMgr->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_soundMgr->switchBgSoundOn(!m_soundMgr->isBgSoundOn());
}
