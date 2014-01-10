#include "labelmessagedialog.h"
#include "filltestwidget.h"
#include "../base/uithemedef.h"
#include "../actions/absnodeaction.h"
#include "../lang/langdef.h"
#include "../lang/stringenum.h"

namespace uilib
{

LabelMessageDialog::LabelMessageDialog::LabelMessageDialog(CCNode *parent,const std::string &theme,const std::string &bg,const CCSize &size)
    : BasDialog()
{
    LangDef *lang = UiThemeMgrProxy::getInstance()->getThemeMgr()->getLangDef();
    m_closeName = lang->getStringById(StringEnum::Close);
    m_titleName = lang->getStringById(StringEnum::Notification);
    CCSize dsize = size;
    if(dsize.width == 0 && dsize.height == 0){
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        if(winSize.width > winSize.height)
            dsize.width = winSize.height * 0.9;
        else
            dsize.width = winSize.width * 0.9;
        dsize.height = dsize.width * 0.9;
    }
    setDialogInfo(theme,bg,dsize);
    setEdgeSize(20);
    m_scrollWidget = new VerScrollWidget("","",dsize);

    BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
    BasNodeAction *moveOut = UiNodeActionFactory::getInstance()->getMoveActionByName("moveout");
    moveOut->setFinishCB(this,callfuncN_selector(LabelMessageDialog::onMoveOutActionFinished));
    moveIn->setEaseType(uilib::EaseSineInOut);
    moveIn->setMoveInType(uilib::ScaleXIn);
    moveOut->setEaseType(uilib::EaseSineInOut);
    moveOut->setMoveOutType(uilib::ScaleYOut);
    this->setMoveinAction(moveIn);
    this->setMoveoutAction(moveOut);

    setTouchPriority(uilib::HighestPriority);
    setBlockEvent(true);
    
    m_closeListener = 0;
    m_closeFunc = 0;

    m_colorLayer = CCLayerColor::create();
    m_colorLayer->initWithColor(ccc4(0,0,0,64));
    parent->addChild(m_colorLayer);
    parent->addChild(this);
}
LabelMessageDialog::~LabelMessageDialog()
{

}
void LabelMessageDialog::setCloseName(const std::string &name)
{
    m_closeName = name;
}
void LabelMessageDialog::setTitleName(const std::string &name)
{
    m_titleName = name;
}
void LabelMessageDialog::addFixedSizeWidget(BasFixedSizeWidget *w)
{
    m_scrollWidget->addFixedSizeWidget(w);
}
void LabelMessageDialog::exec()
{
    if(!m_titleName.empty()){
        setTitle(m_titleName,"");
    }
    if(!m_closeName.empty()){
        std::vector<std::string> buttonNames;
        buttonNames.push_back(m_closeName);
        setButtons(buttonNames);
    }
    setContentWidget(m_scrollWidget);
    setClickCallBack(this,callfuncND_selector(LabelMessageDialog::onCloseClicked));
    BasDialog::exec();
}
void LabelMessageDialog::close()
{
    onCloseClicked(this,0);
}
void LabelMessageDialog::onCloseClicked(CCNode *node,void *data)
{
    moveOut();
    if(m_closeListener && m_closeFunc){
        (m_closeListener->*m_closeFunc)(this);
    }
}
void LabelMessageDialog::onMoveOutActionFinished(CCNode *node)
{
    removeFromParentAndCleanup(true);
    if(m_colorLayer)
        m_colorLayer->removeFromParentAndCleanup(true);
}
void LabelMessageDialog::setOnClosed(CCNode *listener, SEL_CallFuncN func)
{
    m_closeListener = listener;
    m_closeFunc = func;
}

}
