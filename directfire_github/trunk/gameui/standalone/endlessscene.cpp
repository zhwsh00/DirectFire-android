#include "endlessscene.h"
#include "../battle.net/roomlayer.h"
#include "gamecore/gamecore/gameboard.h"
#include "gamecore/serverinterface.h"

#include "cliententry/uimsgevent.h"
#include "cliententry/uimsghandler.h"

#include "../menuscene.h"

EndlessScene::EndlessScene()
{
    ServerInterface::getInstance()->setStartEvCB(this,callfuncND_selector(EndlessScene::serverListener));
}
EndlessScene::~EndlessScene()
{
    ServerInterface *iface = ServerInterface::getInstance();
    if(iface)
        ServerInterface::getInstance()->setStartEvCB(0,0);
}
bool EndlessScene::init()
{
    bool ret = false;
    do {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
#ifdef LINUX
        size = CCEGLView::sharedOpenGLView()->getFrameSize();
#endif
        CC_BREAK_IF(!CCScene::init());
        m_gameBoard = GameBoard::create();
        this->addChild(m_gameBoard,0);
        m_gameBoard->setVisible(true);
        m_gameBoard->setGamePlayType(GameType::Endless);
        m_gameBoard->setGameNetworkType(GameType::StandAlone);
        m_gameBoard->initEndLessGame();
        //endless model is in local,the game should started by self
        ServerInterface::getInstance()->startEndlessMode();
        if(1){
            float width,height;
            /* this will read from map info */
            /* load the default endless map */
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
void EndlessScene::switchToGamePage()
{
    m_gameBoard->setVisible(true);
    CCFadeIn *fade = CCFadeIn::create(0.5);
    m_gameBoard->runAction(fade);
}
void EndlessScene::serverListener(CCNode *node,void *data)
{
    NetEventPackage *netEvent = (NetEventPackage*)data;
    switch(netEvent->eventId()){
    case UiMsgHandler::UiEv_gameInit:{
        break;
    }
    case UiMsgHandler::UiEv_gameEnd:{
        //just back to login page,pop this scene
        ServerInterface::getInstance()->setStartEvCB(0,0);
        CCDirector::sharedDirector()->popScene();
        break;
    }
    default:{
        break;
    }
    }
}
