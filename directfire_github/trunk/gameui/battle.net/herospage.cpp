#include "herospage.h"
#include "herostitle.h"

#include "utils/sysutils.h"
#include "prop/propdef.h"
#include "gamecore/sounds/soundmgr.h"

#include "herositem.h"
#include "gamecore/utils/ccutils.h"

HerosPage::HerosPage(uilib::BasWidget *container) : BasPage(container)
{
    m_serverIface = ServerInterface::getInstance();
    m_id = m_serverIface->getLoginAccountInfo()->m_id;
    m_title = new HerosTitle;
    m_title->setTypeCB(this,callfuncND_selector(HerosPage::onSortTypeClicked));
    m_title->setRefreshCB(this,callfuncND_selector(HerosPage::onRefreshClicked));
    this->addChild(m_title);
    float srate = getAdaptResourceScale();
    m_title->setLeft("parent",uilib::Left);
    m_title->setBottom("parent",uilib::Top);
    m_title->setLeftMargin(20);
    m_title->setRightMargin(20);
    m_title->setWidth(610 * srate);
    m_title->setHeight(92 * srate);

    this->setTopMargin(30);
    m_itemInit = false;
}
HerosPage::~HerosPage()
{

}
void HerosPage::moveinPage()
{
    if(!m_itemInit){
        init();
        this->scheduleOnce(schedule_selector(HerosPage::startHerosInfo),0.5);
    }
}
void HerosPage::moveoutPage()
{

}
void HerosPage::startGetHerosInfo()
{
    if(m_title)
        m_title->setRefreshing(true);
}
void HerosPage::endGetHerosInfo()
{
    if(m_title)
        m_title->setRefreshing(false);
}
void HerosPage::updateHeroInfo()
{
    float width = m_anchorWidth * 0.94;
    for(int i = UiMsgEv::HeroLevel;i <= UiMsgEv::HeroLose;i++){
        const UiMsgEv::HerosInfo *heros = m_serverIface->getHerosDataByType((UiMsgEv::HerosType)i);
        if(heros == 0)
            continue;
        VerScrollWidget *ver = m_cates[i - UiMsgEv::HeroLevel];
        if(ver->scrollItemCount() != 0){
            ver->delAllChild();
        }
        for(unsigned int k = 0;k < heros->m_heros.size();k++){
            const UiMsgEv::HeroInfo &hero = heros->m_heros[k];
            HerosItem *border = new HerosItem;
            border->setId(hero.m_userId);
            border->setWidth(width);
            border->setHeight(100);

            FSizeWidgetDelegate *itemDele = new FSizeWidgetDelegate(border,CCSizeMake(width,100));
            ver->addFixedSizeWidget(itemDele);
            fillItem(border,i,k+1,hero);
        }
        ver->setSpacing(20);
        ver->layout(true);
        ver->scrollToBegin(true);
    }
}
void HerosPage::updateUserInfo()
{
    float width = m_anchorWidth * 0.94;
    UiMsgEv::AccountInfoEv *ev = m_serverIface->getLoginAccountInfo();
    UiMsgEv::HeroInfo hero;
    hero.m_userId = ev->m_id;
    hero.m_userMail = ev->m_mail;
    hero.m_nickName = ev->m_name;
    UiMsgEv::PlayerInfoEv *playEv = m_serverIface->getPlayerInfoByUid(m_id);
    hero.m_level = playEv->m_level;
    hero.m_exp = playEv->m_exp;
    hero.m_wonNum = playEv->m_wonNum;
    hero.m_losedNum = playEv->m_losedNum;
    hero.m_playedNum = playEv->m_playedNum;
    hero.m_propCount = m_serverIface->getPropNumByUid(m_id,PropDef::Props_Gold);
    const std::vector<UiMsgEv::UserRank> *ranks = m_serverIface->getUserRankInfo();
    for(int i = 0;i < ranks->size();i++){
        const UiMsgEv::UserRank &rank = ranks->at(i);
        VerScrollWidget *ver = 0;
        switch(rank.m_sortType){
        case UiMsgEv::HeroLevel:{
            ver = m_cates[0];
            break;
        }
        case UiMsgEv::HeroGold:{
            ver = m_cates[UiMsgEv::HeroGold - UiMsgEv::HeroLevel];
            break;
        }
        case UiMsgEv::HeroPlayed:{
            ver = m_cates[UiMsgEv::HeroPlayed - UiMsgEv::HeroLevel];
            break;
        }
        case UiMsgEv::HeroWon:{
            ver = m_cates[UiMsgEv::HeroWon - UiMsgEv::HeroLevel];
            break;
        }
        case UiMsgEv::HeroLose:{
            ver = m_cates[UiMsgEv::HeroLose - UiMsgEv::HeroLevel];
            break;
        }
        default:{
            break;
        }
        }
        if(ver == 0)
            continue;
        int scrollCount = ver->scrollItemCount();
        if(scrollCount == 0){
            continue;
        }else if(scrollCount >= rank.m_sortNum){
            continue;
        }
        HerosItem *etcitem = new HerosItem;
        etcitem->setTheme("","");
        etcitem->setWidth(width);
        etcitem->setHeight(100);
        FSizeWidgetDelegate *itemDele = new FSizeWidgetDelegate(etcitem);
        ver->addFixedSizeWidget(itemDele);
        CCSprite *etcsprite = CCSprite::createWithSpriteFrameName("veretc.png");
        FSizeCCNodeDelegate *etcdele = new FSizeCCNodeDelegate(etcsprite);
        etcitem->addChild(etcdele);
        etcdele->setCenterIn("parent");

        HerosItem *userItem = new HerosItem;
        userItem->setWidth(width);
        userItem->setHeight(100);
        FSizeWidgetDelegate *userDele = new FSizeWidgetDelegate(userItem);
        ver->addFixedSizeWidget(userDele);
        fillItem(userItem,rank.m_sortType,rank.m_sortNum,hero);

        ver->layout(true);
    }
}
void HerosPage::startHerosInfo(float dt)
{
    m_serverIface->getAllHeros();
    m_serverIface->getUserAllRank();
}
void HerosPage::init(int dummy)
{
    if(m_itemInit)
        return;
    for(int i = UiMsgEv::HeroLevel;i <= UiMsgEv::HeroLose;i++){
        VerScrollWidget *ver = new VerScrollWidget;
        this->addChild(ver);
        ver->setVerticalScrollPolicy(ScrollShow_Need);
        ver->setHorizontalScrollPolicy(ScrollShow_Never);
        ver->setLeft("parent",uilib::Left);
        ver->setRight("parent",uilib::Right);
        ver->setTop("parent",uilib::Top);
        ver->setTopMargin(20);
        ver->setBottom("parent",uilib::Bottom);
        ver->setVisible(false);
        m_cates.push_back(ver);
    }
    this->layout(true);
    m_itemInit = true;
    m_currIndex = 0;
    m_cates[m_currIndex]->setVisible(true);
    m_title->setSelectIndex(m_currIndex + (int)UiMsgEv::HeroLevel);
}
void HerosPage::onRefreshClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_title->isRefreshing()){
        return;
    }else{
        m_serverIface->getAllHeros();
        m_serverIface->getUserAllRank();
        m_title->setRefreshing(true);
    }
}
void HerosPage::onSortTypeClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data - (int)UiMsgEv::HeroLevel;
    if(m_currIndex == index){
        m_title->setSelectIndex(*(int*)data);
        return;
    }
    m_cates[m_currIndex]->setVisible(false);
    m_cates[index]->setVisible(true);
    m_currIndex = index;
    m_title->setSelectIndex(*(int*)data);
}
void HerosPage::fillItem(BasWidget *parent,int type,int sortnum,const UiMsgEv::HeroInfo &hero)
{
    switch(type){
    case UiMsgEv::HeroLevel:{
        fillLevelItem(parent,sortnum,hero);
        break;
    }
    case UiMsgEv::HeroGold:{
        fillGoldItem(parent,sortnum,hero);
        break;
    }
    case UiMsgEv::HeroPlayed:{
        fillPlayedItem(parent,sortnum,hero);
        break;
    }
    case UiMsgEv::HeroWon:{
        fillWonItem(parent,sortnum,hero);
        break;
    }
    case UiMsgEv::HeroLose:{
        fillLoseItem(parent,sortnum,hero);
        break;
    }
    default:{
        break;
    }
    }
}
void HerosPage::fillLevelItem(BasWidget *parent,int sortnum,const UiMsgEv::HeroInfo &hero)
{
    fillItemSortNum(parent,sortnum,m_id == hero.m_userId);

    std::string name = hero.m_nickName;
    if(name.empty()){
        mailToNickName(hero.m_userMail,name);
    }
    if(name.empty()){
        name = hero.m_userId;
    }
    fillItemPlayerName(parent,name,m_id == hero.m_userId);

    ss.str("");ss << "medal" << hero.m_level << ".png";
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ss.str().data());
    if(frame){
        CCSprite *medal = CCSprite::createWithSpriteFrame(frame);
        FSizeCCNodeDelegate *medalDele = new FSizeCCNodeDelegate(medal);
        parent->addChild(medalDele);
        medalDele->setCenterIn("parent");
        ss.str("");ss << "Level" << hero.m_level;
        CCLabelBMFont *level = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
        FSizeCCNodeDelegate *levelDele = new FSizeCCNodeDelegate(level);
        parent->addChild(levelDele);
        levelDele->setLeft(medalDele->getName(),uilib::Right);
        levelDele->setVertical("parent",0.5);
    }else{
        CCSprite *medal = CCSprite::createWithSpriteFrameName("medal2.png");
        FSizeCCNodeDelegate *medalDele = new FSizeCCNodeDelegate(medal);
        parent->addChild(medalDele);
        medalDele->setCenterIn("parent");
        medalDele->setVisible(false);
        ss.str("");ss << "Level" << hero.m_level;
        CCLabelBMFont *level = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
        FSizeCCNodeDelegate *levelDele = new FSizeCCNodeDelegate(level);
        parent->addChild(levelDele);
        levelDele->setLeft(medalDele->getName(),uilib::Right);
        levelDele->setVertical("parent",0.5);
    }

    float wrate = 1.0 * hero.m_wonNum / hero.m_playedNum;
    int wonrate = (int)(wrate*100);
    fillItemWonRate(parent,wonrate);
}
void HerosPage::fillGoldItem(BasWidget *parent,int sortnum,const UiMsgEv::HeroInfo &hero)
{
    fillItemSortNum(parent,sortnum,m_id == hero.m_userId);

    std::string name = hero.m_nickName;
    if(name.empty()){
        mailToNickName(hero.m_userMail,name);
    }
    if(name.empty()){
        name = hero.m_userId;
    }
    fillItemPlayerName(parent,name,m_id == hero.m_userId);

    std::string goldName;
    PropDef::getVirtualPropsName(PropDef::Props_Gold,goldName);
    goldName += ".png";
    CCSprite *goldSprite = CCSprite::createWithSpriteFrameName(goldName.data());
    FSizeCCNodeDelegate *goldDele = new FSizeCCNodeDelegate(goldSprite,CCSizeMake(40,40));
    parent->addChild(goldDele);
    goldDele->setCenterIn("parent");
    ss.str("");ss << hero.m_propCount;
    CCLabelBMFont *numSprite = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
    FSizeCCNodeDelegate *numDele = new FSizeCCNodeDelegate(numSprite);
    parent->addChild(numDele);
    numDele->setLeftMargin(5);
    numDele->setLeft(goldDele->getName(),uilib::Right);
    numDele->setVertical("parent",0.5);

    float wrate = 1.0 * hero.m_wonNum / hero.m_playedNum;
    int wonrate = (int)(wrate*100);
    fillItemWonRate(parent,wonrate);
}
void HerosPage::fillPlayedItem(BasWidget *parent,int sortnum,const UiMsgEv::HeroInfo &hero)
{
    fillItemSortNum(parent,sortnum,m_id == hero.m_userId);

    std::string name = hero.m_nickName;
    if(name.empty()){
        mailToNickName(hero.m_userMail,name);
    }
    if(name.empty()){
        name = hero.m_userId;
    }
    fillItemPlayerName(parent,name,m_id == hero.m_userId);

    CCSprite *playedSprite = CCSprite::createWithSpriteFrameName("heroplayed.png");
    FSizeCCNodeDelegate *playedDele = new FSizeCCNodeDelegate(playedSprite,CCSizeMake(40,40));
    parent->addChild(playedDele);
    playedDele->setCenterIn("parent");
    ss.str("");ss << hero.m_playedNum;
    CCLabelBMFont *numSprite = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
    FSizeCCNodeDelegate *numDele = new FSizeCCNodeDelegate(numSprite);
    parent->addChild(numDele);
    numDele->setLeft(playedDele->getName(),uilib::Right);
    numDele->setLeftMargin(5);
    numDele->setVertical("parent",0.5);

    float wrate = 1.0 * hero.m_wonNum / hero.m_playedNum;
    int wonrate = (int)(wrate*100);
    fillItemWonRate(parent,wonrate);
}
void HerosPage::fillWonItem(BasWidget *parent,int sortnum,const UiMsgEv::HeroInfo &hero)
{
    fillItemSortNum(parent,sortnum,m_id == hero.m_userId);

    std::string name = hero.m_nickName;
    if(name.empty()){
        mailToNickName(hero.m_userMail,name);
    }
    if(name.empty()){
        name = hero.m_userId;
    }
    fillItemPlayerName(parent,name,m_id == hero.m_userId);

    CCSprite *wonSprite = CCSprite::createWithSpriteFrameName("herowin.png");
    FSizeCCNodeDelegate *wonDele = new FSizeCCNodeDelegate(wonSprite,CCSizeMake(40,40));
    parent->addChild(wonDele);
    wonDele->setCenterIn("parent");
    ss.str("");ss << hero.m_wonNum;
    CCLabelBMFont *numSprite = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
    FSizeCCNodeDelegate *numDele = new FSizeCCNodeDelegate(numSprite);
    parent->addChild(numDele);
    numDele->setLeft(wonDele->getName(),uilib::Right);
    numDele->setLeftMargin(5);
    numDele->setVertical("parent",0.5);

    float wrate = 1.0 * hero.m_wonNum / hero.m_playedNum;
    int wonrate = (int)(wrate*100);
    fillItemWonRate(parent,wonrate);
}
void HerosPage::fillLoseItem(BasWidget *parent,int sortnum,const UiMsgEv::HeroInfo &hero)
{
    fillItemSortNum(parent,sortnum,m_id == hero.m_userId);

    std::string name = hero.m_nickName;
    if(name.empty()){
        mailToNickName(hero.m_userMail,name);
    }
    if(name.empty()){
        name = hero.m_userId;
    }
    fillItemPlayerName(parent,name,m_id == hero.m_userId);

    CCSprite *loseSprite = CCSprite::createWithSpriteFrameName("herolose.png");
    FSizeCCNodeDelegate *loseDele = new FSizeCCNodeDelegate(loseSprite,CCSizeMake(40,40));
    parent->addChild(loseDele);
    loseDele->setCenterIn("parent");
    ss.str("");ss << hero.m_losedNum;
    CCLabelBMFont *numSprite = CCLabelBMFont::create(ss.str().data(),"fonts/uifont24.fnt");
    FSizeCCNodeDelegate *numDele = new FSizeCCNodeDelegate(numSprite);
    parent->addChild(numDele);
    numDele->setLeft(loseDele->getName(),uilib::Right);
    numDele->setLeftMargin(5);
    numDele->setVertical("parent",0.5);

    float wrate = 1.0 * hero.m_wonNum / hero.m_playedNum;
    int wonrate = (int)(wrate*100);
    fillItemWonRate(parent,wonrate);
}
void HerosPage::fillItemSortNum(BasWidget *parent,int sortnum,bool isSelf)
{
    std::stringstream ss;
    ss.str("");ss << sortnum;
    CCLabelBMFont *sortLabel = CCLabelBMFont::create(ss.str().data(),"fonts/uifont35.fnt");
    FSizeCCNodeDelegate *sortDele = new FSizeCCNodeDelegate(sortLabel,CCSizeMake(40,40));
    parent->addChild(sortDele);
    sortDele->setLeft("parent",uilib::Left);
    sortDele->setLeftMargin(15);
    sortDele->setVertical("parent",0.5);
    if(isSelf)
        sortDele->setScale(2);
}
void HerosPage::fillItemPlayerName(BasWidget *parent,const std::string &name,bool isSelf)
{
    CCLabelBMFont *nameFont = CCLabelBMFont::create(name.data(),"fonts/uifont24.fnt");
    if(isSelf)
        nameFont->setColor(ccGREEN);
    FSizeCCNodeDelegate *nameDele = new FSizeCCNodeDelegate(nameFont);
    parent->addChild(nameDele);
    nameDele->setVertical("parent",0.5);
    nameDele->setHorizontal("parent",0.3);
}
void HerosPage::fillItemWonRate(BasWidget *parent,int wonrate)
{
    if(wonrate > 100 || wonrate < 0){
        wonrate = 0;
    }
    ss.str("");ss << wonrate << "%";
    CCLabelBMFont *wonSprite = CCLabelBMFont::create(ss.str().data(),"fonts/uifont35.fnt");
    FSizeCCNodeDelegate *wonDele = new FSizeCCNodeDelegate(wonSprite);
    parent->addChild(wonDele);
    wonDele->setRight("parent",uilib::Right);
    wonDele->setRightMargin(15);
    wonDele->setVertical("parent",0.5);
}
