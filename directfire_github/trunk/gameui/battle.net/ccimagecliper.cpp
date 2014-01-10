#include "ccimagecliper.h"
#include "headsettingdialog.h"
#include "gamecore/resource/resourcemgr.h"
#include "gamecore/utils/fileutils.h"
#include "gamecore/serverinterface.h"

#include <sstream>
#include <stdlib.h>
#include <stdio.h>

ClipDrawer::ClipDrawer()
{

}
ClipDrawer::~ClipDrawer()
{

}
void ClipDrawer::setClipSize(int w,int h)
{
    m_width = w;
    m_height = h;
    setContentSize(CCSizeMake(w+10,h+10));
}

void ClipDrawer::draw()
{
    CCNode::draw();
    CHECK_GL_ERROR_DEBUG();
    //glEnable(GL_LINE_SMOOTH);
    ccDrawColor4B(255,0,0,255);
    glLineWidth(1.0);
    ccDrawLine(ccp(0,0),ccp(m_width,0));
    ccDrawLine(ccp(m_width,0),ccp(m_width,m_height));
    ccDrawLine(ccp(m_width,m_height),ccp(0,m_height));
    ccDrawLine(ccp(0,m_height),ccp(0,0));
}

ImageDelete::ImageDelete(CCImageCliper *owner,CCNode *node,const CCSize &_size)
    : BasNodeDelegateWidget(node,_size)
{
    m_owner = owner;
    setCanTouch(true);
}
ImageDelete::~ImageDelete()
{

}
void ImageDelete::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BasNodeDelegateWidget::touchPressEvent(pTouch,pEvent);
}
void ImageDelete::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BasNodeDelegateWidget::touchMoveEvent(pTouch,pEvent);
    CCPoint pos = m_owner->convertToNodeSpace(pTouch->getLocation());
    m_owner->moveDraw(pos);
}
void ImageDelete::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    BasNodeDelegateWidget::touchReleaseEvent(pTouch,pEvent);
}
CCImageCliper::CCImageCliper(const std::string &imagepath,HeadSettingDialog *owner
                             ,CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{
    m_imagePath = imagepath;
    m_owner = owner;
    m_needWidth = 220;
    m_needHeight = 220;
    m_visit = false;
}
CCImageCliper::~CCImageCliper()
{

}
void CCImageCliper::setImageSize(int w,int h)
{
    m_needWidth = w;
    m_needHeight = h;
}
void CCImageCliper::exec()
{
    finish();
    BasShowDialog::exec();;
}
void CCImageCliper::layoutCompleted()
{
    BasShowDialog::layoutCompleted();
    //image
    CCSprite *image = CCSprite::create(m_imagePath.c_str());

    ImageDelete *imageDelete = new ImageDelete(this,image,CCSizeMake(m_anchorWidth -160,m_anchorHeight -160));
    this->addChild(imageDelete);
    imageDelete->setCenterIn("parent");

    m_drawer = new ClipDrawer;
    this->CCNode::addChild(m_drawer);
    m_drawer->setAnchorPoint(ccp(0.5,0.5));
    m_drawer->setClipSize(m_needWidth,m_needHeight);
    m_drawer->setZOrder(100);
    m_drawer->setPosition(ccp(m_anchorWidth / 2.0,m_anchorHeight / 2.0));
}
void CCImageCliper::onCloseClicked(CCNode *node,void *data)
{
    this->destroy();
}
void CCImageCliper::moveDraw(const CCPoint &pos)
{
    m_drawer->setPosition(pos);
}
void CCImageCliper::onOkClicked(CCNode *node,void *data)
{
    //clip here
    CCRenderTexture* rt = CCRenderTexture::create(m_needWidth,m_needHeight);
    CCPoint pos = m_drawer->getPosition();
    m_drawer->setVisible(false);
    CCPoint rtpos;rtpos.x = m_needWidth / 2.0;rtpos.y = m_needHeight / 2;
    rt->begin();
    pos.x -= m_anchorWidth / 2;
    pos.y -= m_anchorHeight / 2;
    this->setPosition(rtpos.x - pos.x,rtpos.y - pos.y);
    this->visit();
    rt->end();
    std::stringstream ss;
    ss << CCFileUtils::sharedFileUtils()->getWriteablePath() << "/";
    ss << "headupload_tmp.jpg";
    std::string file = ss.str();
    rt->saveToFile(file.data());
    rt->release();
    this->setVisible(false);
    this->destroy();

    unsigned long size;
    unsigned char *buf;
    buf = CCFileUtils::sharedFileUtils()->getFileData(file.c_str(),"r",&size);
    if(size == 0){
        m_owner->takePhotoFailed();
    }else{
        ServerInterface::getInstance()->takePhotoFinished((const char*)buf,(int)size,(const char*)buf,(int)size);
        m_owner->takePhotoFinished((const char*)buf,(int)size,(const char*)buf,(int)size);
    }
}
void CCImageCliper::finish()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    setHeight(size.height * 0.9);

    ResourceMgr *mgr = ResourceMgr::getInstance();
    LangDef *lang = mgr->getLangDef();
    BasButton *ok = new BasButton;
    ok->setButtonInfo(lang->getStringById(StringEnum::Ok).data(),"fonts/uifont35.fnt","default","buttonbg",
                      CCSizeMake(0,0));
    this->addChild(ok);
    ok->setHorizontal("parent",0.5);
    ok->setBottom("parent",uilib::Bottom);
    ok->setBottomMargin(10);
    ok->setClickCB(this,callfuncND_selector(CCImageCliper::onOkClicked));
    setCloseCB(this,callfuncND_selector(CCImageCliper::onCloseClicked));
}
