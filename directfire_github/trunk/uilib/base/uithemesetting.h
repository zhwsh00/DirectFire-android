#ifndef _uithemesetting_h_
#define _uithemesetting_h_
#include <string>
#include <map>
#include <iostream>
using namespace std;
#include <libxml/parser.h>
#include <libxml/tree.h>

class UiThemeMgr;
class UiThemeDef;
class UiThemeSetting
{
public:
    UiThemeSetting();
    ~UiThemeSetting();
    void loadFromXmlMemory(const char *buffer, int size, UiThemeMgr *mgr);
    void loadUiThemesFromXml(const std::string &xmlfile,UiThemeMgr*);
    void loadUiResources(xmlNodePtr node,UiThemeMgr *mgr);
    void loadUiEffect(xmlNodePtr node,UiThemeMgr *mgr);
    void loadShopDef(xmlNodePtr node,UiThemeMgr *mgr);
    void loadUiThemes(const std::string &name,xmlNodePtr node,UiThemeMgr *mgr);
    void loadUiSelfAdaptArea(const std::string &name,xmlNodePtr node,UiThemeDef *themeDef);
    void loadUiOthers(xmlNodePtr node,UiThemeDef *themeDef);
    void loadUiFacing(xmlNodePtr node,UiThemeDef *themeDef);
    void loadUiPhrase(xmlNodePtr node,UiThemeDef *themeDef);
    void loadShooterPos(xmlNodePtr node,UiThemeMgr *mgr);
    void loadTribeShooterPos(const std::string &tribe,xmlNodePtr node,UiThemeMgr *mgr);
    
private:
    void loadDoc(xmlDocPtr doc,UiThemeMgr *mgr);
};

#endif
