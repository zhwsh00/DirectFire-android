#include "usershow.h"
#include "wonshow.h"
#include "socialshow.h"
#include "headportraitwidget.h"
#include "socialpage.h"

#include "sendmsgdialog.h"
#include "sendgiftdialog.h"
#include "addfrienddialog.h"
#include "sendmsganim.h"

#include "utils/sysutils.h"
#include "levelexpshow.h"

#include "utils/sysutils.h"

#include "gamecore/serverinterface.h"

#include "gamecore/utils/ccutils.h"

UserShow::UserShow(BasWidget *parent)
{
    if(parent)
        parent->addChild(this);
    clear();
    m_accountId = " ";
    m_nickName = " ";
    m_serverIface = ServerInterface::getInstance();

    m_headWidget = 0;
    m_propShow = 0;
    m_levelShow = 0;
    m_thumbFont = 0;
    m_footFont = 0;
    m_thumbContainer = 0;
    m_coinFont = 0;
    m_goldFont = 0;
}
UserShow::~UserShow()
{

}
bool UserShow::onKeyPadBackClicked()
{
    return m_headWidget->onKeyPadBackClicked();
}
void UserShow::clear()
{
    m_intelligence = 0;
    m_energy = 0;
    m_lucky = 0;
    m_leadership = 0;
    m_socialLevel = 0;
    m_headWidget = 0;
    m_male = false;
    m_propShow = 0;
    m_levelShow = 0;

    m_footNum = 0;
    m_thumbNum = 0;
    m_thumbFont = 0;
    m_footFont = 0;
}
void UserShow::setTheme(const std::string &val)
{
    m_theme = val;
}
void UserShow::setHeadPortrait(const std::string &val)
{
    m_headPortrait = val;
}
void UserShow::setNickName(const std::string &val)
{
    m_nickName = val;
    if(m_nickFont)
        m_nickFont->setString(val.data());
}
void UserShow::setAccountId(const std::string &val)
{
    m_accountId = val;
}
void UserShow::setIntelligence(int val)
{
    m_intelligence = val;
}
void UserShow::setEnergy(int val)
{
    m_energy = val;
}
void UserShow::setLucky(int val)
{
    m_lucky = val;
}
void UserShow::setLeadership(int val)
{
    m_leadership = val;
}
void UserShow::setSocialLevel(int val)
{
    m_socialLevel = val;
}
void UserShow::setOwnsProps()
{

}
void UserShow::setUserPropNum(int id,int num)
{
    //beta2
    if(id == PropDef::Props_Coin){
        std::stringstream ss;
        ss << "x" << num;
        m_coinFont->setString(ss.str().data());
    }else if(id == PropDef::Props_Gold){
        std::stringstream ss;
        ss << "x" << num;
        m_goldFont->setString(ss.str().data());
    }
}
void UserShow::setLevelExp(int level,int exp,int levelexp,int nextexp)
{
    if(m_levelShow){
        m_levelShow->setLevelExp(level,exp,levelexp,nextexp);
    }
}
void UserShow::portraitUpdated(std::string *data)
{
    if(m_headWidget)
        m_headWidget->portraitUpdated(data);
}
void UserShow::upThumbFoot(int thumb,int foot)
{
    m_thumbNum = thumb;
    m_footNum = foot;
    if(m_thumbFont){
        std::stringstream ss;
        ss << "x" << m_thumbNum;
        m_thumbFont->setString(ss.str().data());
    }
    if(m_footFont){
        std::stringstream ss;
        ss << "x" << m_footNum;
        m_footFont->setString(ss.str().data());
    }
    m_thumbContainer->layout(true);
}
void UserShow::notifyResetUserInfo()
{
    if(m_headWidget)
        m_headWidget->openHeadSettingDialog(true);
}

//finish
void UserShow::finish()
{
    float srate = getAdaptResourceScale();
    if(m_theme.empty())
        m_theme = "default";
    if(1){
        //head widget
        m_headWidget = new HeadPortraitWidget;
        this->addChild(m_headWidget);
        m_headWidget->setHorizontal("parent",0.875);
        m_headWidget->setVertical("parent",0.5);
        m_headWidget->setWidth(173 * srate);
        m_headWidget->setHeight(173 * srate);
        std::vector<std::string> fgs;
        fgs.push_back("circleprogbarfg_a");
        for(unsigned int i = 0;i < fgs.size();i++){
            HeadPortraitWidget::CircleBarDef *def = new HeadPortraitWidget::CircleBarDef;
            def->m_barBg = "circleprogbarbg";
            def->m_barFg = fgs[i];
            def->m_percent = 100;
            m_headWidget->addCircleBar(def);
        }
    }
    do{
        //thumb foot show
        CCSprite *sinkBg = CCSprite::createWithSpriteFrameName("sinkbg.png");
        CCSize sinkSize = sinkBg->getContentSize();

        m_thumbContainer = new BasNodeDelegateWidget(sinkBg,CCSizeMake(sinkSize.width * srate,sinkSize.height * srate));
        this->addChild(m_thumbContainer);
        m_thumbContainer->setTop("parent",uilib::Top);
        m_thumbContainer->setLeft("parent",uilib::Left);
        m_thumbContainer->setTopMargin(6);
        m_thumbContainer->setLeftMargin(6);

        std::stringstream ss;
        std::string thumb,foot;
        UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName("");
        uiDef->getNormalData()->getImg("thumb",thumb);
        uiDef->getNormalData()->getImg("foot",foot);
        if(thumb.empty() || foot.empty())
            break;
        CCSprite *thumbImg = CCSprite::createWithSpriteFrameName(thumb.data());
        BasNodeDelegateWidget *thumbDele = new BasNodeDelegateWidget(thumbImg,CCSizeMake(50 * srate,50 * srate));
        m_thumbContainer->addChild(thumbDele);
        thumbDele->setLeft("parent",uilib::Left);
        thumbDele->setLeftMargin(4);
        thumbDele->setVertical("parent",0.5);

        CCSprite *footImg = CCSprite::createWithSpriteFrameName(foot.data());
        BasNodeDelegateWidget *footDele = new BasNodeDelegateWidget(footImg,CCSizeMake(50 * srate,50 * srate));
        m_thumbContainer->addChild(footDele);
        footDele->setHorizontal("parent",0.5);
        footDele->setHorMargin(25 * srate);
        footDele->setVertical("parent",0.5);

        ss.str("");ss << "x00" << m_thumbNum;
        m_thumbFont = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
        BasNodeDelegateWidget *d1 = new BasNodeDelegateWidget(m_thumbFont);
        m_thumbContainer->addChild(d1);
        d1->setVertical("parent",0.5);
        d1->setLeft(thumbDele->getName(),uilib::Right);

        ss.str("");ss << m_footNum << "x00";
        m_footFont = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
        BasNodeDelegateWidget *d2 = new BasNodeDelegateWidget(m_footFont);
        m_thumbContainer->addChild(d2);
        d2->setVertical("parent",0.5);
        d2->setLeft(footDele->getName(),uilib::Right);
    }while(0);
    if(1){
        //nickname
        m_nickFont = CCLabelBMFont::create("","fonts/uifont24.fnt");
        BasNodeDelegateWidget *nickD = new BasNodeDelegateWidget(m_nickFont);
        this->addChild(nickD);
        nickD->setRight(m_headWidget->getName(),uilib::Left);
        nickD->setRightMargin(30);
        nickD->setVertical(m_thumbContainer->getName(),0.5);
    }
    if(1){
        //level exp show
        m_levelShow = new LevelExpShow();
        this->addChild(m_levelShow);
        m_levelShow->setLeft("parent",uilib::Left);
        m_levelShow->setLeftMargin(4);
        m_levelShow->setRight(m_headWidget->getName(),uilib::Left);
        m_levelShow->setRightMargin(12);
        m_levelShow->setVertical("parent",0.537);
        m_levelShow->setHeight(80 * srate);
    }
    if(1){
        //coin ,gold show
        CCSprite *coinSprite = CCSprite::createWithSpriteFrameName("coin.png");
        CCSprite *goldSprite = CCSprite::createWithSpriteFrameName("gold.png");
        CCSize coinSize = coinSprite->getContentSize();
        CCSize goldSize = goldSprite->getContentSize();
        BasNodeDelegateWidget *coinDele = new BasNodeDelegateWidget(coinSprite,CCSizeMake(coinSize.width * srate,coinSize.height * srate));
        BasNodeDelegateWidget *goldDele = new BasNodeDelegateWidget(goldSprite,CCSizeMake(goldSize.width * srate,goldSize.height * srate));
        this->addChild(coinDele);
        this->addChild(goldDele);
        coinDele->setHorizontal("parent",0.269);
        coinDele->setVertical("parent",0.51);
        goldDele->setHorizontal("parent",0.529);
        goldDele->setVertical("parent",0.51);
        m_coinFont = CCLabelBMFont::create("x000000","fonts/uifont24.fnt");
        m_goldFont = CCLabelBMFont::create("x000000","fonts/uifont24.fnt");
        BasNodeDelegateWidget *coinFontDele = new BasNodeDelegateWidget(m_coinFont);
        BasNodeDelegateWidget *goldFontDele = new BasNodeDelegateWidget(m_goldFont);
        this->addChild(coinFontDele);
        this->addChild(goldFontDele);
        coinFontDele->setLeft(coinDele->getName(),uilib::Right);
        coinFontDele->setBottom(coinDele->getName(),uilib::Bottom);

        goldFontDele->setLeft(goldDele->getName(),uilib::Right);
        goldFontDele->setBottom(goldDele->getName(),uilib::Bottom);
    }
}
