#ifndef _langsetting_h_
#define _langsetting_h_
#include <string>
#include <map>
#include <iostream>
using namespace std;
#include <libxml/parser.h>
#include <libxml/tree.h>

class LangDef;
class LangSetting
{
public:
    LangSetting();
    ~LangSetting();
    void loadFromXmlMemory(const char *buffer, int size, LangDef *langDef);
    void loadLangSetting(const std::string &xmlfile,LangDef*);
    void loadString(const std::string &name,xmlNodePtr node,LangDef *langDef);
private:
    void loadDoc(xmlDocPtr doc,LangDef *langDef);
};

#endif
