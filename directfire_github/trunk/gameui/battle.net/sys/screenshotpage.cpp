#include "screenshotpage.h"

#include "utils/sysutils.h"

ScreenShotPage::ScreenShotPage()
{
    m_itemInit = false;
}
ScreenShotPage::~ScreenShotPage()
{

}
void ScreenShotPage::moveInItem()
{
    BasSysPage::moveInItem();
}
void ScreenShotPage::moveOutItem()
{
    BasSysPage::moveOutItem();
}
void ScreenShotPage::layoutCompleted()
{
    BasSysPage::layoutCompleted();
    if(!m_itemInit)
        initItem();
}
void ScreenShotPage::setDir(const std::string &dir)
{
    m_dir = dir;
}
void ScreenShotPage::initItem()
{
    m_scroll = new HorScrollWidget;
    m_scroll->setVerticalScrollPolicy(uilib::ScrollShow_Never);
    m_scroll->setHorizontalScrollPolicy(uilib::ScrollShow_Need);
    this->addChild(m_scroll);
    m_scroll->setFill("parent");
    std::vector<std::string> files;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    std::string resourcedir = CCApplication::sharedApplication()->getResourceRootPath();
    CCApplication::sharedApplication()->setResourceRootPath("");
#else
#endif
    readFilesFromDir(m_dir,files,".png");
    float maxheight = m_anchorHeight * 0.94;
    float width,height;
    for(unsigned int i = 0;i < files.size();i++){
        std::string &file = files[i];
        CCSprite *sprite = CCSprite::create(file.data());
        CCSize size = sprite->getContentSize();
        if(size.height > maxheight){
            height = maxheight;
            width =  size.width/size.height  * height;
        }else{
            width = size.width;
            height = size.height;
        }
        FSizeCCNodeDelegate *dele = new FSizeCCNodeDelegate(sprite,CCSizeMake(width,height));
        m_scroll->addFixedSizeWidget(dele);
    }
    m_scroll->setSpacing(10);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    CCApplication::sharedApplication()->setResourceRootPath(resourcedir.data());
#else
#endif
    m_itemInit = true;
}
