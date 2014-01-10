#ifndef _absxmlsetting_h_
#define _absxmlsetting_h_
#include <map>
#include <string>
using namespace std;

#include <libxml/parser.h>
#include <libxml/tree.h>

class BasXmlSetting
{
public:
	BasXmlSetting();
	virtual ~BasXmlSetting();
    void loadFromXmlMemory(const char *buffer, int size);
	void loadFromXmlFile(const std::string &file);
	void saveToXmlFile(const std::string &file);
	bool getValue(const std::string &key,std::string &value);
	bool getValue(const std::string &key,int &value,int defaultvalue = 0);
	bool getValue(const std::string &key,bool &value,bool defaultvalue = true);
	bool getValue(const std::string &key,float &value,float defaultvalue = 0.0);
	void addValue(const std::string &key,const std::string &value);
	void addValue(const std::string &key,int value);
	void addValue(const std::string &key,bool value);
	void addValue(const std::string &key,float value);
	void removeValue(const std::string &key);
private:
    void loadDoc(xmlDocPtr doc);
    
protected:
	std::map<std::string,std::string> m_map;
};
#endif
