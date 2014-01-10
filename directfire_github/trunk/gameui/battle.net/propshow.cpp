#include "propshow.h"
#include "prop/propdef.h"

PropShow::PropShow()
{
    m_numSprite = 0;
    m_inited = false;
}
PropShow::~PropShow()
{

}
void PropShow::setProp(int id,int num)
{
    m_propId = id;
    m_propNum = num;
    if(m_numSprite != 0){
        std::stringstream ss;
        ss << "x" << num;
        m_numSprite->setString(ss.str().data());
    }
}
void PropShow::layoutCompleted()
{
    BasWidget::layoutCompleted();
    if(!m_inited){
        m_inited = true;
        finish();
    }
}
void PropShow::finish()
{
    std::string propName;
    PropDef::getVirtualPropsName(m_propId,propName);
    if(propName.empty()){
        cout << "PropShow::finish,can not get prop's name by id=" << m_propId << endl;
        return;
    }
    propName += ".png";

    CCSprite *propSprite = CCSprite::create();
    propSprite->initWithSpriteFrameName(propName.data());
    BasNodeDelegateWidget *propWidget = new BasNodeDelegateWidget(propSprite,CCSizeMake(m_anchorHeight,m_anchorHeight));
    this->addChild(propWidget);

    propWidget->setLeft("parent",uilib::Left);
    propWidget->setVertical("parent",0.5);

    BasNodeAction *moveIn = UiNodeActionFactory::getInstance()->getMoveActionByName("movein");
    moveIn->setEaseType(uilib::EaseBackInOut);
    moveIn->setMoveInType(uilib::ScaleIn);
    moveIn->setActionTime(1.2);
    propWidget->setMoveinAction(moveIn);

    //num label
    std::stringstream ss;
    ss << "x" << m_propNum;
    m_numSprite = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
    m_numSprite->setAnchorPoint(ccp(0,0.5));
    propWidget->CCNode::addChild(m_numSprite);
    m_numSprite->setPosition(ccp(m_anchorHeight,m_anchorHeight/2.0));
}
