#ifndef _langdef_h_
#define _langdef_h_
#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

#include "stringenum.h"

class LangDef
{
public:
    typedef struct LangStringDef
    {
        std::string m_name;
        std::map<int,std::string> m_strings;
    }LangStringDef;
    LangDef();
    ~LangDef();
    void loadFromXmlMemory(const char *buffer, int size);
    void loadFromXmlFile(const std::string &xmlfile);
    void setUseLang(const std::string &lang);
    const std::string &getStringById(int id);
    void addLang(LangStringDef*);
protected:
    LangStringDef *m_currUse;
    std::vector<LangStringDef*> m_langs;
protected:
    std::string m_nullString;
};

#endif
