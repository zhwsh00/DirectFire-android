#include "syspage.h"
#include "sys/systitle.h"
#include "sys/abssyspage.h"
#include "sys/gamerulepage.h"
#include "sys/spellintropage.h"
#include "sys/tribeintropage.h"
#include "sys/syssettingpage.h"
#include "sys/screenshotpage.h"
#include "sys/creditintropage.h"
#include "sys/feedbackpage.h"
#include "sys/facebookpage.h"
#include "sys/twitterpage.h"
#include "sys/sinapage.h"
#include "utils/fileutils.h"

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"

#define DF_FB_WEBSITE "https://www.facebook.com/profile.php?id=100007274735836"
#define DF_TWITTER_WEBSITE "https://twitter.com/wonegamer"
SysPage::SysPage(CCNode *parent,const ccColor4B &color) : BasShowDialog(parent,color)
{
    m_itemInit = false;
    m_title = 0;
    m_pageArea = 0;
    m_buttonsPage = 0;
    m_contentsPage = 0;
    m_currPage = 0;
    // dialog size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    setHeight(size.height * 0.9);
}
SysPage::~SysPage()
{

}
void SysPage::exec()
{
    initItem();
    BasShowDialog::exec();
}

void SysPage::headSettingClosed(int status)
{
    // only effect when item active
    if (m_currPage) {
        if (status == 0) {
            m_currPage->setInputBoxVisible(false);
        } else {
            m_currPage->setInputBoxVisible(true);
        }
    }
}
void SysPage::onBackClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_currPage == 0)
        return;
    m_currPage->moveOut();
    m_currPage->moveOutItem();
    BasNodeAction *action = m_buttonsPage->getMoveinAction();
    action->setActionTime(0.5);
    m_buttonsPage->moveIn();
    m_title->setBackEnabled(false);
    m_buttonsPage->setVisible(true);
    m_currPage = 0;
}
void SysPage::onItemClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data;
    std::map<int,BasSysPage*>::iterator iter;
    iter = m_pages.find(index);
    if(iter != m_pages.end()){
        m_currPage = iter->second;
        m_currPage->moveIn();
        m_buttonsPage->moveOut();
        m_currPage->moveInItem();
        m_title->setBackEnabled(true);
        return;
    }
    switch(index){
    case 0:{
        m_currPage = new GameRulePage();
        m_contentsPage->addChild(m_currPage);
        m_currPage->setFill("parent");
        m_contentsPage->layout(true);
        m_currPage->moveIn();
        m_currPage->moveInItem();
        m_buttonsPage->moveOut();
        m_title->setBackEnabled(true);
        m_pages.insert(std::make_pair(index,m_currPage));
        break;
    }
    case 1:{
        m_currPage = new SpellIntroPage();
        m_contentsPage->addChild(m_currPage);
        m_currPage->setFill("parent");
        m_contentsPage->layout(true);
        m_currPage->moveIn();
        m_currPage->moveInItem();
        m_buttonsPage->moveOut();
        m_title->setBackEnabled(true);
        m_pages.insert(std::make_pair(index,m_currPage));
        break;
    }
    case 2:{
        m_currPage = new TribeIntroPage();
        m_contentsPage->addChild(m_currPage);
        m_currPage->setFill("parent");
        m_contentsPage->layout(true);
        m_currPage->moveIn();
        m_currPage->moveInItem();
        m_buttonsPage->moveOut();
        m_title->setBackEnabled(true);
        m_pages.insert(std::make_pair(index,m_currPage));
        break;
    }
    case 3:{
        m_currPage = new SysSettingPage();
        m_contentsPage->addChild(m_currPage);
        m_currPage->setFill("parent");
        m_contentsPage->layout(true);
        m_currPage->moveIn();
        m_currPage->moveInItem();
        m_buttonsPage->moveOut();
        m_title->setBackEnabled(true);
        m_pages.insert(std::make_pair(index,m_currPage));
        break;
    }
    case 4:{
        m_currPage = new ScreenShotPage();
        m_contentsPage->addChild(m_currPage);
        m_currPage->setFill("parent");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        string fullPath = "ui/bg/";
        getAbsoluteResourceFilePath(fullPath);
        fullPath += "/";
        ((ScreenShotPage*)m_currPage)->setDir(fullPath);
#else
        ((ScreenShotPage*)m_currPage)->setDir("../Resources/ui/bg/");
#endif
        m_contentsPage->layout(true);
        m_currPage->moveIn();
        m_currPage->moveInItem();
        m_buttonsPage->moveOut();
        m_title->setBackEnabled(true);
        m_pages.insert(std::make_pair(index,m_currPage));
        break;
    }
    case 5:{
        m_currPage = new FeedBackPage();
        m_contentsPage->addChild(m_currPage);
        m_currPage->setFill("parent");
        m_contentsPage->layout(true);
        m_currPage->moveIn();
        m_currPage->moveInItem();
        m_buttonsPage->moveOut();
        m_title->setBackEnabled(true);
        //m_pages.insert(std::make_pair(index,m_currPage));
        break;
    }
        /*
    case 6:{
        m_currPage = new CreditInfoPage();
        m_contentsPage->addChild(m_currPage);
        m_currPage->setFill("parent");
        m_contentsPage->layout(true);
        m_currPage->moveIn();
        m_currPage->moveInItem();
        m_buttonsPage->moveOut();
        m_title->setBackEnabled(true);
        m_pages.insert(std::make_pair(index,m_currPage));
        break;
    }
    */
    case 6:{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCApplication::sharedApplication()->openURL(DF_FB_WEBSITE);
#else
        m_currPage = new FaceBookPage();
        m_contentsPage->addChild(m_currPage);
        m_currPage->setFill("parent");
        m_contentsPage->layout(true);
        m_currPage->moveIn();
        m_currPage->moveInItem();
        m_buttonsPage->moveOut();
        m_title->setBackEnabled(true);
        m_pages.insert(std::make_pair(index,m_currPage));
#endif
        break;
    }
    case 7:{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCApplication::sharedApplication()->openURL(DF_TWITTER_WEBSITE);
#else
        m_currPage = new TwitterPage();
        m_contentsPage->addChild(m_currPage);
        m_currPage->setFill("parent");
        m_contentsPage->layout(true);
        m_currPage->moveIn();
        m_currPage->moveInItem();
        m_buttonsPage->moveOut();
        m_title->setBackEnabled(true);
        m_pages.insert(std::make_pair(index,m_currPage));
#endif
        break;
    }
    case 8:{
        m_currPage = new SinaPage();
        m_contentsPage->addChild(m_currPage);
        m_currPage->setFill("parent");
        m_contentsPage->layout(true);
        m_currPage->moveIn();
        m_currPage->moveInItem();
        m_buttonsPage->moveOut();
        m_title->setBackEnabled(true);
        m_pages.insert(std::make_pair(index,m_currPage));
        break;
    }
    default:{
        break;
    }
    }
}
void SysPage::initItem()
{
    if(m_itemInit)
        return;
    m_title = new SysTitle();
    m_title->setBackClickCB(this,callfuncND_selector(SysPage::onBackClicked));
    this->addChild(m_title);
    m_title->setWidth(10);
    m_title->setHeight(10);
    m_title->setVertical("parent",0);
    m_title->setHorizontal("parent",0);

    m_pageArea = new BasWidget;
    this->addChild(m_pageArea);
    m_pageArea->setLeft("parent",uilib::Left);
    m_pageArea->setRight("parent",uilib::Right);
    m_pageArea->setTop(m_title->getName(),uilib::Bottom);
    m_pageArea->setBottom("parent",uilib::Bottom);
    m_buttonsPage = new BasWidget;
    m_contentsPage = new BasWidget;
    m_pageArea->addChild(m_buttonsPage);
    m_pageArea->addChild(m_contentsPage);
    m_buttonsPage->setFill("parent");
    m_contentsPage->setFill("parent");
    GridLayout *lay = new GridLayout(5,2);
    int index = 0;
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    if(1){
        //game rule page
        BasButton *button = new BasButton;
        button->setButtonInfo("","default","buttonbg",CCSizeMake(240,100));
        CCLabelBMFont *font = CCLabelBMFont::create(lang->getStringById(StringEnum::GameRule).data(),"fonts/uifont35.fnt");
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(font);
        button->addChild(dele);
        dele->setCenterIn("parent");
        button->setButtonIndex(index++);
        button->setClickCB(this,callfuncND_selector(SysPage::onItemClicked));
        lay->addWidget(button);
    }
    if(1){
        //spell intro page
        BasButton *button = new BasButton;
        button->setButtonInfo("","default","buttonbg",CCSizeMake(240,100));
        CCLabelBMFont *font = CCLabelBMFont::create(lang->getStringById(StringEnum::SpellIntro).data(),"fonts/uifont35.fnt");
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(font);
        button->addChild(dele);
        dele->setCenterIn("parent");
        button->setButtonIndex(index++);
        button->setClickCB(this,callfuncND_selector(SysPage::onItemClicked));
        lay->addWidget(button);
    }
    if(1){
        //tribe intro page
        BasButton *button = new BasButton;
        button->setButtonInfo("","default","buttonbg",CCSizeMake(240,100));
        CCLabelBMFont *font = CCLabelBMFont::create(lang->getStringById(StringEnum::TribeIntro).data(),"fonts/uifont35.fnt");
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(font);
        button->addChild(dele);
        dele->setCenterIn("parent");
        button->setButtonIndex(index++);
        button->setClickCB(this,callfuncND_selector(SysPage::onItemClicked));
        lay->addWidget(button);
    }
    if(1){
        //syssetting page
        BasButton *button = new BasButton;
        button->setButtonInfo("","default","buttonbg",CCSizeMake(240,100));
        CCLabelBMFont *font = CCLabelBMFont::create(lang->getStringById(StringEnum::SysSetting).data(),"fonts/uifont35.fnt");
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(font);
        button->addChild(dele);
        dele->setCenterIn("parent");
        button->setButtonIndex(index++);
        button->setClickCB(this,callfuncND_selector(SysPage::onItemClicked));
        lay->addWidget(button);
    }
    if(1){
        //screen shot page
        BasButton *button = new BasButton;
        button->setButtonInfo("","default","buttonbg",CCSizeMake(240,100));
        CCLabelBMFont *font = CCLabelBMFont::create(lang->getStringById(StringEnum::ScreenShot).data(),"fonts/uifont35.fnt");
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(font);
        button->addChild(dele);
        dele->setCenterIn("parent");
        button->setButtonIndex(index++);
        button->setClickCB(this,callfuncND_selector(SysPage::onItemClicked));
        lay->addWidget(button);
    }
    if(1){
        //feed back page
        BasButton *button = new BasButton;
        button->setButtonInfo("","default","buttonbg",CCSizeMake(240,100));
        CCLabelBMFont *font = CCLabelBMFont::create(lang->getStringById(StringEnum::FeedBack).data(),"fonts/uifont35.fnt");
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(font);
        button->addChild(dele);
        dele->setCenterIn("parent");
        button->setButtonIndex(index++);
        button->setClickCB(this,callfuncND_selector(SysPage::onItemClicked));
        lay->addWidget(button);
    }
    if(1){
        //face book page
        BasButton *button = new BasButton;
        button->setButtonInfo("","default","buttonbg",CCSizeMake(240,100));
        CCLabelBMFont *font = CCLabelBMFont::create(lang->getStringById(StringEnum::SharedToFb).data(),"fonts/uifont35.fnt");
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(font);
        button->addChild(dele);
        dele->setCenterIn("parent");
        button->setButtonIndex(index++);
        button->setClickCB(this,callfuncND_selector(SysPage::onItemClicked));
        lay->addWidget(button);
    }
    if(1){
        //twitter page
        BasButton *button = new BasButton;
        button->setButtonInfo("","default","buttonbg",CCSizeMake(240,100));
        CCLabelBMFont *font = CCLabelBMFont::create(lang->getStringById(StringEnum::SharedToTwitter).data(),"fonts/uifont35.fnt");
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(font);
        button->addChild(dele);
        dele->setCenterIn("parent");
        button->setButtonIndex(index++);
        button->setClickCB(this,callfuncND_selector(SysPage::onItemClicked));
        lay->addWidget(button);
    }
    if(0){
        //sina page
        BasButton *button = new BasButton;
        button->setButtonInfo(lang->getStringById(StringEnum::SharedToSina),"default","sysbuttonbg",CCSizeMake(0,0));
        button->setButtonIndex(index++);
        button->setClickCB(this,callfuncND_selector(SysPage::onItemClicked));
        lay->addWidget(button);
    }
    lay->setSpacing(20);
    m_buttonsPage->setLayout(lay);
    //this->layout(true);
    m_itemInit = true;
    if(1){
        //buttons page movein & moveout
        BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
        moveIn->setActionTime(0);
        BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
        moveIn->setEaseType(uilib::EaseSineInOut);
        moveIn->setMoveInType(uilib::HorizontalLeftIn);
        moveOut->setEaseType(uilib::EaseSineInOut);
        moveOut->setMoveOutType(uilib::HorizontalLeftOut);
        moveOut->setFinishCB(this,callfuncN_selector(SysPage::onButtonPageMoveOutFinished),m_buttonsPage);
        m_buttonsPage->setMoveinAction(moveIn);
        m_buttonsPage->setMoveoutAction(moveOut);
    }
}
void SysPage::onButtonPageMoveOutFinished(CCNode *node)
{
    m_buttonsPage->setVisible(false);
}
