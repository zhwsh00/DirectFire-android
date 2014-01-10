#ifndef _herositem_h_
#define _herositem_h_
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "uilib/uilib.h"
#include "cliententry/uimsgevent.h"

using namespace uilib;

class HerosItem : public BorderWidget
{
public:
    HerosItem();
    virtual ~HerosItem();
    void setId(const std::string &id) { m_id = id;}
    const std::string &id() { return m_id;}
protected:
    std::string m_id;
};

#endif
