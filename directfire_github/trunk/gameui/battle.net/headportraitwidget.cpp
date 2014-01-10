#include "headportraitwidget.h"
#include "utils/sysutils.h"
#include "gamecore/sounds/soundmgr.h"

HeadPortraitWidget::HeadPortraitWidget()
{
    m_actionTime = 2.0;
    m_theme = "default";
    m_headBg = "portraitbg";
    m_headPortrait = "portraitdefault";
    m_indentRate = 16;
    m_headSprite = 0;
    m_headSettingDialog = 0;
    setCanTouch(true);
    setTouchPriority(uilib::HighestPriority);
}
HeadPortraitWidget::~HeadPortraitWidget()
{

}
bool HeadPortraitWidget::onKeyPadBackClicked()
{
    if(m_headSettingDialog){
        onHeadSettingDialogCloseClicked(m_headSettingDialog,0);
        return true;
    }else{
        return false;
    }
}
void HeadPortraitWidget::setPortrait(const std::string &theme,
                 const std::string &bg,
                 const std::string &head)
{
    m_theme = theme;
    m_headBg = bg;
    m_headPortrait = head;
}
void HeadPortraitWidget::setHeadFile(const std::string &headfile)
{
    m_headFile = headfile;
}
void HeadPortraitWidget::updateHeadFile(const std::string &headfile)
{
    //update
    m_headFile = headfile;
}
void HeadPortraitWidget::setActionTime(float time)
{
    m_actionTime = time;
}
void HeadPortraitWidget::addPercentTo(int index,float percent)
{
    if(index >=0 && index < m_circleBars.size())
        m_circleBars[index]->setProgressTo(m_actionTime,percent);
}
void HeadPortraitWidget::addPercentBy(int index,float percent)
{
    if(index >=0 && index < m_circleBars.size())
        m_circleBars[index]->setProgressAdd(m_actionTime,percent);
}
void HeadPortraitWidget::addCircleBar(CircleBarDef *def)
{
    m_barDefs.push_back(def);
}
void HeadPortraitWidget::setIndentRate(float rate)
{
    m_indentRate = rate;
}
void HeadPortraitWidget::portraitUpdated(std::string *data)
{
    if(m_headSprite == 0)
        return;
    CCImage *img = new CCImage;
    img->initWithImageData((void*)data->c_str(),data->size(),
                           CCImage::kFmtUnKnown);
    CCTexture2D *texture = new CCTexture2D;
    texture->initWithImage(img);
    m_headSprite->initWithTexture(texture);
    CCSize csize;csize.width = img->getWidth();csize.height = img->getHeight();
    m_headSprite->setScaleX(m_headSize.width / csize.width);
    m_headSprite->setScaleY(m_headSize.height / csize.height);
    delete img;

    CCFadeIn *fade = CCFadeIn::create(0.5);
    m_headSprite->runAction(fade);
}
void HeadPortraitWidget::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void HeadPortraitWidget::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void HeadPortraitWidget::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    openHeadSettingDialog();
}
void HeadPortraitWidget::openHeadSettingDialog(bool editAble)
{
    // disable hall chat/feedback input box
    ServerInterface::getInstance()->headSettingClosed(false);
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    m_headSettingDialog = new HeadSettingDialog(root,ccc4(0,0,0,128));
    m_headSettingDialog->setCloseCB(this,callfuncND_selector(HeadPortraitWidget::onHeadSettingDialogCloseClicked));
    m_headSettingDialog->setSubmitPortraitCB(this,callfuncND_selector(HeadPortraitWidget::onHeadSettingDialogPortraitSubmitted));
    m_headSettingDialog->setHeadSprite(m_headSprite);
    m_headSettingDialog->setEditAble(editAble);
    m_headSettingDialog->exec();
}
void HeadPortraitWidget::onHeadSettingDialogCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    // enable hall chat/feedback input box
    ServerInterface::getInstance()->headSettingClosed(true);
    if(m_headSettingDialog != 0){
        m_headSettingDialog->destroy();
        m_headSettingDialog = 0;
        return;
    }
}
void HeadPortraitWidget::onHeadSettingDialogPortraitSubmitted(CCNode *node,void *data)
{
    // update portrait cache waiting for server confirm
    ServerInterface::getInstance()->setPortraitWaitingConfirm((std::string *)data);
    portraitUpdated((std::string *)data);
}
void HeadPortraitWidget::layoutCompleted()
{
    BasScaleWidget::layoutCompleted();
    if(m_circleBars.size() == 0 && m_barDefs.size() != 0){
        finish();
    }
}
void HeadPortraitWidget::finish()
{
    if(m_headSprite != 0)
        return;
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    if(m_headFile.size() != 0){
        m_headSprite = ResourceMgr::getInstance()->loadSpriteByTexture(m_headFile);
    }else{
        std::string headimg;
        uiDef->getNormalData()->getImg(m_headPortrait,headimg);
        m_headSprite = CCSprite::create();
        m_headSprite->initWithSpriteFrameName(headimg.data());
    }
    CCSize maxsize,currsize;
    maxsize.width = m_anchorWidth;
    maxsize.height = m_anchorHeight;
    m_headSize.width = maxsize.width - ((m_barDefs.size() - 1) * m_indentRate);
    m_headSize.height = maxsize.height - ((m_barDefs.size() - 1) * m_indentRate);
    m_headSize.width = m_headSize.width * 2/3;
    m_headSize.height = m_headSize.height * 2/3;
    currsize.width = maxsize.width;
    currsize.height = maxsize.height;
    for(unsigned int i = 0;i < m_barDefs.size();i++){
        CircleBarDef *barDef = m_barDefs[i];
        CircleProgressBar *bar = new CircleProgressBar();
        bar->setWidth(currsize.width);
        bar->setHeight(currsize.height);
        bar->setTheme(m_theme,barDef->m_barBg,barDef->m_barFg);
        bar->setProgressTo(m_actionTime,barDef->m_percent);
        bar->setRotation(360.0 * i / m_barDefs.size());
        this->addChild(bar);
        bar->setCenterIn("parent");
        m_circleBars.push_back(bar);
        currsize.width -= m_indentRate;
        currsize.height -= m_indentRate;
    }
    if(1){
        BasNodeDelegateWidget *headDelegate = new BasNodeDelegateWidget(m_headSprite,m_headSize);
        this->addChild(headDelegate);
        headDelegate->setCenterIn("parent");
    }
    if(1){
        std::string headbg;
        CCSprite *headbgSprite = CCSprite::create();
        uiDef->getNormalData()->getImg(m_headBg,headbg);
        headbgSprite->initWithSpriteFrameName(headbg.data());
        BasNodeDelegateWidget *bgDelegate = new BasNodeDelegateWidget(headbgSprite,
                                                                      CCSizeMake(maxsize.width - (m_barDefs.size() - 1) * m_indentRate - 10,
                                                                                 maxsize.height - (m_barDefs.size() - 1) * m_indentRate - 10));
        this->addChild(bgDelegate);
        bgDelegate->setCenterIn("parent");
    }
}
