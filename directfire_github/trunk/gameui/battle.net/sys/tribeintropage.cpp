#include "tribeintropage.h"

#include "gamecore/resource/resourcemgr.h"

TribeIntroPage::TribeIntroPage()
{
    m_scroll = 0;
}
TribeIntroPage::~TribeIntroPage()
{

}
void TribeIntroPage::moveInItem()
{
    BasSysPage::moveInItem();
}
void TribeIntroPage::moveOutItem()
{
    BasSysPage::moveOutItem();
}
void TribeIntroPage::layoutCompleted()
{
    BasSysPage::layoutCompleted();
    if(m_scroll == 0)
        initItem();
}
typedef struct TribeProperty{
    TribeProperty(int hp,int baseHp,int speed,int def){
        m_hp = hp;
        m_baseHp = baseHp;
        m_speed = speed;
        m_def = def;
    }

    int m_hp;
    int m_baseHp;
    int m_speed;
    int m_def;
}TribeProperty;

void TribeIntroPage::initItem()
{
    ResourceMgr *mgr = ResourceMgr::getInstance();
    LangDef *lang = mgr->getLangDef();
    m_scroll = new VerScrollWidget();
    this->addChild(m_scroll);
    m_scroll->setFill("parent");
    m_scroll->setSpacing(10);
    std::vector<std::string> tribes;
    std::vector<TribeProperty> tribeProperty;
    if(1){
        tribes.push_back("human");
        tribeProperty.push_back(TribeProperty(4,5,3,3));
        tribes.push_back("orc");
        tribeProperty.push_back(TribeProperty(3,5,3,4));
        tribes.push_back("nightelf");
        tribeProperty.push_back(TribeProperty(3,5,5,2));
        tribes.push_back("undead");
        tribeProperty.push_back(TribeProperty(5,3,4,3));
        tribes.push_back("dragon");
        tribeProperty.push_back(TribeProperty(3,4,4,4));
    }
    float width = m_anchorWidth * 0.9;
    int enumstart = StringEnum::HumanName;
    const std::string &speed = lang->getStringById(StringEnum::TribeSpeed);
    const std::string &hp = lang->getStringById(StringEnum::TribeHp);
    const std::string &basehp = lang->getStringById(StringEnum::TribeBaseHp);
    const std::string &def = lang->getStringById(StringEnum::TribeDef);
    std::stringstream ss;
    for(unsigned int i = 0;i < tribes.size();i++){
        std::string &tribe = tribes[i];
        tribe += ".png";
        CCSprite *tribeSprite = CCSprite::createWithSpriteFrameName(tribe.data());

        FSizeNullDelegate *nodeDele = new FSizeNullDelegate(CCSizeMake(width,240));
        m_scroll->addFixedSizeWidget(nodeDele);
        FSizeCCNodeDelegate *tribeDele = new FSizeCCNodeDelegate(tribeSprite);
        nodeDele->addChild(tribeDele);
        tribeDele->setVertical("parent",0.5);
        tribeDele->setHorizontal("parent",0.2);

        const std::string &tname = lang->getStringById(i + enumstart);
        CCLabelTTF *nameLabel = CCLabelTTF::create(tname.data(),getSystemFont(),40,CCSizeMake(0,0),kCCTextAlignmentCenter);
        nameLabel->setColor(ccGRAY);
        FSizeCCNodeDelegate *nameDele = new FSizeCCNodeDelegate(nameLabel);
        nodeDele->addChild(nameDele);
        nameDele->setHorizontal("parent",0.7);
        nameDele->setVertical("parent",0.2);

        float margin = nameLabel->getContentSize().width / 2 - 10;
        CCLabelTTF *hpLabel = CCLabelTTF::create(hp.data(),getSystemFont(),30,CCSizeMake(0,0),kCCTextAlignmentCenter);
        hpLabel->setColor(ccBLACK);
        FSizeCCNodeDelegate *hpDele = new FSizeCCNodeDelegate(hpLabel);
        nodeDele->addChild(hpDele);
        hpDele->setTop(nameDele->getName(),uilib::Bottom);
        hpDele->setRight(nameDele->getName(),uilib::Left);
        hpDele->setRightMargin(-margin);

        ss.str("");ss << "star" << tribeProperty[i].m_hp << ".png";
        CCSprite *hpStar = CCSprite::createWithSpriteFrameName(ss.str().data());
        FSizeCCNodeDelegate *hpStarDele = new FSizeCCNodeDelegate(hpStar);
        nodeDele->addChild(hpStarDele);
        hpStarDele->setLeft(nameDele->getName(),uilib::Right);
        hpStarDele->setLeftMargin(-margin);
        hpStarDele->setVertical(hpDele->getName(),0.5);

        CCLabelTTF *baseHpLabel = CCLabelTTF::create(basehp.data(),getSystemFont(),30,CCSizeMake(0,0),kCCTextAlignmentCenter);
        baseHpLabel->setColor(ccBLACK);
        FSizeCCNodeDelegate *baseHpDele = new FSizeCCNodeDelegate(baseHpLabel);
        nodeDele->addChild(baseHpDele);
        baseHpDele->setTop(hpDele->getName(),uilib::Bottom);
        baseHpDele->setRight(nameDele->getName(),uilib::Left);
        baseHpDele->setRightMargin(-margin);

        ss.str("");ss << "star" << tribeProperty[i].m_baseHp << ".png";
        CCSprite *baseHpStar = CCSprite::createWithSpriteFrameName(ss.str().data());
        FSizeCCNodeDelegate *baseHpStarDele = new FSizeCCNodeDelegate(baseHpStar);
        nodeDele->addChild(baseHpStarDele);
        baseHpStarDele->setLeft(nameDele->getName(),uilib::Right);
        baseHpStarDele->setLeftMargin(-margin);
        baseHpStarDele->setVertical(baseHpDele->getName(),0.5);

        CCLabelTTF *speedLabel = CCLabelTTF::create(speed.data(),getSystemFont(),30,CCSizeMake(0,0),kCCTextAlignmentCenter);
        speedLabel->setColor(ccBLACK);
        FSizeCCNodeDelegate *speedDele = new FSizeCCNodeDelegate(speedLabel);
        nodeDele->addChild(speedDele);
        speedDele->setTop(baseHpDele->getName(),uilib::Bottom);
        speedDele->setRight(nameDele->getName(),uilib::Left);
        speedDele->setRightMargin(-margin);

        ss.str("");ss << "star" << tribeProperty[i].m_speed << ".png";
        CCSprite *speedStar = CCSprite::createWithSpriteFrameName(ss.str().data());
        FSizeCCNodeDelegate *speedStarDele = new FSizeCCNodeDelegate(speedStar);
        nodeDele->addChild(speedStarDele);
        speedStarDele->setLeft(nameDele->getName(),uilib::Right);
        speedStarDele->setLeftMargin(-margin);
        speedStarDele->setVertical(speedDele->getName(),0.5);

        CCLabelTTF *defLabel = CCLabelTTF::create(def.data(),getSystemFont(),30,CCSizeMake(0,0),kCCTextAlignmentCenter);
        speedLabel->setColor(ccBLACK);
        FSizeCCNodeDelegate *defDele = new FSizeCCNodeDelegate(defLabel);
        nodeDele->addChild(defDele);
        defDele->setTop(speedDele->getName(),uilib::Bottom);
        defDele->setRight(nameDele->getName(),uilib::Left);
        defDele->setRightMargin(-margin);

        ss.str("");ss << "star" << tribeProperty[i].m_def << ".png";
        CCSprite *defStar = CCSprite::createWithSpriteFrameName(ss.str().data());
        FSizeCCNodeDelegate *defStarDele = new FSizeCCNodeDelegate(defStar);
        nodeDele->addChild(defStarDele);
        defStarDele->setLeft(nameDele->getName(),uilib::Right);
        defStarDele->setLeftMargin(-margin);
        defStarDele->setVertical(defDele->getName(),0.5);
    }
    m_scroll->setSpacing(10);
}
