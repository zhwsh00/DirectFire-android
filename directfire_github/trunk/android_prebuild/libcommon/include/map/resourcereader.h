#ifndef RESOURCEREADER_H
#define RESOURCEREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <map>

#include "consts.h"

using namespace std;
class ResourceReader
{
public:
    ~ResourceReader();
    static ResourceReader* sharedRes();

    bool initResourcePath(const string& path);
    map<string, long *>& getResIndex();
    bool readRootXML(ResInfo &resInfo);
    bool readResDat(ResInfo &resInfo, const string& resKeyPath);
    bool isResExist(const string& resKeyPath);

private:
    void readResIndex();
    
private:
    ResourceReader();
    string m_path;
    map<string, long *> m_resIndex;
    FILE *m_fpr;
};

#endif // RESOURCEREADER_H
