#include "uithemesetting.h"
#include "uithemedef.h"
#include <string.h>

UiThemeSetting::UiThemeSetting()
{

}
UiThemeSetting::~UiThemeSetting()
{

}
void UiThemeSetting::loadFromXmlMemory(const char *buffer, int size, UiThemeMgr *mgr)
{
    xmlDocPtr doc = xmlReadMemory(buffer,size,0,"utf-8",XML_PARSE_RECOVER);
    loadDoc(doc,mgr);
}
void UiThemeSetting::loadUiThemesFromXml(const std::string &xmlfile,UiThemeMgr *mgr)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
    xmlDocPtr doc = xmlReadFile(xmlfile.c_str(),"utf-8",XML_PARSE_RECOVER);
#else
    unsigned long size = 0;
    unsigned char *buf = CCFileUtils::sharedFileUtils()->getFileData(xmlfile.c_str(),"r",&size);
    xmlDocPtr doc = xmlReadMemory((const char*)buf,size,xmlfile.c_str(),NULL,0);
#endif
    loadDoc(doc,mgr);
}
void UiThemeSetting::loadDoc(xmlDocPtr doc,UiThemeMgr *mgr)
{
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if(root == 0){
        //null xml
        return;
    }
    xmlKeepBlanksDefault(0);
    xmlNodePtr node = root->xmlChildrenNode;
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else if(strcmp((char*)node->name, "resources") == 0){
            loadUiResources(node->xmlChildrenNode,mgr);
        }else if(strcmp((char*)node->name, "uieffect") == 0){
            loadUiEffect(node->xmlChildrenNode,mgr);
        }else if(strcmp((char*)node->name, "shop") == 0){
            loadShopDef(node->xmlChildrenNode,mgr);
        }else if(strcmp((char*)node->name, "theme") == 0){
            std::string themeName;
            xmlChar *data = xmlGetProp(node,(xmlChar*)"name");
            themeName = (char*)data;
            xmlFree(data);
            loadUiThemes(themeName,node->xmlChildrenNode,mgr);
        }else if(strcmp((char*)node->name,"shooter") == 0){
            loadShooterPos(node->xmlChildrenNode,mgr);
        }else if(strcmp((char*)node->name,"tdnum")){
            xmlChar *data = xmlNodeGetContent(node);
            int num = atoi((char*)data);
            xmlFree(data);
            mgr->setTowerNum(num);
        }
        node = node->next;
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();
}
void UiThemeSetting::loadUiResources(xmlNodePtr node,UiThemeMgr *mgr)
{
    UiThemeResource resource;
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else{
            resource.plist = (char*)(node->name);
            xmlChar *data = xmlNodeGetContent(node);
            resource.png = (char*)data;
            xmlFree(data);
            node = node->next;
            mgr->addThemeResource(resource);
        }
    }
}
void UiThemeSetting::loadUiEffect(xmlNodePtr node,UiThemeMgr *mgr)
{
    std::string effect;
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else if(strcmp((char*)node->name, "effect") == 0){
            xmlChar *data = xmlNodeGetContent(node);
            effect = (char*)data;
            xmlFree(data);
            mgr->addEffectResource(effect);
        }
        node = node->next;
    }
}
void UiThemeSetting::loadShopDef(xmlNodePtr node,UiThemeMgr *mgr)
{
    std::string name,id;
    float cost;
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else{
            name = (char*)(node->name);
            xmlChar *data = xmlNodeGetContent(node);
            cost = atof((char*)data);
            xmlFree(data);
            xmlChar *iddata = xmlGetProp(node,(const xmlChar *)"id");
            id = (char*)(iddata);
            xmlFree(iddata);
            mgr->addShopDef(name,id,cost);
        }
        node = node->next;
    }
}
void UiThemeSetting::loadUiThemes(const std::string &name,xmlNodePtr node,UiThemeMgr *mgr)
{
    UiThemeDef *themeDef = new UiThemeDef;
    themeDef->setName(name);
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else if(strcmp((char*)node->name, "others") == 0){
            loadUiOthers(node->xmlChildrenNode,themeDef);
        }else if(strcmp((char*)node->name, "facing") == 0){
            loadUiFacing(node->xmlChildrenNode,themeDef);
        }else if(strcmp((char*)node->name, "phrase") == 0){
            loadUiPhrase(node->xmlChildrenNode,themeDef);
        }else{
            loadUiSelfAdaptArea(std::string((char*)node->name),node->xmlChildrenNode,themeDef);
        }
        node = node->next;
    }
    if(themeDef->getName().size() != 0){
        mgr->addThemes(themeDef);
    }else{
        delete themeDef;
    }
}
void UiThemeSetting::loadUiSelfAdaptArea(const std::string &name,xmlNodePtr node,UiThemeDef *themeDef)
{
    if(name.size() == 0){
        return;
    }
    SelfAdaptBgData *bgData = new SelfAdaptBgData;
    bgData->setName(name);
    std::string key,value;
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else{
            key = (char*)node->name;
            xmlChar *data = xmlNodeGetContent(node);
            value = (char*)data;
            xmlFree(data);
            bgData->setAreaData(key,value);
        }
        node = node->next;
    }
    themeDef->addSelfAdaptBgData(bgData);
}
void UiThemeSetting::loadUiOthers(xmlNodePtr node,UiThemeDef *themeDef)
{
    NormalDataDef *normalData = new NormalDataDef;
    std::string key,value;
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else{
            key = (char*)node->name;
            xmlChar *data = xmlNodeGetContent(node);
            value = (char*)data;
            xmlFree(data);
            normalData->addImg(key,value);
        }
        node = node->next;
    }
    themeDef->setNormalData(normalData);
}
void UiThemeSetting::loadUiFacing(xmlNodePtr node,UiThemeDef *themeDef)
{
    std::string face;
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else if(strcmp((char*)node->name, "face") == 0){
            xmlChar *data = xmlNodeGetContent(node);
            face = (char*)data;
            xmlFree(data);
            themeDef->addFacing(face);
        }
        node = node->next;
    }
}
void UiThemeSetting::loadUiPhrase(xmlNodePtr node,UiThemeDef *themeDef)
{
    std::string phrase;
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else if(strcmp((char*)node->name, "p") == 0){
            xmlChar *data = xmlNodeGetContent(node);
            phrase = (char*)data;
            xmlFree(data);
            themeDef->addPhrase(phrase);
        }
        node = node->next;
    }
}
void UiThemeSetting::loadShooterPos(xmlNodePtr node,UiThemeMgr *mgr)
{
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else{
            loadTribeShooterPos((char*)node->name,node->xmlChildrenNode,mgr);
        }
        node = node->next;
    }
}
void UiThemeSetting::loadTribeShooterPos(const std::string &tribe,xmlNodePtr node,UiThemeMgr *mgr)
{
    ShooterPosDef def;
    def.m_tribe = tribe;
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else if(strcmp((char*)node->name,"pos") == 0){
            float x,y;
            xmlChar *xdata = xmlGetProp(node,(const xmlChar *)"x");
            x = atof((char*)xdata);
            xmlFree(xdata);
            xmlChar *ydata = xmlGetProp(node,(const xmlChar *)"y");
            y = atof((char*)ydata);
            xmlFree(ydata);
            def.m_pos.push_back(ccp(x,y));
        }
        node = node->next;
    }
    mgr->addShootPos(def);
}
