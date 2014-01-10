#include "chatwidget.h"
#include "roommainwidget.h"
#include "gamecore/sounds/soundmgr.h"

#include "utils/sysutils.h"

ChatWidget::ChatWidget()
{
    m_sendImg = "sendbutton";
    m_inputBox = 0;
    m_sendButton = 0;
    m_facingButton = 0;
    m_phraseButton = 0;
    m_toButton = 0;
    m_toLabel = 0;
    m_toHead = 0;
    m_groupingWidget = 0;
    m_focusIndex = 0;
    m_autoScroll = true;

    m_theme = "default";
    m_themeBg = "";
    m_init = false;
    m_facingDialog = 0;
    m_phraseDialog = 0;
    m_chatType = UiMsgEv::MsgToRoomAll;

    m_headCanClicked = 0;
    m_headListener = 0;
    m_headFunc = 0;
}
ChatWidget::~ChatWidget()
{

}
void ChatWidget::layoutCompleted()
{
    BorderWidget::layoutCompleted();
    if(m_init)
        return;
    m_uiDef = UiThemeMgrProxy::getInstance()->getThemeByName(m_theme);
    initInputBar();
    initGroupingBar();
    initScrollArea();
    m_init = true;
}
void ChatWidget::setChaterInfo(const std::string &id,const std::string &mail,const std::string &nick)
{
    m_userId = id;
    m_userMail = mail;
    m_userNickName = nick;
}
void ChatWidget::setChatType(UiMsgEv::MsgSendObjType type)
{
    m_chatType = type;
}
void ChatWidget::clearChatType()
{
    m_chatType = UiMsgEv::MsgToRoomAll;
}
void ChatWidget::setRecInfo(const std::string &id,const std::string &mail,const std::string &nick)
{
    m_recId = id;
    m_recMail = mail;
    m_recNickName = nick;
}
void ChatWidget::setRecHead(std::string *head)
{
    float bw = 70;
    float bh = 70;
    if(head == 0 || head->size() == 0)
        return;
    if(m_toLabel)
        m_toLabel->setVisible(false);
    if(m_toHead && m_toHead->getParent()){
        m_toHead->removeFromParentAndCleanup(true);
        m_toHead = 0;
    }
    CCImage *img = new CCImage;
    img->initWithImageData((void*)head->c_str(),head->size(),
                           CCImage::kFmtUnKnown);
    CCTexture2D *texture = new CCTexture2D;
    texture->initWithImage(img);
    delete img;
    m_toHead = CCSprite::create();
    m_toHead->initWithTexture(texture);
    CCSize headSize = m_toHead->getContentSize();
    m_toHead->setScaleX(60 / headSize.width);
    m_toHead->setScaleY(60 / headSize.height);
    m_toButton->CCNode::addChild(m_toHead);
    m_toHead->setAnchorPoint(ccp(0.5,0.5));
    m_toHead->setPosition(ccp(bw/2,bh/2));
}
void ChatWidget::clearRecInfo()
{
    m_recId.clear();
    m_recMail.clear();
    m_recNickName.clear();
    onChatToClicked(0,0);
}
void ChatWidget::setMsgGroup(const std::vector<std::string> &groups)
{
    m_msgGroups = groups;
}
void ChatWidget::setSendImg(const std::string &normal,const std::string &pressed)
{
    m_sendImg = normal;
    m_sendPressedImg = pressed;
}
enum ChatInfoType{
    TypeChar = 0,
    TypeUtfChar,
    TypeFacing
};
typedef struct ChatInfoFmt
{
    ChatInfoFmt(int type,const std::string &str){
        m_type = type;
        m_str = str;
    }
    int m_type;
    std::string m_str;
}ChatInfoFmt;
static void chatStringSplit(const std::string &str,std::vector<ChatInfoFmt> &chats)
{
    const char *data = str.c_str();
    int len = strlen(data);
    for(int i = 0;i < len;){
        if(data[i] > 0){
            if(data[i] == '/' && i < (len - 4)){
                if(data[i+1] == ':'){
                    size_t pos = str.find("/",i+1);
                    if(pos != -1 && (pos - i) >= 3){
                        std::string sub = str.substr(i+2,pos-(i+2));
                        if(sub.size() != 0){
                            chats.push_back(ChatInfoFmt(TypeFacing,sub));
                            i = pos + 1;
                            continue;
                        }
                    }
                }
            }
            chats.push_back(ChatInfoFmt(TypeChar,std::string(1,data[i])));
            i++;
        }else{
            int count = 0;
            if(data[i] & 0x80)
                count++;
            if(data[i] & 0x40)
                count++;
            if(data[i] & 0x20)
                count++;
            if(count <= 1){
                chats.push_back(ChatInfoFmt(TypeChar,std::string(1,data[i])));
                i++;
            }else{
                chats.push_back(ChatInfoFmt(TypeUtfChar,std::string(&data[i],count)));
                i += count;
            }
        }
    }
}

static void stringSplit(const std::string &str,std::vector<std::string> &strs)
{
    const char *data = str.c_str();
    int len = strlen(data);
    for(int i = 0;i < len;){
        if(data[i] > 0){
            strs.push_back(std::string(1,data[i]));
            i++;
        }else{
            int count = 0;
            if(data[i] & 0x80)
                count++;
            if(data[i] & 0x40)
                count++;
            if(data[i] & 0x20)
                count++;
            if(count <= 1){
                strs.push_back(std::string(1,data[i]));
                i++;
            }else{
                strs.push_back(std::string(&data[i],count));
                i += count;
            }
        }
    }
}

void ChatWidget::addChatInfo(UiMsgEv::ChatInfo *info,int group)
{
    int type = info->m_chatType;
    if(type == UiMsgEv::MsgToUserPrivate && info->m_revId != m_userId){
        //this is not for me
        return;
    }
    float fontSize = 30;
    float headWidth = 80;
    float rowHeight = 40;
    ccColor3B fHeadCC3,pHeadCC3,fContentCC3,pContentCC3;
    fHeadCC3 = ccGREEN;
    pHeadCC3 = ccWHITE;
    fContentCC3 = ccGREEN;
    pContentCC3 = ccBLUE;

    ccColor3B headColor,contentColor;
    if(type == UiMsgEv::MsgToUserPrivate)
        headColor = fHeadCC3;
    else
        headColor = pHeadCC3;
    if(type == UiMsgEv::MsgToUserPrivate)
        contentColor = fContentCC3;
    else
        contentColor = pContentCC3;
    float singleCharWidth = 16;
    float multiCharWidth = 30;
    float vscrollWidth = 10;
    float faceWidth = 60;
    float faceHeight = 60;

    float scrollWidth,scrollHeight;
    VerScrollWidget *scrollWidget = m_scrollWidgets[group];
    scrollWidget->getAnchorSize(scrollWidth,scrollHeight);
    //16 is for ver scroll bar
    ChatWidgetLayer *layer = new ChatWidgetLayer(scrollWidth - 16);

    std::string head;
    head = info->m_senderNickName;
    if(head.empty()){
        mailToNickName(info->m_senderMail,head);
        if(head.empty())
            head = "Guest";
    }
    head.insert(0,"["); /* blank for text edge */
    head.append("]:");
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
    CCLabelTTF *headLabel = CCLabelTTF::create(head.data(),getSystemFont(),fontSize
                                               ,CCSizeMake(0,rowHeight),kCCTextAlignmentCenter);
#else
    //android if width ==0 && height != 0 lead to crash,fixed in cc 3.0
    CCLabelTTF *headLabel = CCLabelTTF::create(head.data(),getSystemFont(),fontSize
                                               ,CCSizeMake(0,0),kCCTextAlignmentCenter);
#endif
    headLabel->setColor(headColor);
    FSizeLabelDelegate *headDele = new FSizeLabelDelegate(headLabel,
                                   CCSizeMake(headLabel->getTexture()->getContentSize().width,rowHeight));
    layer->setHeadWidget(headDele);
    layer->setHeadWidth(headWidth);
    if(m_headCanClicked){
        headDele->setCanTouch(true);
        headDele->setClickCB(this,callfuncND_selector(ChatWidget::onHeadClicked));
        ChaterInfo *chater = new ChaterInfo;
        chater->m_id = info->m_senderId;
        chater->m_mail = info->m_senderMail;
        chater->m_nick = info->m_senderNickName;
        m_chaterMap.insert(std::make_pair(headDele->getName(),chater));
    }

    std::string content = info->m_chatContent;
    std::vector<ChatInfoFmt> chats;
    chatStringSplit(content,chats);
    std::string labelcontent;
    //need detract ver scroll width
    scrollWidth -= vscrollWidth;
    float spaceLeft = scrollWidth - headLabel->getTexture()->getContentSize().width;
    for(unsigned int i = 0;i < chats.size();i++){
        ChatInfoFmt &info = chats[i];
        if(info.m_type == TypeChar){
            if((spaceLeft - singleCharWidth) > 0){
                labelcontent.append(info.m_str);
                spaceLeft -= singleCharWidth;
            }else{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
                CCLabelTTF *cLabel = CCLabelTTF::create(labelcontent.data(),getSystemFont(),fontSize,
                                                        CCSizeMake(0,rowHeight),kCCTextAlignmentCenter);
#else
                CCLabelTTF *cLabel = CCLabelTTF::create(labelcontent.data(),getSystemFont(),fontSize,
                                                        CCSizeMake(0,0),kCCTextAlignmentCenter);
#endif
                cLabel->setColor(contentColor);
                FSizeLabelDelegate *deleLabel = new FSizeLabelDelegate(cLabel,cLabel->getTexture()->getContentSize());
                layer->addContentWidget(deleLabel);
                spaceLeft = scrollWidth - headWidth;
                labelcontent.clear();
            }
        }else if(info.m_type == TypeUtfChar){
            if((spaceLeft - multiCharWidth) > 0){
                labelcontent.append(info.m_str);
                spaceLeft -= multiCharWidth;
            }else{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
                CCLabelTTF *cLabel = CCLabelTTF::create(labelcontent.data(),getSystemFont(),fontSize,
                                                        CCSizeMake(0,rowHeight),kCCTextAlignmentCenter);
#else
                CCLabelTTF *cLabel = CCLabelTTF::create(labelcontent.data(),getSystemFont(),fontSize,
                                                        CCSizeMake(0,0),kCCTextAlignmentCenter);
#endif
                cLabel->setColor(contentColor);
                FSizeLabelDelegate *deleLabel = new FSizeLabelDelegate(cLabel,cLabel->getTexture()->getContentSize());
                layer->addContentWidget(deleLabel);
                spaceLeft = scrollWidth - headWidth;
                labelcontent.clear();
            }
        }else if(info.m_type == TypeFacing){
            if(!labelcontent.empty()){
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
                CCLabelTTF *cLabel = CCLabelTTF::create(labelcontent.data(),getSystemFont(),fontSize,
                                                        CCSizeMake(0,rowHeight),kCCTextAlignmentCenter);
#else
                CCLabelTTF *cLabel = CCLabelTTF::create(labelcontent.data(),getSystemFont(),fontSize,
                                                        CCSizeMake(0,0),kCCTextAlignmentCenter);
#endif
                cLabel->setColor(contentColor);
                FSizeLabelDelegate *deleLabel = new FSizeLabelDelegate(cLabel,cLabel->getTexture()->getContentSize());
                layer->addContentWidget(deleLabel);
                spaceLeft -= cLabel->getTexture()->getContentSize().width;
                labelcontent.clear();
            }
            std::string animName,firstFrame;
            animName = info.m_str;
            firstFrame = animName;
            ResourceMgr::getInstance()->getFrameSpriteFirstFrame(firstFrame);
            if(firstFrame.empty())
                continue;
            BasAnimSprite *animSprite = new BasAnimSprite(animName,firstFrame);
            animSprite->start();
            FSizeSpriteDelegate *faceDele = new FSizeSpriteDelegate(animSprite,CCSizeMake(faceWidth,faceHeight));
            layer->addContentWidget(faceDele);
            if((spaceLeft - faceWidth) > 0){
                spaceLeft -= faceWidth;
            }else{
                spaceLeft = scrollWidth - headWidth;
            }
        }
    }
    if(!labelcontent.empty()){
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
        CCLabelTTF *cLabel = CCLabelTTF::create(labelcontent.data(),getSystemFont(),fontSize,
                                                CCSizeMake(0,rowHeight),kCCTextAlignmentCenter);
#else
        CCLabelTTF *cLabel = CCLabelTTF::create(labelcontent.data(),getSystemFont(),fontSize,
                                                CCSizeMake(0,0),kCCTextAlignmentCenter);
#endif
        cLabel->setColor(contentColor);
        FSizeLabelDelegate *deleLabel = new FSizeLabelDelegate(cLabel,cLabel->getTexture()->getContentSize());
        layer->addContentWidget(deleLabel);
    }

    layer->exec();
    scrollWidget->addFixedSizeWidget(layer);
    scrollWidget->layout(true);
    if(m_autoScroll)
        scrollWidget->scrollToEnd(true);
}
void ChatWidget::clearAllChatInfo()
{

}
void ChatWidget::setHeadCanClick(bool can)
{
    m_headCanClicked = can;
}
void ChatWidget::setHeadClickCB(CCNode *listener,SEL_CallFuncND func)
{
    m_headListener = listener;
    m_headFunc = func;
}
void ChatWidget::getHeadInfo(std::string &id,std::string &mail,std::string &nick,CCPoint &pos)
{
    if(m_headName.empty())
        return;
    std::map<std::string,ChaterInfo*>::iterator iter;
    iter = m_chaterMap.find(m_headName);
    if(iter == m_chaterMap.end())
        return;
    ChaterInfo *info = iter->second;
    id = info->m_id;
    mail = info->m_mail;
    nick = info->m_nick;
    pos = m_headWorldPos;
}
void ChatWidget::setChatBoxVisible(bool visible)
{
    m_inputBox->setVisible(visible);
}
void ChatWidget::initInputBar()
{
    float bw = 100;
    float bh = 70;
    if(1){
        //send button
        m_sendButton = new BasButton;
        m_sendButton->setButtonInfo("",m_theme
                                    ,m_sendImg,CCSizeMake(bw,bh),m_sendPressedImg);
        this->addChild(m_sendButton);
        m_sendButton->setRight("parent",uilib::Right);
        m_sendButton->setBottom("parent",uilib::Bottom);
        m_sendButton->setMargins(2);
        m_sendButton->setClickCB(this,callfuncND_selector(ChatWidget::onSendButtonClicked));
    }
    if(1){
        //facing button
        m_facingButton = new BasButton;
        m_facingButton->setButtonInfo("",m_theme,"chatface",CCSizeMake(bh,bh));
        this->addChild(m_facingButton);
        m_facingButton->setMargins(2);
        m_facingButton->setBottom("parent",uilib::Bottom);
        m_facingButton->setRight(m_sendButton->getName(),uilib::Left);
        m_facingButton->setClickCB(this,callfuncND_selector(ChatWidget::onFacingClicked));
    }
    if(1){
        //phrase button
        m_phraseButton = new BasButton;
        m_phraseButton->setButtonInfo("",m_theme,"chatuparrow",CCSizeMake(bh,bh));
        this->addChild(m_phraseButton);
        m_phraseButton->setMargins(2);
        m_phraseButton->setBottom("parent",uilib::Bottom);
        m_phraseButton->setRight(m_facingButton->getName(),uilib::Left);
        m_phraseButton->setClickCB(this,callfuncND_selector(ChatWidget::onPhraseClicked));
    }
    if(1){
        //chat to button
        m_toButton = new BasButton;
        m_toButton->setButtonInfo("",m_theme,"chatto",CCSizeMake(bh,bh));
        this->addChild(m_toButton);
        m_toButton->setMargins(2);
        m_toButton->setBottom("parent",uilib::Bottom);
        m_toButton->setLeft("parent",uilib::Left);
        m_toButton->setClickCB(this,callfuncND_selector(ChatWidget::onChatToClicked));
    }
    if(1){
        //init input
        m_inputBox = new InputBox;
        m_inputBox->setTheme(m_theme,"inputbg");
        m_inputBox->setMaxLength(50);
        this->addChild(m_inputBox);
        m_inputBox->setMargins(2);
        m_inputBox->setMaxHeightRefSize(m_sendButton->getName(),1.0);
        m_inputBox->setMinHeightRefSize(m_sendButton->getName(),1.0);
        m_inputBox->setLeft(m_toButton->getName(),uilib::Right);
        m_inputBox->setBottom("parent",uilib::Bottom);
        m_inputBox->setRight(m_phraseButton->getName(),uilib::Left);
        m_inputBox->setOnReturned(this, callfuncN_selector(ChatWidget::onInputBoxReturned));
    }
}
void ChatWidget::initGroupingBar()
{
    /* no showing when only 1 grouping */
    if(m_msgGroups.size() < 2)
        return;
    m_groupingWidget = new BasWidget;
    float wh = 40;
    float bw = m_anchorWidth / m_msgGroups.size();
    this->addChild(m_groupingWidget);
    m_groupingWidget->setLeft("parent",uilib::Left);
    m_groupingWidget->setRight("parent",uilib::Right);
    m_groupingWidget->setTop("parent",uilib::Top);
    m_groupingWidget->setHeight(wh);
    std::string leftName;
    for(unsigned int i = 0;i < m_msgGroups.size();i++){
        BasButton *button = new BasButton;
        button->setButtonIndex(i);
        button->setButtonInfo(m_msgGroups[i],"","",CCSizeMake(bw,wh));
        button->setWidth(bw);
        m_groupingWidget->addChild(button);
        button->setVertical("parent",0.5);
        if(leftName.empty())
            button->setLeft("parent",uilib::Left);
        else
            button->setLeft(leftName,uilib::Right);
        leftName = button->getName();
        button->setClickCB(this,callfuncND_selector(ChatWidget::onGroupingButtonsClicked));
    }
}
void ChatWidget::initScrollArea()
{
    if(m_msgGroups.size() < 2){
        VerScrollWidget *scroll = new VerScrollWidget;
        scroll->setSpacing(4);
        m_scrollWidgets.push_back(scroll);
        this->addChild(scroll);
        scroll->setMargins(2);
        scroll->setLeftMargin(6);
        scroll->setRightMargin(6);
        scroll->setLeft("parent",uilib::Left);
        scroll->setRight("parent",uilib::Right);
        scroll->setBottom(m_sendButton->getName(),uilib::Top);
        //scroll->setVerticalScrollPolicy(uilib::ScrollShow_Never);
        scroll->setHorizontalScrollPolicy(uilib::ScrollShow_Never);
        if(m_groupingWidget)
            scroll->setTop(m_groupingWidget->getName(),uilib::Bottom);
        else
            scroll->setTop("parent",uilib::Top);
    }else{
        for(unsigned int i = 0;i < m_msgGroups.size();i++){
            VerScrollWidget *scroll = new VerScrollWidget;
            scroll->setSpacing(4);
            m_scrollWidgets.push_back(scroll);
            this->addChild(scroll);
            scroll->setMargins(2);
            scroll->setLeftMargin(6);
            scroll->setRightMargin(6);
            scroll->setLeft("parent",uilib::Left);
            scroll->setRight("parent",uilib::Right);
            scroll->setBottom(m_sendButton->getName(),uilib::Top);
            //scroll->setVerticalScrollPolicy(uilib::ScrollShow_Never);
            scroll->setHorizontalScrollPolicy(uilib::ScrollShow_Never);
            if(m_groupingWidget)
                scroll->setTop(m_groupingWidget->getName(),uilib::Bottom);
            else
                scroll->setTop("parent",uilib::Top);
        }
    }
    for(unsigned int i = 1;i < m_scrollWidgets.size();i++){
        m_scrollWidgets[i]->setVisible(false);
        m_scrollWidgets[i]->setEnabled(false);
    }
}
void ChatWidget::onInputBoxReturned(CCNode *sender)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    std::string text = m_inputBox->getText();
    if(text.empty())
        return;
    m_inputBox->setText("");
    sendChatInfo(text);
    
    UiMsgEv::ChatInfo info;
    info.m_chatType = m_chatType;
    info.m_senderId = m_userId;
    info.m_senderMail = m_userMail;
    info.m_senderNickName = m_userNickName;
    info.m_revId = m_recId;
    info.m_revMail = m_recMail;
    info.m_revNickName = m_recNickName;
    info.m_chatContent = text;
    addChatInfo(&info,m_focusIndex);
}
void ChatWidget::onSendButtonClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    std::string text = m_inputBox->getText();
    if(text.empty())
        return;
    m_inputBox->setText("");
    sendChatInfo(text);

    UiMsgEv::ChatInfo info;
    info.m_chatType = m_chatType;
    info.m_senderId = m_userId;
    info.m_senderMail = m_userMail;
    info.m_senderNickName = m_userNickName;
    info.m_revId = m_recId;
    info.m_revMail = m_recMail;
    info.m_revNickName = m_recNickName;
    info.m_chatContent = text;
    addChatInfo(&info,m_focusIndex);
}
void ChatWidget::onFacingClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_facingDialog == 0){
        float fw,fh;
        m_facingButton->getAnchorSize(fw,fh);
        m_facingDialog = new ChatFacingDialog(this,ccp(fw,fh));
        m_facingDialog->setFacingClickCB(this,callfuncND_selector(ChatWidget::onFacingDialogFaceClicked));
    }
    m_facingDialog->show();
}
void ChatWidget::onPhraseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_phraseDialog == 0){
        float fw,fh;
        m_phraseButton->getAnchorSize(fw,fh);
        m_phraseDialog = new ChatPhraseDialog(this,ccp(fw,fh));
        m_phraseDialog->setPhraseClickCB(this,callfuncND_selector(ChatWidget::onPhraseDialogPhraseClicked));
    }
    m_phraseDialog->show();
}
void ChatWidget::onChatToClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(m_toHead == 0){
        return;
    }else if(m_toHead && m_toHead->getParent()){
        m_toHead->removeFromParentAndCleanup(true);
        m_toHead = 0;
    }
    if(m_toLabel)
        m_toLabel->setVisible(true);
}
void ChatWidget::onGroupingButtonsClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    int index = *(int*)data;
    if(index == m_focusIndex)
        return;
    m_scrollWidgets[m_focusIndex]->setVisible(false);
    m_scrollWidgets[m_focusIndex]->setEnabled(false);
    m_scrollWidgets[index]->setVisible(false);
    m_scrollWidgets[index]->setEnabled(false);
    m_focusIndex = index;
}
void ChatWidget::onFacingDialogFaceClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    std::string face;
    m_facingDialog->getUserClickedFacing(face);
    m_facingDialog->hide();
    if(!face.empty()){
        face.insert(0,"/:");
        face.append("/");
        m_inputBox->appendText(face);
    }
}
void ChatWidget::onPhraseDialogPhraseClicked(CCNode *node,void *data)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    std::string phrase;
    m_phraseDialog->getUserClickedPhrase(phrase);
    m_phraseDialog->hide();
    if(!phrase.empty()){
        sendChatInfo(phrase);
        UiMsgEv::ChatInfo info;
        info.m_chatType = m_chatType;
        info.m_senderId = m_userId;
        info.m_senderMail = m_userMail;
        info.m_senderNickName = m_userNickName;
        info.m_revId = m_recId;
        info.m_revMail = m_recMail;
        info.m_revNickName = m_recNickName;
        info.m_chatContent = phrase;
        addChatInfo(&info,m_focusIndex);
    }
}
void ChatWidget::sendChatInfo(const std::string &chat)
{
    switch(m_chatType){
    case UiMsgEv::MsgToUser:
    {
        break;
    }
    case UiMsgEv::MsgToUserPublic:
    {
        break;
    }
    case UiMsgEv::MsgToUserPrivate:
    {
        break;
    }
    case UiMsgEv::MsgToRoomAll:
    {
        ServerInterface::getInstance()->sendMail("","",chat,UiMsgEv::MsgToRoomAll);
        break;
    }
    case UiMsgEv::MsgToHallAll:
    {
        ServerInterface::getInstance()->sendMail("","",chat,UiMsgEv::MsgToHallAll);
        break;
    }
    default:{
        break;
    }
    }
}
void ChatWidget::onHeadClicked(CCNode *node,void *data)
{
    FSizeLabelDelegate *dele = dynamic_cast<FSizeLabelDelegate*>(node);
    if(dele){
        m_headName = dele->getName();
        float width,height;
        dele->getAnchorSize(width,height);
        m_headWorldPos = dele->convertToWorldSpace(ccp(width/2,height/2));
        VerScrollWidget *scrollWidget = m_scrollWidgets[m_focusIndex];
        if (scrollWidget->containClickPosition(m_headWorldPos.x, m_headWorldPos.y)) {
            SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
            if(m_headListener && m_headFunc)
                (m_headListener->*m_headFunc)(this,0);
        }
    }
}
