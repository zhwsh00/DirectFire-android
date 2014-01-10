#ifndef _consts_h_
#define _consts_h_
#include <string>
#include <cstdlib>
using namespace std;

#define _DEBUG_MAP_DAT_FILE_ 0

typedef struct KPoint
{
    KPoint(){x=y=0;}
	KPoint(float _x,float _y){x = _x;y = _y;}
	float x;
    float y;
}KPoint;


typedef struct ResInfo
{
    ResInfo() {
        fblock = 0;
    }
    unsigned char* fblock;
    long fileSize;
    void resfree() {
        if(fblock) {
            std::free(fblock);
            fblock = 0;
        }
    }
    ~ResInfo() {
        resfree();
    }
} ResInfo;

const std::string ROOT_XML_PATH = "Resource.xml";
#endif
