#include "touchnode.h"
#include "namegenerator.h"

namespace uilib
{

TouchNode::TouchNode(TouchNode *parent)
{
    m_canTouch = false;
    m_addedIntoTouch = false;
    m_blockEvent = false;
    m_enabled = true;
    m_childDirty = true;
    m_selected = false;
    m_mouseIn = false;
    m_clickFunc = 0;
    m_clickListener = 0;
    m_parent = parent;
    m_touchPriority = kCCMenuHandlerPriority - 1;
    m_parentMoveListening = false;
    m_name = NameGenerator::getUnusedName();
    if(m_parent)
        m_parent->addChild(this);
    setAnchorPoint(ccp(0.5,0.5));
}
TouchNode::~TouchNode()
{
    std::map<TouchNode*,std::string>::iterator iter;
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        delete iter->first;
    }
    if(m_addedIntoTouch)
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    m_childsMap.clear();
    m_childsNameMap.clear();
    removeFromParentAndCleanup(true);
    removeAllChildrenWithCleanup(true);
}
bool TouchNode::canTouch()
{
    return m_canTouch;
}
void TouchNode::setCanTouch(bool touch)
{
    m_canTouch = touch;
}
bool TouchNode::blockEvent()
{
    return m_blockEvent;
}
void TouchNode::setBlockEvent(bool block)
{
    m_blockEvent = block;
}
bool TouchNode::isAncestorOf(TouchNode *node)
{
    TouchNode *parent = this;
    while(parent){
        if(node->m_parent == parent)
            return true;
        else
            parent = parent->m_parent;
    }
    return false;
}
bool TouchNode::isParentOf(TouchNode *node)
{
    return node->m_parent == this;
}
bool TouchNode::isChildOf(TouchNode *node)
{
    return node != 0  && m_parent == node;
}
TouchNode *TouchNode::parent()
{
    return m_parent;
}
TouchNode *TouchNode::rootParent()
{
    TouchNode *root = m_parent;
    if(root == 0)
        return this;
    while(root->m_parent){
        root = root->m_parent;
    }
    return root;
}
void TouchNode::setParent(TouchNode *parent)
{
    if(m_parent)
        m_parent->delChild(this);
    m_parent = parent;
    if(m_parent)
        m_parent->addChild(this);
}
bool TouchNode::getShowSprite(std::vector<CCSprite*> &sprites,CCSize &size)
{
    return false;
}
void TouchNode::layout(bool force)
{
    if(force)
        m_childDirty = true;
    if(m_childDirty){
        invalidAllChild();
        if(m_parent == 0){
            m_destPoint = this->getPosition();
            CCSize size;
            getPreferedSize(size);
            setAnchoredSize(size.width,size.height);
            BasAnchor::setAnchored(true);
            layoutCompleted();
        }else{
            if(m_anchorWidth > 0 && m_anchorHeight > 0){
                setAnchoredSize(m_anchorWidth,m_anchorHeight);
                BasAnchor::setAnchored(true);
            }else{
                CCSize size;
                getPreferedSize(size);
                setAnchoredSize(size.width,size.height);
                BasAnchor::setAnchored(true);
            }
            layoutCompleted();
        }
        reLayout();
        resetTouchPriority();
        m_childDirty = false;
    }
}
void TouchNode::getPreferedSize(CCSize &size)
{
    if(m_width > 0  && m_height > 0){
        size.width = m_width;
        size.height = m_height;
    }else if(m_width > 0 || m_height > 0){
        CCSize psize;
        SizePolicy::getPreferedSize(psize);
        if(m_width > 0){
            size.width = m_width;
            size.height = psize.height;
        }else{
            size.width = psize.width;
            size.height = m_height;
        }
    }else{
        SizePolicy::getPreferedSize(size);
    }
}
void TouchNode::adjustSize(CCSize &size)
{
    if(m_width > 0)
        size.width = m_width;
    if(m_height > 0)
        size.height = m_height;
    SizePolicy::adjustSize(size);
}
bool TouchNode::setName(const std::string &name)
{
    if(name == "parent"){
        cout << "TouchNode::setName,error,parent is reserved by uilib" << endl;
        return false;
    }
    if(name == "child"){
        cout << "TouchNode::setName,error child is reserved by uilib" << endl;
        return false;
    }
    if(m_parent == 0){
        m_name = name;
        return true;
    }else{
        return m_parent->setChildName(this,name);
    }
}
void TouchNode::setClickCB(CCNode *listener,SEL_CallFuncND func)
{
    m_clickListener = listener;
    m_clickFunc = func;
}
void TouchNode::resetClickCB()
{
    m_clickListener = 0;
    m_clickFunc = 0;
}
bool TouchNode::containClickPosition(float x,float y)
{
    return containClickPosition(ccp(x,y));
}
bool TouchNode::containClickPosition(const CCPoint &pos)
{
    if(!isVisible())
        return false;
    if(m_parent == 0){
        return this->boundingBox().containsPoint(pos);
    }else{
        return this->boundingBox().containsPoint(
                    m_parent->convertToNodeSpace(pos));
    }
}
bool TouchNode::containClickPosition(CCTouch *pTouch)
{
    if(!isVisible())
        return false;
    if(m_parent == 0){
        return this->boundingBox().containsPoint(pTouch->getLocation());
    }else{
        return this->boundingBox().containsPoint(
                    m_parent->convertTouchToNodeSpace(pTouch));
    }
}
bool TouchNode::addChild(TouchNode *child)
{
    if(child->m_name.size() == 0){
        child->m_name = NameGenerator::getUnusedName();
    }else{
        if(getChildByName(child->m_name)){
            child->m_name = NameGenerator::getUnusedName();
        }
    }
    m_childsNameMap.insert(std::make_pair(child->m_name,child));
    m_childsMap.insert(std::make_pair(child,child->m_name));
    child->m_parent = this;
    CCNode::addChild(child,1);
    m_childDirty = true;
    return true;
}
void TouchNode::delChild(TouchNode *child,bool clean)
{
    std::map<std::string,TouchNode*>::iterator iter;
    iter = m_childsNameMap.find(child->m_name);
    if(iter != m_childsNameMap.end())
        m_childsNameMap.erase(iter);
    std::map<TouchNode *,std::string>::iterator siter;
    siter = m_childsMap.find(child);
    if(siter != m_childsMap.end())
        m_childsMap.erase(siter);
    child->m_parent = 0;
    if(clean)
        child->removeFromParentAndCleanup(true);
    m_childDirty = true;
}
void TouchNode::delAllChild()
{
    std::map<TouchNode *,std::string>::iterator iter;
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        TouchNode *child = iter->first;
        child->m_parent = 0;
        if(child->m_childsMap.size() != 0){
            child->delAllChild();
        }
        child->removeFromParentAndCleanup(true);
    }
    m_childsMap.clear();
    m_childsNameMap.clear();
    m_childDirty = true;
}
TouchNode *TouchNode::childAt(float x,float y)
{
    return childAt(ccp(x,y));
}
TouchNode *TouchNode::childAt(const CCPoint &pos)
{
    std::map<TouchNode *,std::string>::iterator iter;
    TouchNode *child = 0;
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        if(iter->first->containClickPosition(pos)){
            if(child == 0)
                child = iter->first;
            else if(child->m_touchPriority > iter->first->m_touchPriority)
                child = iter->first;
        }
    }
    return child;
}
bool TouchNode::hasFocus()
{
    if(!CCNode::isVisible())
        return false;
    std::map<TouchNode*,std::string>::iterator iter;
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        if(iter->first->isVisible())
            return true;
    }
    return false;
}
void TouchNode::setSizeLimitedToParent()
{
    setMaxWidthRefSize("parent",1.0);
    setMaxHeightRefSize("parent",1.0);
}
int TouchNode::getHighestAncestorPriority()
{
    int priority = this->m_touchPriority;
    TouchNode *parent = m_parent;
    while(parent){
        if(priority > parent->m_touchPriority)
            priority = parent->m_touchPriority;
        parent = parent->m_parent;
    }
    return priority;
}
void TouchNode::setEnabled(bool enabled)
{
    m_enabled = enabled;
    std::map<TouchNode*,std::string>::iterator iter;
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        iter->first->setEnabled(enabled);
    }
}
bool TouchNode::ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_blockEvent && isVisible()){
        //block has the high priority level
        if(m_canTouch){
            touchPressEvent(pTouch,pEvent);
            if(m_parent && m_parentMoveListening){
                m_parent->listenerPressEvent(pTouch,pEvent);
            }
            m_selected = true;
            return true;
        }
        return true;
    }
    TouchNode *parent = m_parent;
    do{
        if(parent && (!parent->isVisible() || !parent->isEnabled()))
            return false;
        if(parent == 0)
            break;
        parent = parent->m_parent;
    }while(1);
    if(!m_canTouch || !this->isVisible() || !m_enabled)
        return false;
    CCPoint pos = m_parent->convertToNodeSpace(pTouch->getLocation());
    if(this->boundingBox().containsPoint(pos)){
        touchPressEvent(pTouch,pEvent);
        if(m_parent && m_parentMoveListening){
            m_parent->listenerPressEvent(pTouch,pEvent);
        }
        m_selected = true;
        m_mouseIn = true;
        return true;
    }else{
        return false;
    }
}
void TouchNode::ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_selected){
        touchMoveEvent(pTouch,pEvent);
        if(m_parent && m_parentMoveListening){
            m_parent->listenerMoveEvent(pTouch,pEvent);
        }
        if (m_parent) {
            CCPoint pos = m_parent->convertToNodeSpace(pTouch->getLocation());
            bool in = this->boundingBox().containsPoint(pos);
            if(m_mouseIn == in){
                return;
            }else{
                m_mouseIn = in;
                if(m_mouseIn){
                    touchMoveInEvent(pTouch,pEvent);
                }else{
                    touchMoveOutEvent(pTouch,pEvent);
                }
            }
        }
    }
}
void TouchNode::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_selected){
        m_selected = false;
        CCPoint pos = m_parent->convertToNodeSpace(pTouch->getLocation());
        m_mouseIn = this->boundingBox().containsPoint(pos);
        bool needRelease = true;
        if(m_parent && m_parentMoveListening){
            needRelease = !m_parent->listenerReleaseEvent(pTouch,pEvent);
        }
        if(needRelease)
            touchReleaseEvent(pTouch,pEvent);
    }
}
void TouchNode::onEnter()
{
    CCNode::onEnter();
    //always register as hight priority than menu layer(kCCMenuHandlerPriority)
    if(m_parent == 0 && !m_addedIntoTouch){
        CCDirector::sharedDirector()->getTouchDispatcher()
                ->addTargetedDelegate(this,m_touchPriority,true);
        m_addedIntoTouch = true;
    }
}
void TouchNode::onExit()
{
    CCNode::onExit();
    if(m_addedIntoTouch)
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    m_addedIntoTouch = false;
}
void TouchNode::update(float fDelta)
{
    //donothing
}
void TouchNode::touchPressEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    //donothing
}
void TouchNode::touchMoveInEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    //donothing
}
void TouchNode::touchMoveOutEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    //donothing
}
void TouchNode::touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    //donothing
}
void TouchNode::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_clickListener && m_clickFunc){
        CCPoint pos = convertToWorldSpace(convertTouchToNodeSpace(pTouch));
        (m_clickListener->*m_clickFunc)(this,&pos);
    }
}
void TouchNode::moveInStart()
{
    std::map<TouchNode*,std::string>::iterator iter;
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        iter->first->moveInStart();
    }
}
void TouchNode::moveOutStart()
{
    std::map<TouchNode*,std::string>::iterator iter;
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        iter->first->moveOutStart();
    }
}
bool TouchNode::checkChildLocationValid()
{
    std::map<TouchNode *,std::string>::iterator iter;
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        if(!iter->first->isValidLocation()){
            cout << "TouchNode::checkChildLocationValid: child " <<
                    iter->first->m_name << " has invalid location,please check" << endl;
            return false;
        }
    }
    return true;
}
void TouchNode::reLayout()
{
    m_finishedPool.clear();
    m_unfinishedPool.clear();
    std::map<TouchNode *,std::string>::iterator iter;
    TouchNode *child;
    childLayoutStarted();
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        child = iter->first;
        if(child->isAbsoluteLocation()){
            if(child->doAbsoluateLayout())
                m_finishedPool.insert(std::make_pair(child->m_name,child));
            else
                m_unfinishedPool.insert(std::make_pair(child->m_name,child));
        }else if(child->isRelativeLocation()){
            m_unfinishedPool.insert(std::make_pair(child->m_name,child));
        }else{
            cout << "TouchNode::reLayout,no valid layout info for node " << child->m_name << endl;
        }
    }
    if((m_finishedPool.size() + m_unfinishedPool.size()) != m_childsMap.size()){
        checkChildLocationValid();
    }else{
        doLayout();
        childLayoutCompleted();
    }
}
void TouchNode::invalidAllChild()
{
    std::map<TouchNode *,std::string>::iterator iter;
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        iter->first->setAnchored(false);
        iter->first->m_childDirty = true;
        iter->first->invalidAllChild();
    }
}
void TouchNode::doLayout()
{
    int left = m_unfinishedPool.size();
    if(left == 0){
        std::map<TouchNode*,std::string>::iterator iter;
        for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
            iter->first->reLayout();
        }
        return;
    }
    std::map<std::string,TouchNode*>::iterator iter;
    TouchNode *node;
    for(iter = m_unfinishedPool.begin();iter != m_unfinishedPool.end();){
        node = iter->second;
        if(node->isAbsoluteLocation()){
            if(node->doAbsoluateLayout()){
                m_unfinishedPool.erase(iter++);
                m_finishedPool.insert(std::make_pair(node->m_name,node));
            }else{
                iter++;
            }
        }else if(node->isRelativeLocation()){
            if(node->doRelativeLayout()){
                m_unfinishedPool.erase(iter++);
                m_finishedPool.insert(std::make_pair(node->m_name,node));
            }else{
                iter++;
            }
        }else{
            iter++;
        }
    }
    if(left == m_unfinishedPool.size()){
        cout << "TouchNode::doLayout,no Node layout success in this loop why?" << endl;
    }else{
        doLayout();
    }
}
bool TouchNode::doAbsoluateLayout()
{
    CCSize size;
    getPreferedSize(size);
    m_anchorWidth = size.width;
    m_anchorHeight = size.height;
    bool success = false;
    /* CenterIn < Fill < HorizontalCenter < VerticalCenter */
    success = handleCenterIn(size);
    if(!success) return false;
    success = handleFill(size);
    if(!success) return false;
    success = handleHorizontal(size);
    if(!success) return false;
    success = handleVertical(size);
    if(success){
        m_anchorWidth = m_anchorRight - m_anchorLeft;
        m_anchorHeight = m_anchorTop - m_anchorBottom;
        this->setAnchoredSize(m_anchorWidth,m_anchorHeight);
        m_destPoint = ccp(m_anchorLeft + m_anchorWidth / 2,
                          m_anchorBottom + m_anchorHeight / 2);
        layoutCompleted();
        this->setAnchored(true);
        return true;
    }else{
        return false;
    }
}
bool TouchNode::doRelativeLayout()
{
    CCSize size;
    getPreferedSize(size);
    bool success = false;
    m_anchorLeft = 0;
    m_anchorTop = 0;
    m_anchorRight = size.width;
    m_anchorBottom = size.height;
    success = handleHorizontal(size);
    if(!success) return false;
    success = handleVertical(size);
    if(!success) return false;
    success = handleLeft(size);
    if(!success) return false;
    success = handleRight(size);
    if(!success) return false;
    success = handleTop(size);
    if(!success) return false;
    success = handleBottom(size);
    if(!success){
        return false;
    }else{
        if((m_leftAnchored || m_rightAnchored) &&
                (m_topAnchored || m_bottomAnchored)){
            m_anchorWidth = m_anchorRight - m_anchorLeft;
            m_anchorHeight = m_anchorTop - m_anchorBottom;
            this->setAnchoredSize(m_anchorWidth,m_anchorHeight);
            m_destPoint = ccp(m_anchorLeft + m_anchorWidth / 2,
                              m_anchorBottom + m_anchorHeight / 2);
            layoutCompleted();
            this->setAnchored(true);
            return true;
        }else{
            return false;
        }
    }
}
void TouchNode::layoutCompleted()
{
    if(m_parent != 0){
        this->setAnchorPoint(ccp(0.5,0.5));
        this->setPosition(m_destPoint);
    }
}
void TouchNode::childLayoutStarted()
{

}
void TouchNode::childLayoutCompleted()
{

}
bool TouchNode::handleCenterIn(const CCSize &preferedSize)
{
    if(m_centerInName.size() == 0)
        return true;
    TouchNode *anchorNode = getAnchorNode(m_centerInName);
    if(anchorNode == 0){
        cout << "TouchNode::handleCenterIn,invalid anchorCenterIn=" << m_centerInName << endl;
        return true;
    }else if(!anchorNode->isAnchored()){
        return false;
    }
    float anchorW,anchorH;
    if(!anchorNode->getAnchorSize(anchorW,anchorH)){
        return false;
    }
    CCPoint anchorPos;
    //we need diff parent and other'child here
    if(anchorNode == m_parent){
        anchorPos = ccp(0,0);
    }else{
        CCPoint anchorPoint = anchorNode->getAnchorPoint();
        anchorPos = anchorNode->getDestPoint();
        anchorPos.x -= anchorPoint.x * anchorW;
        anchorPos.y -= anchorPoint.y * anchorH;
    }
    m_anchorLeft = anchorPos.x + anchorW / 2 - preferedSize.width / 2;
    m_anchorRight = m_anchorLeft + preferedSize.width;
    m_anchorTop = anchorPos.y + anchorH / 2 + preferedSize.height / 2;
    m_anchorBottom = m_anchorTop - preferedSize.height;
    return true;
}
bool TouchNode::handleFill(const CCSize &)
{
    if(m_fillName.size() == 0)
        return true;

    TouchNode *anchorNode = getAnchorNode(m_fillName);
    if(anchorNode == 0){
        cout << "TouchNode::handleFill,invalid anchorFill=" << m_fillName << endl;
        return true;
    }else if(!anchorNode->isAnchored()){
        return false;
    }
    float anchorW,anchorH;
    if(!anchorNode->getAnchorSize(anchorW,anchorH))
        return false;
    CCPoint anchorPos;
    //we need diff parent and other'child here
    if(anchorNode == m_parent){
        anchorPos = ccp(0,0);
    }else{
        CCPoint anchorPoint = anchorNode->getAnchorPoint();
        anchorPos = anchorNode->getDestPoint();
        anchorPos.x -= anchorPoint.x * anchorW;
        anchorPos.y -= anchorPoint.y * anchorH;
    }
    m_anchorLeft = anchorPos.x + m_leftMargin;
    m_anchorRight = anchorPos.x + anchorW - m_rightMargin;
    m_anchorTop = anchorPos.y + anchorH - m_topMargin;
    m_anchorBottom = anchorPos.y + m_bottomMargin;
    return true;
}
bool TouchNode::handleHorizontal(const CCSize &preferedSize)
{
    if(m_horizontalName.size() == 0)
        return true;

    TouchNode *anchorNode = getAnchorNode(m_horizontalName);
    if(anchorNode == 0){
        cout << "TouchNode::handleHorizontal,invalid anchorHorizontal=" << m_horizontalName << endl;
        return true;
    }else if(!anchorNode->isAnchored()){
        return false;
    }
    float anchorW,anchorH;
    if(!anchorNode->getAnchorSize(anchorW,anchorH))
        return false;
    CCPoint anchorPos;
    //we need diff parent and other'child here
    if(anchorNode == m_parent){
        anchorPos = ccp(0,0);
    }else{
        CCSize anchorSize = anchorNode->getContentSize();
        CCPoint anchorPoint = anchorNode->getAnchorPoint();
        anchorPos = anchorNode->getDestPoint();
        anchorPos.x -= anchorPoint.x * anchorSize.width;
        anchorPos.y -= anchorPoint.y * anchorSize.height;
    }
    m_anchorLeft = anchorPos.x + anchorW * m_horizontalValue - preferedSize.width / 2 + m_leftMargin + m_horMargin;
    m_anchorRight = anchorPos.x + anchorW * m_horizontalValue + preferedSize.width /2 - m_rightMargin + m_horMargin;
    m_leftAnchored = true;
    m_rightAnchored = true;
    return true;
}
bool TouchNode::handleVertical(const CCSize &preferedSize)
{
    if(m_verticalName.size() == 0)
        return true;

    TouchNode *anchorNode = getAnchorNode(m_verticalName);
    if(anchorNode == 0){
        cout << "TouchNode::handleVertical,invalid anchorVertical=" << m_verticalName << endl;
        return true;
    }else if(!anchorNode->isAnchored()){
        return false;
    }
    float anchorW,anchorH;
    if(!anchorNode->getAnchorSize(anchorW,anchorH))
        return false;
    CCPoint anchorPos;
    //we need diff parent and other'child here
    if(anchorNode == m_parent){
        anchorPos = ccp(0,0);
    }else{
        CCSize anchorSize = anchorNode->getContentSize();
        CCPoint anchorPoint = anchorNode->getAnchorPoint();
        anchorPos = anchorNode->getDestPoint();
        anchorPos.x -= anchorPoint.x * anchorSize.width;
        anchorPos.y -= anchorPoint.y * anchorSize.height;
    }
    m_anchorTop = anchorPos.y + anchorH * (1 - m_verticalValue) + preferedSize.height / 2 - m_topMargin - m_verMargin;
    m_anchorBottom = anchorPos.y + anchorH * (1 - m_verticalValue) - preferedSize.height/2 + m_bottomMargin - m_verMargin;
    m_topAnchored = true;
    m_bottomAnchored = true;
    return true;
}
bool TouchNode::handleLeft(const CCSize &preferedSize)
{
    if(m_leftName.size() == 0)
        return true;
    TouchNode *anchorNode = getAnchorNode(m_leftName);
    if(anchorNode == 0){
        cout << "TouchNode::handleLeft,invalid anchorLeft=" << m_leftName << endl;
        return true;
    }else if(!anchorNode->isAnchored()){
        return false;
    }
    float anchorW,anchorH;
    if(!anchorNode->getAnchorSize(anchorW,anchorH))
        return false;
    CCPoint anchorPos;
    //we need diff parent and other'child here
    if(anchorNode == m_parent){
        anchorPos = ccp(0,0);
    }else{
        CCSize anchorSize = anchorNode->getContentSize();
        CCPoint anchorPoint = anchorNode->getAnchorPoint();
        anchorPos = anchorNode->getDestPoint();
        anchorPos.x -= anchorPoint.x * anchorSize.width;
        anchorPos.y -= anchorPoint.y * anchorSize.height;
    }
    if(m_leftType == Left){
        m_anchorLeft = anchorPos.x + m_leftMargin;
    }else if(m_leftType == Right){
        m_anchorLeft = anchorPos.x + anchorW + m_leftMargin;
    }else{
        return false;
    }
    m_leftAnchored = true;
    if(!m_rightAnchored)
        m_anchorRight = m_anchorLeft + preferedSize.width;
    return true;
}
bool TouchNode::handleTop(const CCSize &preferedSize)
{
    if(m_topName.size() == 0)
        return true;
    TouchNode *anchorNode = getAnchorNode(m_topName);
    if(anchorNode == 0){
        cout << "TouchNode::handleTop,invalid anchorTop=" << m_topName << endl;
        return true;
    }else if(!anchorNode->isAnchored()){
        return false;
    }
    float anchorW,anchorH;
    if(!anchorNode->getAnchorSize(anchorW,anchorH))
        return false;
    CCPoint anchorPos;
    //we need diff parent and other'child here
    if(anchorNode == m_parent){
        anchorPos = ccp(0,0);
    }else{
        CCSize anchorSize = anchorNode->getContentSize();
        CCPoint anchorPoint = anchorNode->getAnchorPoint();
        anchorPos = anchorNode->getDestPoint();
        anchorPos.x -= anchorPoint.x * anchorSize.width;
        anchorPos.y -= anchorPoint.y * anchorSize.height;
    }
    if(m_topType == Top){
        m_anchorTop = anchorPos.y + anchorH - m_topMargin;
    }else if(m_topType == Bottom){
        m_anchorTop = anchorPos.y - m_topMargin;
    }else{
        return false;
    }
    m_topAnchored = true;
    if(!m_bottomAnchored)
        m_anchorBottom = m_anchorTop - preferedSize.height;
    return true;
}
bool TouchNode::handleRight(const CCSize &preferedSize)
{
    if(m_rightName.size() == 0)
        return true;
    TouchNode *anchorNode = getAnchorNode(m_rightName);
    if(anchorNode == 0){
        cout << "TouchNode::handleRight,invalid anchorRight=" << m_rightName << endl;
        return true;
    }else if(!anchorNode->isAnchored()){
        return false;
    }
    float anchorW,anchorH;
    if(!anchorNode->getAnchorSize(anchorW,anchorH))
        return false;
    CCPoint anchorPos;
    //we need diff parent and other'child here
    if(anchorNode == m_parent){
        anchorPos = ccp(0,0);
    }else{
        CCSize anchorSize = anchorNode->getContentSize();
        CCPoint anchorPoint = anchorNode->getAnchorPoint();
        anchorPos = anchorNode->getDestPoint();
        anchorPos.x -= anchorPoint.x * anchorSize.width;
        anchorPos.y -= anchorPoint.y * anchorSize.height;
    }
    if(m_rightType == Left){
        m_anchorRight = anchorPos.x - m_rightMargin;
    }else if(m_rightType == Right){
        m_anchorRight = anchorPos.x + anchorW - m_rightMargin;
    }else{
        return false;
    }
    m_rightAnchored = true;
    if(!m_leftAnchored)
        m_anchorLeft = m_anchorRight - preferedSize.width;
    return true;
}
bool TouchNode::handleBottom(const CCSize &preferedSize)
{
    if(m_bottomName.size() == 0)
        return true;
    TouchNode *anchorNode = getAnchorNode(m_bottomName);
    if(anchorNode == 0){
        cout << "TouchNode::handleBottom,invalid anchorBottom=" << m_bottomName << endl;
        return true;
    }else if(!anchorNode->isAnchored()){
        return false;
    }
    float anchorW,anchorH;
    if(!anchorNode->getAnchorSize(anchorW,anchorH))
        return false;
    CCPoint anchorPos;
    //we need diff parent and other'child here
    if(anchorNode == m_parent){
        anchorPos = ccp(0,0);
    }else{
        CCSize anchorSize = anchorNode->getContentSize();
        CCPoint anchorPoint = anchorNode->getAnchorPoint();
        anchorPos = anchorNode->getDestPoint();
        anchorPos.x -= anchorPoint.x * anchorSize.width;
        anchorPos.y -= anchorPoint.y * anchorSize.height;
    }
    if(m_bottomType == Top){
        m_anchorBottom = anchorPos.y + anchorH + m_bottomMargin;
    }else if(m_bottomType == Bottom){
        m_anchorBottom = anchorPos.y + m_bottomMargin;
    }else{
        return false;
    }
    m_bottomAnchored = true;
    if(!m_topAnchored)
        m_anchorTop = m_anchorBottom + preferedSize.height;
    return true;
}
TouchNode *TouchNode::getAnchorNode(const std::string &name)
{
    if(name == "parent"){
        return m_parent;
    }else if(m_parent->m_name == name){
        return m_parent;
    }else if(m_name == name){
        cout << "TouchNode::getAnchorNode,can not anchor to self,please check!" << endl;
        return 0;
    }else{
        return m_parent->getChildByName(name);
    }
}
void TouchNode::resetTouchPriority()
{
    CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    if(m_parent && (m_touchPriority > (m_parent->m_touchPriority - 1))){
        m_touchPriority = m_parent->m_touchPriority - 1;
    }
    this->retain();
    if(m_addedIntoTouch)
        dispatcher->removeDelegate(this);
    dispatcher->addTargetedDelegate(this,m_touchPriority,true);
    m_addedIntoTouch = true;
    if(m_childsMap.size() == 0)
        return;
    std::map<TouchNode*,std::string>::iterator iter;
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        if(iter->first->m_touchPriority > (m_touchPriority - 1))
            iter->first->m_touchPriority = m_touchPriority - 1;
        if(iter->first->m_addedIntoTouch)
            dispatcher->removeDelegate(iter->first);
        dispatcher->addTargetedDelegate(iter->first,iter->first->m_touchPriority,true);
        iter->first->m_addedIntoTouch = true;
        iter->first->setTouchPriorityFinished();
        if(iter->first->m_childsMap.size() != 0)
            iter->first->resetTouchPriority();
    }
    setTouchPriorityFinished();
}
void TouchNode::setTouchPriorityFinished()
{

}
bool TouchNode::setChildName(TouchNode *child,const std::string &name)
{
    if(name == child->m_name)
        return true;
    if(m_name == name){
        cout << "TouchNode::setChildName,you can not set child name same with parent!" << endl;
        return false;
    }
    if(hasChildByName(name))
        return false;
    m_childsNameMap.erase(child->m_name);
    m_childsMap.erase(child);
    child->m_name = name;
    m_childsNameMap.insert(std::make_pair(name,child));
    m_childsMap.insert(std::make_pair(child,name));
    return true;
}
bool TouchNode::hasChildByName(const std::string &name)
{
    std::map<std::string,TouchNode*>::iterator iter;
    iter = m_childsNameMap.find(name);
    if(iter != m_childsNameMap.end())
        return true;
    else
        return false;
}
TouchNode *TouchNode::getChildByName(const std::string &name)
{
    std::map<std::string,TouchNode*>::iterator iter;
    iter = m_childsNameMap.find(name);
    if(iter != m_childsNameMap.end())
        return iter->second;
    else
        return 0;
}
void TouchNode::getRefSize(const std::string &name,CCSize &size)
{
    if(name.size() == 0){
        size.width = 0;
        size.height = 0;
        return;
    }else{
        TouchNode *node = getAnchorNode(name);
        if(node){
            if(node->isAnchored()){
                float w,h;
                node->getAnchorSize(w,h);
                size.width = w;
                size.height = h;
            }else if(getWidth() > 0 && getHeight() > 0){
                size.width = getWidth();
                size.height = getHeight();
            }else if(node->isParentOf(this) && node->preferedSizeToChildMax()){
                size.width = 0;
                size.height = 0;
            }else{
                node->getPreferedSize(size);
            }
        }
    }
}
void TouchNode::setAnchoredSize(float width,float height)
{
    BasAnchor::setAnchoredSize(width,height);
    if(m_width > 0 && m_height > 0){
        setScaleX(width / m_width);
        setScaleY(height / m_height);
    }
}
void TouchNode::getChildMaxPreferedSize(CCSize &size)
{
    float maxw = -1,maxh = -1;
    CCSize csize;
    std::map<TouchNode*,std::string>::iterator iter;
    for(iter = m_childsMap.begin();iter != m_childsMap.end();iter++){
        TouchNode *child = iter->first;
        if(child->isAnchored()){
            child->getAnchorSize(csize.width,csize.height);
            if(maxw < csize.width)
                maxw = csize.width;
            if(maxh < csize.height)
                maxh = csize.height;
        }else{
            child->getPreferedSize(csize);
            if(maxw < csize.width)
                maxw = csize.width;
            if(maxh < csize.height)
                maxh = csize.height;
        }
    }
    size.width = maxw;
    size.height = maxh;
}
void TouchNode::getSilbingMaxPreferedSize(CCSize &size)
{
    if(m_parent == 0)
        return;
    float maxw = -1,maxh = -1;
    CCSize csize;
    std::map<TouchNode*,std::string>::iterator iter;
    for(iter = m_parent->m_childsMap.begin();iter != m_parent->m_childsMap.end();iter++){
        TouchNode *child = iter->first;
        if(child->isAnchored()){
            child->getAnchorSize(csize.width,csize.height);
            if(maxw < csize.width)
                maxw = csize.width;
            if(maxh < csize.height)
                maxh = csize.height;
        }else{
            child->getPreferedSize(csize);
            if(maxw < csize.width)
                maxw = csize.width;
            if(maxh < csize.height)
                maxh = csize.height;
        }
    }
    size.width = maxw;
    size.height = maxh;
}

}
