#include "addfrienddialog.h"

#include "gamecore/resource/resourcemgr.h"

AddFriendDialog::AddFriendDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_addImg = "buttonbg";
    m_addListener = 0;
    m_addFunc = 0;
    m_idInput = 0;
    m_wordInput = 0;
    m_edgeSize = 20;
}
AddFriendDialog::~AddFriendDialog()
{

}
void AddFriendDialog::setAddImg(const std::string &normal,const std::string &pressed)
{
    m_addImg = normal;
    m_addPressedImg = pressed;
}
void AddFriendDialog::setAddCB(CCNode *listener,SEL_CallFuncND func)
{
    m_addListener = listener;
    m_addFunc = func;
}
void AddFriendDialog::getAskInfo(std::string &id,std::string &word)
{
    if(m_idInput)
        id = m_idInput->getText();
    if(m_wordInput)
        word = m_wordInput->getText();
}
void AddFriendDialog::setAddId(const std::string &id)
{
    m_setId = id;
}
void AddFriendDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void AddFriendDialog::finish()
{
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    BasButton *button = new BasButton;
    button->setButtonInfo(lang->getStringById(StringEnum::Add).data(),"fonts/uifont24.fnt",m_theme,m_addImg,CCSizeMake(0,0));
    button->setClickCB(m_addListener,m_addFunc);
    this->addChild(button);
    button->setRight("parent",uilib::Right);
    button->setBottom("parent",uilib::Bottom);
    button->setRightMargin(m_edgeSize);
    button->setBottomMargin(m_edgeSize);

    BasWidget *inputWidget = new BasWidget;
    this->addChild(inputWidget);
    inputWidget->setTop("parent",uilib::Top);
    inputWidget->setLeft("parent",uilib::Left);
    inputWidget->setRight("parent",uilib::Right);
    inputWidget->setBottom(button->getName(),uilib::Top);
    inputWidget->setLeftMargin(m_edgeSize);
    inputWidget->setRightMargin(m_edgeSize);
    inputWidget->setTopMargin(m_edgeSize);

    VerticalLayout *vlay = new VerticalLayout;
    BasLabel *label1 = new BasLabel;
    label1->setLabelInfo(lang->getStringById(StringEnum::FriendId).data(),"fonts/uifont24.fnt","","",CCSizeMake(0,0));
    BasLabel *label2 = new BasLabel;
    label2->setLabelInfo(lang->getStringById(StringEnum::MsgWord).data(),"fonts/uifont24.fnt","","",CCSizeMake(0,0));

    m_idInput = new InputBox;
    m_idInput->setTheme("default","inputbg");
    m_idInput->setMaxLength(9);
    m_idInput->setText(m_setId);
    m_idInput->setHeight(80);
    
    m_wordInput = new InputBox;
    m_wordInput->setTheme("default","inputbg");
    m_wordInput->setMaxLength(50);
    m_wordInput->setHeight(80);

    vlay->addWidget(label1);
    vlay->addWidget(m_idInput);
    vlay->addWidget(label2);
    vlay->addWidget(m_wordInput);

    vlay->setAlignChildsSize(false);
    vlay->setAveraged(true);
    vlay->setChildAlign(0,uilib::Left);
    vlay->setChildAlign(2,uilib::Left);
    vlay->setChildAlign(1,uilib::Left);
    vlay->setChildAlign(1,uilib::Right);
    vlay->setChildAlign(3,uilib::Left);
    vlay->setChildAlign(3,uilib::Right);

    inputWidget->setLayout(vlay);
}
