#ifndef _fillborderwidget_h_
#define _fillborderwidget_h_
#include "../base/widget.h"

namespace uilib
{

class FillBorderWidget : public BasWidget
{
public:
    FillBorderWidget();
    virtual ~FillBorderWidget();
    void layoutCompleted();
    void setEdgeSize(float h,float v);
    void setTheme(const std::string &theme,const std::string &bg,const std::string &pattern);
    const std::string &getTheme();
    const std::string &getThemeBg();
    const std::string &getThemePattern();
protected:
    std::string m_theme;
    std::string m_themeBg;
    std::string m_pattern;
    float m_hEdge;
    float m_vEdge;
};

}
#endif
