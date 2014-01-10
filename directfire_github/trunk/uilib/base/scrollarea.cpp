#include "../skin/absskin.h"
#include "uithemedef.h"
#include "scrollarea.h"
#include "../widgets/filltestwidget.h"
#include "../base/fontutil.h"

namespace uilib
{

ScrollViewDelegate::ScrollViewDelegate(BasScrollArea *owner,TouchNode *parent)
    : NullFrame(parent)
{
    m_owner = owner;
    setCanTouch(true);
    m_scrollView = 0;
    m_canUserScroll = true;
}
ScrollViewDelegate::~ScrollViewDelegate()
{

}
void ScrollViewDelegate::setContainer(CCNode *node,const CCSize &contentSize,bool ver)
{
    if(m_scrollView){
        cout << "ScrollViewDelegate::setContainer,you can not set Container more times!" << endl;
        return;
    }
    if(!isAnchored()){
        cout << "ScrollViewDelegate::setContainer,must set this after layout!" << endl;
        return;
    }

    m_scrollView = CCScrollView::create(CCSizeMake(m_anchorWidth,m_anchorHeight));

    m_scrollView->retain();
    m_scrollView->setDelegate(m_owner);
    m_scrollView->setTouchEnabled(true);
    this->CCNode::addChild(m_scrollView);
    if(ver){
        m_scrollView->setDirection(kCCScrollViewDirectionVertical);
    }else{
        m_scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    }
    if(ver){
        if(contentSize.height > m_anchorHeight){
            m_scrollView->setContentSize(contentSize);
            m_scrollView->setContentOffset(ccp(0,m_anchorHeight - contentSize.height));
        }else{
            m_scrollView->setContentSize(CCSizeMake(m_anchorWidth,m_anchorHeight));
        }
    }else{
        if(contentSize.width > m_anchorWidth){
            m_scrollView->setContentSize(contentSize);
            m_scrollView->setContentOffset(ccp(0,(contentSize.height - m_anchorHeight)/2));
        }else{
            m_scrollView->setContentSize(CCSizeMake(m_anchorWidth,m_anchorHeight));
            m_scrollView->setContentOffset(ccp(0,(contentSize.height - m_anchorHeight)/2));
        }
    }
    m_scrollView->addChild(node);
    node->ignoreAnchorPointForPosition(false);
    CCSize csize = m_scrollView->getContentSize();
    if(ver){
        node->setAnchorPoint(ccp(0,1));
        node->setPosition(ccp((m_anchorWidth - contentSize.width)/2,csize.height));
    }else{
        node->setAnchorPoint(ccp(0,1.0));
        node->setPosition(ccp(0,csize.height));
    }
}
void ScrollViewDelegate::updateContainer(CCNode *node,const CCSize &contentSize,bool ver)
{
    /*
      Modify version:
      water: no adjust contentOffset in updateContainer,2013/7/1
      */
    if(ver){
        if(contentSize.height > m_anchorHeight){
            m_scrollView->setContentSize(contentSize);
            //m_scrollView->setContentOffset(ccp(0,m_anchorHeight - contentSize.height));
        }else{
            m_scrollView->setContentSize(CCSizeMake(m_anchorWidth,m_anchorHeight));
        }
    }else{
        if(contentSize.width > m_anchorWidth){
            m_scrollView->setContentSize(contentSize);
            //m_scrollView->setContentOffset(ccp(0,(contentSize.height - m_anchorHeight)/2));
        }else{
            m_scrollView->setContentSize(CCSizeMake(m_anchorWidth,m_anchorHeight));
            //m_scrollView->setContentOffset(ccp(0,(contentSize.height - m_anchorHeight)/2));
        }
    }
    node->ignoreAnchorPointForPosition(false);
    CCSize csize = m_scrollView->getContentSize();
    if(ver){
        node->setAnchorPoint(ccp(0,1));
        node->setPosition(ccp((m_anchorWidth - contentSize.width)/2,csize.height));
    }else{
        node->setAnchorPoint(ccp(0,1.0));
        node->setPosition(ccp(0,csize.height));
    }
}
void ScrollViewDelegate::setDirection (CCScrollViewDirection direction)
{
    if(m_scrollView)
        m_scrollView->setDirection(direction);
}
void ScrollViewDelegate::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_scrollView && m_canUserScroll)
        m_scrollView->ccTouchBegan(pTouch,pEvent);
}
void ScrollViewDelegate::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    m_owner->m_userScrolling = true;
    if(m_scrollView && m_canUserScroll){
        m_scrollView->ccTouchMoved(pTouch,pEvent);
    }
}
void ScrollViewDelegate::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_scrollView && m_canUserScroll)
        m_scrollView->ccTouchEnded(pTouch,pEvent);
}
void ScrollViewDelegate::scrollToEnd(bool ver)
{
    if(m_scrollView == 0)
        return;
    if(ver){
        CCSize size = m_scrollView->getContentSize();
         if(m_anchorHeight > size.height)
            return;
         else
            m_scrollView->setContentOffset(ccp(0,0),true);
    }else{
        //no debug
        m_scrollView->setContentOffset(ccp(0,m_anchorHeight / 2),true);
    }
}
void ScrollViewDelegate::scrollToEnd(float dt,bool ver)
{
    if(m_scrollView == 0)
        return;
    if(ver){
        CCSize size = m_scrollView->getContentSize();
         if(m_anchorHeight > size.height)
            return;
        else
             m_scrollView->setContentOffsetInDuration(ccp(0,0),dt);
    }else{
        //no debug
        m_scrollView->setContentOffset(ccp(0,m_anchorHeight / 2),true);
    }
}
void ScrollViewDelegate::scrollToBegin(bool ver)
{
    if(m_scrollView == 0)
        return;
    if(ver){
        CCSize size = m_scrollView->getContentSize();
         if(m_anchorHeight > size.height){
            return;
        }else{
            CCSize size = m_scrollView->getContentSize();
            m_scrollView->setContentOffset(ccp(0,-size.height + m_anchorHeight),true);
         }
    }else{
        //no debug
        m_scrollView->setContentOffset(ccp(0,m_anchorHeight / 2),true);
    }
}
void ScrollViewDelegate::scrollToBegin(float dt,bool ver)
{
    if(m_scrollView == 0)
        return;
    if(ver){
        CCSize size = m_scrollView->getContentSize();
         if(m_anchorHeight > size.height){
            return;
        }else{
            CCSize size = m_scrollView->getContentSize();
            m_scrollView->setContentOffsetInDuration(ccp(0,-size.height + m_anchorHeight),true);
         }
    }else{
        //no debug
        m_scrollView->setContentOffset(ccp(0,m_anchorHeight / 2),true);
    }
}
void ScrollViewDelegate::setUserCanScroll(bool can)
{
    m_canUserScroll = can;
}
void ScrollViewDelegate::resetScrollOffset(bool ver)
{
    CCSize contentSize = m_owner->m_containerCSize;
    if(ver){
        if(contentSize.height > m_anchorHeight){
            m_scrollView->setContentOffset(ccp(0,m_anchorHeight - contentSize.height));
        }
    }else{
        if(contentSize.width > m_anchorWidth){
            m_scrollView->setContentOffset(ccp(0,(m_anchorHeight - contentSize.height)/2));
        }else{
            m_scrollView->setContentOffset(ccp(0,(contentSize.height - m_anchorHeight)/2));
        }
    }
}
void ScrollViewDelegate::listenerPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    touchPressEvent(pTouch,pEvent);
    m_listenerPressPos = pTouch->getLocationInView();
    m_eatListener = false;
}
void ScrollViewDelegate::listenerMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    touchMoveEvent(pTouch,pEvent);
    if(!m_eatListener){
        CCPoint pos = pTouch->getLocationInView();
        if(fabs(pos.x - m_listenerPressPos.x) > 5 && fabs(pos.y - m_listenerPressPos.y) > 5)
            m_eatListener = true;
        else
            m_eatListener = false;
    }
}
bool ScrollViewDelegate::listenerReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    touchReleaseEvent(pTouch,pEvent);
    return m_eatListener;
}

BasScrollArea::BasScrollArea(const std::string &themeName,const std::string &themeBg,const CCSize &size)
{
    m_themeName = themeName;
    m_themeBg = themeBg;
    m_themeSize = size;
    m_containerNode = 0;
    m_viewDelegate = 0;

    m_vscrollBar = 0;
    m_hscrollBar = 0;
    m_vscrollPolicy = ScrollShow_Need;
    m_hscrollPolicy = ScrollShow_Need;
    m_userScrolling = false;
    init();
}
void BasScrollArea::init(const std::string &para)
{
    UiThemeDef *theme = 0;
    if(m_themeName.empty())
        m_themeName = "default";
    if(m_themeName.size() != 0)
        theme = UiThemeMgrProxy::getInstance()->getThemeByName(m_themeName);

    if(theme != 0 && m_vscrollBar == 0 && m_hscrollBar == 0){
        m_vscrollBar = new ScrollBar(VScrollBar,theme,this);
        m_hscrollBar = new ScrollBar(HScrollBar,theme,this);
        CCSize preferedSize;
        m_vscrollBar->getPreferedSize(preferedSize);
        m_vscrollBar->setMargins(preferedSize.width);
        m_hscrollBar->setMargins(preferedSize.width);
        m_vscrollBar->setRightMargin(2);
        m_hscrollBar->setBottomMargin(2);

        m_vscrollBar->setTop("parent",uilib::Top);
        m_vscrollBar->setBottom("parent",uilib::Bottom);
        m_vscrollBar->setRight("parent",uilib::Right);

        m_hscrollBar->setLeft("parent",uilib::Left);
        m_hscrollBar->setRight("parent",uilib::Right);
        m_hscrollBar->setBottom("parent",uilib::Bottom);
        //init view delegate
        m_viewDelegate = new ScrollViewDelegate(this,this);
        m_viewDelegate->setMargins(0);
        m_viewDelegate->setLeft("parent",uilib::Left);
        m_viewDelegate->setTop("parent",uilib::Top);
        m_viewDelegate->setRight(m_vscrollBar->getName(),uilib::Left);
        m_viewDelegate->setBottom(m_hscrollBar->getName(),uilib::Top);
    }
}
void BasScrollArea::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(m_viewDelegate){
        if(m_vscrollPolicy == ScrollShow_Never){
            m_viewDelegate->setRight("parent",uilib::Right);
        }else{
            m_viewDelegate->setRight(m_vscrollBar->getName(),uilib::Left);
            CCSize ssize;
            m_vscrollBar->getPreferedSize(ssize);
            m_viewDelegate->setLeftMargin(ssize.width);
        }
        if(m_hscrollPolicy == ScrollShow_Never){
            m_viewDelegate->setBottom("parent",uilib::Bottom);
        }else{
            m_viewDelegate->setBottom(m_hscrollBar->getName(),uilib::Top);
        }
    }
    if(m_skin == 0 && m_themeName.size() != 0 && m_themeBg.size() != 0){
        UiThemeDef *theme = UiThemeMgrProxy::getInstance()->getThemeByName(m_themeName);
        BasSkin *skin = BorderImageSkin::create(CCSizeMake(m_anchorWidth,m_anchorHeight),theme,m_themeBg);
        if(skin)
            BasWidget::setSkin(skin);
    }
}
void BasScrollArea::childLayoutCompleted()
{
    BasWidget::childLayoutCompleted();
}
BasScrollArea::BasScrollArea(UiThemeDef *theme,const std::string &bgname,const CCSize &size)
    : BasWidget()
{
    m_containerNode = 0;
    m_viewDelegate = 0;

    m_vscrollBar = 0;
    m_hscrollBar = 0;
    m_vscrollPolicy = ScrollShow_Need;
    m_hscrollPolicy = ScrollShow_Need;
    //init
    BasSkin *skin = BorderImageSkin::create(size,theme,bgname);
    if(skin)
        BasWidget::setSkin(skin);
    if(theme)
        m_themeName = theme->getName();
    m_themeBg = bgname;
    init();
}
BasScrollArea::~BasScrollArea()
{
    if(m_vscrollBar)
        m_vscrollBar->removeFromParentAndCleanup(true);
    if(m_hscrollBar)
        m_hscrollBar->removeFromParentAndCleanup(true);
}
void BasScrollArea::setUserCanScroll(bool can)
{
    if(m_viewDelegate)
        m_viewDelegate->setUserCanScroll(can);
}
void BasScrollArea::finishLayout()
{
    setScrollBar();
    BasWidget::finishLayout();
}
void BasScrollArea::setContainer(CCNode *node,const CCSize &contentSize,bool ver)
{
    if(m_containerNode != 0 && m_containerNode == node){
        m_containerCSize = contentSize;
        m_viewDelegate->updateContainer(node,contentSize,ver);
    }else if(m_containerNode != 0){
        cout << "BasScrollArea::setContainer,you can not set multi container into scrollarea,please check!" << endl;
        return;
    }else{
        m_containerNode = node;
        m_containerCSize = contentSize;
        m_viewDelegate->setContainer(node,contentSize,ver);
    }
    setScrollBar();
}
void BasScrollArea::setDirection (CCScrollViewDirection direction)
{
    m_viewDelegate->setDirection(direction);
}
void BasScrollArea::setVerticalScrollPolicy(ScrollAreaShowPolicy policy)
{
    m_vscrollPolicy = policy;
}
void BasScrollArea::setHorizontalScrollPolicy(ScrollAreaShowPolicy policy)
{
    m_hscrollPolicy = policy;
}
void BasScrollArea::scrollToEnd(bool ver)
{
    m_viewDelegate->scrollToEnd(ver);
}
void BasScrollArea::scrollToEnd(float dt,bool ver)
{
    m_viewDelegate->scrollToEnd(dt,ver);
}
void BasScrollArea::scrollToBegin(bool ver)
{
    m_viewDelegate->scrollToBegin(ver);
}
void BasScrollArea::scrollToBegin(float dt,bool ver)
{
    m_viewDelegate->scrollToBegin(dt,ver);
}
bool BasScrollArea::hasUserScrolled()
{
    return m_userScrolling;
}
void BasScrollArea::clearUserScrolled()
{
    m_userScrolling = false;
}
void BasScrollArea::resetScrollOffset(bool ver)
{
    m_viewDelegate->resetScrollOffset(ver);
}
void BasScrollArea::setScrollBar()
{
    //operating on scrollview
    if(m_vscrollBar == 0 || m_hscrollBar == 0)
        return;
    if(m_containerNode != 0){
        float anchorW,anchorH;
        m_viewDelegate->getAnchorSize(anchorW,anchorH);
        if(m_vscrollPolicy == ScrollShow_Always){
            m_vscrollBar->setVisible(true);
        }else if(m_vscrollPolicy == ScrollShow_Need){
            if(m_containerCSize.height > anchorH)
                m_vscrollBar->setVisible(true);
            else
                m_vscrollBar->setVisible(false);
        }else if(m_vscrollPolicy == ScrollShow_Never){
            m_vscrollBar->setVisible(false);
        }
        if(m_hscrollPolicy == ScrollShow_Always){
            m_hscrollBar->setVisible(true);
        }else if(m_hscrollPolicy == ScrollShow_Need){
            if(m_containerCSize.width > anchorW)
                m_hscrollBar->setVisible(true);
            else
                m_hscrollBar->setVisible(false);
        }else if(m_hscrollPolicy == ScrollShow_Never){
            m_hscrollBar->setVisible(false);
        }
    }else{
        if(m_vscrollPolicy == ScrollShow_Always){
            m_vscrollBar->setVisible(true);
        }else if(m_vscrollPolicy == ScrollShow_Need){
            m_vscrollBar->setVisible(false);
        }else if(m_vscrollPolicy == ScrollShow_Never){
            m_vscrollBar->setVisible(false);
        }
        if(m_hscrollPolicy == ScrollShow_Always){
            m_hscrollBar->setVisible(true);
        }else if(m_hscrollPolicy == ScrollShow_Need){
            m_hscrollBar->setVisible(false);
        }else if(m_hscrollPolicy == ScrollShow_Never){
            m_hscrollBar->setVisible(false);
        }
    }
}
CCNode *BasScrollArea::getContainer()
{
    return m_containerNode;
}
void BasScrollArea::scrollViewDidScroll(CCScrollView* view)
{
    CCPoint offset = view->getContentOffset();
    float percent,lenoffset;
    float anchorW,anchorH;
    m_viewDelegate->getAnchorSize(anchorW,anchorH);
    if(m_vscrollBar && m_vscrollBar->isVisible()){
        if(offset.y > 0)
            offset.y = 0;
        else
            offset.y = -offset.y;
        lenoffset = m_containerCSize.height - anchorH;
        if(offset.y > lenoffset)
            offset.y = lenoffset;
        percent =  1 - offset.y / lenoffset;
        m_vscrollBar->setScrollPercent(percent);
    }
    if(m_hscrollBar && m_hscrollBar->isVisible()){
        if(offset.x > 0)
            offset.x = 0;
        else
            offset.x = -offset.x;
        lenoffset = m_containerCSize.width - anchorW;
        if(offset.x > lenoffset)
            offset.x = lenoffset;
        percent = offset.x / lenoffset;
        m_hscrollBar->setScrollPercent(percent);
    }
}
void BasScrollArea::scrollViewDidZoom(CCScrollView* view)
{

}
void BasScrollArea::getPreferedScrollAreaSize(float &w,float &h)
{
    m_viewDelegate->getAnchorSize(w,h);
    if(w == 0 && h == 0){
        CCSize size;
        m_viewDelegate->getPreferedSize(size);
        w = size.width;
        h = size.height;
    }
}

TextScrollArea::TextScrollArea() : BasScrollArea("","bg")
{

}
TextScrollArea::~TextScrollArea()
{

}
void TextScrollArea::setTheme(const std::string &themeName,const std::string &bgName)
{
    m_themeName = themeName;
    m_themeBg = bgName;
    init();
}
void TextScrollArea::setTextInfo(const std::string &text,const std::string &fontfamily,int fontSize,ccColor3B color)
{
    m_text = text;
    if (m_fontFamily.empty()) {
        m_fontFamily = getSystemFont();
    } else {
        m_fontFamily = fontfamily;
    }
    m_fontSize = fontSize;
    m_fontColor = color;
}
void TextScrollArea::childLayoutCompleted()
{
    BasScrollArea::childLayoutCompleted();
    if(m_viewDelegate && m_text.size() != 0){
        CCSize viewsize;
        m_viewDelegate->getAnchorSize(viewsize.width,viewsize.height);
        CCLabelTTF *label = CCLabelTTF::create(m_text.data(),m_fontFamily.data(),m_fontSize,CCSizeMake(viewsize.width,0),kCCTextAlignmentCenter);
        label->setColor(m_fontColor);
        viewsize.height = label->getTexture()->getContentSize().height;
        this->setContainer(label,viewsize);
        this->setDirection(kCCScrollViewDirectionVertical);
    }
}

}
