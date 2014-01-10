#include "HelloWorldScene.h"
#include "tinyxml\tinyxml.h"

using namespace cocos2d;

#define MY_DEF_SCREENKEY	"kkkkk"

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}
HelloWorld::HelloWorld()
{
	//m_pTarget = NULL;
	m_xmlDoc = NULL;
}
	HelloWorld::~HelloWorld()
	{
	//	m_pTarget->release();
	//	m_pBrush->release();
			if(m_xmlDoc)
	{
		delete m_xmlDoc;
		m_xmlDoc = NULL;
	}
	}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
  
        CC_BREAK_IF(! CCLayer::init());

		m_bIsTouchEnabled = true;
 

		CCSize s = CCDirector::sharedDirector()->getWinSize();

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(s.width/2, s.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, -1);

	//	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(getStr(),"MarkerFelt.ttc", 20);

		//pLabel->setPosition(ccp(200,200));
	  //  pLabel->setColor(ccRED);
       // addChild(pLabel);
		addChild(&m_moveLabel,1);

		m_moveLabel.init(s.width/2, s.height/2,500,200);
	    m_moveLabel.initStr(getStr(),CCSizeMake(300,1600),kCCTextAlignmentLeft,"MarkerFelt.ttc",20);
	//	m_moveLabel.initStr("\xe5\x93\x88\xe5\x93\x88",CCSizeMake(200,1600),kCCTextAlignmentLeft,"MarkerFelt.ttc",20);
		
	

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}
void HelloWorld::draw()
{
	m_moveLabel.run();
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint location = pTouch->getLocation();
	location = CCDirector::sharedDirector()->convertToGL(location);
	m_moveLabel.touchDown(location.x,location.y);
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint location = pTouch->getLocation();
	location = CCDirector::sharedDirector()->convertToGL(location);
	m_moveLabel.touchUp(location.x,location.y);
}
void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint location = pTouch->getLocation();
	location = CCDirector::sharedDirector()->convertToGL(location);


	
	m_moveLabel.touchMove(location.x,location.y);
}

void HelloWorld::DelPoint(short x,short y,unsigned char nA)
{

}

 

bool HelloWorld::getNodePointerByName(TiXmlElement* pRootEle,std::string &strNodeName,TiXmlElement* &Node)  
{  

     if (strNodeName==pRootEle->Value())  
     {  
         Node = pRootEle;  
         return true;  
     }  
      TiXmlElement* pEle = pRootEle;    
      for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())    
    {    
          if(getNodePointerByName(pEle,strNodeName,Node))  
              return true;  
     }    
     return false;  
}   






char *HelloWorld::getStr()
{
	

	if(m_xmlDoc)
	{
		delete m_xmlDoc;
		m_xmlDoc = NULL;
	}
	m_xmlDoc = new TiXmlDocument(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("hello.xml"));  
	m_xmlDoc->LoadFile();  
	TiXmlElement* rootElement = m_xmlDoc->RootElement();


	
	TiXmlElement *nodeElement  =  NULL;
	TiXmlElement *titleElement = NULL;
	TiXmlElement *childElement = NULL;
	std::string str = "Words";
	getNodePointerByName(rootElement,str,nodeElement);

	if(!nodeElement)
	{
		return NULL;
	}

	//childElement = nodeElement->FirstChildElement();
	for(int i = 0; i< 1; i++)
	{
		//childElement = childElement->NextSiblingElement();
	}
	char *ps=(char *)nodeElement->GetText();
	char *pr =ps; 
	int len = strlen(ps);
	for(int i =0 ; i < len; i++ )
	{
		//CCLog("%x ",*(unsigned char*)ps);
		if(*ps == '\\')
		{
			*ps = 10;
		}
		ps++;
	}

	return  pr;

}