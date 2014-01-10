#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "moveLabel.h"
//#include "SimpleAudioEngine.h"
//#include "cocos-ext.h"
using namespace cocos2d;
//using namespace CocosDenshion;
//using namespace cocos2d::extension;

class HelloWorld : public cocos2d::CCLayer
{
public:

	HelloWorld();
	~HelloWorld();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	virtual void draw();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void DelPoint(short x,short y,unsigned char nA = 255);
	char *getStr();
	bool getNodePointerByName(TiXmlElement* pRootEle,std::string &strNodeName,TiXmlElement* &Node);
public:
	CCImage* m_pimage;
	CCTexture2D* m_ptexture;
	CCSprite* m_pSprite;
	//	CCSprite* m_pBrush;
	//CCRenderTexture *m_pTarget;
//	unsigned char *m_p;// = m_pimage->getData();
	//short m_nW;// = m_pimage->getWidth();
//	short m_nH;// = m_pimage->getHeight();
	MoveLabel m_moveLabel;

	TiXmlDocument* m_xmlDoc ;
	

};

#endif  // __HELLOWORLD_SCENE_H__