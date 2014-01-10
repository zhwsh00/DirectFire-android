#include "chatfacingdialog.h"
#include "../base/uithemedef.h"

namespace uilib
{

ChatFacingDialog::ChatFacingDialog(TouchNode *parent,const CCPoint &pos)
{
    parent->addChild(this);
    m_pos = pos;
    m_theme = "default";
    m_themeBg = "inputbg";
    m_facingBg = "facebg";
    m_faceListener = 0;
    m_faceFunc = 0;
    setCanTouch(true);
    setBlockEvent(true);
    setTouchPriority(uilib::TopPriority);
    init();
}
ChatFacingDialog::~ChatFacingDialog()
{

}
void ChatFacingDialog::init(int dummy)
{
    float fw,fh,iw,ih;
    int colnum,rownum;
    fw = fh = 80;
    iw = ih = 60;
    UiThemeDef *uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    const std::vector<std::string> &hasFacing = uiDef->getFacing();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    colnum = winSize.width / (fw + 2);
    m_size.width = winSize.width;
    rownum = ceil(hasFacing.size() * 1.0 / colnum);
    m_size.height = rownum * (fh + 2);

    setWidth(m_size.width);
    setHeight(m_size.height);
    int index = 0;
    std::string facebg;
    uiDef->getNormalData()->getImg(m_facingBg,facebg);
    for(int i = 0;i < rownum;i++){
        for(int k = 0;k < colnum;k++,index++){
            if(index >= hasFacing.size())
                break;
            const std::string &name = hasFacing[index];
            std::string firstFrame = name;
            if(UiThemeMgrProxy::getInstance()->getThemeMgr()->getFrameSpriteFirstFrame(firstFrame)){
                CCSprite *bg = CCSprite::createWithSpriteFrameName(facebg.data());
                CCSprite *frame = CCSprite::createWithSpriteFrameName(firstFrame.data());
                CCSize bgsize = bg->getContentSize();
                bg->addChild(frame);
                frame->setAnchorPoint(ccp(0.5,0.5));
                frame->setPosition(ccp(bgsize.width/2,bgsize.height/2));
                CCSize fsize = frame->getContentSize();
                frame->setScaleX(iw / fsize.width);
                frame->setScaleY(ih / fsize.height);
                BasButton *button = new BasButton;
                button->setName(name);
                button->setButtonInfo("","","",CCSizeMake(fw,fh));
                button->setClickCB(this,callfuncND_selector(ChatFacingDialog::onFaceClicked));
                this->addChild(button);
                button->CCNode::addChild(bg);
                bg->setAnchorPoint(ccp(0.5,0.5));
                bg->setPosition(ccp(fw/2,fh/2));
                button->setHorizontal("parent",(2*k + 1) * 1.0 / (colnum * 2));
                button->setVertical("parent",(2*i + 1) * 1.0 / (rownum * 2));
            }
        }
    }
    layout(true);
    setAnchorPoint(ccp(0,0));
    setPosition(ccp(0,m_pos.y));
}
void ChatFacingDialog::show()
{
    setVisible(true);
}
void ChatFacingDialog::hide()
{
    setVisible(false);
}
void ChatFacingDialog::getUserClickedFacing(std::string &face)
{
    face = m_clickedFace;
}
void ChatFacingDialog::setFacingClickCB(CCNode *node,SEL_CallFuncND func)
{
    m_faceListener = node;
    m_faceFunc = func;
}
void ChatFacingDialog::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BorderWidget::touchPressEvent(pTouch,pEvent);
}
void ChatFacingDialog::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BorderWidget::touchMoveEvent(pTouch,pEvent);
}
void ChatFacingDialog::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    hide();
}
void ChatFacingDialog::onFaceClicked(CCNode *node,void *data)
{
    TouchNode *touch = (TouchNode*)node;
    m_clickedFace = touch->getName();
    if(m_faceListener && m_faceFunc){
        (m_faceListener->*m_faceFunc)(this,0);
    }
}
}
