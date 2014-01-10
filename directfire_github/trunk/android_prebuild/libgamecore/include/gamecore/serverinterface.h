#ifndef _serverinterface_h_
#define _serverinterface_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;
#include "cliententry/cliententry.h"
#include "cliententry/uimsghandler.h"

class ServerInterface : public ClientEntry,public CCNode
{
    static ServerInterface *m_instance;
    ServerInterface();
public:
    ~ServerInterface();
    static ServerInterface *getInstance();
    void update(float fDelta);
    virtual void handleNetEvent(NetEventPackage *event);
    virtual UiMsgHandler::UiEvHandleResult handleGameEvent(GameEventPackage *event);
public:
    void applicationDidEnterBackground();
    void applicationWillEnterForeground();
public:
    void setMainMenuEvCB(CCNode *listener,SEL_CallFuncND func);
    void setHallEvCB(CCNode *listener,SEL_CallFuncND func);
    void setRoomEvCB(CCNode *listener,SEL_CallFuncND func);
    void setGameEvCB(CCNode *listener,SEL_CallFuncND func);
    void setStartEvCB(CCNode *listener,SEL_CallFuncND func);
    void setSellBuyEvCB(CCNode *listener,SEL_CallFuncND func);
    void setHeadSettingCB(CCNode *listener,SEL_CallFuncND succFunc,SEL_CallFuncND failFunc);
protected:
    CCNode *m_menuEvListener;
    SEL_CallFuncND m_menuEvFunc;
protected:
    CCNode *m_hallEvListener;
    SEL_CallFuncND m_hallEvFunc;
protected:
    CCNode *m_roomEvListener;
    SEL_CallFuncND m_roomEvFunc;
protected:
    CCNode *m_gameEvListener;
    SEL_CallFuncND m_gameEvFunc;
protected:
    CCNode *m_startEvListener;
    SEL_CallFuncND m_startEvFunc;
protected:
    CCNode *m_sellBuyEvListener;
    SEL_CallFuncND m_sellBuyFunc;
protected:
    CCNode *m_headSettingEvListener;
    SEL_CallFuncND m_headSettingSuccFunc;
    SEL_CallFuncND m_headSettingFailFunc;
    
};
#endif
