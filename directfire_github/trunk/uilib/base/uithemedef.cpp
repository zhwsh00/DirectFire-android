#include "uithemedef.h"
#include "uithemesetting.h"
#include "../base/absanimsprite.h"
#include "../lang/langdef.h"

static std::map<std::string,int> s_areaEnumNameMap;

static void initAreaEnumNameMap()
{
    if(s_areaEnumNameMap.size() != 0)
        return;
    s_areaEnumNameMap.insert(std::make_pair("lt",Area_lt));
    s_areaEnumNameMap.insert(std::make_pair("top",Area_top));
    s_areaEnumNameMap.insert(std::make_pair("rt",Area_rt));
    s_areaEnumNameMap.insert(std::make_pair("left",Area_left));
    s_areaEnumNameMap.insert(std::make_pair("center",Area_center));
    s_areaEnumNameMap.insert(std::make_pair("right",Area_right));
    s_areaEnumNameMap.insert(std::make_pair("lb",Area_lb));
    s_areaEnumNameMap.insert(std::make_pair("bottom",Area_bottom));
    s_areaEnumNameMap.insert(std::make_pair("rb",Area_rb));
}
static int getAreaIndexByName(const std::string &name)
{
    if(s_areaEnumNameMap.size() == 0)
        initAreaEnumNameMap();
    std::map<std::string,int>::iterator iter;
    iter = s_areaEnumNameMap.find(name);
    if(iter != s_areaEnumNameMap.end()){
        return iter->second;
    }else{
        return -1;
    }
}

SelfAdaptBgData::SelfAdaptBgData()
{
    init();
}
SelfAdaptBgData::~SelfAdaptBgData()
{

}
void SelfAdaptBgData::init()
{
    for(int i = Area_lt;i < Area_end;i++){
        m_areaData.push_back(std::string());
    }
}
void SelfAdaptBgData::setName(const std::string &name)
{
    m_name = name;
}
const std::string &SelfAdaptBgData::getName()
{
    return m_name;
}
void SelfAdaptBgData::setAreaData(int area,const std::string &name)
{
    if(area < 0 || area >= Area_end)
        return;
    m_areaData[area] = name;
}
void SelfAdaptBgData::setAreaData(const std::string &area,const std::string &name)
{
    int index = getAreaIndexByName(area);
    if(index >= 0)
         m_areaData[index] = name;
}
std::vector<std::string> &SelfAdaptBgData::getAreaData()
{
    return m_areaData;
}
NormalDataDef::NormalDataDef()
{

}
NormalDataDef::~NormalDataDef()
{

}
void NormalDataDef::addImg(const std::string &name,const std::string &img)
{
    m_imgMap.insert(std::make_pair(name,img));
}
bool NormalDataDef::getImg(const std::string &name,std::string &img)
{
    std::map<std::string,std::string>::iterator iter;
    iter = m_imgMap.find(name);
    if(iter != m_imgMap.end()){
        img = iter->second;
        return true;
    }else{
        return false;
    }
}
UiThemeDef::UiThemeDef()
{
    m_normalData = 0;
}
UiThemeDef::~UiThemeDef()
{

}
void UiThemeDef::setName(const std::string &name)
{
    m_name = name;
}
const std::string &UiThemeDef::getName()
{
    return m_name;
}
void UiThemeDef::addSelfAdaptBgData(SelfAdaptBgData *bgdata)
{
    m_selfAdaptDatas.insert(std::make_pair(bgdata->getName(),bgdata));
}
void UiThemeDef::setNormalData(NormalDataDef *data)
{
    m_normalData = data;
}
NormalDataDef *UiThemeDef::getNormalData()
{
    return m_normalData;
}
SelfAdaptBgData *UiThemeDef::getSelfAdaptDataByName(const std::string &name)
{
    std::map<string,SelfAdaptBgData*>::iterator iter;
    iter = m_selfAdaptDatas.find(name);
    if(iter != m_selfAdaptDatas.end()){
        return iter->second;
    }else{
        return 0;
    }
}

UiThemeMgr::UiThemeMgr()
{
    m_towerNum = 20;
	UiThemeMgrProxy *proxy = UiThemeMgrProxy::getInstance(this);
}
UiThemeMgr::~UiThemeMgr()
{

}
void UiThemeMgr::loadFromXmlMemory(const char *buffer, int size)
{
    UiThemeSetting loader;
    loader.loadFromXmlMemory(buffer,size,this);
}
void UiThemeMgr::loadFromXmlFile(const std::string &name)
{
    UiThemeSetting loader;
    loader.loadUiThemesFromXml(name,this);
}
void UiThemeMgr::addThemes(UiThemeDef *theme)
{
    m_themes.insert(std::make_pair(theme->getName(),theme));
}
UiThemeDef *UiThemeMgr::getTheme(const std::string &theme)
{
	std::string _theme = theme;
	if(_theme.empty()){
		_theme = "default";
	}
    std::map<std::string,UiThemeDef*>::iterator iter;
    iter = m_themes.find(_theme);
    if(iter != m_themes.end()){
        return iter->second;
    }else{
        return 0;
    }
}
void UiThemeMgr::getThemesNames(std::vector<std::string> &names)
{
    std::map<std::string,UiThemeDef*>::iterator iter;
    for(iter = m_themes.begin();iter != m_themes.end();iter++){
        names.push_back(iter->first);
    }
}
void UiThemeMgr::addThemeResource(UiThemeResource &resource)
{
    m_themeResources.push_back(resource);
}
std::vector<UiThemeResource> &UiThemeMgr::getThemeResource()
{
    return m_themeResources;
}
void UiThemeMgr::addEffectResource(const std::string &effect)
{
    m_effectResources.push_back(effect);
}
std::vector<std::string> &UiThemeMgr::getEffectResource()
{
    return m_effectResources;
}
void UiThemeMgr::addShopDef(const std::string &name,const std::string &id,float cost)
{
    m_shopDef.push_back(ShopDef(name,id,cost));
}
const std::vector<ShopDef> &UiThemeMgr::getShopDef()
{
    return m_shopDef;
}
const ShooterPosDef &UiThemeMgr::getShooterPosByTribe(const std::string &tribe)
{
    for(unsigned int i = 0;i < m_shootPosDef.size();i++){
        ShooterPosDef &def = m_shootPosDef[i];
        if(def.m_tribe == tribe){
            return def;
        }
    }
    return m_tmpShooter;
}
void UiThemeMgr::addShootPos(const ShooterPosDef &pos)
{
     m_shootPosDef.push_back(pos);
}
LangDef *UiThemeMgr::getLangDef()
{
	return m_langDef;
}
LangDef *UiThemeMgr::getNetLangDef()
{
	return m_netLangDef;
}
UiThemeMgrProxy *UiThemeMgrProxy::m_instance = 0;
UiThemeMgrProxy *UiThemeMgrProxy::getInstance(UiThemeMgr *mgr)
{
	if(m_instance == 0){
		m_instance = new UiThemeMgrProxy(mgr);
	}
	return m_instance;
}
UiThemeDef *UiThemeMgrProxy::getThemeByName(const std::string &name)
{
	return m_instance->m_mgr->getTheme(name);
}
UiThemeMgrProxy::UiThemeMgrProxy(UiThemeMgr *mgr)
{
	m_mgr = mgr;
}
UiThemeMgrProxy::~UiThemeMgrProxy()
{

}
UiThemeMgr *UiThemeMgrProxy::getThemeMgr()
{
	return m_instance->m_mgr;
}