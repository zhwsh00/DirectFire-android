#ifndef _basmap_
#define _basmap_
#include "consts.h"
#include <vector>
#include <string.h>
using namespace std;

#include "mapmetainfo.h"
#include "mapimageinfo.h"

class BasMap
{
public:
    typedef enum {
        MAP_BG_LAYER = 0,
        MAP_PATH_SHADOW_LAYER = 90,
        MAP_PATH_LAYER = 100,
        MAP_COVER_LAYER = 110,
        MAP_FG_LAYER = 200
    } MAP_LAYER_ORDER;

    typedef struct BezierVertex
    {
		float x;        // position x
        float y;		// position y
        float distance;	// 到Bezier起始点的曲线长度
		float degree;   // 切线角度
    } mapPathVertex;

    typedef struct ShooterPoint
    {
        ShooterPoint(){x=y=0;prior=0;}
        ShooterPoint(float _x,float _y, int _prior){x = _x;y = _y;prior=_prior;}
        float x;
        float y;
        int prior; // 0: none 1: player1 ... ... 4: player4
    } ShooterPoint;

    typedef struct PathRectanglePoint
    {
        PathRectanglePoint(){minx=miny=maxx=maxy=0;prior=0;}
        PathRectanglePoint(float _minx,float _miny, float _maxx,float _maxy, int _prior){
            minx = _minx; miny = _miny; maxx = _maxx; maxy = _maxy; prior=_prior;}
        float minx; float miny; // min
        float maxx; float maxy; // max
        int prior;
    } PathRectanglePoint;

    typedef struct MapHeadInfo
    {
        char head[25];
        char id[20];
        char version[15];
        void clear(){
            memset(&head[0], 0, sizeof(head));
            memset(&id[0], 0, sizeof(id));
            memset(&version[0], 0, sizeof(version));
        }
    } MapHeadInfo;

	BasMap();
	virtual ~BasMap();
    virtual void dumpInfo();
    virtual void setResDir(const string&);
    virtual const string& resDir();
	virtual bool loadMap(const char *fullpath) = 0;
    virtual bool loadGateFromMemory(const char *buf, int size, const string& relativePath) = 0;
    virtual bool loadPathFromMemory(const char *buf, int size) = 0;
    virtual const string& getPathFileRelativePath();
	virtual bool getMapPath(std::vector<mapPathVertex *> paths, std::vector<int> &counts) = 0;
	virtual float getSamplingLen() = 0;
    virtual const string& getBackground();
    virtual vector<MapImageInfo> getBackgrounds();
    virtual const string& getFrontground();
    virtual vector<MapImageInfo> getFrontgrounds();
    virtual const string& getGateId();
    virtual const string& getGateName();
    virtual const string& getMapShotPath();
    virtual int getMaxPlayers();
    virtual int getMaxTeams();
    virtual int getMapSizeW();
    virtual int getMapSizeH();
    virtual vector<MapSceneInfo>& getStaticScene();
    virtual vector<MapSceneInfo>& getDynamicScene();
    virtual vector<MapSceneInfo>& getAllScene();
    virtual std::vector<MapImageInfo>& getImages();
    virtual std::vector<MapImageInfo>& getImages(int);
    virtual std::vector<MapImageInfo>& getLayerImages(int, MAP_LAYER_ORDER);
	virtual const std::vector<KPoint>& getStartPoints();
	virtual const std::vector<KPoint>& getEndPoints();
    virtual const std::vector<ShooterPoint>& getShootPoints();
    virtual bool getShootPoint(ShooterPoint&, int);
    virtual std::vector<PathRectanglePoint*> getPathRectangles();
    virtual bool getPathRectangle(PathRectanglePoint&, int);
    virtual bool getMapHead(BasMap::MapHeadInfo&);
	virtual bool getMapPathVertex(int index,mapPathVertex **path,int &count);
	/* maybe we should not pos the draw function here,just for test */
	virtual void drawMap() = 0;
	virtual void drawMapPath() = 0;
	virtual void drawStartPoint() = 0;
	virtual void drawEndPoint() = 0;
	virtual void drawShootPoint() = 0;
protected:
    string m_resDir;
    string m_pathFileRelativePath;
    string m_bgFileName;
    string m_fgFileName;
    std::vector<MapImageInfo> m_bgFileNames;
    std::vector<MapImageInfo> m_fgFileNames;
	std::vector<KPoint> m_startPoints;
	std::vector<KPoint> m_endPoints;
    std::vector<ShooterPoint> m_shootPoints;
    std::vector<PathRectanglePoint*> m_pathRectangles;
	std::vector<mapPathVertex*> m_pathsVertexs;
    std::vector<int> m_pathsVertexsPrior;
	std::vector<int> m_pathsVertexsCounts;
    std::vector<MapImageInfo> m_images;
    std::vector<MapImageInfo> m_priorImages;
    MapHeadInfo *m_fileHead;
    MapMetaInfo m_mapMetaInfo;

    char *mapBasename(const char*);
};
#endif
