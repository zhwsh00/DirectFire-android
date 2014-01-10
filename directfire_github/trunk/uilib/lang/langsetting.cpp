#include "langsetting.h"
#include "langdef.h"
#include "string.h"

#include "cocos2d.h"
using namespace cocos2d;

LangSetting::LangSetting()
{

}
LangSetting::~LangSetting()
{

}
void LangSetting::loadFromXmlMemory(const char *buffer, int size, LangDef *langDef)
{
    xmlDocPtr doc = xmlReadMemory(buffer,size,0,"UTF-8",XML_PARSE_RECOVER);
    loadDoc(doc,langDef);
}
void LangSetting::loadLangSetting(const std::string &xmlfile,LangDef *langDef)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
    xmlDocPtr doc = xmlReadFile(xmlfile.c_str(),"utf-8",XML_PARSE_RECOVER);
#else
    unsigned long size = 0;
    unsigned char *buf = CCFileUtils::sharedFileUtils()->getFileData(xmlfile.c_str(),"r",&size);
    xmlDocPtr doc = xmlReadMemory((const char*)buf,size,xmlfile.c_str(),NULL,0);
#endif;
    loadDoc(doc,langDef);
}
void LangSetting::loadDoc(xmlDocPtr doc,LangDef *langDef)
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
            continue;;
        }else if(strcmp((char*)node->name, "lang") == 0){
            std::string langName;
            xmlChar *data = xmlGetProp(node,(xmlChar*)"name");
            langName = (char*)data;
            xmlFree(data);
            loadString(langName,node->xmlChildrenNode,langDef);
        }
        node = node->next;
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();
}
void LangSetting::loadString(const std::string &name,xmlNodePtr node,LangDef *langDef)
{
    LangDef::LangStringDef *stringDef = new LangDef::LangStringDef;
    stringDef->m_name = name;
    int id;
    std::string tran;
    while(node){
        if(strcmp((char*)node->name, "text") == 0){
            //filter return char here
            node = node->next;
            continue;
        }else{
            xmlChar *data = xmlNodeGetContent(node);
            tran = (char*)data;
            xmlFree(data);
            data = xmlGetProp(node,(xmlChar*)"num");
            id = atoi((char*)(data));
            xmlFree(data);
            stringDef->m_strings.insert(std::make_pair(id,tran));
            node = node->next;
        }
    }
    langDef->addLang(stringDef);
}
