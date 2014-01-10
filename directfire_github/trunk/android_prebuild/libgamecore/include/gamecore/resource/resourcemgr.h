#ifndef _resourcemgr_h_
#define _resourcemgr_h_
#include "cocos2d.h"
using namespace cocos2d;
#include <string>
#include <map>
#include <vector>
#include <sstream>
using namespace std;
#include "gamecore/sys/framesetting.h"

#include "map/resourcereader.h"
#include "uilib/uilib.h"

/* this class response for
 * Images/Sound/Particle loading/asking
 */

class BasFrameSprite;
class BallDatas;
class BasEntity;
class UiThemeMgr;
class ResourceThread;
class ResourceEvent;
class LangDef;
class SplashDef;
class UserDataMgr;
class SysSetting;
class SoundMgr;
class UiStatusMgr;
class ResourceMgr : public UiThemeMgr
{
public:
    typedef struct StepFrameInfo
    {
        StepFrameInfo(){

        }
        StepFrameInfo(int loop,int frame,int totalframe,float time){
            loopNum = loop;
            frameNum = frame;
            totalFrame = totalframe;
            totalTime = time;
        }
        int loopNum;
        int frameNum;
        int totalFrame;
        float totalTime;
        float scale;
    }StepFrameInfo;

	enum FrameStage{
		Null = -1,
		Wink,
		Posing,
		Pre,
		Exec,
		Move,
		End
	};
	static ResourceMgr *getInstance();
	void init();
    void initInThread(ResourceThread *thread);
    bool isInit() { return m_inited;}
    virtual BasAnimSprite *getAnimSpriteByName(const std::string &name);
	virtual bool getFrameSpriteFirstFrame(std::string &first);
    void loadSplash();//this called standalone and first
    UiThemeMgr *getUiThemeMgr();
    LangDef *getLangDef();
    LangDef *getNetLangDef();
    SplashDef *getSplashDef();
    UserDataMgr *getUserDataMgr();
    SysSetting *getSysSetting();
    SoundMgr *getSoundMgr();
    UiStatusMgr *getUiStatusMgr();
	void getTribes(std::vector<std::string> &tribe);    
    int getRandomTribe(int userIndex);
	void getTribeName(int tribe,std::string &name);
	int getTribeRadius(int tribe);
	int getTribeRadius(const std::string &tribe);
	int getTribeSpeed(int tribe);
	int getTribeSpeed(const std::string &trib);
    int getTribeRunSpeed(int tribe);
    int getTribeRunSpeed(const std::string &tribe);
    int getAddBallFStep(int tribe);
    int getAddBallFStep(const std::string &tribe);
	void getTribeColor(int tribe,int &start,int &end,int &num);
	void getTribeColor(const std::string &tribe,int &start,int &end,int &num);
	int getTribeCollNum(int tribe);
	int getTribeCollNum(const std::string &tribe);
	int getTribeSpeedStep(int tribe);
	int getTribeSpeedStep(const std::string &tribe);
    int getTribeInitNum(int tribe);
    int getTribeInitNum(const std::string &tribe);
	void initBallEntity(int tribe,BasEntity *entity);
	void initBallEntity(const std::string &tribe,BasEntity *entity);
	void initBaseEntity(int tribe,BasEntity *entity);
	void initBaseEntity(const std::string &tribe,BasEntity *entity);
	const std::vector<std::string> &propsNames();
    const std::vector<std::string> &battlePropsNames();
    const std::vector<std::string> &tdPropsNames();
	static void getPropsSetting(const std::string &prop,const std::string &key,std::string &value,const std::string &def,int stage = ResourceMgr::Null);
	static void getPropsSetting(const std::string &prop,const std::string &key,int &value,int def = 0,int stage = ResourceMgr::Null);
	static void getPropsSetting(const std::string &prop,const std::string &key,float &value,float def = 0,int stage = ResourceMgr::Null);
	static void getPropsSetting(const std::string &prop,const std::string &key,bool &value,bool def = false,int stage = ResourceMgr::Null);
    static void getFrameSpriteTotalFrame(const std::string &key,int &loops,int &totalFrame,int &frameNum,float &totalTime,float &scale);
    static void getPropsRuntype(const std::string &prop,std::string &runtype,int stage = ResourceMgr::Null);
	static void getPropsType(const std::string &prop,std::string &type,int stage = ResourceMgr::Null);
    static bool getPropsEraseBall(const std::string &prop,int stage = ResourceMgr::Null);

	static bool getPropsCanRotate(const std::string &prop,std::string &type,int stage = ResourceMgr::Null);
	static void getPropsKeyFrames(const std::string &prop,std::vector<int> &ints,int stage = ResourceMgr::Null);
	static bool getAttractCollisionData(const std::string &prop,int key,float &radius,float &time,float &angle,float &scale,int stage = ResourceMgr::Null);
	static bool getPropsDeliverAttractData(const std::string &prop,int key,float &radius,float &time,float &angle,float &scale,int stage = ResourceMgr::Null);
	static void getPropsCollType(const std::string &prop,std::string &type,int stage = ResourceMgr::Null);
	static void getPropsCollRadius(const std::string &prop,int key,float &radius,int stage = ResourceMgr::Null);
	static void getPropsCollRect(const std::string &prop,int key,float &w,float &h,int stage = ResourceMgr::Null);
    static void getPropsAttack(const std::string &prop,float &attack,int key,int stage = ResourceMgr::Null);
	static bool getAlphaCollisionData(const std::string &prop,int key,unsigned char **data,int &width,int &height,int stage = ResourceMgr::Exec);
	static bool getDispelCollisionData(const std::string &prop,int key,float &radius,float &time,float &scale,int stage = ResourceMgr::Null);
	static bool getWormCollisionData(const std::string &prop,int key,float &radius,float &looptime,
			float &runtime,float &delay,int &ballnum,float &scale,int &speed,int stage = ResourceMgr::Null);
	static bool getCycloneCollisionData(const std::string &prop,int key,float &time,float &movelen,float &topwidth,int stage = ResourceMgr::Null);
	static bool getDeliverCollisionData(const std::string &prop,float &runtime,float &delay,float &scale,float &radius,int &speed,int stage = ResourceMgr::Null);
	static const std::string getBallDeath() { return "death"; }
	static const std::string getPropsSpellStageName(int stage);
    bool getPatcileDict(const std::string &name,CCDictionary **dict);
    
public:
    ResourceReader *resReader();
    bool isResExist(const std::string& relativePath);
    CCSprite* loadSpriteByTexture(const std::string& relativePath);
    CCSprite* loadSpriteByTexture(const std::string& relativePath, const CCRect& rect);
    void addSpriteFrames(const std::string& plist, const std::string& relativePath);
    void addSpriteFrames(const std::string& plist, CCTexture2D *texture);
    void addSpriteFrames(CCSpriteFrameCache *dest, const std::string& plist, const std::string& relativePath);
    void addSpriteFrames(CCSpriteFrameCache *dest, const std::string& plist, CCTexture2D *texture);
    void initWithImageFile(CCImage *img, const string& relativePath);
    
    bool isLanguageSupport(int lang);
private:
    CCTexture2D* getTextureFromResData(const std::string& relativePath);
    bool loadXmlFileBasSetting(BasXmlSetting* loader, const std::string& relativePath);
    bool loadXmlFileBallDatas(BallDatas* loader, const std::string& relativePath);
    bool loadXmlFileUiThemeMgr(UiThemeMgr* loader, const std::string& relativePath);
    bool loadXmlFileLangDef(LangDef* loader, const std::string& relativePath);
    
private:
	ResourceMgr();
	~ResourceMgr();
	static ResourceMgr *m_instance;
    
protected:
    void loadSysSetting();
	void loadProps();
	void loadBalls();
	void loadSys();
	void loadParticle();
    void loadUiTheme();
    void loadUiEffect();
    void loadLangDef();
    void loadUserData();
    void loadSoundMgr();
    void loadLanguageSupport();
protected: //tools
    void loadFrameAnimation(std::string &name,std::string &plist,std::string &pngname,
			std::string &xmlfile,std::string &keyname,bool loadimg = true);
	void loadFrameSetting(const std::string &dir,const std::string &name);
private://ball resource
private: //frame resource
    void propsFrameInit();
	void loadPropPre(const std::string &prop);
	void loadPropEnd(const std::string &prop);
    void loadPropExec(const std::string &prop);
	void loadPropSetting(const std::string &prop);
    std::vector<std::string> m_propsNames;
    std::vector<std::string> m_battlePropsNames;
    std::vector<std::string> m_tdPropsNames;
	std::string m_propsDir;
private: //sound setting
    SoundMgr *m_soundMgr;
private: //splash data
    SplashDef *m_splashDef;
private: //user data
    UserDataMgr *m_userDataMgr;
private: //sys setting
    SysSetting *m_sysSetting;
private: //particle resource
private: //props
	std::map<std::string,FrameSetting*> m_propsSetting;
	std::map<std::string,std::string> m_firstFrameMap;
    std::map<std::string,StepFrameInfo > m_totalFrameMap;
	std::map<std::string,CCImage *> m_alphaCollisionMap;
    std::map<std::string,CCImage *> m_alphaCollisionNameMap;
private: //particle
	std::map<std::string,CCDictionary*> m_particleDictMap;
private: //balls
	BallDatas *m_ballDatas;
private:
    bool m_inited;
    bool m_asyncLoading;
    ResourceThread *m_loadingThread;
    ResourceEvent *m_loadingEvent;
private:
    ResourceReader *m_resReader;
private:
    std::vector<int> m_supportLanguage;
};
#endif
