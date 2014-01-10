#ifndef _font_h_
#define _font_h_
#include <string>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

namespace uilib{
    
    static const char* getSystemFont(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        return "Arial-BoldMT";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        return "times";
#else
        return "times";
#endif
    }
}

#endif
