#include "roomscene.h"
#include "roomlayer.h"
#include "gamecore/gamecore/gameboard.h"
#include "gamecore/serverinterface.h"

#include "cliententry/uimsgevent.h"
#include "cliententry/uimsghandler.h"

static GameBoard *m_gameBoard = 0;
RoomScene::RoomScene()
{
    m_roomLayer = 0;
    ServerInterface::getInstance()->setStartEvCB(this,callfuncND_selector(RoomScene::serverListener));
}
RoomScene::~RoomScene()
{
    if(m_gameBoard){
        m_gameBoard->removeFromParent();
    }
    ServerInterface::getInstance()->setStartEvCB(0,0);
}
bool RoomScene::init()
{
    bool ret = false;
    do {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
#ifdef LINUX
        size = CCEGLView::sharedOpenGLView()->getFrameSize();
#endif
        CC_BREAK_IF(!CCScene::init());        
        m_roomLayer = RoomLayer::create();
        this->addChild(m_roomLayer,-1);
        if(m_gameBoard == 0){
            m_gameBoard = GameBoard::create();
            m_gameBoard->retain();
            this->addChild(m_gameBoard,0);
            m_gameBoard->setVisible(false);
            m_gameBoard->setGamePlayType(GameType::MultiOnline);
            m_gameBoard->setGameNetworkType(GameType::BattleNet);
        }else{
            this->addChild(m_gameBoard,0);
            m_gameBoard->setVisible(false);
        }
        if(1){
            float width,height;
            /* this will read from map info */
            UiMsgEv::RoomInfoEv *ev = ServerInterface::getInstance()->getRoomInfo();
            width = ev->m_mapWidth;
            height = ev->m_mapHeight;
            float vrate = width / height;
            float rrate = size.width / size.height;
            float rate;
            float x = 0,y = 0;
            if(fabs(vrate - rrate) < 0.001){
                rate = size.width / width;
            }else if(vrate > rrate){
                rate = size.width / width;
                x = 0;
                y = (size.height - size.width / vrate) / 2;
            }else if(vrate < rrate){
                rate = size.height / height;
                y = 0;
                x = (size.width - vrate * size.height) / 2;
            }else{
                rate = size.width / width;
            }
            m_gameBoard->setContentSize(CCSizeMake(width,height));
            m_gameBoard->setScale(rate);
            m_gameBoard->setAnchorPoint(ccp(0,0));
            m_gameBoard->setPosition(ccp(x,y));
            m_gameBoard->setMapOffset(ccp(x,y),rate);
        }
        ret = true;
    } while (0);
    return ret;
}
void RoomScene::switchToGamePage()
{
    //FIXME: remove mapboard backgroud for improve fps
    m_roomLayer->setVisible(false);
    m_roomLayer->setEnable(false);
    m_gameBoard->setVisible(true);
    CCFadeIn *fade = CCFadeIn::create(0.5);
    m_gameBoard->runAction(fade);
}
void RoomScene::switchToRoomPage()
{
    // restore fps
    CCDirector::sharedDirector()->setAnimationInterval(1.0/30.0);
    m_gameBoard->stopGame();
    m_gameBoard->setVisible(false);
    m_roomLayer->setVisible(true);
    m_roomLayer->setEnable(true);
    CCFadeIn *fade = CCFadeIn::create(0.5);
    m_roomLayer->runAction(fade);
}
void RoomScene::serverListener(CCNode *node,void *data)
{
    NetEventPackage *netEvent = (NetEventPackage*)data;
    switch(netEvent->eventId()){
    case UiMsgHandler::UiEv_gameInit:{
        switchToGamePage();
        m_gameBoard->initBattleGame((UiMsgEv::GameInitInfo*)netEvent->param1());
        break;
    }
    case UiMsgHandler::UiEv_gameEnd:{
        switchToRoomPage();
        break;
    }
    default:{
        break;
    }
    }
}

