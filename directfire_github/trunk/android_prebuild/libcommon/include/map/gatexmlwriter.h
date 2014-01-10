#ifndef GATEXMLWRITER_H
#define GATEXMLWRITER_H
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <string>
#include <vector>

#include "absmap.h"
using namespace std;

class GateXMLWriter
{
public:
    GateXMLWriter(const string &file);
    ~GateXMLWriter();
    bool writeGateXml();

    void setMapMetaInfo(MapMetaInfo& mapMetaInfo){m_mapMetaInfo = mapMetaInfo;}
    void setImages(vector<MapImageInfo>& images) {m_images = images;}
private:
    string m_gateFileName;
    MapMetaInfo m_mapMetaInfo;
    vector<MapImageInfo> m_images;
};

#endif // GATEXMLWRITER_H
