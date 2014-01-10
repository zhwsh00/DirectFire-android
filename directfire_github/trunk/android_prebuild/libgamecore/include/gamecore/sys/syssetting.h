#ifndef _syssetting_h_
#define _syssetting_h_
#include <string>
using namespace std;
#include "absxmlsetting.h"

class SysSetting : public BasXmlSetting
{
public:
	static SysSetting *getInstance();
    void getSupportLanguage(std::string &lang);
	void getLoginSever(std::string &ip);
    int getLoginPort();
    void getResourceDir(std::string &dir);
    void getLabel(std::string &label);
    void getVersion(std::string &version);
    void getDevice(std::string &device);
private:
	SysSetting();
	~SysSetting();
	static SysSetting *m_instance;
};
#endif
