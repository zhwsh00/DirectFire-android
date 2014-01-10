#include "frienditem.h"
#include "friendspage.h"
#include "sendgiftdialog.h"
#include "sendmsgdialog.h"
#include "delfrienddialog.h"
#include "sendmsganim.h"

#include "utils/sysutils.h"
#include "prop/propdef.h"

#include "resource/resourcemgr.h"
#include "gamecore/serverinterface.h"
#include "sounds/soundmgr.h"

FriendItem::FriendItem(FriendsPage *owner)
{
    m_owner = owner;
    m_theme = "default";
    m_themeBg = "propbg";
    m_info = 0;
    m_id = -1;
    m_init = false;
    m_headSprite = 0;
    m_headWidget = 0;
    m_wonShow = 0;
    m_propWidget = 0;
    m_infoWidget = 0;
    m_onlineWidget = 0;
    m_online = false;
    m_sendGiftDialog = 0;
    m_sendMsgDialog = 0;
    m_delFriendDialog = 0;
}

FriendItem::~FriendItem()
{

}

void FriendItem::setItemInfo(UiMsgEv::PlayerInfoEv *ev)
{
    m_info = ev;
}

void FriendItem::setHeadPortrait(const std::string &head)
{
    m_headPortrait = head;
}
void FriendItem::createFriendHead()
{
    UiThemeDef *def = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    if(!m_init){
        m_headSprite = CCSprite::create();
        if(!m_headPortrait.empty()){
            CCImage *img = new CCImage;
            img->initWithImageData((void*)m_headPortrait.c_str(),m_headPortrait.size(),
                                   CCImage::kFmtUnKnown);
            CCTexture2D *texture = new CCTexture2D;
            texture->initWithImage(img);
            delete img;
            m_headSprite->initWithTexture(texture);
        }else{
            std::string img;
            def->getNormalData()->getImg("portraitdefault",img);
            m_headSprite->initWithSpriteFrameName(img.data());
        }
        BasNodeDelegateWidget *headWidget = new BasNodeDelegateWidget(m_headSprite,CCSizeMake(76,76));
        headWidget->setCanTouch(true);
        headWidget->setClickCB(this,callfuncND_selector(FriendItem::onHeadClicked));
        this->addChild(headWidget);
        headWidget->setVertical("parent",0.5);
        headWidget->setLeft("parent",uilib::Left);
        headWidget->setLeftMargin(15);

        m_headWidget = headWidget;
    }else{
        CCImage *img = new CCImage;
        img->initWithImageData((void*)m_headPortrait.c_str(),m_headPortrait.size(),
                               CCImage::kFmtUnKnown);
        CCTexture2D *texture = new CCTexture2D;
        texture->initWithImage(img);
        delete img;
        m_headSprite->initWithTexture(texture);
        CCSize size = m_headSprite->getContentSize();
        m_headSprite->setScaleX(76 / size.width);
        m_headSprite->setSkewY(76 / size.height);
    }
}
void FriendItem::createFriendInfo()
{
    if(m_info == 0)
        return;
    createWonNum();
    createProps();
    createProperty();
    createOnline();
}
void FriendItem::createProperty()
{
    bool needlay = false;
    if(m_infoWidget == 0){
        m_infoWidget = new HorScrollWidget;
        this->addChild(m_infoWidget);
        m_infoWidget->setVerticalScrollPolicy(ScrollShow_Never);
        m_infoWidget->setHorizontalScrollPolicy(ScrollShow_Never);
        m_infoWidget->setLeft(m_headWidget->getName(),uilib::Right);
        m_infoWidget->setLeftMargin(10);
        m_infoWidget->setRight("parent",uilib::Right);
        m_infoWidget->setRightMargin(20);
        if(m_wonShow)
            m_infoWidget->setTop(m_wonShow->getName(),uilib::Bottom);
        else
            m_infoWidget->setTop("parent",uilib::Top);

        if(m_propWidget)
            m_infoWidget->setBottom(m_propWidget->getName(),uilib::Top);
        else
            m_infoWidget->setTop("parent",uilib::Bottom);
    }else{
        needlay = true;
        m_infoWidget->delAllChild();
    }
    if(1){
        std::string name = m_info->m_nickName;
        if(name.empty())
            mailToNickName(m_info->m_userMail,name);
        if(name.empty())
            name = m_info->m_userId;
        if(name.empty())
            name = "no name";
        name += "  ";
        CCLabelBMFont *nameFont = CCLabelBMFont::create(name.data(),"fonts/uifont24.fnt");
        FSizeCCNodeDelegate *nameDele = new FSizeCCNodeDelegate(nameFont);
        m_infoWidget->addFixedSizeWidget(nameDele);
    }
    if(1){
        std::string name = "Lev:";
        std::stringstream ss;
        ss << m_info->m_level;
        name.append(ss.str());
        CCLabelBMFont *nameFont = CCLabelBMFont::create(name.data(),"fonts/uifont24.fnt");

        FSizeCCNodeDelegate *nameDele = new FSizeCCNodeDelegate(nameFont);
        m_infoWidget->addFixedSizeWidget(nameDele);
    }
    do{
        std::string name = m_info->m_creditName;
        if(name.empty())
            break;
        CCLabelBMFont *nameFont = CCLabelBMFont::create(name.data(),"fonts/uifont24.fnt");

        FSizeCCNodeDelegate *nameDele = new FSizeCCNodeDelegate(nameFont);
        m_infoWidget->addFixedSizeWidget(nameDele);
    }while(0);
    if(needlay)
        m_infoWidget->layout(true);
}
void FriendItem::createWonNum()
{
    m_won = m_info->m_wonNum;
    m_lost = m_info->m_losedNum;
    m_offline = m_info->m_offlineNum;
    m_escape = m_info->m_escapeNum;
    if(m_wonShow == 0){
        //won,lost... show
        m_wonShow = new WonGameShow();
        std::vector<std::string> fgs;
        std::vector<float> rates;
        fgs.push_back("redhbar");
        fgs.push_back("bluehbar");
        fgs.push_back("greenhbar");
        fgs.push_back("grayhbar");
        float sum = m_won + m_lost + m_offline + m_escape;
        if(sum != 0){
            rates.push_back(m_won / sum);
            rates.push_back(m_lost / sum);
            rates.push_back(m_offline / sum);
            rates.push_back(m_escape / sum);
        }else{
            rates.push_back(0.25);
            rates.push_back(0.25);
            rates.push_back(0.25);
            rates.push_back(0.25);
        }
        for(unsigned i = 0;i < fgs.size();i++){
            WonGameShow::WonBarDef *def = new WonGameShow::WonBarDef;
            def->m_barBg = "hbarcolorbg";
            def->m_barFg =fgs[i];
            def->m_percent = rates[i];
            m_wonShow->addWonBarDef(def);
        }
        this->addChild(m_wonShow);
        if(m_headWidget)
            m_wonShow->setLeft(m_headWidget->getName(),uilib::Right);
        else
            m_wonShow->setLeft("parent",uilib::Left);
        m_wonShow->setTop("parent",uilib::Top);
        m_wonShow->setTopMargin(2);
        m_wonShow->setHeight(10);
        m_wonShow->setSkinFillVer(true);
        m_wonShow->setMinWidthRefSize("parent",0.6);
        m_wonShow->setMaxWidthRefSize("parent",0.6);
    }else{
        std::vector<float> rates;
        float sum = m_won + m_lost + m_offline + m_escape;
        if(sum != 0){
            rates.push_back(m_won / sum);
            rates.push_back(m_lost / sum);
            rates.push_back(m_offline / sum);
            rates.push_back(m_escape / sum);
        }else{
            rates.push_back(0.25);
            rates.push_back(0.25);
            rates.push_back(0.25);
            rates.push_back(0.25);
        }
        m_wonShow->resetWonBarLen(rates);
    }
}
void FriendItem::createProps()
{
    bool propNeedLay = false;
    if(m_propWidget != 0){
        propNeedLay = true;
        m_propWidget->delAllChild();
    }else{
        m_propWidget = new HorScrollWidget;
        m_propWidget->setVerticalScrollPolicy(ScrollShow_Never);
        m_propWidget->setHorizontalScrollPolicy(ScrollShow_Never);
        this->addChild(m_propWidget);
        m_propWidget->setLeft(m_headWidget->getName(),uilib::Right);
        m_propWidget->setRight("parent",uilib::Right);
        m_propWidget->setBottom("parent",uilib::Bottom);
        m_propWidget->setHeight(42);
    }
    float w = 42;
    float h = 42;
    CCSize psize = CCSizeMake(w,h);
    for(unsigned int i = 0;i < m_hasProps.size();i++){
        std::string imgname;
        PropDef::getVirtualPropsName(m_hasProps[i].m_id,imgname);
        if(imgname.empty())
            continue;
        imgname += ".png";
        CCSprite *imgsprite = CCSprite::create();
        imgsprite->initWithSpriteFrameName(imgname.data());
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(imgsprite,psize);
        FSizeWidgetDelegate *fdele = new FSizeWidgetDelegate(dele,psize);
        m_propWidget->addFixedSizeWidget(fdele);
    }
    if(propNeedLay)
        m_propWidget->layout(true);
}
void FriendItem::createOnline()
{
    if(m_onlineWidget == 0){
        UiThemeDef *uidef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
        std::string oname;
        uidef->getNormalData()->getImg("playerol",oname);
        if(oname.empty())
            return;
        CCSprite *osprite = CCSprite::create();
        osprite->initWithSpriteFrameName(oname.data());
        BasNodeDelegateWidget *dele = new BasNodeDelegateWidget(osprite);
        this->addChild(dele);
        dele->setRight("parent",uilib::Right);
        dele->setTop("parent",uilib::Top);
        m_onlineWidget = dele;
    }
    m_onlineWidget->setVisible(m_online);
}
void FriendItem::createPlayingGame()
{

}
void FriendItem::onHeadClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    TouchNode *root = m_owner;
    CCPoint pos = root->convertToNodeSpace(*(CCPoint*)data);
    LangDef *lang = ResourceMgr::getInstance()->getLangDef();
    PopButtonsDialog *pop = new PopButtonsDialog(root,pos);
    pop->setButtonCB(this,callfuncND_selector(FriendItem::onPopButtonsClicked));

    pop->addButton(lang->getStringById(StringEnum::SendMsg));
    pop->addButton(lang->getStringById(StringEnum::SendGift));
    pop->addButton(lang->getStringById(StringEnum::DelFriend));
    pop->setSpacing(10);
    pop->setEdgeSize(20);
    pop->exec();
}
void FriendItem::onPropClicked(CCNode *node,void *data)
{

}
void FriendItem::onInfoClicked(CCNode *node,void *data)
{

}
void FriendItem::clearProp()
{
    m_hasProps.clear();
}
void FriendItem::addProp(int id,int count)
{
    m_hasProps.push_back(UiMsgEv::GiftPropEv(id,count));
}
void FriendItem::finish()
{
    if(!m_init){
        createFriendHead();
        createFriendInfo();
    }else{
        createFriendHead();
        createFriendInfo();
    }
    m_init = true;
}
void FriendItem::updateProp()
{
    createProps();
}
void FriendItem::updateFriendHead(const std::string &head)
{
    m_headPortrait = head;
    createFriendHead();
}
void FriendItem::updateWonNum(UiMsgEv::PlayerInfoEv *ev)
{
    m_info = ev;
    createWonNum();
}
void FriendItem::updateProperty(UiMsgEv::PlayerInfoEv *ev)
{
    m_info = ev;
    createProperty();
}
void FriendItem::updateOnline(bool on)
{
    m_online = on;
    createOnline();
}
void FriendItem::updatePlayingGame(const std::string &name,const std::string &icon)
{

}
void FriendItem::onPopButtonsClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data;
    switch(index){
    case 0:{
        onSendMsgClicked();
        break;
    }
    case 1:{
        onSendGiftClicked();
        break;
    }
    case 2:{
        onDelFriendClicked();
        break;
    }
    default:{
        break;
    }
    }
}
void FriendItem::onSendMsgClicked()
{
    if(m_sendMsgDialog != 0){
        m_sendMsgDialog->destroy();
        m_sendMsgDialog = 0;
    }
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_sendMsgDialog == 0){
        m_sendMsgDialog = new SendMsgDialog(root,ccc4(0,0,0,128));
        m_sendMsgDialog->setCloseCB(this,callfuncND_selector(FriendItem::onSendMsgCloseClicked));
        m_sendMsgDialog->setSendCB(this,callfuncND_selector(FriendItem::onSendMsgSendClicked));
        m_sendMsgDialog->setInitShowPage(true);
        m_sendMsgDialog->setInitPage(true,false);
        std::string name = m_info->m_nickName;
        if(name.empty())
            mailToNickName(m_info->m_userMail,name);
        m_sendMsgDialog->setRecInfo(m_info->m_userId,name,m_headPortrait);
        m_sendMsgDialog->exec();
    }
}
void FriendItem::onSendGiftClicked()
{
    if(m_sendGiftDialog != 0){
        m_sendGiftDialog->destroy();
        m_sendGiftDialog = 0;
    }
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_sendGiftDialog == 0){
        m_sendGiftDialog = new SendGiftDialog(root,ccc4(0,0,0,128));
        m_sendGiftDialog->setCloseCB(this,callfuncND_selector(FriendItem::onSendGiftCloseClicked));
        m_sendGiftDialog->setSendCB(this,callfuncND_selector(FriendItem::onSendGiftSendClicked));
        std::string name = m_info->m_nickName;
        if(name.empty())
            mailToNickName(m_info->m_userMail,name);
        if(m_headPortrait.empty())
            m_sendGiftDialog->setSendtoInfo(name,"");
        else
            m_sendGiftDialog->setSendtoInfo(name,m_headPortrait);

        std::vector<UiMsgEv::GiftPropEv> props;
        ServerInterface *serverIface = ServerInterface::getInstance();
        std::string id = serverIface->getLoginAccountInfo()->m_id;
        serverIface->getAllUnzeroProps(id,props);
        std::sort(props.begin(),props.end(),prop_sortbyId);
        for(unsigned int i = 0;i < props.size();i++){
            if (PropDef::propCanPresentAble(props[i].m_id)) {
                m_sendGiftDialog->addProp(props[i].m_id,props[i].m_count);
            }
        }
        m_sendGiftDialog->exec();
    }
}
void FriendItem::onDelFriendClicked()
{
    if(m_delFriendDialog != 0){
        m_delFriendDialog->destroy();
        m_delFriendDialog = 0;
    }
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_delFriendDialog == 0){
        m_delFriendDialog = new DelFriendDialog(root,ccc4(0,0,0,128));
        m_delFriendDialog->setCloseCB(this,callfuncND_selector(FriendItem::onDelFriendCloseClicked));
        m_delFriendDialog->setOkCB(this,callfuncND_selector(FriendItem::onDelFriendDelClicked));
        std::string name = m_info->m_nickName;
        if(name.empty())
            mailToNickName(m_info->m_userMail,name);
        m_delFriendDialog->setDelInfo(m_info->m_userId,name,m_headPortrait);
        m_delFriendDialog->exec();
    }
}
void FriendItem::onSendGiftCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_sendGiftDialog){
        m_sendGiftDialog->destroy();
        m_sendGiftDialog = 0;
    }
}
void FriendItem::onSendGiftSendClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    std::vector<UiMsgEv::GiftPropEv> gifts;
    std::string word;
    if(m_sendGiftDialog){
        m_sendGiftDialog->getSendProp(gifts,word);
        m_sendGiftDialog->destroy();
        m_sendGiftDialog = 0;
        if(word.empty() && gifts.size() == 0)
            return;
        ServerInterface::getInstance()->sendGift(m_info->m_userId,word,gifts);
        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        SendMsgAnim *anim = new SendMsgAnim(root,ccp(winSize.width / 2,winSize.height / 2));
        anim->setTheme(m_theme,"uigiftsending");
        anim->exec();
    }
}
void FriendItem::onSendMsgCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_sendMsgDialog){
        m_sendMsgDialog->destroy();
        m_sendMsgDialog = 0;
    }
}
void FriendItem::onSendMsgSendClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_sendMsgDialog){
        std::string title,word;
        m_sendMsgDialog->getSendMsg(title,word);
        m_sendMsgDialog->destroy();
        m_sendMsgDialog = 0;
        if(word.size() != 0){
            ServerInterface::getInstance()->sendMail(m_info->m_userId,title,word);
            CCNode *root = this->getParent();
            while(root->getParent())
                root = root->getParent();
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            SendMsgAnim *anim = new SendMsgAnim(root,ccp(winSize.width / 2,winSize.height / 2));
            anim->exec();
        }
    }
}
void FriendItem::onDelFriendCloseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_delFriendDialog != 0){
        m_delFriendDialog->destroy();
        m_delFriendDialog = 0;
    }
}
void FriendItem::onDelFriendDelClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_delFriendDialog != 0){
        m_delFriendDialog->destroy();
        m_delFriendDialog = 0;
    }
    ServerInterface::getInstance()->delFriend(m_info->m_userId);
    m_owner->deleteItem(this);
}
