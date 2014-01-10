#include "taskshowdialog.h"

#include "gamecore/resource/resourcemgr.h"

#include "prop/propdef.h"

TaskShowDialog::TaskShowDialog(CCNode *parent,const ccColor4B &color)
    :   BasShowDialog(parent,color)
{
    m_drawImg = "buttonbg";
    m_drawListener = 0;
    m_drawFunc = 0;
    m_taskInfo = 0;
    m_edgeSize = 20;
}
TaskShowDialog::~TaskShowDialog()
{

}
void TaskShowDialog::setDrawCB(CCNode *listener,SEL_CallFuncND func)
{
    m_drawListener = listener;
    m_drawFunc = func;
}
void TaskShowDialog::setDrawImg(const std::string &normal,const std::string &pressed)
{
    m_drawImg = normal;
    m_drawPressedImg = pressed;
}
void TaskShowDialog::setAwardTaskInfo(UiMsgEv::AwardTaskInfo *info)
{
    m_taskInfo = info;
}
void TaskShowDialog::getTaskRuleKey(std::string &key)
{
    if(m_taskInfo == 0)
        key.clear();
    else
        key = m_taskInfo->m_taskKey;
}
void TaskShowDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
int TaskShowDialog::getTaskDescIdFromTaskKey(const std::string &key)
{
    string dailyHead = "dailyAward";
    string holidayHead = "holidayAward";
    string portraitHead = "portraitAward";
    if(key.compare(0, dailyHead.size(), dailyHead) == 0)
        return StringEnum::DailyAward;
    else if(key.compare(0, dailyHead.size(), dailyHead) == 0)
        return StringEnum::HolidayAward;
    else if(key.compare(0, portraitHead.size(), portraitHead) == 0)
        return StringEnum::PortraitAward;
    else
        return StringEnum::TaskAward;
}
void TaskShowDialog::finish()
{
    if(m_taskInfo == 0)
        return;
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    BasButton *drawButton = new BasButton;
    drawButton->setButtonInfoWithBorder(lang->getStringById(StringEnum::DrawTask).data(),
                                        "fonts/uifont24.fnt",m_theme,"button",CCSizeMake(160,60));
    this->addChild(drawButton);
    drawButton->setClickCB(m_drawListener,m_drawFunc);
    drawButton->setRight("parent",uilib::Right);
    drawButton->setBottom("parent",uilib::Bottom);
    drawButton->setRightMargin(m_edgeSize);
    drawButton->setBottomMargin(m_edgeSize);

    BasLabel *taskDesc = 0;
    int descId = getTaskDescIdFromTaskKey(m_taskInfo->m_taskKey);
    if(descId >= 0){
        taskDesc = new BasLabel;
        taskDesc->setLabelInfo(lang->getStringById(descId).data(),"fonts/uifont35.fnt",m_theme,"",CCSizeMake(0,0));
        this->addChild(taskDesc);
        taskDesc->setMargins(m_edgeSize);
        taskDesc->setTop("parent",uilib::Top);
        taskDesc->setHorizontal("parent",0.5);
    }
    std::vector<UiMsgEv::PropDef> &props = m_taskInfo->m_awards;
    HFSizeWidgetContainer *container = new HFSizeWidgetContainer;
    std::string propName;
    std::stringstream ss;
    for(unsigned int i = 0;i < props.size();i++){
        ss.str("");
        int type = props[i].m_type;
        int count = props[i].m_count;
        PropDef::getVirtualPropsName(type,propName);
        if(propName.empty())
            continue;
        propName += ".png";
        CCSprite *typeSprite = CCSprite::createWithSpriteFrameName(propName.data());
        CCSize typeSize = typeSprite->getContentSize();
        ss << "x" << count;
        CCLabelBMFont *countSprite = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
        CCSize countSize = countSprite->getContentSize();
        CCNode *fnode = CCNode::create();
        CCSize size = CCSizeMake(typeSize.width + countSize.width,MAX(typeSize.height,countSize.height));
        fnode->setContentSize(size);
        fnode->addChild(typeSprite);
        fnode->addChild(countSprite);
        typeSprite->setAnchorPoint(ccp(0,0.5));
        typeSprite->setPosition(ccp(0,size.height / 2));
        countSprite->setAnchorPoint(ccp(1.0,0.5));
        countSprite->setPosition(ccp(size.width,size.height / 2));

        FSizeCCNodeDelegate *node = new FSizeCCNodeDelegate(fnode,size);
        container->addFSizeWidget(node);
    }
    container->setSpacing(10);
    this->addChild(container);
    container->setCenterIn("parent");
    container->exec();
    if(1){
        //show anim
        CCSprite *anim = CCSprite::create();
        anim->initWithSpriteFrameName("whiteshining.png");
        CCScaleTo *scale = CCScaleTo::create(0.5,40);
        CCFadeOut *fade = CCFadeOut::create(0.5);
        anim->runAction(CCSequence::create(scale,fade,CCCallFuncN::create(this,callfuncN_selector(TaskShowDialog::onShowAnimFinished)),0));
        BasNodeDelegateWidget *delegate = new BasNodeDelegateWidget(anim);
        this->addChild(delegate);
        delegate->setCenterIn("parent");
    }
}
void TaskShowDialog::onShowAnimFinished(CCNode *node)
{
    node->removeFromParentAndCleanup(true);
}
