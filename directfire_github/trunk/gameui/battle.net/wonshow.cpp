#include "wonshow.h"

WonGameShow::WonGameShow()
{
    m_actionTime = 2.0;
    m_theme = "default";
}
WonGameShow::~WonGameShow()
{

}
void WonGameShow::setTheme(const std::string &theme)
{
    m_theme = theme;
}
void WonGameShow::addWonBarDef(WonBarDef *def)
{
    m_barDefs.push_back(def);
}
void WonGameShow::resetWonBarLen(const std::vector<float> &lens)
{
    if(lens.size() != m_wonBars.size())
        return;
    for(unsigned int i = 0;i < lens.size();i++){
        m_wonBars[i]->setMaxWidthRefSize("parent",lens[i]);
        m_wonBars[i]->setMinWidthRefSize("parent",lens[i]);
        m_wonBars[i]->setProgressTo(m_actionTime,100);
    }
    this->layout(true);
}
void WonGameShow::setActionTime(float time)
{
    m_actionTime = time;
}
void WonGameShow::addPercentTo(int index,float percent)
{
    if(index >=0 && index < m_wonBars.size())
        m_wonBars[index]->setProgressTo(m_actionTime,percent);
}
void WonGameShow::addPercentBy(int index,float percent)
{
    if(index >=0 && index < m_wonBars.size())
        m_wonBars[index]->setProgressAdd(m_actionTime,percent);
}
void WonGameShow::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(m_barDefs.size() != 0 && m_wonBars.size() == 0)
        finish();
}
void WonGameShow::finish()
{
    std::string name;
    for(unsigned int i = 0;i < m_barDefs.size();i++){
        WonBarDef *def = m_barDefs[i];
        HorTriProgressBar *bar = new HorTriProgressBar();
        bar->setSkinFillVer(m_skinFillVer);
        bar->setTheme(m_theme,def->m_barBg,def->m_barFg);
        this->addChild(bar);
        bar->setMaxWidthRefSize("parent",def->m_percent);
        bar->setMinWidthRefSize("parent",def->m_percent);
        if(name.empty()){
            bar->setLeft("parent",uilib::Left);
        }else{
            bar->setLeft(name,uilib::Right);
        }
        bar->setTop("parent",uilib::Top);
        bar->setBottom("parent",uilib::Bottom);
        name = bar->getName();
        m_wonBars.push_back(bar);
    }
    for(unsigned int i = 0;i < m_barDefs.size();i++){
        m_wonBars[i]->setProgressTo(m_actionTime,100);
    }
}
