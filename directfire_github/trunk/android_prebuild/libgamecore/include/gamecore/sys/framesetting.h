#ifndef _framesetting_h_
#define _framesetting_h_
#include <string>
#include <vector>
using namespace std;
#include "absxmlsetting.h"

class FrameSetting : public BasXmlSetting
{
public:
	FrameSetting();
	~FrameSetting();
    bool loadFrame(int &start,int &end,std::string &prefix,std::string &postfix,float &frametime,int &loop,float &scale);
	bool firstFrame(std::string &name);
	void getIntsBeginWith(const std::string &key,std::vector<int> &ints);
	void getKeysBeginWith(const std::string &key,std::vector<std::string> &values);
	void getValuesBeginWith(const std::string &key,std::vector<std::string> &values);
private:
};
#endif
