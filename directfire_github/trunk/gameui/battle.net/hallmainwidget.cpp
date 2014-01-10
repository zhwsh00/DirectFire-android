#include "hallmainwidget.h"
#include "baspage.h"
#include "gamecore/utils/ccutils.h"

#include "gamecore/sounds/soundmgr.h"

HallMainWidget::HallMainWidget()
{
    m_currPage = -1;
}
HallMainWidget::~HallMainWidget()
{

}
bool HallMainWidget::onKeyPadBackClicked()
{
    return false;
}
void HallMainWidget::finish()
{
    float hrate = getHorAdaptResourceScale();
    CCSprite *bottomBg = CCSprite::createWithSpriteFrameName("hallbottom.png");
    CCSize bgSize = bottomBg->getContentSize();
    BasNodeDelegateWidget *bottomBar = new BasNodeDelegateWidget(bottomBg,CCSizeMake(bgSize.width * hrate,bgSize.height * hrate));
    this->addChild(bottomBar);
    bottomBar->setLeft("parent",uilib::Left);
    bottomBar->setRight("parent",uilib::Right);
    bottomBar->setBottom("parent",uilib::Bottom);
    bottomBar->setHeight(bgSize.height * hrate);

    BasWidget *pageWidget = new BasWidget;
    this->addChild(pageWidget);
    pageWidget->setLeft("parent",uilib::Left);
    pageWidget->setRight("parent",uilib::Right);
    pageWidget->setTop("parent",uilib::Top);
    pageWidget->setBottom(bottomBar->getName(),uilib::Top);

    BasWidget *buttonContainer =  bottomBar;

    if(m_pages.size() != 0){
        HorizontalLayout *barlay = new HorizontalLayout;
        barlay->setSpacing(5);
        barlay->setAlignChildsSize(true);
        barlay->setAveraged(true);
        barlay->setSizeLimitedToParent();
        BasButton *button;
        if(m_buttonTheme.empty())
            m_buttonTheme = "default";

        BasNodeAction *pageMoveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
        pageMoveIn->setEaseType(uilib::EaseNone);
        pageMoveIn->setMoveInType(uilib::HorizontalRightIn);

        BasNodeAction *pageMoveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
        pageMoveOut->setEaseType(uilib::EaseNone);
        pageMoveOut->setMoveOutType(uilib::HorizontalRightOut);

        for(unsigned int i = 0;i < m_pages.size();i++){
            HallPageDef *page = m_pages[i];
            button = new BasButton;
            button->setTouchPriority(uilib::HighestPriority);
            button->setButtonIndex(i);
            button->setClickCB(this,callfuncND_selector(HallMainWidget::onPageButtonClicked));
            button->setButtonInfo("",m_buttonTheme,
                                  page->m_img,
                                  CCSizeMake(0,0),
                                  page->m_pressedImg
                                  );
            button->setWidthHeightRate(0.735);
            barlay->addWidget(button);
            page->m_page->setContainer(pageWidget);
            page->m_page->setMoveinAction(pageMoveIn);
            page->m_page->setMoveoutAction(pageMoveOut);
        }
        buttonContainer->setLayout(barlay);
        m_currPage = 0;
    }
}
void HallMainWidget::addPage(HallPageDef *page)
{
    m_pages.push_back(page);
}
int HallMainWidget::pageCount()
{
    return m_pages.size();
}
BasPage *HallMainWidget::getPageByIndex(int index)
{
    return m_pages[index]->m_page;
}
void HallMainWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
}
void HallMainWidget::childLayoutCompleted()
{
    BasWidget::childLayoutCompleted();
    for(unsigned int i = 1;i < m_pages.size();i++){
        m_pages[i]->m_page->moveOut();
    }
}
void HallMainWidget::onPageButtonClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    
    int page = *(int*)data;
    if(page == m_currPage)
        return;
    if(m_currPage == -1){
        m_currPage = page;
        enablePage(m_currPage);
        return;
    }
    BasNodeAction *moveOut = m_pages[m_currPage]->m_page->getMoveoutAction();
    BasNodeAction *moveIn = m_pages[page]->m_page->getMoveinAction();
    if(moveOut && moveIn){
        if(m_currPage <  page){
            moveOut->setMoveOutType(uilib::HorizontalLeftOut);
            moveIn->setMoveInType(uilib::HorizontalRightIn);
        }else{
            moveOut->setMoveOutType(uilib::HorizontalRightOut);
            moveIn->setMoveInType(uilib::HorizontalLeftIn);
        }
    }
    disablePage(m_currPage);
    m_currPage = page;
    enablePage(m_currPage);
}
void HallMainWidget::disablePage(int index)
{
    BasPage *page = m_pages[index]->m_page;
    page->moveoutPage();
    page->moveOut();
}
void HallMainWidget::enablePage(int index)
{
    BasPage *page = m_pages[index]->m_page;
    page->moveinPage();
    page->moveIn();
}
