#include "okdialog.h"

#include "gamecore/resource/resourcemgr.h"
#include "gamecore/sounds/soundmgr.h"

OkDialog::OkDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_okClickedListener = 0;
    m_okClickedFunc = 0;
    m_edgeSize = 20;
}
OkDialog::~OkDialog()
{
}
void OkDialog::setDialogContent(const std::string &content)
{
    m_content = content;
}
void OkDialog::setOnOkClickedCB(CCNode *listener, SEL_CallFuncND func)
{
    m_okClickedListener = listener;
    m_okClickedFunc = func;
}
void OkDialog::onOkClicked(CCNode *node,void *data)
{
    if(m_okClickedListener && m_okClickedFunc)
        (m_okClickedListener->*m_okClickedFunc)(this, data);
    destroy();
}
void OkDialog::onClosedClicked(CCNode *node,void *data)
{
    if(m_okClickedListener && m_okClickedFunc)
        (m_okClickedListener->*m_okClickedFunc)(this, data);
    destroy();
}
void OkDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void OkDialog::finish()
{
    BasLabel *content = new BasLabel;
    content->setLabelInfo(m_content,"","",CCSizeMake(0,0),getSystemFont(),25);
    this->addChild(content);
    content->setVertical("parent",0.5);
    content->setHorizontal("parent",0.5);

    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    BasButton *okBtn = new BasButton;
    okBtn->setButtonInfo(lang->getStringById(StringEnum::Ok),"default","buttonbg",CCSizeMake(0,0),"",getSystemFont(),24,ccWHITE);
    okBtn->setClickCB(this,callfuncND_selector(OkDialog::onOkClicked));
    this->addChild(okBtn);
    okBtn->setBottom("parent",uilib::Bottom);
    okBtn->setBottomMargin(m_edgeSize);
    okBtn->setHorizontal("parent",0.5);

    setCloseCB(this,callfuncND_selector(OkDialog::onClosedClicked));
}
