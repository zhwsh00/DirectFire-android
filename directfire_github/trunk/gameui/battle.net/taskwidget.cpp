#include "taskwidget.h"
#include "taskshowdialog.h"

#include "gamecore/sounds/soundmgr.h"

TaskWidget::TaskWidget(BasWidget *parent)
{
    m_inited = false;
    m_theme = "default";
    m_hasImg = "task_yes.png";
    m_hasSprite = 0;
    m_has = false;
    m_showDialog = 0;
    m_serverIface = ServerInterface::getInstance();
    parent->addChild(this);
    setCanTouch(true);
}
TaskWidget::~TaskWidget()
{

}
void TaskWidget::taskUpdated()
{
    m_has = m_serverIface->hasUnreadTask();
    if(m_has){
        this->setEffectActionEnabled(true);
    }else{
        this->setEffectActionEnabled(false);
    }
}
void TaskWidget::setTheme(const std::string &theme,const std::string &has,const std::string &no)
{
    m_theme = theme;
    m_hasImg = has;
}
void TaskWidget::finish()
{
    m_hasSprite = CCSprite::createWithSpriteFrameName(m_hasImg.data());

    BasNodeDelegateWidget *hasDele = new BasNodeDelegateWidget(m_hasSprite,CCSizeMake(m_anchorWidth,m_anchorHeight));
    this->addChild(hasDele);
    hasDele->setCenterIn("parent");

    BasNodeEffectAction *effectAction = UiNodeActionFactory::getInstance()->getEffectActionByName("scale");
    this->setEffectAction(effectAction);
    this->setEffectActionEnabled(false);
}
void TaskWidget::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(!m_inited){
        m_inited = true;
        finish();
    }
}
void TaskWidget::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BasWidget::touchPressEvent(pTouch,pEvent);
}
void TaskWidget::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BasWidget::touchMoveEvent(pTouch,pEvent);
}
void TaskWidget::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(!m_has)
        return;
    UiMsgEv::AwardTaskInfo *info = m_serverIface->getAwardTaskInfo();
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_showDialog = new TaskShowDialog(root,ccc4(0,0,0,128));
    m_showDialog->setCloseCB(this,callfuncND_selector(TaskWidget::onTaskDialogCloseClicked));
    m_showDialog->setDrawCB(this,callfuncND_selector(TaskWidget::onTaskDialogDrawClicked));
    m_showDialog->setAwardTaskInfo(info);
    m_showDialog->exec();
    if(!m_serverIface->hasUnreadTask()){
        taskUpdated();
    }
}
void TaskWidget::onTaskDialogCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    m_showDialog->destroy();
    m_showDialog = 0;
    m_serverIface->resumeOneTask();
}
void TaskWidget::onTaskDialogDrawClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    std::string key;
    m_showDialog->getTaskRuleKey(key);
    m_showDialog->destroy();
    m_showDialog = 0;
    if(!key.empty()){
        //submit task
        m_serverIface->submitTaskRule(key);
    }
}
