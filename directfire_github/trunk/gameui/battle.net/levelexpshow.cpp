#include "levelexpshow.h"
#include "gamecore/resource/resourcemgr.h"
#include "gamecore/utils/ccutils.h"

LevelExpShow::LevelExpShow()
{
    m_progressBar = 0;
    m_medalWidget = 0;
    m_lightWidget = 0;

    m_theme = "default";
    m_bg = "roundedhbarbg";
    m_fg = "goldenhbar";
    setCanTouch(true);
}
LevelExpShow::~LevelExpShow()
{

}
void LevelExpShow::setBarTheme(const std::string &theme,
                            const std::string &bg,const std::string &fg)
{
    m_theme = theme;
    m_bg = bg;
    m_fg = fg;
}
void LevelExpShow::setLevelExp(int level,int exp,int levelexp,int nextexp)
{
    if(m_progressBar != 0){
        this->delChild(m_progressBar);
        m_progressBar = 0;
    }
    if(m_medalWidget){
        this->delChild(m_medalWidget);
        m_medalWidget = 0;
    }
    if(m_lightWidget){
        this->delChild(m_lightWidget);
        m_lightWidget = 0;
    }
    std::stringstream ss;
    m_level = level;
    m_exp = exp;
    m_levelExp = levelexp;
    m_nextLevelNeedExp = nextexp;
    if(m_levelExp == 0 || m_nextLevelNeedExp == 0)
        return;

    m_progressBar = new HorTriProgressBar;
    m_progressBar->setSkinFillVer(true);
    m_progressBar->setTheme(m_theme,m_bg,m_fg);
    this->addChild(m_progressBar);
    m_progressBar->setLeft("parent",uilib::Left);
    m_progressBar->setRight("parent",uilib::Right);
    m_progressBar->setHeight(12);
    m_progressBar->setBottom("parent",uilib::Bottom);
    m_progressBar->setProgressTo(2.0,100 * m_exp / m_nextLevelNeedExp);

    ss << "medal" << m_level << ".png";
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ss.str().data());

    if(frame){
        CCSprite *medal = CCSprite::create();
        medal->initWithSpriteFrame(frame);
        CCSize size = medal->getContentSize();
        float frate = getAdaptResourceScale();
        m_medalWidget = new BasNodeDelegateWidget(medal,CCSizeMake(size.width * frate,size.height * frate));
        m_medalWidget->setLeft("parent",uilib::Left);
        m_medalWidget->setBottom(m_progressBar->getName(),uilib::Top);
        m_medalWidget->setTop("parent",uilib::Top);
        this->addChild(m_medalWidget);

        std::stringstream ss;
        ss << "Lv:" << m_level;
        CCLabelBMFont *levelFont = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
        BasNodeDelegateWidget *levelDele = new BasNodeDelegateWidget(levelFont);
        this->addChild(levelDele);
        levelDele->setLeft(m_medalWidget->getName(),uilib::Right);
        levelDele->setBottom(m_medalWidget->getName(),uilib::Bottom);
    }

    this->layout(true);
}
void LevelExpShow::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BasWidget::touchPressEvent(pTouch,pEvent);
}
void LevelExpShow::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BasWidget::touchMoveEvent(pTouch,pEvent);
}
void LevelExpShow::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BasWidget::touchReleaseEvent(pTouch,pEvent);
}
