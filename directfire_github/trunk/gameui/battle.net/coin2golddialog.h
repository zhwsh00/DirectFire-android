#ifndef _coin2golddialog_h_
#define _coin2golddialog_h_
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"
using namespace uilib;

#include "prop/propdef.h"
class ServerInterface;
class Coin2GoldDialog : public BasShowDialog
{
public:
    Coin2GoldDialog(CCNode *parent = 0,const ccColor4B &color = ccc4(0,0,0,0));
    virtual ~Coin2GoldDialog();
    virtual void exec();
    void exchangeReply(bool succ);
protected:
    void finish();
protected:
    void onIncButtonClicked(CCNode *node,void *data);
    void onDecButtonClicked(CCNode *node,void *data);
    void onSubmitButtonClicked(CCNode *node,void *data);
protected:
    void autoIncStep(float dt);
    void autoDecStep(float dt);
    void onIncTouchBegin(CCNode *node,void *data);
    void onIncTouchEnd(CCNode *node,void *data);
    void onDecTouchBegin(CCNode *node,void *data);
    void onDecTouchEnd(CCNode *node,void *data);
protected:
    std::string m_id;
    ServerInterface *m_serverIface;
    int m_coinHad;
    int m_goldHad;
    CCLabelBMFont *m_coinSprite;
    CCLabelBMFont *m_goldSprite;
    int m_coinOnEx;
    CCLabelBMFont *m_coinExSprite;
    int m_exRate;
protected:
    BasButton *m_submitButton;
    BasButton *m_incButton;
    BasButton *m_decButton;
protected:
    BasAnimSprite *m_busyAnim;
protected:

};
#endif
