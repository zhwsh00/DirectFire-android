#ifndef MAPMETAINFO_H
#define MAPMETAINFO_H
#include <iostream>
#include <vector>
using namespace std;

#include "mapsceneinfo.h"

class MapMetaInfo
{
public:
    MapMetaInfo();
    ~MapMetaInfo();
    void dumpInfo();

    void setMaxPlayers(int count){m_maxPlayers = count;}
    int maxPlayers() {return m_maxPlayers;}
    void setMaxTeams(int count){m_maxTeams = count;}
    int maxTeams() {return m_maxTeams;}
    void setMapSizeW(int w){m_mapSizeW = w;}
    int mapSizeW() {return m_mapSizeW;}
    void setMapSizeH(int h){m_mapSizeH = h;}
    int mapSizeH() {return m_mapSizeH;}

    void setGateId(const string& id){m_gateId = id;}
    const string& gateId(){return m_gateId;}
    void setGateName(const string& name){m_gateName = name;}
    const string& gateName(){return m_gateName;}
    const string& gateFileName(){return m_gateFileName;}
    void setGateFileName(const string& file){m_gateFileName = file;}
    const string& pathFileName(){return m_pathFileName;}
    void setPathFileName(const string& file){m_pathFileName = file;}
    const string& mapShotPath(){return m_mapShotPath;}
    void setMapShotPath(const string& file){m_mapShotPath = file;}

    void setAllScene(vector<MapSceneInfo>& scene) {m_allScene = scene;}
    vector<MapSceneInfo>& allScene() {return m_allScene;}
    void setStaticScene(vector<MapSceneInfo>& scene) {m_staticScene = scene;}
    vector<MapSceneInfo>& staticScene() {return m_staticScene;}
    void setDynamicScene(vector<MapSceneInfo>& scene) {m_dynamicScene = scene;}
    vector<MapSceneInfo>& dynamicScene() {return m_dynamicScene;}
private:
    int m_maxPlayers;
    int m_maxTeams;
    int m_mapSizeW;
    int m_mapSizeH;
    string m_gateId;
    string m_gateName;
    string m_gateFileName;
    string m_pathFileName;
    string m_mapShotPath;
    vector<MapSceneInfo> m_allScene;
    vector<MapSceneInfo> m_staticScene;
    vector<MapSceneInfo> m_dynamicScene;
};

#endif // MAPMETAINFO_H
