#ifndef _propshow_h_
#define _propshow_h_
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "uilib/uilib.h"
using namespace uilib;

#include "prop/propdef.h"

class PropShow : public BasWidget
{
public:
    PropShow();
    virtual ~PropShow();
    void setProp(int id,int num);
    void layoutCompleted();
    void finish();
protected:
    int m_propId;
    int m_propNum;
    std::string m_barTheme;
    std::string m_barBg;
protected:
    CCLabelBMFont *m_numSprite;
    bool m_inited;
};

#endif
