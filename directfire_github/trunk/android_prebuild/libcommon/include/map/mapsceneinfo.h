#ifndef MAPSENCEINFO_H
#define MAPSENCEINFO_H
#include <string>
#include <iostream>
using namespace std;

class MapSceneInfo
{
public:
    MapSceneInfo();
    ~MapSceneInfo();
    void dumpInfo();

    void setSceneType(int type){m_sceneType = type;}
    int sceneType(){return m_sceneType;}
    void setSceneX(float x){m_sceneX = x;}
    float sceneX(){return m_sceneX;}
    void setSceneY(float y){m_sceneY = y;}
    float sceneY(){return m_sceneY;}

    void setSceneId(const string& id){m_sceneId = id;}
    const string& sceneId(){return m_sceneId;}
    void setSceneName(const string& name){m_sceneName = name;}
    const string& sceneName(){return m_sceneName;}
private:
    int m_sceneType;
    float m_sceneX;
    float m_sceneY;
    string m_sceneId;
    string m_sceneName;
};

#endif // MAPSENCEINFO_H
