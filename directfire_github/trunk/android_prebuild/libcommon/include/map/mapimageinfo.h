#ifndef MAPIMAGEINFO_H
#define MAPIMAGEINFO_H
#include <string>

using namespace std;

#include "consts.h"

class MapImageInfo
{
public:
    MapImageInfo();
    ~MapImageInfo();
    void dumpInfo();

    void setZOrder(int zOrder){m_zOrder = zOrder;}
    int zOrder(){return m_zOrder;}
    void setPrior(int prior){m_prior = prior;}
    int prior(){return m_prior;}

    // 0: no change 1: turnx
    void setTurnX(int turn){m_turnX = turn;}
    int turnX(){return m_turnX;}
    // 0: no change 1: turny
    void setTurnY(int turn){m_turnY = turn;}
    int turnY(){return m_turnY;}

    void setPosition(KPoint& position){m_position = position;}
    KPoint& position(){return m_position;}

    void setImageId(const string& imageId){m_imageId = imageId;}
    const string& imageId(){return m_imageId;}
    void setImageFileName(const string& imageFileName){m_imageFileName = imageFileName;}
    const string& imageFileName(){return m_imageFileName;}
private:
    int m_zOrder;
    int m_prior;
    int m_turnX;
    int m_turnY;
    KPoint m_position;

    string m_imageId;
    string m_imageFileName;
};

#endif // MAPIMAGEINFO_H
