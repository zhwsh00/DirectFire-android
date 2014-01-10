#ifndef _userdata_h_
#define _userdata_h_
#include "cocos2d.h"
using namespace cocos2d;

class UserDataMgr
{
    UserDataMgr();
    ~UserDataMgr();
    static CCUserDefault *m_instance;
public:
    static CCUserDefault *getInstance();
protected:
};

#endif
