#include "langdef.h"
#include "langsetting.h"

LangDef::LangDef()
{
    m_currUse = 0;
}
LangDef::~LangDef()
{

}
void LangDef::loadFromXmlMemory(const char *buffer, int size)
{
    LangSetting setting;
    setting.loadFromXmlMemory(buffer,size,this);
}
void LangDef::loadFromXmlFile(const std::string &xmlfile)
{
    LangSetting setting;
    setting.loadLangSetting(xmlfile,this);
}
void LangDef::setUseLang(const std::string &lang)
{
    for(int i = 0;i < m_langs.size();i++){
        if(m_langs[i]->m_name == lang){
            m_currUse = m_langs[i];
            break;
        }
    }
    if(m_currUse == 0)
        m_currUse = m_langs[0];
}
const std::string &LangDef::getStringById(int id)
{
    if(m_currUse == 0)
        m_currUse = m_langs[0];
    std::map<int,std::string>::iterator iter;
    iter = m_currUse->m_strings.find(id);
    if(iter == m_currUse->m_strings.end())
        return m_nullString;
    else
        return iter->second;
}
void LangDef::addLang(LangStringDef *lang)
{
    m_langs.push_back(lang);
}
