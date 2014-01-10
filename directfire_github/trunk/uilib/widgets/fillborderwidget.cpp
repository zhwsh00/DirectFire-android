#include "fillborderwidget.h"
#include "../skin/absskin.h"
#include "../actions/absnodeaction.h"
#include "../base/uithemedef.h"

namespace uilib
{

FillBorderWidget::FillBorderWidget()
{
    m_vEdge = 25.0;
    m_hEdge = 0.0;
}
FillBorderWidget::~FillBorderWidget()
{

}
void FillBorderWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(m_skin == 0 && !m_theme.empty() && !m_themeBg.empty()){
        CCSize size = CCSizeMake(m_anchorWidth,m_anchorHeight);
        UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
        BasSkin *skin = BorderImageSkin::create(size,uiDef,m_themeBg);
        setSkin(skin);
    }
    if(!m_pattern.empty()){
        /* the texture must be standalone,so we left here,
          if the image need to tiled show,we can save the
          image file alone
          */
        CCSize size;
        size.width = m_anchorWidth - m_hEdge * 2;
        size.height = m_anchorHeight - m_vEdge * 2;
        CCSprite *sprite = CCSprite::create(m_pattern.c_str(),CCRectMake(0,0,size.width,size.height));
        ccTexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
        sprite->getTexture()->setTexParameters(&tp);
        sprite->setPosition(ccp(m_anchorWidth/2,m_anchorHeight/2));
        this->CCNode::addChild(sprite,0);
    }
}
void FillBorderWidget::setTheme(const std::string &theme,const std::string &bg,const std::string &pattern)
{
    m_theme = theme;
    m_themeBg = bg;
    m_pattern = pattern;
}
const std::string &FillBorderWidget::getTheme()
{
    return m_theme;
}
const std::string &FillBorderWidget::getThemeBg()
{
    return m_themeBg;
}
const std::string &FillBorderWidget::getThemePattern()
{
    return m_pattern;
}

}
