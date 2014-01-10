#ifndef _dialog_h_
#define _dialog_h_
#include <string>
#include <iostream>
#include <list>
#include <vector>
using namespace std;
#include "widget.h"
#include "scrollarea.h"
namespace uilib
{

class BasDialog : public BasWidget
{
public:
    BasDialog();
    virtual ~BasDialog();
    virtual bool finish();
    void setDialogInfo(const std::string &theme = "default",
                       const std::string &bg = "bg",
                       const CCSize &size = CCSizeMake(640,480));
    void setButtons(const std::vector<std::string> &buttons);
    void setButtonThemes(const std::vector<std::string> &themes);
    void setContentWidget(BasWidget *content);
    void setTitle(const std::string &title,const std::string &titlebg = "dialogtitle_a");
    void setClickCallBack(CCNode *listener,SEL_CallFuncND func);
    inline void setEdgeSize(float size) { m_edgeSize = size;}
    inline float getEdgeSize() { return m_edgeSize;}
    BasButton *getButtonByIndex(int index);
    BasWidget *getContentWidget() { return m_contentWidget;}
    BasWidget *getTitleWidget() { return m_titleWidget;}
    virtual void onButtonClicked(CCNode *pSender,void *index);
    virtual void exec();
protected:
    std::vector<std::string> m_buttonTexts;
    std::vector<std::string> m_buttonThemes;
    std::vector<BasButton*> m_buttons;
    CCNode *m_dialogListener;
    SEL_CallFuncND m_dialogFunc;
    BasWidget *m_contentWidget;
    std::string m_theme;
    std::string m_bg;
    CCSize m_dialogSize;
protected:
    BasButton *m_titleWidget;
    std::string m_titleText;
    std::string m_titleBg;
    bool m_finished;
protected:
    float m_edgeSize;
};

class TextScrollArea;
class MessageDialog : public BasDialog
{
public:
    MessageDialog();
    virtual ~MessageDialog();    
    void setTextInfo(const std::string &text,const std::string &fontfamily = "",int fontSize = 60,ccColor3B color = ccBLACK);
protected:
    TextScrollArea *m_scrollArea;
};


}
#endif
