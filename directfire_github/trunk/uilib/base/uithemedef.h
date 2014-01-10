#ifndef _uithemedef_h_
#define _uithemedef_h_
#include <string>
#include <map>
#include <iostream>
#include <vector>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

namespace uilib{
class BasAnimSprite;
}
class LangDef;
enum SelfAdaptBgAreaEnum
{
    Area_lt = 0,
    Area_top,
    Area_rt,
    Area_left,
    Area_center,
    Area_right,
    Area_lb,
    Area_bottom,
    Area_rb,
    Area_end
};
class SelfAdaptBgData
{
public:
    SelfAdaptBgData();
    ~SelfAdaptBgData();
    void init();
    void setName(const std::string &name);
    const std::string &getName();
    void setAreaData(int area,const std::string &name);
    void setAreaData(const std::string &area,const std::string &name);
    std::vector<std::string> &getAreaData();
protected:
    std::vector<std::string> m_areaData;
    std::string m_name;
};

class NormalDataDef
{
public:
    NormalDataDef();
    ~NormalDataDef();
    void addImg(const std::string &name,const std::string &img);
    bool getImg(const std::string &name,std::string &img);
protected:
    std::map<std::string,std::string> m_imgMap;
private:

};

class UiThemeDef
{
public:
    UiThemeDef();
    ~UiThemeDef();
    void setName(const std::string &name);
    const std::string &getName();
    void addSelfAdaptBgData(SelfAdaptBgData *bgdata);
    void setNormalData(NormalDataDef *data);
    NormalDataDef *getNormalData();
    SelfAdaptBgData *getSelfAdaptDataByName(const std::string &name);
    const std::vector<std::string> &getFacing() { return m_facingVector;}
    const std::vector<std::string> &getPhrase() { return m_phraseVector;}
    void addFacing(const std::string &face) { m_facingVector.push_back(face);}
    void addPhrase(const std::string &phrase) { m_phraseVector.push_back(phrase);}
protected:
    std::map<string,SelfAdaptBgData*> m_selfAdaptDatas;
    NormalDataDef *m_normalData;
protected:
    vector<std::string> m_facingVector;
    vector<std::string> m_phraseVector;
private:
    std::string m_name;
};

typedef struct UiThemeResource
{
    std::string plist;
    std::string png;
}UiThemeResource;

typedef struct ShopDef{
    ShopDef(){

    }
    ShopDef(const std::string &name,const std::string &id,float cost){
        m_name = name;
        m_shopId = id;
        m_cost = cost;
    }
    std::string m_name;
    std::string m_shopId;
    float m_cost;
}ShopDef;

typedef struct ShooterPosDef
{
    std::string m_tribe;
    std::vector<CCPoint> m_pos;
}ShooterPosDef;

class UiThemeMgr
{
public:
    UiThemeMgr();
    ~UiThemeMgr();
    void loadFromXmlMemory(const char *buffer, int size);
    void loadFromXmlFile(const std::string &name);
    void addThemes(UiThemeDef *theme);
    UiThemeDef *getTheme(const std::string &theme);
    void getThemesNames(std::vector<std::string> &name);
    void addThemeResource(UiThemeResource &resource);
    std::vector<UiThemeResource> &getThemeResource();
    void addEffectResource(const std::string &effect);
    std::vector<std::string> &getEffectResource();
    void addShopDef(const std::string &name,const std::string &id,float cost);
    const std::vector<ShopDef> &getShopDef();
    const std::vector<ShooterPosDef> &getShooterPos() { return m_shootPosDef;}
    const ShooterPosDef &getShooterPosByTribe(const std::string &tribe);
    void addShootPos(const ShooterPosDef &pos);
    void setTowerNum(int num) { m_towerNum = num;}
    int getTowerNum() { return m_towerNum;}
    virtual uilib::BasAnimSprite *getAnimSpriteByName(const std::string &name) = 0;
	virtual bool getFrameSpriteFirstFrame(std::string &first) = 0;
	void initLangDef(const std::string &lang);
	void initNetLangDef(const std::string &netlang);
    LangDef *getLangDef();
    LangDef *getNetLangDef();
protected:
    std::map<std::string,UiThemeDef*> m_themes;
    std::vector<UiThemeResource> m_themeResources;
    std::vector<std::string> m_effectResources;
    std::vector<ShopDef> m_shopDef;
    std::vector<ShooterPosDef> m_shootPosDef;
	LangDef *m_langDef;
	LangDef *m_netLangDef;
private:
    ShooterPosDef m_tmpShooter;
private:
    int m_towerNum;
};
class UiThemeMgrProxy
{
public:
	static UiThemeMgrProxy *getInstance(UiThemeMgr *mgr = 0);
	UiThemeMgr *getThemeMgr();
	UiThemeDef *getThemeByName(const std::string &name);
private:
	static UiThemeMgrProxy *m_instance;
	UiThemeMgr *m_mgr;
	UiThemeMgrProxy(UiThemeMgr *mgr = 0);
	~UiThemeMgrProxy();
};

#endif
