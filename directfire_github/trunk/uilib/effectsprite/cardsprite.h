#ifndef _cardsprite_h_
#define _cardsprite_h_

#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
#include <map>
using namespace std;

namespace uilib {

class CardSprite : public CCNode
{
public:
    CardSprite(const CCSize &size,float time = 0.5);
    ~CardSprite();
    void setCards(const std::string &in,const std::string &out);
    void openCard();
    void closeCard();
    bool isClosed();
    void setFlipListener(CCNode *node,SEL_CallFuncND func);
    CCSprite *backSprite() { return m_outSprite;}
    CCSprite *frontSprite() { return m_inSprite;}
protected:
    void onFlipFinished(CCNode *node,void *data);
protected:
    CCNode *m_listener;
    SEL_CallFuncND m_func;
protected:
    CCSprite *m_inSprite;
    CCSprite *m_outSprite;
    CCSize m_cSize;
protected:
    std::string m_inImg;
    std::string m_outImg;
    float m_time;
private:
    bool m_isOpened;
    CCActionInterval* m_openAnimIn;
    CCActionInterval* m_openAnimOut;
    void initData(const char* inCardImageName, const char* outCardImageName, float duration);
};

}
#endif
