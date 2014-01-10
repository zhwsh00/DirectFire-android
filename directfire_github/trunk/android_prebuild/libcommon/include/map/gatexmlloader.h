#ifndef GATEXMLLOADER_H
#define GATEXMLLOADER_H
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string>
#include <vector>

using namespace std;

#include "absmap.h"
#include "mapimageinfo.h"
#include "mapmetainfo.h"

class GateXMLLoader
{
public:
    GateXMLLoader();
    GateXMLLoader(const string &file);
    ~GateXMLLoader();
    void dumpInfo();

    void setXmlFile(const string& filePath);
    void parseXml();
    void parseXmlMemory(const char *buf, int size);
    
    int maxPlayers() {return m_maxPlayers;}
    int maxTeams() {return m_maxTeams;}
    int mapSizeW() {return m_mapSizeW;}
    int mapSizeH() {return m_mapSizeH;}

    const string& gateFileName(){return m_gateFileName;}
    const string& gateId(){return m_gateId;}
    const string& gateName(){return m_gateName;}
    const string& pathFileName(){return m_pathFileName;}
    const string& mapShotPath(){return m_mapShotPath;}

    vector<MapSceneInfo>& allScene() {return m_allScene;}
    vector<MapSceneInfo>& staticScene() {return m_staticScene;}
    vector<MapSceneInfo>& dynamicScene() {return m_dynamicScene;}
    vector<MapImageInfo>& getImages();
    void getMetaInfo(MapMetaInfo& metaInfo);

private:
    void loadDoc(xmlDocPtr doc);
    void loadScenes(xmlNodePtr node);
    void loadScene(xmlNodePtr node, MapSceneInfo& sceneInfo);
    void loadImages(xmlNodePtr node);
    void loadImage(xmlNodePtr node, MapImageInfo& mapImageInfo);

private:
    int m_maxPlayers;
    int m_maxTeams;
    int m_mapSizeW;
    int m_mapSizeH;
    string m_gateFileName;
    string m_gateId;
    string m_gateName;
    string m_pathFileName;
    string m_mapShotPath;
    vector<MapSceneInfo> m_allScene;
    vector<MapSceneInfo> m_staticScene;
    vector<MapSceneInfo> m_dynamicScene;
    vector<MapImageInfo> m_images;
};

#endif // GATEXMLLOADER_H
