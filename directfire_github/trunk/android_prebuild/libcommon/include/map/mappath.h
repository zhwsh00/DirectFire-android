/*
 * mappath.h
 *
 *  Created on: 2013-1-23
 *      Author: xujun
 */

#ifndef MAPPATH_H_
#define MAPPATH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "absmap.h"
using namespace std;

class MapPath : public BasMap{
public:
    MapPath();
    virtual ~MapPath();
    virtual bool loadMap(const char *map);
    virtual bool loadGateFromMemory(const char *buf, int size, const string& relativePath);
    virtual bool loadPathFromMemory(const char *buf, int size);
    virtual bool getMapPath(std::vector<mapPathVertex *> paths, std::vector<int> &counts);
    virtual float getSamplingLen();
    // not implemented
    virtual void drawMap(){};
    virtual void drawMapPath(){};
    virtual void drawStartPoint(){};
    virtual void drawEndPoint(){};
    virtual void drawShootPoint(){};

private:
    bool readPathFile(const string& fullPath);
    bool readPathFile(const char* fullPath);
    bool readPathFileFromMemory(void* fblock, int size);
    bool readGateFile(const string& fullPath);
    bool readGateFile(const char* fullPath);
    bool readGateFileFromMemory(const char *buf, int size, const string& gatePath);

    void readHead(void *fblock);
    void readShooters(void *fblock);
    void readPaths(void *fblock);
    bool mapMemcpy(void *dest, void *src, int n);  // 基于fblock偏移量进行内存复制
    unsigned long m_fblockOffset;                  // fblock指针偏移位置
    long m_fileSize;                               // 地图文件大小
};

#endif /* MAPPATH_H_ */
