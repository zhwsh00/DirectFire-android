#ifndef SOUNDLOADER_H
#define SOUNDLOADER_H
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string>
#include <map>

using namespace std;

class SoundLoader
{
public:
    SoundLoader();
    ~SoundLoader();
    void dumpInfo();
    void setXmlPath(const string &file);
    void getSoundPath(int soundType, string& soundPath);
    
private:
    void parseXml();
    
private:
    std::map<int, string> m_sounds;
    string m_soundXmlFile;
};

#endif // SOUNDLOADER_H
