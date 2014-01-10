#include "feedbackpage.h"

#include "gamecore/resource/resourcemgr.h"

#include "gamecore/serverinterface.h"
#include "../sendmsganim.h"

FeedBackPage::FeedBackPage()
{
    m_sendButton = 0;
    m_titleInput = 0;
    m_contentInput = 0;
    initItem();
}

FeedBackPage::~FeedBackPage()
{
    setInputBoxVisible(false);
}

void FeedBackPage::moveInItem()
{
    setInputBoxVisible(true);
    BasSysPage::moveInItem();
}

void FeedBackPage::moveOutItem()
{
    setInputBoxVisible(false);
    BasSysPage::moveOutItem();
}

void FeedBackPage::setInputBoxVisible(bool visible)
{
    if(m_titleInput) {
        m_titleInput->setVisible(visible);
        m_titleInput->setEnabled(visible);
    }
    if(m_contentInput) {
        m_contentInput->setVisible(visible);
        m_contentInput->setEnabled(visible);
    }
}

void FeedBackPage::layoutCompleted()
{
    BasSysPage::layoutCompleted();
}

void FeedBackPage::initItem()
{
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    m_sendButton = new BasButton;
    m_sendButton->setButtonInfo(lang->getStringById(StringEnum::Send).data(),"fonts/uifont35.fnt","default","buttonbg",CCSizeMake(0,0));
    m_sendButton->setClickCB(this,callfuncND_selector(FeedBackPage::onSendClicked));
    this->addChild(m_sendButton);
    m_sendButton->setBottom("parent",uilib::Bottom);
    m_sendButton->setRight("parent",uilib::Right);
    m_sendButton->setMargins(20);

    BasLabel *titleLabel = new BasLabel;
    titleLabel->setLabelInfo(lang->getStringById(StringEnum::Title).data(),"fonts/uifont35.fnt","","",CCSizeMake(0,0));
    this->addChild(titleLabel);
    titleLabel->setLeft("parent",uilib::Left);
    titleLabel->setLeftMargin(10);
    titleLabel->setTop("parent",uilib::Top);
    titleLabel->setTopMargin(40);

    m_titleInput = new InputBox;
    m_titleInput->setTheme("default","inputbg");
    this->addChild(m_titleInput);
    m_titleInput->setLeft("parent",uilib::Left);
    m_titleInput->setTop(titleLabel->getName(),uilib::Bottom);
    m_titleInput->setRight("parent",uilib::Right);
    m_titleInput->setHeight(100);
    m_titleInput->setLeftMargin(20);
    m_titleInput->setRightMargin(20);
    m_titleInput->setMaxLength(30);

    BasLabel *contentLabel = new BasLabel;
    contentLabel->setLabelInfo(lang->getStringById(StringEnum::Content).data(),"fonts/uifont35.fnt","","",CCSizeMake(0,0));
    this->addChild(contentLabel);
    contentLabel->setLeft("parent",uilib::Left);
    contentLabel->setLeftMargin(10);
    contentLabel->setTop(m_titleInput->getName(),uilib::Bottom);

    m_contentInput = new InputBox;
    m_contentInput->setTheme("default","inputbg");
    this->addChild(m_contentInput);
    m_contentInput->setLeft("parent",uilib::Left);
    m_contentInput->setTop(contentLabel->getName(),uilib::Bottom);
    m_contentInput->setRight("parent",uilib::Right);
    m_contentInput->setHeight(100);
    m_contentInput->setLeftMargin(20);
    m_contentInput->setRightMargin(20);
    m_contentInput->setMaxLength(500);
    m_itemInit = true;
}
void FeedBackPage::onSendClicked(CCNode *node,void *data)
{
    //send out
    std::string title,content;
    title = m_titleInput->getText();
    content = m_contentInput->getText();
    if(title.size() != 0 && content.size() != 0){
        std::string send;
        send = "Title:";
        send += title;
        send += ". ";
        send += "Content:";
        send += content;
        ServerInterface::getInstance()->sendFeedback(send);

        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        SendMsgAnim *anim = new SendMsgAnim(root,ccp(winSize.width / 2,winSize.height / 2));
        anim->setTheme("default","uimailsending");
        anim->exec();
        m_titleInput->setText("");
        m_contentInput->setText("");
    }
}
